#include <bits/stdc++.h>

using namespace std;

// Define your grammar rules here
vector<pair<char, string>> grammarRules = {{'S', "AA"}, {'A', "aA"}, {'A', "b"}};

// Define your parsing table here
vector<vector<string>> parsingTable = {{"S3", "S4", "", "1", "2"}, {"", "", "accept", "", ""}, {"S6", "S7", "", "", "5"}, {"S3", "S4", "", "", "8"}, {"R3", "R3", "", "", ""}, {"", "", "R1", "", ""}, {"S6", "S7", "", "", "9"}, {"", "", "R3", "", ""}, {"R2", "R2", "", "", ""}, {"", "", "R2", "", ""}};

// Function to perform CLR(1) parsing
void parse(string input)
{
    stack<char> symbolStack;
    stack<int> stateStack;
    int currentState = 0;
    int inputIndex = 0;

    // Push initial state and start symbol onto the state and symbol stacks
    stateStack.push(currentState);
    symbolStack.push('$'); // Start symbol

    cout << "Parsing Input: " << input << endl;

    while (!symbolStack.empty())
    {
        char currentSymbol = input[inputIndex];

        // Get the action from the parsing table based on the current state and input symbol
        string action = parsingTable[currentState][currentSymbol - 'a'];

        cout << "Current State: " << currentState << ", Input Symbol: " << currentSymbol << ", Action: " << action << endl;

        if (action[0] == 'S')
        {
            // Shift the input symbol onto the symbol stack and move to the next state
            symbolStack.push(input[inputIndex]);
            stateStack.push(currentState);
            currentState = stoi(action.substr(1));
            inputIndex++;
        }
        else if (action[0] == 'R')
        {
            // Reduce by applying the grammar rule
            int productionNumber = stoi(action.substr(1));
            char nonTerminal = grammarRules[productionNumber].first;
            string production = grammarRules[productionNumber].second;

            // Pop symbols from the symbol stack and state stack based on the length of the production
            for (size_t i = 0; i < production.length(); i++)
            {
                symbolStack.pop();
                stateStack.pop();
            }

            // Push the non-terminal symbol onto the symbol stack
            symbolStack.push(nonTerminal);

            // Get the new state from the goto table based on the current state and non-terminal symbol
            currentState = stoi(parsingTable[stateStack.top()][nonTerminal - 'A']);
        }
        else if (action == "accept")
        {
            // Parsing is successful
            cout << "Input accepted!" << endl;
            return;
        }
        else
        {
            // Error occurred
            cout << "Error occurred!" << endl;
            return;
        }
    }

    // Parsing failed
    cout << "Input rejected!" << endl;
}

int main()
{
    string input;
    cout << "Enter input string: ";
    cin >> input;

    parse(input);

    return 0;
}
