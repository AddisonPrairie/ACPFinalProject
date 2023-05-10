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

//the function that each thread will run
void threadFunc(
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

        //draw the color of every one of those pixels
        for (int x = nextTile->xLow; x < nextTile->xHigh; x++) {
            for (int y = nextTile->yLow; y < nextTile->yHigh; y++) {
                Ray ray = camera->getRayForPixel(x, y);
                RayHit hit = scene->intersect(ray);
                if (hit.bHit) {
                    pixels[4 * (screenWidth * y + x) + 0] = fabs(hit.hitNormal.z) * 255;
                    pixels[4 * (screenWidth * y + x) + 1] = fabs(hit.hitNormal.y) * 255;
                    pixels[4 * (screenWidth * y + x) + 2] = fabs(hit.hitNormal.x) * 255;
                    pixels[4 * (screenWidth * y + x) + 3] = 255;
                } else {
                    pixels[4 * (screenWidth * y + x) + 0] = 0;
                    pixels[4 * (screenWidth * y + x) + 1] = 0;
                    pixels[4 * (screenWidth * y + x) + 2] = 0;
                    pixels[4 * (screenWidth * y + x) + 3] = 255;
                }
            }
        }
    }
}