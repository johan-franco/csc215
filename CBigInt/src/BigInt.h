#include <algorithm> 
#include<iostream>
#include<string>
using namespace std;

class BigInt 
{
    bool flag;
    string digits;

    public:
    // constructors
    BigInt();
    BigInt(int);
    BigInt(string);
    BigInt(string n, bool b);


    // helper functions
    BigInt sum_common_digits(const BigInt&) const;

    // member functions
    string to_string() const;
    bool operator==(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>=(const BigInt&) const;
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
};
