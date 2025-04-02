//
// Created by Abraham Hernandez on 4/1/25.
//

#include "SynAnalyzer.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

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
        ++tokitr; ++lexitr;
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
// Start of Abraham's Section
bool SyntaxAnalyzer::stmtlist() { // STMTLIST → STMT [STMT]m | Ø
    int result = stmt();
    while (result != -1) {
        result = stmt();
    }
    return true;
}
int SyntaxAnalyzer::stmt() {
    if (tokitr != lexemes.end() && *tokitr == "t_if") {
        tokitr++; lexitr++;
        if (!ifstmt()){ //check if it is a boolean since wwe are returning integer
            //checking if they are true
            return 0; //0 means this statement isn't valid/does not apply here
        } else {
            return 1; //1 means valid
        }
    }
    if (tokitr != lexemes.end() && *tokitr == "t_while") {
        tokitr++; lexitr++;
        if (!whilestmt()) {
            return 0;
        }
        else {
            return 1;
        }
    }
    if (tokitr != lexemes.end() && *tokitr == "t_assign") {
        tokitr++; lexitr++; //start with an id
        if (!assignstmt()) {
            return 0;
        }
        else {
            return 1;
        }

    }
    if (tokitr != lexemes.end() && *tokitr == "t_input") {
        tokitr++; lexitr++;
        if (!inputstmt()) {
            return 0;
        }
        else {
            return 1;
        }
    }
    if (tokitr != lexemes.end() && *tokitr == "t_output") {
        tokitr++; lexitr++;
        if (!outputstmt()) {
            return 0;
        }
        else {
            return 1;
        }
    }
    return -1; // no staements exist, means empty set
}

bool SyntaxAnalyzer::term() {
    // TERM -> number | text | id | (EXPR)
    if (tokitr != lexemes.end()) {
        //this checks if token is num, text, or id
        if (*tokitr == "t_number" || *tokitr == "t_text" || *tokitr == "t_id") {
            ++tokitr; ++lexitr;
            return true;
        }
        //this will check for EXPR
        else if (*tokitr == "s_lparen") {
            ++tokitr; ++lexitr; //this will eat '(' (i think lol)
            if (expr()) {
                if (expr()) {
                    if (tokitr != lexemes.end() && *tokitr == "s_rparen") {
                        ++tokitr; ++lexitr; // should eat ')'
                        return true;
                    } else {
                        cout << "error in source code" << endl;
                        cout << "missing ')' in term" << endl;
                        return false;
                    }
                } else {
                    return false;
                }
            }
        }
        return false;
    }
}
bool SyntaxAnalyzer::arithop() { // ARITHOP -> s_plus | s_minus | s_mult | s_div | s_mod
    if (tokitr != lexemes.end()) {
        if (*tokitr == "s_plus" || *tokitr == "s_minus" || *tokitr == "s_div") {
            return true;
        }
    }
    return false;
}

bool SyntaxAnaluzer::expr() { //EXPR -> SIMPLEEXPR  [LOGICOP  SIMPLEEXPR]1
    if (simpleexpr()) {
        if (tokir != lexeme.end()) {
            if (*tokitr == "t_and" || *tokitr == "t_or") {
                ++tokitr: ++lexitr;
                if (!simpleexpr()) {
                    cout << "error in source code" << endl;
                    cout << "simple expression after logical op is needed" << endl;
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
// End of Abraham's Section

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