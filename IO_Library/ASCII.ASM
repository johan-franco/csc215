; TOGETHER CR LF MAKE A NEW LINE /n
CR      EQU     0DH     ; CARRIAGE RETURN
LF      EQU     0AH     ; LINE FEED
CTRLZ   EQU     1AH     ;OPERATOR INTERRUPT

;CP/M BDOS FUNCTIONS
RCONF   EQU     1    
WCONF   EQU     2      
RBUFF   EQU     10      

;CP/M ADDRESSES
RBOOT   EQU     0     
BDOS    EQU     5      
TPA     EQU     100H  
        ORG     TPA    

START:  LXI	SP,STAK		
        CALL	CCRLF		
	CALL    SPMSG	; DISPLAY WORD TO GUESS
        DB  'GUESS THE WORD (MAKE SURE TO USE ONLY CAPITALS)',CR,LF,0
	

CCRLF:  MVI     A,CR
        CALL    CO
        MVI     A,LF
        JMP     CO

COMSG:  MOV     A,M             ; GET A CHARACTER
        ORA     A               ; ZERO IS THE TERMINATOR
        RZ                      ; RETURN ON ZERO
        CALL    CO              ; ELSE OUTPUT THE CHARACTER
        INX     H               ; POINT TO THE NEXT ONE
        JMP     COMSG           ; LOOP

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
        JMP     MAIN2  ; KEEP GOING

; SET UP STACK SPACE AT THE END OF PROGRAM
        DS      64      ; 40H LOCATIONS (64 IN DEC)
STAK:   DB      0       ; TOP OF STACK


        END