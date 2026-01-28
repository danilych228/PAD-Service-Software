// Helper C file for assembly SDL application
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
    printf("Assembly SDL Application starting...\n");
    
    // Call the assembly main function
    int result = asm_main_func();
    
    printf("Assembly SDL Application exited.\n");
    return result;
}

// C helper functions called from assembly
int init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }

    g_window = SDL_CreateWindow("Assembly SDL Application",
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
    // Clear screen with purple color
    SDL_SetRenderDrawColor(g_renderer, 128, 0, 128, 255);
    SDL_RenderClear(g_renderer);

    // Draw a white triangle
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
    
    // Simple triangle drawing using points
    int centerX = g_screen_width / 2;
    int centerY = g_screen_height / 2;
    int size = 80;
    
    // Draw triangle points
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i + j < size) {
                SDL_RenderDrawPoint(g_renderer, centerX - size/2 + i, centerY - size/2 + j);
            }
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