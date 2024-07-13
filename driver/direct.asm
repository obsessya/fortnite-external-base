section .text

global direct_device_control

direct_device_control:
    ; Move the value of rcx to r10
    mov r10, rcx
    ; Set rax to 7, which is a placeholder for the system call number on Windows
    mov rax, 7
    ; Invoke the system call using int 0x2E
    int 0x2E
    ; Return from the procedure
    ret