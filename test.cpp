#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class CLR1Parser
{
public:
    CLR1Parser(const vector<string> &grammar)
    {
        this->grammar = grammar;
    }

    bool parse(const string &input)
    {
    }

private:
    // The grammar rules.
    vector<string> grammar;

    // The parsing table.
    vector<vector<int>> parsingTable;

    // The stack of states.
    stack<int> stateStack;

    // The input buffer.
    string inputBuffer;

    // The current input symbol.
    char currentSymbol;

    // Parse the next symbol in the input buffer.
    void parseNextSymbol()
    {
        // Get the next symbol from the input buffer.
        currentSymbol = inputBuffer[0];

        // Shift the current symbol onto the stack.
        stateStack.push(parsingTable[stateStack.top()][currentSymbol]);

        // Remove the current symbol from the input buffer.
        inputBuffer.erase(inputBuffer.begin());
    }

    // Reduce the current stack state using the given production rule.
    void reduce(const string &productionRule)
    {
        // Get the number of symbols on the right-hand side of the production rule.
        int numSymbols = productionRule.size() - 1;

        // Pop the symbols from the stack.
        for (int i = 0; i < numSymbols; i++)
        {
            stateStack.pop();
        }

        // Get the state to go to next.
        int nextState = parsingTable[stateStack.top()][productionRule[0]];

        // Push the next state onto the stack.
        stateStack.push(nextState);
    }

    // Accept the input.
    void accept()
    {
        // The input is accepted if the stack is empty and the current symbol is the end-of-file symbol.
        if (stateStack.empty() && currentSymbol == '$')
        {
            cout << "Input accepted." << endl;
        }
        else
        {
            cout << "Input rejected." << endl;
        }
    }
};

int main()
{
    // Create the grammar.
    vector<string> grammar = {
        "S -> E $",
        "E -> T E'",
        "E' -> + T E' | ε",
        "T -> F T'",
        "T' -> * F T' | ε",
        "F -> ( E ) | id"};

    // Create the parser.
    CLR1Parser parser(grammar);

    // Parse the input string.
    // string input = "id + id * id $";
    string input = "banana";
    bool accepted = parser.parse(input);

    // Print the result.
    if (accepted)
    {
        cout << "Input accepted." << endl;
    }
    else
    {
        cout << "Input rejected." << endl;
    }

    return 0;
}