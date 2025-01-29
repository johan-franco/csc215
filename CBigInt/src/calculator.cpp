#include <iostream>
#include <string>
using namespace std;

enum OpType { ADD, SUBSTRACT, MULTIPLY, STOP, ILLEGAL_OP };


OpType string_to_op(const string &s) {
    if (s == "+") return ADD;
    if (s == "-") return SUBSTRACT;
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
    int accumulator = 0;
    int current;
    OpType op = ADD;

    while (op != STOP) {
        cout << "Enter value: ";
        cin >> current;
        switch (op) {
            case ADD:
                accumulator += current;
                break;
            case SUBSTRACT:
                accumulator -= current;
            case MULTIPLY:
                accumulator *= current;
                break;
            default:
                cerr << "Error with operator" << endl;
        }
        cout << "--> " << accumulator << endl;
        op = get_op();
    }
    cout << "Final Total: " << accumulator << endl;

    return 0;
}
