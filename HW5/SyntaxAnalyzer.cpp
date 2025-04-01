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

bool whilestmt(vector<string> lexemes, vector<string> tokens,
               vector<string>::iterator lexitr, vector<string>::iterator tokitr) {
    if (tokitr != lexemes.end() && *tokitr == "t_while") {
        ++tokitr;++lexitr;
        if (tokitr != lexemes.end() && *tokitr == "s_lparen") {
            ++tokitr;++lexitr;
            if (tokitr != lexemes.end() && expr(lexemes, tokens, lexitr, tokitr)) {
                ++tokitr;++lexitr;
                if (tokitr != lexemes.end() && *tokitr == "s_rparen") {
                    ++tokitr;++lexitr;
                    if (tokitr != lexemes.end && *tokitr == "s_lbrace") {
                        ++tokitr;++lexitr;
                        if (tokitr != lexemes.end() && stmtlist(lexemes, tokens, lexitr, tokitr)) {
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

bool inputstmt(vector<string> lexemes, vector<string> tokens,
               vector<string>::iterator lexitr, vector<string>::iterator tokitr) {
    if (tokitr != lexemes.end() && *tokitr == "t_input") {
        ++tokitr;
        ++lexitr;
        if (tokitr != lexemes.end() && *tokitr == "s_lparen") {
            ++tokitr;
            ++lexitr;
            if (tokitr != lexemes.end() && *tokitr == "t_id") {
                ++tokitr;
                ++lexitr;
                if (tokitr != lexemes.end() && *tokitr == "s_rparen") {
                    ++tokitr;
                    ++lexitr;
                    if (tokitr == lexemes.end()) {
                        tokitr--;
                        lexitr--;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

bool outputstmt(vector<string> lexemes, vector<string> tokens,
                vector<string>::iterator lexitr, vector<string>::iterator tokitr) {
    if (tokitr != lexemes.end() && *tokitr == "t_output") {
        ++tokitr;
        ++lexitr;
        if (tokitr != lexemes.end() && *tokitr == "s_lparen") {
            ++tokitr;
            ++lexitr;
            if (tokitr != lexemes.end() && expr(lexemes, tokens, lexitr, tokitr)) {
                ++tokitr;
                ++lexitr;
                if (tokitr != lexemes.end() && *tokitr == "s_rparen") {
                    ++tokitr;
                    ++lexitr;
                    if (tokitr == tokens.end()) {
                        tokitr--;
                        tokitr--;
                    }
                    return true;
                }
            } else if (tokitr != lexemes.end() && *tokitr == "t_text") {
                ++tokitr;
                ++lexitr;
                if (tokitr != lexemes.end() && *tokitr == "s_lparen") {
                    ++tokitr;
                    ++lexitr;
                    if (tokitr == tokens.end()) {
                        tokitr--;
                        tokitr--;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

bool simpleexpr(vector<string> lexemes, vector<string> tokens, vector<string>::iterator lexitr,
                vector<string>::iterator tokitr) {
    if (tokitr != lexemes.end() && term(lexemes, tokens, lexitr, tokitr)) {
        ++tokitr;
        ++lexitr;
        int count = 0;
        while (count < 1) {
            if (arithop(lexemes, tokens, lexitr, tokitr)) {
                ++tokitr;
                ++lexitr;
                if (tokitr != lexemes.end() && term(lexemes, tokens, lexitr, tokitr)) {
                    ++tokitr;
                    ++lexitr;
                    if (tokitr == tokens.end()) {
                        --tokitr;
                        --lexitr;
                    }
                    ++count;
                    return true;
                }
            } else if (relop(lexemes, tokens, lexitr, tokitr)) {
                ++tokitr;
                ++lexitr;
                if (tokitr != lexemes.end() && term(lexemes, tokens, lexitr, tokitr)) {
                    ++tokitr;
                    ++lexitr;
                    if (tokitr == tokens.end()) {
                        --tokitr;
                        --lexitr;
                    }
                    ++count;
                    return true;
                }
            } else {
                count++;
                return false;
            }
        }
    }
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
