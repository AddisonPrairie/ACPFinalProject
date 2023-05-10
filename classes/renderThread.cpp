#include "../headers/camera.h"
#include "../headers/scene.h"
#include "../headers/renderThread.h"
#include "../headers/shared.h"
#include "../headers/tile.h"
#include "../headers/tileQueue.h"

#include "../glm/glm.hpp"
#include "../glm/vec3.hpp"

#include <iostream>

//generates a random sample about a hemisphere
//https://pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations 
glm::vec3 uniformSampleHemisphere() {
    float r1 = frand1(); float r2 = frand1();
    float r = std::sqrt(std::max(0.f, 1.f - r1 * r1));
    float phi = 2 * PI * r2;
    return glm::vec3(r * std::cos(phi), r * std::sin(phi), r1);
}

glm::vec3 sample(Camera* camera, Scene* scene, int x, int y) {
    Ray currentRay = camera->getRayForPixel(x + frand1(), y + frand1());
    glm::vec3 throughput = glm::vec3(1., 1., 1.);
    bool bFoundLight = false;
    for (int bounces = 0;; bounces++) {
        RayHit hit = scene->intersect(currentRay);
        //if we hit the sky
        if (!hit.bHit) {
            bFoundLight = true;
            break;
        }

        //lambertian bsdf / pdf
        glm::vec3 bsdf = glm::vec3(.5, 0.5, 0.5) / PI; float pdf = 1. / (2. * PI);

        //get a world-space random hemisphere sample around the hit normal
        glm::vec3 hemiSample = uniformSampleHemisphere();
        glm::vec3 o1;
        if (fabs(hit.hitNormal.x) > fabs(hit.hitNormal.y)) {
            o1 = glm::normalize(
                glm::vec3(-hit.hitNormal.y, hit.hitNormal.x, 0.)
                );
        } else {
            o1 = glm::normalize(
                glm::vec3(0., -hit.hitNormal.z, hit.hitNormal.y)
                );
        }
        glm::vec3 o2 = glm::normalize(glm::cross(o1, hit.hitNormal));
        glm::vec3 worldSpaceSample = glm::normalize(o1 * hemiSample.x + o2 * hemiSample.y + hit.hitNormal * hemiSample.z);
        //get the new ray direction
        currentRay.origin = currentRay.origin + currentRay.direction * hit.distance + .0001f * hit.hitNormal;
        currentRay.direction = worldSpaceSample;

        //update the throughput
        throughput *= bsdf * glm::abs(glm::dot(hit.hitNormal, currentRay.direction)) / pdf;

        //terminate path by russian roulette
        if (bounces > 2) {
            float q = std::max(.05f, 1.f - throughput.y);
            if (frand1() < q) break;
            throughput /= 1.f - q;
        }
    }

    if (!bFoundLight) throughput *= 0.f;

    return throughput;
}

//the function that each thread will run
void threadFunc(
    int threadID,
    unsigned char* pixels,
    int screenWidth, int screenHeight,
    Camera* camera,
    Scene* scene,
    TileQueue* tileQueue
) {
    while (1) {
        tileQueue->queueLock.lock();
        Tile* nextTile = tileQueue->pop();
        tileQueue->queueLock.unlock();
        if (nextTile == nullptr) {
            break;
        }

        printf("thread %i doing tile x: %i -> %i, y: %i -> %i\n", 
            threadID, nextTile->xLow, nextTile->xHigh, nextTile->yLow, nextTile->yHigh
        );

        //draw the color of every one of those pixels
        for (int x = nextTile->xLow; x < nextTile->xHigh; x++) {
            for (int y = nextTile->yLow; y < nextTile->yHigh; y++) {
                int numSamples = 100;
                glm::vec3 sumSamples = glm::vec3(0.);
                for (int i = 0; i < numSamples; i++) {
                    sumSamples += sample(camera, scene, x, y);
                }
                sumSamples /= (float) numSamples;
                sumSamples.x = fclamp(sumSamples.x, 0., 1.);
                sumSamples.y = fclamp(sumSamples.y, 0., 1.);
                sumSamples.z = fclamp(sumSamples.z, 0., 1.);

                pixels[4 * (screenWidth * y + x) + 0] = sumSamples.z * 255;
                pixels[4 * (screenWidth * y + x) + 1] = sumSamples.y * 255;
                pixels[4 * (screenWidth * y + x) + 2] = sumSamples.x * 255;
                pixels[4 * (screenWidth * y + x) + 3] = 255;
            }
        }
    }
}