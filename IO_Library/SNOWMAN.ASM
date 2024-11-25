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
        LXI     H,MSG   
        CALL    COMSG   ; Display the message

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
        LXI     H,FIR    ; Load success message
        CALL    DISPLAY
        JMP     MAIN

SUS:    CALL    CCRLF
        LXI     H,SEC    ; Load success message
        CALL    DISPLAY
        JMP     MAIN

SUT:    CALL    CCRLF
        LXI     H,THR    ; Load success message
        CALL    DISPLAY
        JMP     MAIN

FAILURE:CALL    CCRLF
        LXI     H,FAIL  ; Otherwise, load failure message
        CALL    DISPLAY
        JMP     MAIN

DISPLAY:CALL    COMSG   ; Display the message
        CALL    CCRLF   ; Print newline
        RET

EXIT:   CALL    CCRLF   ; Print a newline before exiting
        END             ; Exit program


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
MSG:    DB      'Guess the letter: ', 0
FIR:    DB      'FIRST CHAR!', CR, LF, 0
SEC:    DB      'SECOND CHAR',CR,LF,0
THR:    DB      'THIRD CHAR',CR,LF,0
FAIL:   DB      'Wrong, try again!', CR, LF, 0

; Stack space
STAK:   DS      64      ; Reserve stack space

        END
