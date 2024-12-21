#include <stdio.h>
#define MAX_DIGITS 100

struct bigint {
    char negative;               /* Flag for neg */
    char numdigits;              
    char digits[MAX_DIGITS];     /* Array to hold the digits */
};

void set_bigint();
char* get_bigint();
int my_strlen();

int main() {
    struct bigint bint1;
    struct bigint bint2;
    struct bigint bint3;
    char buffer[2 * MAX_DIGITS + 2]; /* Buffer for the string rep of bigint */

    set_bigint("1234567", &bint1);
    printf("bint1 is: %s\n", get_bigint(&bint1, buffer));

    set_bigint("321", &bint2);
    printf("bint2 is: %s\n", get_bigint(&bint2, buffer));

    set_bigint("-17", &bint3);
    printf("bint3 is: %s\n", get_bigint(&bint3, buffer));

    return 0;
}

/* Custom strlen function (string.h not found) */
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

    /* Determine if num is negative */
    if (numstr[0] == '-') {
        num->negative = 1;
    } else {
        num->negative = 0;
    }

    /* Calc number of digits */
    length = my_strlen(numstr);
    if (num->negative) {
        num->numdigits = length - 1;
    } else {
        num->numdigits = length;
    }

    /* Set the last position in the input string */
    last_pos = length - 1;    
    /* Reverse the digits into the digits array */
    i = 0;
    while (i < num->numdigits) {
        num->digits[i] = numstr[last_pos - i];
        i = i + 1;
    }

    /* Fill remaining digits with '0'*/
    while (i < MAX_DIGITS) {
        num->digits[i] = '0';
        i = i + 1;
    }
}

char* get_bigint(num, buffer)
struct bigint *num;
char *buffer;
{
    int i;
    int start_pos;

    /* Determine starting position based on negativity */
    if (num->negative) {
        buffer[0] = '-';
        start_pos = 1;
    } else {
        start_pos = 0;
    }

    /* make num into string*/
    i = 0;
    while (i < num->numdigits) {
        buffer[i + start_pos] = num->digits[num->numdigits - 1 - i];
        i = i + 1;
    }

    /* Null-terminator*/
    buffer[num->numdigits + start_pos] = '\0';

    return buffer;
}


void Subtract(vic, subtractor)
struct bigint *vic;
struct bigint *subtractor;
{
    int i;
    int borrow;
    borrow = 0;
    int max_digits;
    int vic_digit;
    int sub_dig;
    max_digits = vic->numdigits > subtractor->numdigits ? vic->numdigits : subtractor->numdigits;

    vic->digits = realloc(vic->digits, max_digits + 1);

    for (i = 0; i < max_digits; i++) {
        vic_digit = (i < vic->numdigits) ? vic->digits[i] - '0' : 0;
        sub_dig = (i < subtractor->numdigits) ? subtractor->digits[i] - '0' : 0;
        
        int result;
        result = vic_digit - sub_dig - borrow;

        if (result < 0) {
            result += 10;  
            borrow = 1;   
        } else {
            borrow = 0;
        }
        
        vic->digits[i] = result + '0';  
    }
    while (vic->numdigits > 1 && vic->digits[vic->numdigits - 1] == '0') {
        vic->numdigits--;
    }

    if (vic->numdigits == 0) {
        vic->numdigits = 1;
        vic->digits[0] = '0';  
    }
}






