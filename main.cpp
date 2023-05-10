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

#include "glm/glm.hpp"
#include "glm/vec3.hpp"

//starts SDL and creates a window
bool startSDL();

//frees memory and shuts down SDL
void closeSDL();

//sets the value of a pixel
void setPixel(unsigned char r, unsigned char g, unsigned char b, int x, int y, unsigned char* pixelArray);

//the main SDL window
SDL_Window* mainWindow = nullptr;

//the main surfaec that the window contains
SDL_Surface* mainScreenSurface = nullptr;

//the size of our window
const int INIT_WIDTH = 512; const int INIT_HEIGHT = 512;

int main(int argc, char* argv[]) {
    bool bSuccess = startSDL();
    if (!bSuccess) return 0;

    glm::vec3 forward; glm::vec3 right;
    float zRotation = 0.; float fRotation = 0.;

    Camera::generateForwardAndRightFromAngles(zRotation, fRotation, forward, right);
    Camera mainCamera = Camera(INIT_WIDTH, INIT_HEIGHT, 1., forward * (-5.f), forward, right);
    mainCamera.printInfo();

    //get the pixel array for the main surface to edit later
    unsigned char* pixels = (unsigned char*) mainScreenSurface->pixels;

    //temporary - generate a random scene of 40 spheres
    Scene scene = Scene();
    for (int i = 0; i < 1; i++) {
        float r = 1.;
        Sphere* sphere = new Sphere(glm::vec3(0., 0., i), r);
        scene.addObjectToScene(sphere);
    }

    auto start = std::chrono::high_resolution_clock::now();

    //create the rendering tile queue
    TileQueue* tileQueue = new TileQueue(150, 150, INIT_WIDTH, INIT_HEIGHT);

    int numThreads = 16;
    std::thread** threadArr = (std::thread**) malloc(sizeof(std::thread*) * numThreads);

    for (int i = 0; i < numThreads; i++) {
        threadArr[i] = new std::thread(threadFunc, pixels, INIT_WIDTH, INIT_HEIGHT, &mainCamera, &scene, tileQueue);
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