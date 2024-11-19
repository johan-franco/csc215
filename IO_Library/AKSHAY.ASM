; ROT13 NOVEMBER 15 2024
; CYPHERS TEXT TO ROT13, CEASER CYPHER
; ONLY WORKS WITH CAPITAL LETTERS!
; CREATOR: AKSHAY KUCHIBHATLA
; I realized that Z is not done properly. It should be M but it outputs Z.
; In his converting code he had to increase the value of the maximum so that Z would be accounted for.
; I changed the maximum to 91 so that Z (ASCII value is 90) would be properly accounted for.
;ASCII CHARACTERS' SETUP
; TOGETHER CR LF MAKE A NEW LINE /n
CR      EQU     0DH     ; CARRIAGE RETURN
LF      EQU     0AH     ; LINE FEED
CTRLZ   EQU     1AH     ;OPERATOR INTERRUPT

;CP/M BDOS FUNCTIONS
RCONF   EQU     1    ; READ CON: INTO (A)
WCONF   EQU     2      ;WRITE (A) INTO CON:
RBUFF   EQU     10      ;READ A CONSOLE LINE FUNCTION

;CP/M ADDRESSES
RBOOT   EQU     0       ;REBOOT CP/M SYSTEM
BDOS    EQU     5       ; THE SYSTEM CALL ENTRY
TPA     EQU     100H    ; TRANSIENT PROGRAM AREA
        ORG     TPA     ;ASSEMBLY PROGRAM FOR TPA

START:  LXI     SP,STAK ;SET UP THE USER STACK
START1: CALL    CCRLF   ; START A NEW LINE
        LXI     H,SINON ; WITH SIGN-ON MESSAGE
        CALL    COMSG
START2: CALL    CIMSG   ; GET A LINE OF INPUT FROM THE USER
        CALL    CCRLF
        LXI     H,INBUF+2       ; POINT TO THE TEXT IS THE BUFFER
        CALL    COMSG   ; ECHO THE HWOLE LINE
        CALL    CCRLF   ; ADD CR, LF
        JMP     START2  ; KEEP GOING!

SINON:  DB      'EBG13: GUR PRNFRE PLCURE',CR,LF,0

; CONSOLE CHARACTER INTO REGISTER A MASKED TO 7 BITS
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
        MVI     C,WCONF ; SELECT FUNCTION AND MOVE INT (C)
        MOV     E,A     ;CHARACTER MOVED FROM (A) TO (E)
        CALL    BDOS    ; OUTPUT BY CP/M
        POP     H       
        POP     D
        POP     B
        RET

; FIRST, WE INITIALIZE THE CARRIAGE RETURN AND LINEFEED TO THE CONSOLE.
CCRLF:  MVI     A,CR
        CALL    CO
        MVI     A,LF
        JMP     CO

; PRINT MESSAGE TO THE CONSOLE IN ROT13
COMSG:  MOV     A,M     ; RETRIEVE ONE CHARACTER
        ORA     A       ; ZERO IS THE TERMINATOR CHARACTER
        RZ              ; RETURN OUT OF THE FUNCTION ON ZERO
        CALL    R13CHR  ; OTHERWISE, CONVERT TO R13
        CALL    CO      ; OTHERWISE, OUTPUT THE CHARACTER.
        INX     H       ; INCREMENT INDEX REGISTER
        JMP     COMSG   ; KEEP GOING

; INPUT CONSOLE MESSAGE INTO THE BBUFFER USING THIS FUCNTION
CIMSG:  PUSH    B       ; START BY SAVING REGISTERS.
        PUSH    D
        PUSH    H
        LXI     H,INBUF+1       ; ZERO CHARACTER COUNTER
        MVI     M,0
        DCX     H       ; DECREMENTS THE INDEX REGISTER PAIR.
        MVI     M,80
        XCHG            ; SEND INBUFF POINTER TO DE REGISTERS
        MVI     C,RBUFF ; SET UP READ BUFFER FUNCTION
        CALL    BDOS    ; INPUT A LINE
        LXI     H,INBUF+1 ; GET THE CHARACTER COUNTER
        MOV     E,M
        MVI     D,0
        DAD     D
        INX     H
        MVI     M,0
        POP     H
        POP     D
        POP     B
        RET

; CONVERT CHARACTER IN A USING ROT13
R13CHR: PUSH    B       ; SAVE REGISTERS
        PUSH    D
        PUSH    H
        CPI     41H     ; CHAR IS CAPS LETTER?
        JC      SKIP1   ; IF NOT, JMP
        CPI     5BH     ; CHECKING AGAIN
        JNC     SKIP1   ; IF NOT CAPS, JMP
        CPI     4DH     ; OVER 77? (PAST M?)
        JC      SKIP    ; IF NO, THEN ADD 13
        JZ      SKIP    ; IF EQUAL, ADD 13.
        SBI     0DH     ; IF LESS, THEN SUB 13
        JMP     SKIP1   ; NO ADDING
SKIP:   ADI     0DH     ; ADDING 13
SKIP1:  POP     H       ; RESTORE REGISTERS
        POP     D
        POP     B
        RET

INBUF:  DS      83      ;LINE INPUT BUFFER
        CALL    CCRLF   ; ADD CR, LF
        JMP     START2  ; KEEP GOING

; SET UP STACK SPACE AT THE END OF PROGRAM
        DS      64      ; 40H LOCATIONS (64 IN DEC)
STAK:   DB      0       ; TOP OF STACK

        END