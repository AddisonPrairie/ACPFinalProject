//this is just a test file
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <stdio.h>
#include <SDL.h>

#include "headers/camera.h"
#include "headers/sphere.h"
#include "headers/scene.h"
#include "headers/tileQueue.h"
#include "headers/renderThread.h"
#include "headers/lambertian.h"
#include "headers/mesh.h"
#include "headers/emissive.h"

#include "glm/glm.hpp"
#include "glm/vec3.hpp"

//starts SDL and creates a window
bool startSDL();

//frees memory and shuts down SDL
void closeSDL();

//the main SDL window
SDL_Window* mainWindow = nullptr;

//the main surfaec that the window contains
SDL_Surface* mainScreenSurface = nullptr;

//the size of our window
const int INIT_WIDTH = 512; const int INIT_HEIGHT = 512;

float* genPlane(glm::vec3 root, char normal, float length) {
    float len2 = length / 2.;
    float* tris = (float*) malloc(sizeof(float) * 18);
    if (normal == 'z') {
        tris[0] = root.x - len2;
        tris[1] = root.y - len2;
        tris[2] = root.z;
        tris[3] = root.x - len2;
        tris[4] = root.y + len2;
        tris[5] = root.z;
        tris[6] = root.x + len2;
        tris[7] = root.y + len2;
        tris[8] = root.z;
        tris[9] = root.x - len2;
        tris[10]= root.y - len2;
        tris[11]= root.z;
        tris[12]= root.x + len2;
        tris[13]= root.y + len2;
        tris[14]= root.z;
        tris[15]= root.x + len2;
        tris[16]= root.y - len2;
        tris[17]= root.z;
        return tris;
    }
    if (normal == 'x') {
        tris[0] = root.x;
        tris[1] = root.y - len2;
        tris[2] = root.z - len2;
        tris[3] = root.x;
        tris[4] = root.y + len2;
        tris[5] = root.z - len2;
        tris[6] = root.x;
        tris[7] = root.y + len2;
        tris[8] = root.z + len2;
        tris[9] = root.x;
        tris[10]= root.y - len2;
        tris[11]= root.z - len2;
        tris[12]= root.x;
        tris[13]= root.y + len2;
        tris[14]= root.z + len2;
        tris[15]= root.x;
        tris[16]= root.y - len2;
        tris[17]= root.z + len2;
        return tris;
    }
    if (normal == 'y') {
        tris[0] = root.x - len2;
        tris[1] = root.y;
        tris[2] = root.z - len2;
        tris[3] =  root.x + len2;
        tris[4] = root.y;
        tris[5] = root.z - len2;
        tris[6] = root.x + len2;
        tris[7] = root.y;
        tris[8] = root.z + len2;
        tris[9] = root.x - len2;
        tris[10]= root.y;
        tris[11]= root.z - len2;
        tris[12]= root.x + len2;
        tris[13]= root.y;
        tris[14]= root.z + len2;
        tris[15]= root.x - len2;
        tris[16]= root.y;
        tris[17]= root.z + len2;
        return tris;
    }
    return nullptr;
}

