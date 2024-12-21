#include <stdio.h>
#define BAD_OP  '\0'
#define MAX_DIGITS 100

struct bigint {
    char negative;              
    char numdigits;              
    char digits[MAX_DIGITS];     /* Array to hold the digits */
};

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
                Subtract(&accumulator, &input, &result);
                break;
            case '*':
                printf("not working");
                break;
            default:
                printf("Error with operator\n");

            case 'c':
                set_bigint("0", &result);
                break;
       }

       printf("--> %s\n", get_bigint(&accumulator, buffer));

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



/* Custom strlen function */
int my_strlen(s)
char *s;
{
    int len;
    len = 0;
    while (s[len] != '\0') {
        len = len + 1;
    }
    return len;
}

/* Function to set the value of a bigint from a string */
void set_bigint(numstr, num)
char *numstr;
struct bigint *num;
{
    int i;
    int last_pos;
    int length;

    num->negative = 0;
    if (numstr[0] == '-') {
        num->negative = 1;
    }

    length = my_strlen(numstr);
    num->numdigits = length;
    if (num->negative) {
        num->numdigits = length - 1;
    }

    last_pos = length - 1;
    i = 0;
    while (i < num->numdigits) {
        num->digits[i] = numstr[last_pos - i];
        i = i + 1;
    }

    while (i < MAX_DIGITS) {
        num->digits[i] = '0';
        i = i + 1;
    }
}

/* Function to get the string representation of a bigint */
char* get_bigint(num, buffer)
struct bigint *num;
char *buffer;
{
    int i;
    int start_pos;

    start_pos = 0;
    if (num->negative) {
        buffer[0] = '-';
        start_pos = 1;
    }

    i = 0;
    while (i < num->numdigits) {
        buffer[i + start_pos] = num->digits[num->numdigits - 1 - i];
        i = i + 1;
    }

    buffer[num->numdigits + start_pos] = '\0';

    return buffer;
}

/* Addition function */
void Add(a, b, result)
struct bigint *a;
struct bigint *b;
struct bigint *result;
{
    int carry;
    int sum;
    int i;
    int digit_a;
    int digit_b;
    int max_digits;

    carry = 0;
    max_digits = a->numdigits;
    if (b->numdigits > max_digits) {
        max_digits = b->numdigits;
    }

    i = 0;
    while (i < max_digits || carry) {
        digit_a = 0;
        /*Subtracting b '0' helps convert char to actual value as its ascii is 48*/
        if (i < a->numdigits) {
            digit_a = a->digits[i] - '0';
        }

        digit_b = 0;
        if (i < b->numdigits) {
            digit_b = b->digits[i] - '0';
        }

        sum = digit_a + digit_b + carry;
        carry = sum / 10;
        result->digits[i] = (sum % 10) + '0';
        /*Add '0' to reconvert to str*/
        i = i + 1;
    }
/*Removing zeros and acutally placing values into result bigint*/

    result->numdigits = i;
    result->negative = 0;

    while (result->numdigits > 1 && result->digits[result->numdigits - 1] == '0') {
        result->numdigits = result->numdigits - 1;
    }
}

/* very similar to addition except with borrow instead of carry */
void Subtract(a, b, result)
struct bigint *a;
struct bigint *b;
struct bigint *result;
{
    int borrow;
    int diff;
    int i;
    int digit_a;
    int digit_b;
    int max_digits;

    borrow = 0;
    max_digits = a->numdigits;
    if (b->numdigits > max_digits) {
        max_digits = b->numdigits;
    }

    i = 0;
    while (i < max_digits) {
        digit_a = 0;
        if (i < a->numdigits) {
            digit_a = a->digits[i] - '0';
        }

        digit_b = 0;
        if (i < b->numdigits) {
            digit_b = b->digits[i] - '0';
        }

        diff = digit_a - digit_b - borrow;
        if (diff < 0) {
            diff = diff + 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result->digits[i] = diff + '0';

        i = i + 1;
    }

/*Removing zeros and acutally placing values into result bigint*/
    result->numdigits = max_digits;
    result->negative = 0;

    while (result->numdigits > 1 && result->digits[result->numdigits - 1] == '0') {
        result->numdigits = result->numdigits - 1;
    }
}
