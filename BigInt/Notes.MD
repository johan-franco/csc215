# General Notes
- Arbitraty-Precision integer:"indicates that calculations are performed on numbers whose digits of precision are potentially limited only by the available memory of the host system." (wikipedia def)
- In the case study they decide on using class bigint for the values that are larger than what int can handle
- It will also be useful to construct a BigInt from a string value since a string can contain as many characters as needed to represent any BigInt value