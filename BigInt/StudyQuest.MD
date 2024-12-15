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
We would need to make it so that the values taken in by scan are double values and not integers. Though doing this does could cause rounding errors.

4. Most modern systems support graphical displays and mouse (or other
pointer) input. Rewrite the Calculator program to take advantage of
these features to produce an on-screen push-button calculator (this is a
large programming project).

There are a lot of libraries in C++ that can be used. However, I don't believe it is currently possible to change our version of Calculator to graphical output.

5. Show how a new command, "C", which acts like the "Clear" command on
a calculator could be implemented. The clear command sets the current
value to zero.
If we wanted to do that we would add another case value and have it set accumulator to 0.


6. (AB only) How could the calculator be modified to allow the use of
parentheses to control the order of operations?
I think to modify our program to do that we would need to hold the values of all of them and then write a function to activate when a "(" is detected that executes the proper order of operations until a ")" is detected.