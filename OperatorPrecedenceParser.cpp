#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isOperand(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int getPrecedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else
        return 0;
}

bool canBeParsed(const string& expression) {
    stack<char> parentheses;
    bool lastWasOperator = true;

    for (char c : expression) {
        if (c == '(') {
            parentheses.push(c);
            lastWasOperator = true;
        } else if (c == ')') {
            if (parentheses.empty() || lastWasOperator) {
                return false;
            }
            parentheses.pop();
            lastWasOperator = false;
        } else if (isOperator(c)) {
            if (lastWasOperator) {
                return false;
            }
            lastWasOperator = true;
        } else if (isOperand(c)) {
            lastWasOperator = false;
        } else {
            return false;
        }
    }

    return parentheses.empty() && !lastWasOperator;
}

int main() {
    string expression;
    cout << "Enter an expression: ";
    cin >> expression;

    if (canBeParsed(expression)) {
        cout << "The expression is parseable." << endl;
    } else {
        cout << "The expression cannot be parsed." << endl;
    }

    return 0;
}