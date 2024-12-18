# General Notes
- Arbitraty-Precision integer:"indicates that calculations are performed on numbers whose digits of precision are potentially limited only by the available memory of the host system." (wikipedia def)
- In the case study they decide on using class bigint for the values that are larger than what int can handle
- It will also be useful to construct a BigInt from a string value since a string can contain as many characters as needed to represent any BigInt value
- Requirements for their class
    -  be convenient and intuitive for programmers to use;
    -    be useful in a wide variety of applications;
    - mimic operations on C++ integers so that a program written and debugged using int values can be quickly and reliably converted to use BigInt values; and
    - utilize information hiding; it should be possible to use BigInt variables without knowledge of the underlying data structures or algorithms used
- Store digits as a sequence, using:
    - Arrays or vectors for arbitrary size.
    - Sign flag to handle positive/negative numbers.
- Logical indexing:
    - Least Significant Digit (LSD) is at index 0.
    - Most Significant Digit (MSD) has the highest index.
- Use helper functions for digit manipulation:
    - GetDigit: Access a specific digit.
    - ChangeDigit: Modify a digit.
    - AddSigDigit: Append a most significant digit.
- Big Int Class:
    - Constructors (initalizes from int or str)
    - Has both arithmetic and comparison operators
    - conversion functions (to change from class to int or double)


- Errors can arise from overflow during arithmetic & invalid input


