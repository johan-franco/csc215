3A # LDA - load divisor
40
00
47 # MOV (A->B) - move to register B
3A # LDA - load dividend
30
00
B8 # CMP: Compare 
DA # JNC Jump if sub not possible
10
00
90 # SUB Register from accumulator
0C #Increment C register 
C3 #Jump back to CMP
07
00
32 # Storing remainder
51
00
79 #Move Register C to accumulator
32 #Storing quotient to memry
50
00
76 # Halt
===
30:10 #16
40:02 #2

