; ASCII Characters
CR      EQU     0DH     ; Carriage Return
LF      EQU     0AH     ; Line Feed
CTRLZ   EQU     1AH     ; Operator Interrupt

; CP/M BDOS Functions
RCONIN  EQU     1       ; Read Console (into A)
WCONOUT EQU     2       ; Write (A) to Console
RBUF    EQU     10      ; Read Buffered Input

; CP/M Addresses
RBOOT   EQU     0       ; Reboot CP/M System
BDOS    EQU     5       ; System Call Entry
TPA     EQU     100H    ; Transient Program Area

        ORG     TPA     ; Assemble program for TPA

; Main Program Start
START:  LXI     SP,STAK ; Set up user's stack
START1: CALL    CCRLF   ; Start a new line
        LXI     H,SIGNON ; With sign-on message
        CALL    COMSG
START2: CALL    CIMSG   ; Get a line of input
        CALL    CCRLF   ; Add a new line
        LXI     H,INBUF+2 ; Point to its text
        CALL    COMSG   ; Echo the whole line
        CALL    CCRLF   ; And add CR, LF
        JMP     START2  ; Loop back for another input

SIGNON: DB      'SIGN-ON MESSAGE',CR,LF,0

; Console Character Input Routine
CI:     PUSH    B       ; Save registers
        PUSH    D
        PUSH    H
        MVI     C,RCONIN ; Read function
        CALL    BDOS
        ANI     7FH      ; Mask to 7 bits
        POP     H        ; Restore registers
        POP     D
        POP     B
        RET

; Console Output Character Routine
CO:     PUSH    B       ; Save registers
        PUSH    D
        PUSH    H
        MVI     C,WCONOUT ; Select function
        MOV     E,A     ; Character to E
        CALL    BDOS    ; Output by CP/M
        POP     H       ; Restore registers
        POP     D
        POP     B
        RET

; Carriage Return and Line Feed Routine
CCRLF:  MVI     A,CR
        CALL    CO
        MVI     A,LF
        JMP     CO

; Print Message Pointed to by HL to Console
COMSG:  MOV     A,M     ; Get A character
        ORA     A       ; Check if zero
        RZ              ; Return on zero
        CALL    CO      ; Else output the character
        INX     H       ; Point to the next character
        JMP     COMSG   ; Repeat

; Input Console Message into Buffer
CIMSG:  PUSH    B       ; Save registers
        PUSH    D
        PUSH    H
        LXI     H,INBUF+1 ; Zero character counter
        MVI     M,0
        DCX     H
        MVI     M,80    ; Set maximum line length
        XCHG            ; INBUF pointer to DE registers
        MVI     C,RBUF  ; Set up read buffer function
        CALL    BDOS    ; Input a line
        MOV     E,M     ; Get character count
        LXI     H,INBUF+1 ; Point HL to start
        MOV     E,M  ; INTO LSB OF DE REGISTER PAIR
        MVI     D,0     ; Zero MSB
        DAD     D       ; Add length to start
        INX     H       ; Point to end
        MVI     M,0     ; Insert null terminator
        POP     H       ; Restore registers
        POP     D
        POP     B
        RET

INBUF:  DS      83      ; Line input buffer

; Stack Setup
        DS      64      ; 40H locations for stack
STAK:   DB      0       ; Top of stack

        END