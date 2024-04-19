#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;


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
int main() {
    ifstream fin("input.txt");
    vector<string> array;
    int tokenCount = 0;

    if (!fin.is_open()) {
        cout << "File not found" << endl;
        return 1;
    }

    string line;
    while (getline(fin, line, '\n')) {
        size_t pos = line.find("//");
        if (pos != string::npos) {
            line.erase(pos);
        }

        pos = line.find("/*");
        if (pos != string::npos) {
            size_t endPos = line.find("*/", pos);
            if (endPos != string::npos) {
                line.erase(pos, endPos - pos + 2);
            }
        }

        array.push_back(line);
    }
    // for (const auto& x : array) {
    //     cout << x << endl;
    // }
    for (const auto& line : array) {
        vector<string> vectorElement = tokenize(line);
        tokenCount += vectorElement.size();
    }

    cout << "Total number of tokens: " << tokenCount << endl;

    

    fin.close();
    return 0;
}













