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
START2: CALL    CI   ; GET ONE CHAR
        CALL    COMPARE 
        CALL    CCRLF
        JMP     START2  ; KEEP GOING!

SINON:  DB      'WELCOME TO SNOWMAN GAME',CR,LF,0
WORD:   DB      'GUESS',CR,LF,0
WARN:   DB      'ONLY CAPITAL',CR,LF,0

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

; PRINT MESSAGE TO THE CONSOLE 
COMSG:  MOV     A,M     ; RETRIEVE ONE CHARACTER
        ORA     A       ; ZERO IS THE TERMINATOR CHARACTER
        RZ              ; RETURN OUT OF THE FUNCTION ON ZERO
        CALL    CO      ; OTHERWISE, OUTPUT THE CHARACTER.
        INX     H       ; INCREMENT INDEX REGISTER
        JMP     COMSG   ; KEEP GOING

CHECK:  MOV     A,M     ; RETRIEVE ONE CHARACTER
        ORA     A       ; ZERO IS THE TERMINATOR CHARACTER
        RZ              ; RETURN OUT OF THE FUNCTION ON ZERO
        CPI     E
        JZ      COR
        INX     H       ; INCREMENT INDEX REGISTER
        JMP     CHECK   ; KEEP GOING



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

COMPARE:PUSH    B       ; START BY SAVING REGISTERS.
        PUSH    D
        PUSH    H
        MOV     E,A     ;CHARACTER MOVED FROM (A) TO (E)  
        LXI     H,WORD
        CALL    CHECK

        POP     H       ; RESTORE REGISTERS
        POP     D
        POP     B
        RET
        


COR:    LXI     H,SINON
        CALL    COMSG
        POP     H       ; RESTORE REGISTERS
        POP     D
        POP     B
        END

SPMSG:  XTHL                    ; GET "RETURN ADDRESS" TO HL
        XRA     A               ; CLEAR FLAGS AND ACCUMULATOR
        ADD     M               ; GET ONE MESSAGE CHARACTER
        INX     H               ; POINT TO NEXT
        XTHL                    ; RESTORE STACK FOR
        RZ                      ; RETURN IF DONE
        CALL    CO              ; ELSE DISPLAY CHARACTER
        JMP     SPMSG           ; AND DO ANOTHER

INBUF:  DS      83      ;LINE INPUT BUFFER
        CALL    CCRLF   ; ADD CR, LF
        JMP     START2  ; KEEP GOING

; SET UP STACK SPACE AT THE END OF PROGRAM
        DS      64      ; 40H LOCATIONS (64 IN DEC)
STAK:   DB      0       ; TOP OF STACK

        END
