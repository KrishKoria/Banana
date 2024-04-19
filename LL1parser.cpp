#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
map<char, vector<string>> grammar = {
    {'S', {"A$"}},
    {'A', {"xYzS", "a"}},
    {'Y', {"xYz", "y"}}};

map<char, set<char>> followSets;

set<char> first(char symbol)
{
    set<char> result;

    if (!grammar.count(symbol))
    {
        result.insert(symbol);
    }
    else
    {
        for (const string &production : grammar[symbol])
        {
            if (!grammar.count(production[0]))
            {
                result.insert(production[0]);
            }
            else
            {
                set<char> firstSet = first(production[0]);
                result.insert(firstSet.begin(), firstSet.end());
            }
        }
    }

    return result;
}

void calculateFollowSets()
{
    followSets['S'].insert('$');

    for (const auto &pair : grammar)
    {
        for (const string &production : pair.second)
        {
            for (size_t i = 0; i < production.size(); ++i)
            {
                if (grammar.count(production[i]) && i + 1 < production.size())
                {
                    if (!grammar.count(production[i + 1]))
                    {
                        followSets[production[i]].insert(production[i + 1]);
                    }
                    else
                    {
                        set<char> firstSet = first(production[i + 1]);
                        followSets[production[i]].insert(firstSet.begin(), firstSet.end());
                    }
                }
            }
        }
    }
    for (const auto &pair : grammar)
    {
        char nonTerminal = pair.first;
        for (const string &production : pair.second)
        {
            for (size_t i = 0; i < production.size(); ++i)
            {
                if (grammar.count(production[i]) && i + 1 < production.size())
                {
                    if (grammar.count(production[i + 1]))
                    {
                        set<char> followSet = followSets[nonTerminal];
                        followSets[production[i]].insert(followSet.begin(), followSet.end());
                    }
                }
            }
        }
    }
}

int main()
{
    for (const auto &pair : grammar)
    {
        set<char> firstSet = first(pair.first);
        cout << "FIRST(" << pair.first << ") = { ";
        for (char symbol : firstSet)
        {
            cout << symbol << " ";
        }
        cout << "}\n";
    }

    calculateFollowSets();
    for (const auto &pair : followSets)
    {
        cout << "FOLLOW(" << pair.first << ") = { ";
        for (char symbol : pair.second)
        {
            cout << symbol << " ";
        }
        cout << "}\n";
    }

    return 0;
}