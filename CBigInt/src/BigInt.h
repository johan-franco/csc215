#include <string>
using namespace std;

class BigInt
{
    bool negative;
    string digits;

    public:
    // constructors
    BigInt();
    BigInt(int);
    BigInt(string);
    BigInt(string, bool);

    // member functions
    string to_string() const;

    bool operator==(const BigInt&) const;
};