section .data
    title db 'Third Implementation - Assembly', 0
    format_string db "%s", 10, 0

section .bss
    event_buffer resb 56  ; SDL_Event is typically 56 bytes

section .text
    extern SDL_Init
    extern SDL_CreateWindow
    extern SDL_CreateRenderer
    extern SDL_SetRenderDrawColor
    extern SDL_RenderClear
    extern SDL_RenderFillRect
    extern SDL_RenderPresent
    extern SDL_PollEvent
    extern SDL_DestroyRenderer
    extern SDL_DestroyWindow
    extern SDL_Quit
    extern SDL_GetError
    extern printf

    global asm_main

; Define constants
%define SDL_INIT_VIDEO 0x00000020
%define SDL_WINDOWPOS_UNDEFINED 0x2FFF0000
%define SDL_WINDOW_SHOWN 4
%define SCREEN_WIDTH 800
%define SCREEN_HEIGHT 600

; SDL_Rect structure
struc SDL_Rect
    .x: resd 1
    .y: resd 1
    .w: resd 1
    .h: resd 1
endstruc

; SDL_Event structure (simplified)
struc SDL_Event
    .type: resd 1
    ; ... other fields
endstruc

asm_main:
    push rbp
    mov rbp, rsp

    ; Initialize SDL
    mov edi, SDL_INIT_VIDEO
    call SDL_Init
    test eax, eax
    js error_init

    ; Create window
    mov rdi, title
    mov esi, SDL_WINDOWPOS_UNDEFINED
    mov edx, SDL_WINDOWPOS_UNDEFINED
    mov ecx, SCREEN_WIDTH
    mov r8d, SCREEN_HEIGHT
    mov r9d, SDL_WINDOW_SHOWN
    sub rsp, 8
    call SDL_CreateWindow
    add rsp, 8
    test rax, rax
    jz error_window
    mov rbx, rax    ; Store window pointer

    ; Create renderer
    mov rdi, rbx
    mov esi, -1
    mov edx, 0x00000002  ; SDL_RENDERER_ACCELERATED
    sub rsp, 8
    call SDL_CreateRenderer
    add rsp, 8
    test rax, rax
    jz error_renderer
    mov rcx, rax    ; Store renderer pointer

    ; Main loop
main_loop:
    ; Poll for events
    lea rdi, [event_buffer]
    sub rsp, 8
    call SDL_PollEvent
    add rsp, 8
    test eax, eax
    jz skip_event_check

    ; Check if quit event
    mov eax, dword [event_buffer]
    cmp eax, 0x100  ; SDL_QUIT event type
    je cleanup

skip_event_check:
    ; Clear screen with yellow color (255, 255, 0, 255)
    mov rdi, rcx    ; renderer
    mov esi, 255    ; r
    mov edx, 255    ; g
    mov r8d, 0      ; b
    mov r9d, 255    ; a
    sub rsp, 8
    call SDL_SetRenderDrawColor
    add rsp, 8

    sub rsp, 8
    call SDL_RenderClear
    add rsp, 8

    ; Draw red diamond shape
    mov rdi, rcx    ; renderer
    mov esi, 255    ; r
    mov edx, 0      ; g
    mov r8d, 0      ; b
    mov r9d, 255    ; a
    sub rsp, 8
    call SDL_SetRenderDrawColor
    add rsp, 8

    ; Draw diamond by filling multiple small rectangles
    ; We'll draw a diamond centered in the screen
    mov r10, 0      ; Loop counter x
    mov r11d, 0     ; Loop counter y

draw_diamond:
    mov eax, r10d   ; x coordinate
    mov ebx, r11d   ; y coordinate

    ; Adjust coordinates to center of screen
    add eax, SCREEN_WIDTH / 2
    add ebx, SCREEN_HEIGHT / 2

    ; Calculate absolute values for diamond equation
    mov r12d, r10d
    mov r13d, r11d
    
    ; Make positive if negative
    cmp r12d, 0
    jge x_positive
    neg r12d
x_positive:
    cmp r13d, 0
    jge y_positive
    neg r13d
y_positive:

    ; Check if point is inside diamond: |x| + |y| <= radius
    mov r14d, r12d
    add r14d, r13d
    cmp r14d, 100   ; radius of diamond
    jg next_pixel

    ; Set draw color again before drawing pixel
    mov rdi, rcx    ; renderer
    mov esi, 255    ; r
    mov edx, 0      ; g
    mov r8d, 0      ; b
    mov r9d, 255    ; a
    sub rsp, 8
    call SDL_SetRenderDrawColor
    add rsp, 8

    ; Draw pixel
    lea rdi, [event_buffer]  ; Use buffer temporarily for SDL_Rect
    mov dword [rdi], eax    ; x
    mov dword [rdi+4], ebx  ; y
    mov dword [rdi+8], 2    ; width
    mov dword [rdi+12], 2   ; height
    mov rsi, rcx            ; renderer
    sub rsp, 8
    call SDL_RenderFillRect
    add rsp, 8

next_pixel:
    inc r10d
    cmp r10d, 100   ; x boundary
    jle draw_diamond

    mov r10d, -100  ; Reset x
    inc r11d
    cmp r11d, 100   ; y boundary
    jle draw_diamond

    mov r11d, -100  ; Reset y

    ; Stop after drawing the diamond (limit iterations)
    mov eax, SCREEN_WIDTH
    cmp r10d, 200   ; Break condition
    jl draw_diamond

    ; Update screen
    mov rdi, rcx    ; renderer
    sub rsp, 8
    call SDL_RenderPresent
    add rsp, 8

    jmp main_loop

cleanup:
    ; Clean up
    mov rdi, rcx
    sub rsp, 8
    call SDL_DestroyRenderer
    add rsp, 8

    mov rdi, rbx
    sub rsp, 8
    call SDL_DestroyWindow
    add rsp, 8

    sub rsp, 8
    call SDL_Quit
    add rsp, 8

    mov eax, 0      ; Return success
    jmp end_asm

error_init:
    mov rdi, format_string
    mov rsi, SDL_GetError
    sub rsp, 8
    call printf
    add rsp, 8
    mov eax, 1
    jmp end_asm

error_window:
    mov rdi, format_string
    mov rsi, SDL_GetError
    sub rsp, 8
    call printf
    add rsp, 8
    sub rsp, 8
    call SDL_Quit
    add rsp, 8
    mov eax, 1
    jmp end_asm

error_renderer:
    mov rdi, format_string
    mov rsi, SDL_GetError
    sub rsp, 8
    call printf
    add rsp, 8
    mov rdi, rbx
    sub rsp, 8
    call SDL_DestroyWindow
    add rsp, 8
    sub rsp, 8
    call SDL_Quit
    add rsp, 8
    mov eax, 1

end_asm:
    mov rsp, rbp
    pop rbp
    ret