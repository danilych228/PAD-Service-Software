#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Second C Implementation - SDL2 Cross",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop
    int quit = 0;
    SDL_Event e;
    
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear screen with cyan color
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);  // Cyan background
        SDL_RenderClear(renderer);

        // Draw a magenta cross
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);  // Magenta
        
        // Horizontal line of the cross
        SDL_Rect hLine = {SCREEN_WIDTH/4 - 50, SCREEN_HEIGHT/2 - 20, SCREEN_WIDTH/2 + 100, 40};
        SDL_RenderFillRect(renderer, &hLine);
        
        // Vertical line of the cross
        SDL_Rect vLine = {SCREEN_WIDTH/2 - 20, SCREEN_HEIGHT/4 - 50, 40, SCREEN_HEIGHT/2 + 100};
        SDL_RenderFillRect(renderer, &vLine);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}