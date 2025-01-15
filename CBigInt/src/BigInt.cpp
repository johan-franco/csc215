#include <iostream>
#include <string>
#include "BigInt.h"
using namespace std;

BigInt::BigInt()
{
    negative = false;
    digits = "0";
}

BigInt::BigInt(int i)
{
    negative = (i >= 0) ? false : true;
    digits = (i >= 0) ? std::to_string(i) : std::to_string(-i);
}

BigInt::BigInt(string n)
{
    negative = (n.front() == '-') ? true: false;
    digits = (n.front() == '-') ? n.substr(1, n.size() - 1) : n;
}

string BigInt::to_string() const
{
    return (!negative) ? digits : "-" + digits;
}

BigInt::BigInt(string n, bool b)
{
    negative = b;
    digits = n;
}
bool BigInt::operator==(const BigInt& i2) const
{
    BigInt b1 = BigInt(digits, negative);
    if (stoi(b1.to_string()) == stoi(i2.to_string()))
        return true;
    else
        return false;
}

