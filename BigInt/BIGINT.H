#include <stdio.h>
struct bigint {
    char negative;
    char numdigits;
    char* digits;
};

int main() {
    struct bigint num1, num2;

    set_bigint("12345", &num1);
    set_bigint("678", &num2);

    printf("num1: %s\n", get_bigint(&num1));
    printf("num2: %s\n", get_bigint(&num2));

    Subtract(&num1, &num2);
    
    printf("Result of subtraction: %s\n", get_bigint(&num1));

    return 0;
}

void set_bigint(numstr, num)
char *numstr;
struct bigint *num;
{
    char last_pos, i;
    num->negative = (numstr[0] == '-');
    num->numdigits = strlen(numstr) - num->negative;
    num->digits = alloc(num->numdigits);
    last_pos = num->numdigits + (num->negative ? 0 : -1);

    /*Least significant is held at [0]*/
    for (i = 0; i < num->numdigits; i++) {
        num->digits[i] = numstr[last_pos-i];
        /* printf("numstr[%d] is %c\n", last_pos-i, numstr[last_pos-i]); */
    }
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


char* get_bigint(num)
struct bigint *num;
{
   char *numstr;
   char start_pos, i;
   numstr = alloc(num->numdigits + (num->negative ? 2 : 1));
   start_pos = num->negative;
   if (start_pos == 1) numstr[0] = '-';
   for (i = 0; i < num->numdigits; i++) {
       numstr[i+start_pos] = num->digits[num->numdigits-(i+1)];
       /* printf("numstr[%d] is %c\n", i, numstr[i+start_pos]); */
   }
   numstr[num->numdigits+start_pos] = '\0';
   return numstr;
}

