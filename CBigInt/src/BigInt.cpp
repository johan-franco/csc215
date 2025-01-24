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
    int i1, i2, carry = 0;
    int max_digits = max(b1.digits.length(), b2.digits.length());
    string s(max_digits + 1, ' ');  // one extra space for carry

    // Case 1: Both are positive
    if (!b1.flag && !b2.flag) {
        for (int i = 0; i < max_digits || carry; i++) {
            i1 = (i < b1.digits.size()) ? (b1.digits[b1.digits.size() - 1 - i] - '0') : 0;
            i2 = (i < b2.digits.size()) ? (b2.digits[b2.digits.size() - 1 - i] - '0') : 0;

            int result = i1 + i2 + carry;
            carry = result / 10;
            s[max_digits - i] = (result % 10) + '0';
        }
    size_t not_space = s.find_first_not_of(' ');

    // If there's any non-space character, cut the string to remove the leading spaces
    if (not_space != string::npos) {
        s = s.substr(not_space);
    }
        return BigInt(s, false);

    }
    // Case 2: Both BigInts are negative
    else if (b1.flag && b2.flag) {
        for (int i = 0; i < max_digits || carry; i++) {
            i1 = (i < b1.digits.size()) ? (b1.digits[b1.digits.size() - 1 - i] - '0') : 0;
            i2 = (i < b2.digits.size()) ? (b2.digits[b2.digits.size() - 1 - i] - '0') : 0;

            int result = i1 + i2 + carry;
            carry = result / 10;
            s[max_digits - i] = (result % 10) + '0';
        }
        size_t not_space = s.find_first_not_of(' ');
        // If there's any non-space character, cut the string to remove the leading spaces
        if (not_space != string::npos) {
            s = s.substr(not_space);
        }
        return BigInt(s, true); 
    }
    // Case 3: One BigInt is positive and the other is negative
    else {
        BigInt positive = (b1.flag ? b2 : b1); // whichever is positive
        BigInt negative = (b1.flag ? b1 : b2); // whichever is negative
        if (positive > negative) {  // positive > negative
            for (int i = 0; i < max_digits || carry; i++) {
                i1 = (i < positive.digits.size()) ? (positive.digits[positive.digits.size() - 1 - i] - '0') : 0;
                i2 = (i < negative.digits.size()) ? (negative.digits[negative.digits.size() - 1 - i] - '0') : 0;

                int result = i1 - i2 + carry;
                carry = (result < 0) ? -1 : 0; // carry is -1 when result is negative
                if (result < 0) result += 10;
                s[max_digits - i] = result + '0';
            }
            size_t not_space = s.find_first_not_of(' ');
            // If there's any non-space character, cut the string to remove the leading spaces
            if (not_space != string::npos) {
                s = s.substr(not_space);
            }
            return BigInt(s, positive.flag); // result flag follows the sign of positive
        } else {  // negative > positive
            for (int i = 0; i < max_digits || carry; i++) {
                i1 = (i < positive.digits.size()) ? (positive.digits[positive.digits.size() - 1 - i] - '0') : 0;
                i2 = (i < negative.digits.size()) ? (negative.digits[negative.digits.size() - 1 - i] - '0') : 0;

                int result = i2 - i1 + carry;
                carry = (result < 0) ? -1 : 0; // carry is -1 when result is negative
                if (result < 0) result += 10;
                s[max_digits - i] = result + '0';
            }
            size_t not_space = s.find_first_not_of(' ');
            // If there's any non-space character, cut the string to remove the leading spaces
            if (not_space != string::npos) {
                s = s.substr(not_space);
            }
            return BigInt(s, negative.flag); // result will have negative flag
        }
    }
}
BigInt BigInt::operator-(const BigInt& sub2) const {
    /*Still need to handle that double - are appearing & other cases*/
    BigInt b1(digits, flag);
    int i1, i2, carry = 0;
    int max_digits = max(b1.digits.length(), sub2.digits.length());
    string s(max_digits + 1, ' ');  // one extra space for carry
    //Subtraction is just addition

    if(!sub2.flag == b1.flag) {
        //Handles case where the reverse of sub2 makes it tbe same sign as b1 
        return b1 + BigInt(sub2.digits, !sub2.flag);
    }
    if (sub2.flag == true){
        //handles double negative
        string s = (b1 + BigInt(sub2.digits, false)).to_string();
        size_t not_zero = s.find_first_not_of('0');
        // Cut the string to remove the leading zeros
        if (not_zero != string::npos) {
            s = s.substr(not_zero);
        }
        return BigInt(s,(b1 + BigInt(sub2.digits, !sub2.flag)).flag);
    }
    else {
        BigInt positive = b1;
        BigInt negative = sub2;
        if (positive > negative) {  // positive > negative
            for (int i = 0; i < max_digits || carry; i++) {
                i1 = (i < positive.digits.size()) ? (positive.digits[positive.digits.size() - 1 - i] - '0') : 0;
                i2 = (i < negative.digits.size()) ? (negative.digits[negative.digits.size() - 1 - i] - '0') : 0;

                int result = i1 - i2 + carry;
                carry = (result < 0) ? -1 : 0; // carry is -1 when result is negative
                if (result < 0) result += 10;
                s[max_digits - i] = result + '0';
            }
            size_t not_space = s.find_first_not_of(' ');
            // If there's any non-space character, cut the string to remove the leading spaces
            if (not_space != string::npos) {
                s = s.substr(not_space);
            }
            return BigInt(s, positive.flag); // result flag follows the sign of positive
        } else {  // negative > positive
            for (int i = 0; i < max_digits || carry; i++) {
                i1 = (i < positive.digits.size()) ? (positive.digits[positive.digits.size() - 1 - i] - '0') : 0;
                i2 = (i < negative.digits.size()) ? (negative.digits[negative.digits.size() - 1 - i] - '0') : 0;

                int result = i2 - i1 + carry;
                carry = (result < 0) ? -1 : 0; // carry is -1 when result is negative
                if (result < 0) result += 10;
                s[max_digits - i] = result + '0';
            }
            size_t not_space = s.find_first_not_of(' ');
            // If there's any non-space character, cut the string to remove the leading spaces
            if (not_space != string::npos) {
                s = s.substr(not_space);
            }
            return BigInt(s, true); // result will have negative flag
        }
    }
}
