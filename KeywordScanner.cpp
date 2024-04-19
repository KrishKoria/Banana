#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

vector<string> cKeywords = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while",
    };
vector<string> tokenize(const string& str) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    string delimiters = " \t\n\r\f\v!#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

    bool insideQuotes = false;

    while (getline(ss, token, ' ')) {
        size_t start = 0;
        size_t found;

        if (token.front() == (char)34) {
            insideQuotes = true;
        }

        if (token.back() == (char)34) {
            insideQuotes = false;
        }

        if (insideQuotes) {
            tokens.push_back(token);
        } else {
            size_t pos = token.find("//");
            if (pos != string::npos) {
                // If a comment is found, stop processing the line
                break;
            }

            while ((found = token.find_first_of(delimiters, start)) != string::npos) {
                if (found > start) {
                    tokens.push_back(token.substr(start, found - start));
                }

                tokens.push_back(string(1, token[found]));

                start = found + 1;
            }

            if (start < token.length()) {
                tokens.push_back(token.substr(start));
            }
        }
    }

    tokens.erase(remove_if(tokens.begin(), tokens.end(), [](const string& s) { return s.empty(); }), tokens.end());

    return tokens;
}



bool isCppKeyword(const string& word) {
    string lowercaseWord = word;
    transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);
    return find(cKeywords.begin(), cKeywords.end(), lowercaseWord) != cKeywords.end();
}


int main() {
    ifstream fin("input.txt");
    vector<string> array;
    vector<string> vectorElement;
    string s;
    vector<string> allElements;
    if (!fin.is_open()) {
        cout << "File not found" << endl;
        return 1;
    }

    string line;
    while (getline(fin, line, '\n')) {
        size_t posSingleLine = line.find("//");
        size_t posMultiLineStart = line.find("/*");

        if (posSingleLine != string::npos) {
            line.erase(posSingleLine);
        }

        if (posMultiLineStart != string::npos) {
            size_t endPos = line.find("*/", posMultiLineStart);
            if (endPos != string::npos) {
                line.erase(posMultiLineStart, endPos - posMultiLineStart + 2);
            }
        }

        array.push_back(line);
    }

    for (const auto& line : array) {
        vector<string> vectorElement = tokenize(line);
        allElements.insert(allElements.end(), vectorElement.begin(), vectorElement.end());
        }
    for (const auto& x : allElements) {
        if(isCppKeyword(x)){
            cout << x << " "<<" is a Keyword" <<  endl;
        } else if(!isalnum(x[0])){
            continue;
        } else if(isdigit(x[0])){
            cout << x << " " << "is a number" << endl;
        } else {
            cout << x  << " " << "is an identifier "<< endl;
        }
    }
    fin.close();
    return 0;
}

