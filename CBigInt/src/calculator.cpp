#include <iostream>
#include <string>
#include "BigInt.cpp"  
using namespace std;

enum OpType { ADD, SUBTRACT, MULTIPLY, STOP, ILLEGAL_OP };

OpType string_to_op(const string &s) {
    if (s == "+") return ADD;
    if (s == "-") return SUBTRACT;
    if (s == "*") return MULTIPLY;
    if (s == "=") return STOP;
    return ILLEGAL_OP;
}

OpType get_op() {
    string s;
    OpType op;
    do {
        cout << "Enter + - * (or = to quit): ";
        cin >> s;
    } while ((op = string_to_op(s)) == ILLEGAL_OP);
    
    return op;
}

int main() {
    BigInt accumulator("0");  
    BigInt current("0");    
    OpType op = ADD;

    while (op != STOP) {
        cout << "Enter value: ";
        string input;
        cin >> input;
        current = BigInt(input);  
        
        switch (op) {
            case ADD:
                accumulator = accumulator + current;  
                break;
            case SUBTRACT:
                accumulator = accumulator - current;  
                break;
            case MULTIPLY:
                accumulator = accumulator * current; 
                break;
            default:
                cerr << "Error with operator" << endl;
        }
        cout << "--> " << accumulator.to_string() << endl; 
        op = get_op(); 
    }
    cout << "Final Total: " << accumulator.to_string() << endl; 

    return 0;
}
