; ATTEMPT TO FIX SNOWMAN.ASM's failure with printing wrong with SPMSG
CR      EQU     0DH     ; Carriage Return
LF      EQU     0AH     ; Line Feed

; CP/M BDOS Functions
RCONF   EQU     1     
WCONF   EQU     2    
BDOS    EQU     5      

TPA     EQU     100H    ; Transient Program Area
        ORG     TPA

START:  LXI     SP,STAK ; Set up the stack
        CALL    CCRLF 
        CALL    SPMSG
        DB      'Guess the letter (USE CAPITAL LETTERS):', 0

MAIN:   CALL    CI     
        CPI     'e'  
        JZ      EXIT    

        CPI     'C'   
        JZ      SUO 

        CPI     'A'
        JZ      SUS 
        
        CPI     'T'
        JZ      SUT
        JMP     FAILURE ; Jump to display message

SUO:    CALL    CCRLF
        CALL    SPMSG
        DB      'C__', CR, LF, 0
        CALL    CCRLF
        JMP     MAIN

SUS:    CALL    CCRLF
        CALL    SPMSG
        DB      '_A_',CR,LF,0
        CALL    CCRLF  
        JMP     MAIN

SUT:    CALL    CCRLF
        CALL    SPMSG
        DB      '__T',CR,LF,0
        CALL    CCRLF
        JMP     MAIN

FAILURE:CALL    CCRLF
        CALL    SPMSG  ; Otherwise, load failure message
        DB      'Wrong', CR, LF, 0
        CALL    CCRLF
        JMP     MAIN

DISPLAY:CALL    COMSG   
        CALL    CCRLF 
        RET

EXIT:   CALL    CCRLF  
        RET             ; Exit program


COMSG:  MOV     A,M     ; RETRIEVE ONE CHARACTER
        ORA     A       ; ZERO IS THE TERMINATOR CHARACTER
        RZ              ; RETURN OUT OF THE FUNCTION ON ZERO
        CALL    CO      ; OTHERWISE, OUTPUT THE CHARACTER.
        INX     H       ; INCREMENT INDEX REGISTER
        JMP     COMSG   ; KEEP GOING

CCRLF:  MVI     A,CR
        CALL    CO
        MVI     A,LF
        JMP     CO

SPMSG:  XTHL                    ; GET "RETURN ADDRESS" TO HL
        XRA     A               ; CLEAR FLAGS AND ACCUMULATOR
        ADD     M               ; GET ONE MESSAGE CHARACTER
        INX     H               ; POINT TO NEXT
        XTHL                    ; RESTORE STACK FOR
        RZ                      ; RETURN IF DONE
        CALL    CO              ; ELSE DISPLAY CHARACTER
        JMP     SPMSG           ; AND DO ANOTHER

CI:     PUSH    B    
        PUSH    D
        PUSH    H
        MVI     C,RCONF ; Read console function
        CALL    BDOS    ; Call BDOS
        ANI     7FH     
        POP     H       ; Restore registers
        POP     D
        POP     B
        RET             ; Return with input in A
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

CO:     PUSH    B     
        PUSH    D
        PUSH    H
        MVI     C,WCONF 
        MOV     E,A     
        CALL    BDOS    
        POP     H       
        POP     D
        POP     B
        RET             ; Return

; Messages
MSG:    DB      'Guess the letter (USE CAPITAL LETTERS): ', 0
FIR:    DB      'C', CR, LF, 0
SEC:    DB      '_A_',CR,LF,0
THR:    DB      '__T',CR,LF,0
FAIL:   DB      'Wrong', CR, LF, 0
TEST:   DB      'TEST', CR, LF, 0

; Stack space
STAK:   DS      64      ; Reserve stack space

        END
