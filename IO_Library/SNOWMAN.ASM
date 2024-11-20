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

; FIRST, WE INITIALIZE THE CARRIAGE RETURN AND LINEFEED TO THE CONSOLE.
CCRLF:  MVI     A,CR
        CALL    CO
        MVI     A,LF
        JMP     CO

WORD:   DB  'GUESS',CR,LF,0
WARN:   DB  'ONLY CAPITAL LETTERS',CR,LF,0


COMPARE:    CPI     41H     ; CHAR IS CAPS LETTER? (checks minimum)
            JC      SKIP1   ; IF NOT, JMP
            CPI     5BH     ; CHECKING AGAIN
            JNC     SKIP1   ; IF NOT CAPS, JMP
            END
SKIP1:      LXI H,WARN
            RET


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
        PUSH    D       ; Pushes value out of register and adds it to stack
        PUSH    H
        CPI     41H     ; CHAR IS CAPS LETTER? (checks minimum)
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