#include <SDL2/SDL.h>
#include <stdio.h>

// Function declarations that will be implemented in assembly
extern int asm_main();

int main(int argc, char* argv[]) {
    return asm_main();
}