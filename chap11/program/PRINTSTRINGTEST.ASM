    mov si, message       ;The message location *you can change this*
    call print            ;CALL tells the pc to jump back here when done

    print:
      mov ah, 0Eh         ;Set function

    .run:
      lodsb               ;Get the char
    ; cmp al, 0x00        ;I would use this but ya know u dont so use:
      cmp al, 0           ;0 has a HEX code of 0x48 so its not 0x00
      je .done            ;Jump to done if ending code is found
      int 10h             ;Else print
      jmp .run            ; and jump back to .run

    .done:
      ret                 ;Return

    message           db  'Hello, world', 0 ;IF you use 0x00
    ;message          db  'Hello, world', 0x00