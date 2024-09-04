# Notes:

## Front panel switches
- 25 toggle switches, 36 indicator lights 
- Most operation (256 bites of memory) can be done with 15 switches and 16 of the indicator lights.
- On-Off switch is one of them and when you turn it off the memory is wiped.
- Stop-Run switch either stops the program or runs it
- Single Step Switch implements a single instruction each time it is ran. it may requiere  
- Examine-Examine Next it displays the memory of the specified memory address using the 8 LED lights and examine next shows the next sequence
- Deposit-Deposit Next causes the data byte to be stored into the 8 DATA switches to be loaded into a specified memory address and the next causes the next sequential to be loaded through.
- Reset-Clr sets program counter to first memory address 0 000 000 000 000 000 CLr is a command for external equipment.
- Protect-Unprotect Protect stops the data from being changed unprotect allows it to be altered
- There are AUX switches for other equipment
- Data/Address switches are designated 7-0 and address are 15-0. If a switch is up that is the 1 position if done that is 0. addresses 8-15 should not be used in basic ALTAIR

## Indicator LED's
LED Behavior:
- Stopped Machine: A glowing LED represents a 1 bit (active), while a non-glowing LED represents a 0 bit (inactive).
- Running Machine: LED indications may be unreliable while the machine is executing a program.
LED Indicators
- ADDRESS LEDs (A15-A0): Display the memory address currently being accessed or loaded with data.
- DATA LEDs (D7-D0): Show the data stored at the current memory address.
- INTE (Interrupt Enabled): Illuminates when an interrupt is enabled.
- PROT (Protected Memory): Lights up when the memory is in a protected state.
- WAIT: Glows when the CPU is in a wait state.
- HLDA (Hold Acknowledged): Indicates a hold request has been acknowledged by the CPU.
## Status LEDs

- Status Indication: A glowing LED represents an active status for the condition it monitors.
LED Definitions:
- MEMR (Memory Read): Indicates the memory bus is active for reading data.
- INP (Input Address): Shows the address bus is pointing to an input device. The input data will be on the data bus.
- M1 (First Machine Cycle): Denotes the CPU is processing the first cycle of an instruction.
- OUT (Output Address): Displays the address of an output device. The data bus will contain the output data.
- HLTA (Halt Acknowledged): Lights up when a HALT instruction is executed and acknowledged.
- STACK: Shows the stack pointer’s current address on the address bus.
- WO (Write/Output): Indicates the current machine cycle is for writing to memory or outputting data. If not lit, the cycle is for reading memory or input.
- INT (Interrupt Acknowledged): Glows when an interrupt request is acknowledged.
## Loading a Sample Program

- LDA: Load the accumulator with data from a specified memory address.
- MOV (A→B): Transfer the accumulator’s content to register B.
- ADD (B+A): Add the contents of register B to the accumulator.
- STA: Store the accumulator’s content in a specific memory address.
- JMP: Jump to the specified address to loop the program.
### Loading Process
- Determine Memory Addresses: Start the program at memory address 0, with data addresses beginning at address 128.
- Convert to Machine Language: Convert mnemonics to bit patterns and load them into memory.
### Example:
- LDA at address 128 would translate to a specific bit pattern and be loaded into memory sequentially.
- Use the front panel switches to enter bit patterns step by step, storing each in memory.
- After loading, use the RESET and RUN switches to execute the program. Use the EXAMINE switch to view the result stored in memory.
## Memory Usage in ALTAIR 8800
- Memory Organization: Organize memory into blocks, such as reserving the first 100 words for programs, the next 100 for subroutines, and the remaining for data.
- Memory Map Updates: Regularly update the memory map when the organization changes.
## Memory Addressing
- Direct Addressing: The instruction includes the memory address directly following the instruction byte.
- Register Pair Addressing: Memory addresses are stored in register pairs, primarily H (high) and L (low).
- Stack Pointer Addressing: Used for PUSH and POP operations, requiring the programmer to designate a stack location.
- Immediate Addressing: Data is loaded directly into memory along with the program.
- Stack Addressing for Subroutines: Subroutine calls push the return address onto the stack, and a RETURN instruction pops it to resume the main program.
## Operating Tips
### Proofreading Programs
- Always review a program after entry by comparing the stored bit patterns against the intended values, using the EXAMINE and DEPOSIT switches.
- Scatter NOP instructions within a program to reserve space for potential future modifications.
- Use the SINGLE STEP switch to run the program cycle by cycle, allowing observation of STATUS LEDs for troubleshooting errors.