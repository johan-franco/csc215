#include <stdio.h>
#define BAD_OP  '\0'
#include "BIGINT.H"
/*
This program implements a three function calculator as the first step to a
test program for bignum struct.
*/
int main()
{
    struct bigint accumulator;
    struct bigint input;
    struct bigint result;

    char buffer[3 * MAX_DIGITS ];
    char op;
    /* Set op to '+' so first entered value is added to zero. */
    set_bigint("0", &accumulator);
    op = '+';
    while (op != '=')
    {
        char input_str[3*MAX_DIGITS];
        printf("Enter value: ");
        scanf("%d", input_str);
        set_bigint(input_str,&input);

        switch (op)
        {
            case '+':
                Add(&accumulator,&input, &result);
                break;
            case '-':
                accumulator -= input;
                break;
            case '*':
                accumulator *= input;
                break;
            default:
                printf("Error with operator\n");

            case 'c':
                accumulator = 0;
                break;
       }
       printf("--> %d\n", accumulator);
       op = get_operator();
    }
}

char string_to_op(s)
char* s;
{
    if (s[0] == '=' || s[0] == '+' || s[0] == '-' || s[0] == '*')
        return s[0];
    return BAD_OP;
}

char get_operator() {
    char* op_str;
    char op;

    do {
        printf("Enter + - * ( = to quit) ");
        scanf("%s", op_str);
    } while ((op = string_to_op(op_str)) == BAD_OP);

    return op;
}