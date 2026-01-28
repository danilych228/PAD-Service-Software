#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class SDLApplication {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

public:
    SDLApplication() : window(nullptr), renderer(nullptr), isRunning(false) {}

    bool init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }

        window = SDL_CreateWindow("C++ SDL Application",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (!window) {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            return false;
        }

        isRunning = true;
        return true;
    }

    void run() {
        SDL_Event e;
        
        while (isRunning) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    isRunning = false;
                }
            }

            // Clear screen with green color
            SDL_SetRenderDrawColor(renderer, 0, 150, 100, 255);
            SDL_RenderClear(renderer);

            // Draw a yellow circle-like shape
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            int centerX = SCREEN_WIDTH / 2;
            int centerY = SCREEN_HEIGHT / 2;
            int radius = 100;
            
            for (int w = -radius; w < radius; w++) {
                for (int h = -radius; h < radius; h++) {
                    if ((w * w + h * h) < (radius * radius)) {
                        SDL_RenderDrawPoint(renderer, centerX + w, centerY + h);
                    }
                }
            }

            // Update screen
            SDL_RenderPresent(renderer);
        }
    }

    void cleanup() {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
        SDL_Quit();
    }
};

int main(int argc, char* argv[]) {
    SDLApplication app;
    
    if (!app.init()) {
        std::cout << "Failed to initialize SDL application!" << std::endl;
        return -1;
    }

    std::cout << "C++ SDL Application running..." << std::endl;
    app.run();
    app.cleanup();

    std::cout << "C++ SDL Application exited." << std::endl;
    return 0;
}