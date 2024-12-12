## Introduction Study Questions 
1. Suppose you want to add unary operations (i.e., ones requiring only one
operand) to the calculator. For example, we might add "M" to indicate
unary minus (i.e., change the sign of the old value) and "A" to indicate
absolute value. What changes would need to be made to the program?

    In order to accomplish that goal we would need to add these operators to the list of operators that can be used. Meaning we would need seperate logic if the input was equal to "M" or "A". For the unary operator I believe we could just add code that subtracts the current operand by itself twice and returns that value. This would flip the sign of the old value regardless of whether it is negative or positive. For absolute value we would want to check if the operand is less than 0 and if it is then we would subtract it byitself twice again. Unlike the other operations we won't need to ask for a new operand as we only need the current operand.

2. Suppose that words rather than single character symbols are to be used
for the operators (e.g., the user types "times" instead of "*"). Where in
the program would the necessary changes occur?

        For a specific space in the CALC.C given by Jeff we would implement a change in the case statements that dictate what changes are done. Instead of checking if the case is '*' we would check if it is "times".

3. Suppose that the calculator is to be converted to use C++ double values
rather than integers. Where would changes need to be made?

4. Most modern systems support graphical displays and mouse (or other
pointer) input. Rewrite the Calculator program to take advantage of
these features to produce an on-screen push-button calculator (this is a
large programming project).