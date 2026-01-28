// Helper C file for second assembly SDL application
#include <SDL2/SDL.h>
#include <stdio.h>

// Extern functions that will be implemented in assembly
extern int asm_main_func();

// Global variables accessible from assembly
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
int g_screen_width = 800;
int g_screen_height = 600;

// C main function that calls assembly
int main(int argc, char* argv[]) {
    printf("Second Assembly SDL Application starting...\n");
    
    // Call the assembly main function
    int result = asm_main_func();
    
    printf("Second Assembly SDL Application exited.\n");
    return result;
}

// C helper functions called from assembly
int init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }

    g_window = SDL_CreateWindow("Second Assembly Implementation - SDL2 Grid",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                g_screen_width, g_screen_height,
                                SDL_WINDOW_SHOWN);
    if (!g_window) {
        SDL_Quit();
        return -1;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (!g_renderer) {
        SDL_DestroyWindow(g_window);
        SDL_Quit();
        return -1;
    }

    return 0;
}

void render_frame() {
    // Clear screen with dark gray color
    SDL_SetRenderDrawColor(g_renderer, 50, 50, 50, 255);  // Dark gray background
    SDL_RenderClear(g_renderer);

    // Draw a colorful grid pattern
    int cellSize = 40;
    int cols = g_screen_width / cellSize;
    int rows = g_screen_height / cellSize;
    
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            // Calculate color based on position
            Uint8 r = (x * 20) % 255;
            Uint8 g = (y * 30) % 255;
            Uint8 b = ((x + y) * 10) % 255;
            
            SDL_SetRenderDrawColor(g_renderer, r, g, b, 255);
            
            SDL_Rect rect = {x * cellSize, y * cellSize, cellSize, cellSize};
            SDL_RenderFillRect(g_renderer, &rect);
            
            // Draw border around each cell
            SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);  // White border
            SDL_RenderDrawRect(g_renderer, &rect);
        }
    }
    
    SDL_RenderPresent(g_renderer);
}

void cleanup_sdl() {
    if (g_renderer) {
        SDL_DestroyRenderer(g_renderer);
    }
    if (g_window) {
        SDL_DestroyWindow(g_window);
    }
    SDL_Quit();
}

int poll_events() {
    SDL_Event e;
    int quit = 0;
    
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = 1;
        }
    }
    
    return quit;
}