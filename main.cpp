//this is just a test file
#include <iostream>
#include <stdio.h>
#include <SDL.h>

//starts SDL and creates a window
bool startSDL();

//frees memory and shuts down SDL
void closeSDL();

//the main SDL window
SDL_Window* mainWindow = nullptr;

//the main surfaec that the window contains
SDL_Surface* mainScreenSurface = nullptr;


int main(int argc, char* argv[]) {

    bool bSuccess = startSDL();
    if (!bSuccess) return 0;

    //main loop - keeps window open
    bool bQuit = false; SDL_Event currentEvent;
    while (!bQuit) {
        while (SDL_PollEvent(&currentEvent) != 0) {
            if (currentEvent.type == SDL_QUIT) {
                bQuit = true;
            }
        }
    }
}

bool startSDL() {
    //flag whether start is successful or not
    bool bSuccess = true;

    //starting screensize and settings
    const int INIT_WIDTH = 700; const int INIT_HEIGHT = 700;
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