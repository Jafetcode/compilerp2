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

SyntaxAnalyzer::SyntaxAnalyzer(istream &infile) {
    string wordPair;
    while (getline(infile, wordPair)) {
        unsigned int pos = wordPair.find(" : ");
        string token = wordPair.substr(0, pos);
        string lex = wordPair.substr(pos + 1, wordPair.size());
        lexemes.push_back(lex);
        tokens.push_back(token);
    }
}

bool SyntaxAnalyzer::parse() {
    if (tokitr != tokens.end() && *tokitr  == "t_main") {
        tokitr++;lexitr++;
        if (tokitr!=tokens.end() && *tokitr  == "s_lbrace") {
            tokitr++; lexitr++;
            if (stmtlist()) {
                if (tokitr!=tokens.end() && *tokitr  == "s_rbrace") {
                    tokitr++; lexitr++;
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
    if (tokitr != lexemes.end() && *tokitr == "t_while") {
        ++tokitr;++lexitr;
        if (tokitr != lexemes.end() && *tokitr == "s_lparen") {
            ++tokitr;++lexitr;
            if (tokitr != lexemes.end() && expr()) {
                ++tokitr;++lexitr;
                if (tokitr != lexemes.end() && *tokitr == "s_rparen") {
                    ++tokitr;++lexitr;
                    if (tokitr != lexemes.end && *tokitr == "s_lbrace") {
                        ++tokitr;++lexitr;
                        if (tokitr != lexemes.end() && stmtlist()) {
                            ++tokitr;++lexitr;
                            if (tokitr != lexemes.end() && *tokitr == "s_rbrace") {
                                ++tokitr;++lexitr;
                                return true;
                            } else {
                                cout << "error in source code" << endl;
                            }
                        } else {
                            cout << "error in source code" << endl;
                        }
                    } else {
                        cout << "error in source code" << endl;
                    }
                } else {
                    cout << "error in source code" << endl;
                }
            } else {
                cout << "error in source code" << endl;
            }
        } else {
            cout << "error in source code" << endl;
        }
    } else {
        cout << "error in source code" << endl;
    }
    return false;
}

bool SyntaxAnalyzer::inputstmt() {
    if (tokitr != lexemes.end() && *tokitr == "t_input") {
        ++tokitr;++lexitr;
        if (tokitr != lexemes.end() && *tokitr == "s_lparen") {
            ++tokitr;++lexitr;
            if (tokitr != lexemes.end() && *tokitr == "t_id") {
                ++tokitr;++lexitr;
                if (tokitr != lexemes.end() && *tokitr == "s_rparen") {
                    ++tokitr;++lexitr;
                    if (tokitr == lexemes.end()) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool SyntaxAnalyzer::outputstmt() {
    if (tokitr != lexemes.end() && *tokitr == "t_output") {
        ++tokitr;++lexitr;
        if (tokitr != lexemes.end() && *tokitr == "s_lparen") {
            ++tokitr;++lexitr;
            if (tokitr != lexemes.end() && expr()) {
                ++tokitr;++lexitr;
                if (tokitr != lexemes.end() && *tokitr == "s_rparen") {
                    ++tokitr;++lexitr;
                    if (tokitr == tokens.end()) {
                        tokitr--;tokitr--;
                    }
                    return true;
                }
            } else if (tokitr != lexemes.end() && *tokitr == "t_text") {
                ++tokitr;++lexitr;
                if (tokitr != lexemes.end() && *tokitr == "s_lparen") {
                    ++tokitr;++lexitr;
                    if (tokitr == tokens.end()) {
                        tokitr--;tokitr--;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

bool SyntaxAnalyzer::simpleexpr() {
    if (tokitr != lexemes.end() && term()) {
        ++tokitr;++lexitr;
            if (arithop()) {
                ++tokitr;++lexitr;
                if (tokitr != lexemes.end() && term()) {
                    ++tokitr;++lexitr;
                    if (tokitr == tokens.end()) {
                        --tokitr;--lexitr;
                    }
                    return true;
                }
            } else if (relop()) {
                ++tokitr;++lexitr;
                if (tokitr != lexemes.end() && term()) {
                    ++tokitr;++lexitr;
                    if (tokitr == tokens.end()) {
                        --tokitr;--lexitr;
                    }
                    return true;
                }
            } else {
                return true;
            }
        }
    return false;
    }

bool logicop(vector<string> lexemes, vector<string> tokens, vector<string>::iterator lexitr,
             vector<string>::iterator tokitr) {
    if (tokitr != lexemes.end() && *tokitr == "t_and") {
        ++tokitr;
        ++lexitr;
        if (tokitr == tokens.end()) {
            tokitr--;
            lexitr--;
        }
        return true;
    } else if (tokitr != lexemes.end() && *tokitr == "t_or") {
        ++tokitr;
        ++lexitr;
        if (tokitr == tokens.end()) {
            tokitr--;
            lexitr--;
        }
        return true;
    } else {
        return false;
    }
}
