; Small ver of snowman
CR      EQU     0DH     ; Carriage Return
LF      EQU     0AH     ; Line Feed

; CP/M BDOS Functions
RCONF   EQU     1       ; Read console input to (A)
WCONF   EQU     2       ; Write (A) to console
BDOS    EQU     5       ; BDOS system call entry

TPA     EQU     100H    ; Transient Program Area
        ORG     TPA     ; Start program at TPA

START:  LXI     SP,STAK ; Set up the stack
        CALL    CCRLF   ; 
        LXI     H,MSG   ; 
        CALL    COMSG   ; 

MAIN:   CALL    CI      ; Get input character
        CPI     'A'     ; Compare input with 'A'
        JZ      SUCCESS ; If equal, jump to success
        LXI     H,FAIL  ; 
        CALL    CCRLF
        JMP     DISPLAY

SUCCESS:
        LXI     H,OK    ; Load success message
        CALL    DISPLAY

DISPLAY:
        CALL    COMSG   ; Display the message
        CALL    CCRLF   ; Print newline
        JMP     MAIN    ; Repeat

; Subroutine to print a message to console
COMSG:  MOV     A,M     ; Load character from memory
        ORA     A       
        RZ              
        CALL    CO      ; Print character
        INX     H       ; Increment pointer
        JMP     COMSG   


CCRLF:  MVI     A,CR
        CALL    CO
        MVI     A,LF
        JMP     CO


CI:     PUSH    B       ;SAVE REGISTERS
        PUSH    D
        PUSH    H
        MVI     C,RCONF ;READ FUNCTION IN (C)
        CALL    BDOS
        ANI     7FH     ;MASK TO 7 BITS
        POP     H       ;RESTORE REGISTERS
        POP     D       
        POP     B
        RET

; CHARACTER IN REGISTER A OUTPUT TO CONSOLE 
CO:     PUSH    B       ;SAVE REGISTERS
        PUSH    D
        PUSH    H
        MVI     C,WCONF 
        MOV     E,A     
        CALL    BDOS    
        POP     H       
        POP     D
        POP     B
        RET

; Messages
MSG:    DB      'Guess the letter: ', 0
OK:     DB      'Correct!', CR, LF, 0
FAIL:   DB      'Wrong', CR, LF, 0

; Stack space
STAK:   DS      64      ; Reserve stack space

        END
