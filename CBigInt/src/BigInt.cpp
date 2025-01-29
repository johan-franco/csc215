#include <iostream>
#include <string>
#include "BigInt.h"
#define to_num(c) (c-'0')
using namespace std;

BigInt::BigInt()
{
    flag = false;
    digits = "0";
    reverse = digits;
}

BigInt::BigInt(int i)
{
    flag = (i >= 0) ? false : true;
    digits = (i >= 0) ? std::to_string(i) : std::to_string(-i);
    reverse = digits;
    std::reverse(reverse.begin(), reverse.end());


}

BigInt::BigInt(string n)
{
    flag = (n.front() == '-') ? true: false;
    digits = (n.front() == '-') ? n.substr(1, n.size() - 1) : n;  
    reverse = digits;
    std::reverse(reverse.begin(), reverse.end());

}

std::string BigInt::to_string() const {
    std::string str = digits;
    
    // Remove leading zeros except for a single zero
    while (str.size() > 1 && str[0] == '0') {
        str.erase(str.begin());
    }

    return (flag && str != "0") ? "-" + str : str;
}

BigInt::BigInt(string n, bool b)
{
    flag = b;
    digits = (n.front() == '-') ? n.substr(1, n.size() - 1) : n;  
    reverse = digits;
    std::reverse(reverse.begin(), reverse.end());
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

BigInt BigInt::operator+(const BigInt& b2) const {
    BigInt b1(digits, flag);
    int carry = 0;
    int max_digits = max(b1.digits.length(), b2.digits.length());
    string s(max_digits + 1, '0');

    if (b1.flag == b2.flag) {
        for (int i = 0; i < max_digits || carry; i++) {
            int i1 = (i < b1.digits.size()) ? b1.digits[b1.digits.size() - 1 - i] - '0' : 0;
            int i2 = (i < b2.digits.size()) ? b2.digits[b2.digits.size() - 1 - i] - '0' : 0;

            int sum = i1 + i2 + carry;
            carry = sum / 10;
            s[max_digits - i] = (sum % 10) + '0';
        }
        if (carry) s.insert(s.begin(), '1');
        return BigInt(s, b1.flag);
    } else {
        return (*this - BigInt(b2.digits, !b2.flag));
    }
}

BigInt BigInt::operator-(const BigInt& b2) const {
    if (flag != b2.flag) { // -a - b || a - -b (always neg/pos no possibility of anything else)
        return *this + BigInt(b2.digits, !b2.flag); // Convert subtraction to addition if opposite signs
    }
    //Possiblity of either pos or neg -a - -b || a - b
    //Therefore i need to ensure that the largest is identified
    bool negateResult = flag; //By default assume that a is larger
    BigInt larger = *this, smaller = b2;

    if (larger < smaller) {  // Flip operands if necessary
        std::swap(larger, smaller);
        negateResult = !flag; //If we are wrong then we need to have values swapped for flag
    }

    std::string result; //will carry result in char in normal order meaing it needs to be reversed
    int carry = 0;
    //If we know which is the largest then we can evaluate it as largest - smaller and then set the flag as pos or neg
    //Ex if we know that -a - (-b) will be pos then b(larg) - a(small) is the same thing and we know not to worry about whether a is enough to make it neg
    int i = larger.digits.size() - 1, j = smaller.digits.size() - 1; //reduce by one as least sig are at highest index val
    while (i >= 0) {
        int dl = larger.digits[i] - '0'; //convert char to int
        int ds = (j >= 0) ? smaller.digits[j] - '0' : 0; //makes ds 0 if no more num to sub

        if (dl < ds + carry) {
            ds += 10;
            result += (dl - ds - carry) + '0'; //add zero or sub to convert between char and int
            carry = 1;
        } else {
            result += (dl - ds - carry) + '0';
            carry = 0;
        }

        i--;
        j--;
    }

    std::reverse(result.begin(), result.end());
    
    // Ensure that zeros are trimmed
    while (result.size() > 1 && result[0] == '0') {
        result.erase(result.begin());
    }

    return BigInt(result, negateResult);
}



BigInt BigInt::operator*(const BigInt& mult)const {
    BigInt b1(digits, flag);
    int max_digits = 100;
    double count = 0;
    string s(max_digits, ' ');
    BigInt temp(b1.digits, false);

    //We want to use the regular BigInt mult with ints for the bigint mult by bigint
    //something like temp=int(mult.digits[i]*10^c + temp)
    for(int i = 1; i < mult.digits.length(); i++) {
        for(int j =0; j < mult.digits[count];j++) {
            temp = (BigInt(temp.digits, false) + (BigInt(b1.digits, false)*pow(10.0,count)));
        }
        count++;
    }

    return (b1.flag == mult.flag) ? BigInt(temp.digits, false): BigInt(temp.digits,true);
    
}
BigInt BigInt::operator*(int mult)const {
    BigInt b1(digits, flag);
    int max_digits = 100;
    string s(max_digits, ' ');
    BigInt temp(b1);

    for(int i = 1; i < mult; i++) {
        temp = (temp + b1);
    }
    return temp;
}