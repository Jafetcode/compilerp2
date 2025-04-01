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

// jacob section
bool SyntaxAnalyzer::vdecassign() {
    // TYPE id = EXPR;
    if (tokitr != tokens.end()) {
        if (*tokitr == "t_integer" || *tokitr == "t_string") {
            string test = *lexitr;
            ++tokitr; ++lexitr;
            if (tokitr != tokens.end() && *tokitr == "t_id") {
                // makes only one variable be in the list at once.
                if (!symboltable.contains(*lexitr)) {
                    symboltable.insert(make_pair(*lexitr, test));
                }
                ++tokitr; ++lexitr;

                if (tokitr != tokens.end() && *tokitr == "s_assign") {
                    ++tokitr; ++lexitr;
                    if (expr()) { // expr should move up after it is done
                        if (tokitr != tokens.end() && *tokitr == "s_semi") {
                            ++tokitr; ++lexitr;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
} // jacob
bool SyntaxAnalyzer::ifstmt() {
    // if (EXPR) { STMTLIST } ELSEPART
    if (tokitr != tokens.end()) {
        if (*tokitr == "t_if") {
            ++tokitr; ++lexitr;
            if (tokitr != tokens.end() && *tokitr == "s_lparen") {
                ++tokitr; ++lexitr;
                if (expr()) {
                    if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                        ++tokitr; ++lexitr;
                        if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
                            ++tokitr; ++lexitr;
                            if (stmtlist()) {
                                if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                                    ++tokitr; ++lexitr;
                                    if (elsepart()) {
                                        ++tokitr; ++lexitr;
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
} // jacob
bool SyntaxAnalyzer::elsepart() {
    // else { STMTLIST } | null
    if (tokitr != tokens.end() && *tokitr == "t_else") {
        ++tokitr; ++lexitr;
        if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
            ++tokitr; ++lexitr;
            if (stmtlist()) {
                if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                    ++tokitr; ++lexitr;
                    return true;
                }
            }
        }
        return false;
    }
    return true;
} // jacob
bool SyntaxAnalyzer::assignstmt() {
    // id = EXPR;
    if (tokitr != tokens.end()) {
        if (*tokitr == "t_id" && symboltable.contains(*lexitr)) {
            if (tokitr != tokens.end() && *tokitr == "s_assign") {
                ++tokitr; ++lexitr;
                if (expr()) {
                    if (tokitr != tokens.end() && *tokitr == "s_semi") {
                        ++tokitr; ++lexitr;
                        return true;
                    }
                }
            }
        }
    }
    return false;
} // jacob
bool SyntaxAnalyzer::relop() {
    if (tokitr != tokens.end()) {
        if (*tokitr == "s_lt" || *tokitr == "s_gt" || *tokitr == "s_eq" ||*tokitr == "s_ne") {
            ++tokitr; ++lexitr;
            return true;
        }
    }
    return false;
} // jacob
bool SyntaxAnalyzer::typecheck(const string& type1) {
    if (type1 == symboltable[*lexitr]) {
        return true;
    }
    return false;
} // jacob
// end of jacob section
