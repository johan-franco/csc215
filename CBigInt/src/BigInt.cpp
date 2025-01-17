#include <iostream>
#include <string>
#include "BigInt.h"
#define to_num(c) (c-'0')
using namespace std;

BigInt::BigInt()
{
    flag = false;
    digits = "0";
}

BigInt::BigInt(int i)
{
    flag = (i >= 0) ? false : true;
    digits = (i >= 0) ? std::to_string(i) : std::to_string(-i);
}

BigInt::BigInt(string n)
{
    flag = (n.front() == '-') ? true: false;
    digits = (n.front() == '-') ? n.substr(1, n.size() - 1) : n;  
}

string BigInt::to_string() const
{
    return (!flag) ? digits : "-" + digits;
}

BigInt::BigInt(string n, bool b)
{
    flag = b;
    digits = n;
}


bool BigInt::operator==(const BigInt& i2) const
{
    if (digits.size() != i2.digits.size()) return false;
    if (flag != i2.flag) return false;
    for (int i = 0; i < digits.size(); i++)
        if (digits[i] != i2.digits[i])
            return false;
    return true;
}

bool BigInt::operator>(const BigInt& i2) const
{
    if (!flag && i2.flag) return true;
    if (flag && !i2.flag) return false;
    // They have the same sign
    if (digits.size() > i2.digits.size()) {
        return flag ? false : true;
    }
    if (digits.size() < i2.digits.size()) {
        return flag ? true : false;
    }
    // They have the same number of digits 
    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] > i2.digits[i]) {
            return flag ? false : true;
        }
    }
    // They are equal
    return false;
}

bool BigInt::operator!=(const BigInt& i2) const
{
    return !(this->operator==(i2));
}

bool BigInt::operator<=(const BigInt& i2) const
{
    return !(this->operator>(i2));
}

bool BigInt::operator<(const BigInt& i2) const
{
    return !(this->operator==(i2)) && !(this->operator>(i2));
}

bool BigInt::operator>=(const BigInt& i2) const
{
    return (this->operator>(i2)) || (this->operator==(i2));
}

/*BigInt BigInt::sum_common_digits(const BigInt& i2) const
{
    char digsum, carry = 0;
    string sum = digits;

    for (int i = sum.size() - 1; i >= 0; i--) {
        digsum = (sum[i] - '0') + (i2.digits[i] - '0');
        sum[i] = digsum % 10 + '0' + carry;
        carry = digsum > 9 ? 1 : 0;
    }
    return BigInt(sum);
}*/

BigInt BigInt::operator+(const BigInt& b2) const
{
    BigInt b1(digits, flag);
    BigInt sum;
    string s;
    int i1;
    int i2;
    

    int carry = 0;
    int max_digits = b1.digits.length();
    if (b2.digits.length() > max_digits) {
        max_digits = b2.digits.length();
    }
    for(int i; i < max_digits || carry; i++) {
        i1 = 0;
        /*Subtracting b '0' helps convert char to actual value as its ascii is 48*/
        if (i < b1.digits.length()) {
            i1 = b1.digits[i] - '0';
        }

        i2 = 0;
        if (i < b2.digits.length()) {
            i2 = b2.digits[i] - '0';
        }

        result = i1 + i2 + carry;
        carry = result / 10;
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
    
    return sum;
}

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
