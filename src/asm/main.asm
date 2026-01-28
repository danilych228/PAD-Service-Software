section .text
    global asm_main_func
    extern init_sdl
    extern render_frame
    extern cleanup_sdl
    extern poll_events

; Entry point for our assembly function called from C
asm_main_func:
    push rbp
    mov rbp, rsp
    
    ; Initialize SDL
    call init_sdl
    test rax, rax
    js .error           ; Jump if initialization failed
    
.main_loop:
    ; Render frame
    call render_frame
    
    ; Poll events
    call poll_events
    test rax, rax
    jnz .cleanup        ; Jump to cleanup if quit event received
    
    ; Small delay to prevent 100% CPU usage
    mov rax, 35         ; sys_nanosleep
    mov rdi, sleep_time
    xor rsi, rsi
    syscall
    
    jmp .main_loop      ; Continue loop

.cleanup:
    call cleanup_sdl
    xor rax, rax        ; Return success
    jmp .exit

.error:
    mov rax, -1         ; Return error

.exit:
    mov rsp, rbp
    pop rbp
    ret

section .data
    sleep_time:
        dq 0            ; seconds
        dq 16666667     ; nanoseconds (about 1/60th second)