int main(int argc, char* argv[]) {
    bool bSuccess = startSDL();
    if (!bSuccess) return 0;

    glm::vec3 forward; glm::vec3 right;
    float zRotation = 0.; float fRotation = 0.;

    Camera::generateForwardAndRightFromAngles(zRotation, fRotation, forward, right);
    Camera mainCamera = Camera(INIT_WIDTH, INIT_HEIGHT, 1., glm::vec3(0., 0., 2.5f) + forward * (-10.f), forward, right);
    mainCamera.printInfo();

    //get the pixel array for the main surface to edit later
    unsigned char* pixels = (unsigned char*) mainScreenSurface->pixels;

    //temporary - generate a random scene of 40 spheres
    Scene scene = Scene();
    scene.addObjectToScene(
        new Sphere(
            glm::vec3(0., 0., 1.), 1.,
            new Lambertian(
                glm::vec3(.7, .7, .7)
            )
        )
    );

    scene.addObjectToScene(
        new Sphere(
            glm::vec3(-2., 2., .125), .125,
            new Emissive(
                glm::vec3(.6, .4, .6) * 10.f
            )
        )
    );

    scene.addObjectToScene(
        new Sphere(
            glm::vec3(2., -2., .25), .25,
            new Emissive(
                glm::vec3(.2, .4, .8) * 5.f
            )
        )
    );

    scene.addObjectToScene(new Mesh(
        glm::vec3(0.f), genPlane(glm::vec3(0.f), 'z', 5.), 2, 
        new Lambertian(glm::vec3(.9, .9, .9))
    ));
    scene.addObjectToScene(new Mesh(
        glm::vec3(0.f), genPlane(glm::vec3(0.f, 0.f, 5.), 'z', 5.), 2, 
        new Lambertian(glm::vec3(.9, .9, .9))
    ));
    scene.addObjectToScene(new Mesh(
        glm::vec3(0.f), genPlane(glm::vec3(0.f, 2.5f, 2.5f), 'y', 5.), 2, 
        new Lambertian(glm::vec3(.9, .4, .4))
    ));
    scene.addObjectToScene(new Mesh(
        glm::vec3(0.f), genPlane(glm::vec3(0.f, -2.5f, 2.5f), 'y', 5.), 2, 
        new Lambertian(glm::vec3(.4, .4, .9))
    ));
    scene.addObjectToScene(new Mesh(
        glm::vec3(0.f), genPlane(glm::vec3(2.5f, 0.f, 2.5f), 'x', 5.), 2, 
        new Lambertian(glm::vec3(.9, .9, .9))
    ));

    scene.addObjectToScene(new Mesh(
        glm::vec3(0.f), genPlane(glm::vec3(0.f, 0.f, 4.99), 'z', 1.), 2, 
        new Emissive(glm::vec3(10.))
    ));


    auto start = std::chrono::high_resolution_clock::now();

    //create the rendering tile queue
    TileQueue* tileQueue = new TileQueue(50, 50, INIT_WIDTH, INIT_HEIGHT);

    int numThreads = 16;
    std::thread** threadArr = (std::thread**) malloc(sizeof(std::thread*) * numThreads);

    for (int i = 0; i < numThreads; i++) {
        threadArr[i] = new std::thread(threadFunc, i, pixels, INIT_WIDTH, INIT_HEIGHT, &mainCamera, &scene, tileQueue);
    }

    for (int i = 0; i < numThreads; i++) {
        threadArr[i]->join(); 
        delete threadArr[i];
    }
    free(threadArr);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "time elapsed: " << (double)duration.count() / (1e6) << std::endl;

    SDL_UpdateWindowSurface(mainWindow);

    //main loop - keeps window open
    bool bQuit = false; SDL_Event currentEvent;
    while (!bQuit) {
        SDL_UpdateWindowSurface(mainWindow);
        while (SDL_PollEvent(&currentEvent) != 0) {
            if (currentEvent.type == SDL_QUIT) {
                bQuit = true;
            }
        }
    }
    closeSDL();

    return 0;
}

void setPixel(unsigned char r, unsigned char g, unsigned char b, int x, int y, unsigned char* pixelArray) {
    pixelArray[4 * (INIT_WIDTH * y + x) + 0] = b;
    pixelArray[4 * (INIT_WIDTH * y + x) + 1] = g;
    pixelArray[4 * (INIT_WIDTH * y + x) + 2] = r;
    pixelArray[4 * (INIT_WIDTH * y + x) + 3] = 255;
}


bool startSDL() {
    //flag whether start is successful or not
    bool bSuccess = true;

    //starting screensize and settings
    const int WINDOW_CREATION_FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize. Error: %s\n", SDL_GetError());
        bSuccess = false;
    } else {
        mainWindow = SDL_CreateWindow("ACPFinalProject", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, INIT_WIDTH, INIT_HEIGHT, WINDOW_CREATION_FLAGS);
        if (mainWindow == nullptr) {
            printf("Window could not be created. Error: %s\n", SDL_GetError());
            bSuccess = false;
        } else {
            mainScreenSurface = SDL_GetWindowSurface(mainWindow);
        }
    }

    return bSuccess;
}

void closeSDL() {
    //destroy window
    SDL_DestroyWindow(mainWindow);
    mainWindow = nullptr;

    //quit SDL subsystems
    SDL_Quit();
}