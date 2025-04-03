#include "SyntaxAnalyzer.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int main() {
    vector<string> lexemes;
    vector<string> tokens;
    vector<string>::iterator lexitr;
    vector<string>::iterator tokitr;

    map<string, string> symboltable;
}

//Method written as a group
SyntaxAnalyzer::SyntaxAnalyzer(istream &infile) {
    string wordPair;
    while (getline(infile, wordPair)) {
        unsigned int pos = wordPair.find(" : ");
        string token = wordPair.substr(0, pos);
        string lex = wordPair.substr(pos + 3, wordPair.size());
        lexemes.push_back(lex);
        tokens.push_back(token);
    }
    tokitr = tokens.begin();
    lexitr = lexemes.begin();
}

//Method written as a group
bool SyntaxAnalyzer::parse() {
    if (tokitr != tokens.end() && *tokitr == "t_main") {
        tokitr++;
        lexitr++;
        if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
            tokitr++;
            lexitr++;
            if (stmtlist()) {
                if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                    tokitr++;
                    lexitr++;
                    if (tokitr == tokens.end()) {
                        return true;
                    }
                }
            }
        }
    }
    cout << *tokitr << " " << *lexitr << endl;
    return false;
}


bool SyntaxAnalyzer::whilestmt() {
    if (tokitr != tokens.end() && *tokitr == "s_lparen") {
        ++tokitr;
        ++lexitr;
        if (tokitr != tokens.end() && expr()) {
            ++tokitr;
            ++lexitr;
            if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                ++tokitr;
                ++lexitr;
                if (tokitr != lexemes.end && *tokitr == "s_lbrace") {
                    ++tokitr;
                    ++lexitr;
                    if (tokitr != tokens.end() && stmtlist()) {
                        ++tokitr;
                        ++lexitr;
                        if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                            ++tokitr;
                            ++lexitr;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool SyntaxAnalyzer::inputstmt() {
    if (tokitr != tokens.end() && *tokitr == "s_lparen") {
        ++tokitr;
        ++lexitr;
        if (tokitr != tokens.end() && *tokitr == "t_id") {
            if (symboltable.contains(*tokitr)) {
                ++tokitr;
                ++lexitr;
                if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                    ++tokitr;
                    ++lexitr;
                    if (tokitr == tokens.end()) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool SyntaxAnalyzer::outputstmt() {
    if (tokitr != tokens.end() && *tokitr == "s_lparen") {
        ++tokitr;
        ++lexitr;
        if (tokitr != tokens.end() && expr()) {
            ++tokitr;
            ++lexitr;
            if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                ++tokitr;
                ++lexitr;

                return true;
            }
        } else if (tokitr != tokens.end() && *tokitr == "t_text") {
            ++tokitr;
            ++lexitr;
            if (tokitr != tokens.end() && *tokitr == "s_lparen") {
                ++tokitr;
                ++lexitr;
                return true;
            }
        }
    }
    return false;
}

bool SyntaxAnalyzer::simpleexpr() {
    if (tokitr != tokens.end() && term()) {
        ++tokitr;
        ++lexitr;
        if (arithop()) {
            ++tokitr;
            ++lexitr;
            if (tokitr != tokens.end() && term()) {
                ++tokitr;
                ++lexitr;
                if (tokitr == tokens.end()) {
                    --tokitr;
                    --lexitr;
                }
                return true;
            }
        } else if (relop()) {
            ++tokitr;
            ++lexitr;
            if (tokitr != tokens.end() && term()) {
                ++tokitr;
                ++lexitr;
                if (tokitr == tokens.end()) {
                    --tokitr;
                    --lexitr;
                }
                return true;
            }
        } else {
            return true;
        }
    }
    return false;
}

bool SyntaxAnalyzer::logicop() {
    if (tokitr != tokens.end() && *tokitr == "t_and") {
        ++tokitr;
        ++lexitr;
        if (tokitr == tokens.end()) {
            tokitr--;
            lexitr--;
        }
        return true;
    }
    if (tokitr != tokens.end() && *tokitr == "t_or") {
        ++tokitr;
        ++lexitr;
        return true;
    }
    return false;
}
