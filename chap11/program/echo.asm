BDOS    EQU     5           
RCONF  EQU     1           
WCONF EQU     2           
ORG     100H        
START:
            MVI     C, RCONF   ; Load C with the function code for console input
            CALL    BDOS        
            MOV     A, L        

            CPI     0DH         ; Check if it's a carriage return
            JZ      EXIT        

            MVI     C, WCONF  ; Load C with the function code for console output
            MOV     E, A        
            CALL    BDOS        
            JMP     START     

EXIT:
            RET            

            END     START       
