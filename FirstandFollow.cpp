#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<char, vector<string>> grammar = {
    {'S', {"ACB", "Cbb", "Ba"}},
    {'A', {"da", "BC"}},
    {'B', {"g", "e"}},
    {'C', {"h", "e"}}
};


map<char, set<char>> firstSets;
map<char, set<char>> followSets;

set<char> calculateFirst(char nonTerminal) {
    set<char> firstSet;
    for (string production : grammar[nonTerminal]) {
        if (production == "e") {
            firstSet.insert('e');
        } else {
            for (char symbol : production) {
                if (!grammar.count(symbol)) {
                    firstSet.insert(symbol);
                    break;
                } else {
                    set<char> subFirstSet = calculateFirst(symbol);
                    firstSet.insert(subFirstSet.begin(), subFirstSet.end());
                    if (!subFirstSet.count('e')) {
                        break;
                    }
                    if (symbol == production.back() && subFirstSet.count('e')) {
                        firstSet.insert('e');
                    }
                }
            }
        }
    }

    return firstSet;
}

void calculateFirstSets() {
    for (const auto& pair : grammar) {
        char nonTerminal = pair.first;
        firstSets[nonTerminal] = calculateFirst(nonTerminal);
    }

    bool changed;
    do {
        changed = false;
        for (const auto& pair : grammar) {
            char nonTerminal = pair.first;
            set<char> oldFirstSet = firstSets[nonTerminal];
            set<char> newFirstSet = calculateFirst(nonTerminal);
            if (oldFirstSet != newFirstSet) {
                firstSets[nonTerminal] = newFirstSet;
                changed = true;
            }
        }
    } while (changed);
}

void calculateFollowSets() {
    followSets['S'].insert('$');

    bool changed;
    do {
        changed = false;
        for (const auto& pair : grammar) {
            char nonTerminal = pair.first;
            for (const string& production : pair.second) {
                set<char> followSet = followSets[nonTerminal];
                for (int i = production.size() - 1; i >= 0; --i) {
                    if (grammar.count(production[i])) { 
                        set<char> oldFollowSet = followSets[production[i]];
                        followSets[production[i]].insert(followSet.begin(), followSet.end());
                        if (oldFollowSet != followSets[production[i]]) {
                            changed = true;
                        }
                        if (firstSets[production[i]].count('e')) {
                            followSet.insert(firstSets[production[i]].begin(), firstSets[production[i]].end());
                            followSet.erase('e');
                        } else {
                            followSet = firstSets[production[i]];
                        }
                    } else { 
                        followSet = {production[i]};
                    }
                }
            }
        }
    } while (changed);
}
int main() {
    calculateFirstSets();
    calculateFollowSets();

    for (const auto& pair : firstSets) {
        cout << "FIRST(" << pair.first << ") = { ";
        for (char symbol : pair.second) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }

    for (const auto& pair : followSets) {
        cout << "FOLLOW(" << pair.first << ") = { ";
        for (char symbol : pair.second) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }

    return 0;
}