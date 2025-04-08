//
// The code was created by Jacob, Jafet, Abraham.
//
// The code looks through a file of valid lexemes to see if they
// fit the grammar of the language.
//
// Functions made by Jacob: vdecassign, ifstmt, elsepart, assignstmt, and relop.
// Functions made by Abraham: stmtlist, stmt, expr, term, and arithop.
// Functions made by Jafet: whilestmt, inputstmt, outputstmt, simpleexpr, logicop.

#include "SyntaxAnalyzer.h"
#include <iostream>

// Made by Group
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

// Made by Group
bool SyntaxAnalyzer::parse() {
    if (tokitr != tokens.end() && *tokitr == "t_main") {
        ++tokitr;
        ++lexitr;
        if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
            ++tokitr;
            ++lexitr;
            if (stmtlist()) {
                if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                    ++tokitr;
                    ++lexitr;
                    if (tokitr == tokens.end()) {
                        return true;
                    }
                }
            }
        }
    }
    cout << "Error at " << *tokitr << " " << *lexitr << endl;
    return false;
}

// Made by Jacob
bool SyntaxAnalyzer::vdecassign(const string &type) {
    if (tokitr != tokens.end()) {
        if (*tokitr == "t_id") {
            if (!symboltable.contains(*lexitr)) {
                symboltable.insert(make_pair(*lexitr, type));
                ++tokitr;
                ++lexitr;
                if (tokitr != tokens.end() && *tokitr == "s_assign") {
                    ++tokitr;
                    ++lexitr;
                    if (expr()) {
                        if (tokitr != tokens.end() && *tokitr == "s_semi") {
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

// Made by Jacob
bool SyntaxAnalyzer::ifstmt() {
    if (tokitr != tokens.end()) {
        if (tokitr != tokens.end() && *tokitr == "s_lparen") {
            ++tokitr;
            ++lexitr;
            if (expr()) {
                if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                    ++tokitr;
                    ++lexitr;
                    if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
                        ++tokitr;
                        ++lexitr;
                        if (stmtlist()) {
                            if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                                ++tokitr;
                                ++lexitr;
                                if (elsepart()) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Made by Jacob
bool SyntaxAnalyzer::elsepart() {
    if (tokitr != tokens.end() && *tokitr == "t_else") {
        ++tokitr;
        ++lexitr;
        if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
            ++tokitr;
            ++lexitr;
            if (stmtlist()) {
                if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                    ++tokitr;
                    ++lexitr;
                    return true;
                }
            }
        }
        return false;
    }
    return true;
}

// Made by Jacob
bool SyntaxAnalyzer::assignstmt() {
    if (tokitr != tokens.end()) {
        if (tokitr != tokens.end() && *tokitr == "s_assign") {
            ++tokitr;
            ++lexitr;
            if (expr()) {
                if (tokitr != tokens.end() && *tokitr == "s_semi") {
                    ++tokitr;
                    ++lexitr;
                    return true;
                }
            }
        }
    }
    return false;
}

// Made by Jacob
bool SyntaxAnalyzer::relop() {
    if (tokitr != tokens.end()) {
        if (*tokitr == "s_lt" || *tokitr == "s_gt" || *tokitr == "s_eq" || *tokitr == "s_ne") {
            ++tokitr;
            ++lexitr;
            return true;
        }
    }
    return false;
}

// Made by Jafet
bool SyntaxAnalyzer::whilestmt() {
    if (tokitr != tokens.end() && *tokitr == "s_lparen") {
        ++tokitr;
        ++lexitr;
        if (tokitr != tokens.end() && expr()) {
            if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                ++tokitr;
                ++lexitr;
                if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
                    ++tokitr;
                    ++lexitr;
                    if (tokitr != tokens.end() && stmtlist()) {
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

// Made by Jafet
bool SyntaxAnalyzer::inputstmt() {
    if (tokitr != tokens.end() && *tokitr == "s_lparen") {
        ++tokitr;
        ++lexitr;
        if (tokitr != tokens.end() && *tokitr == "t_id") {
            if (symboltable.contains(*lexitr)) {
                ++tokitr;
                ++lexitr;
                if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                    ++tokitr;
                    ++lexitr;
                    return true;
                }
            }
        }
    }
    return false;
}

// Made by Jafet
bool SyntaxAnalyzer::outputstmt() {
    if (tokitr != tokens.end() && *tokitr == "s_lparen") {
        ++tokitr;
        ++lexitr;
        if (tokitr != tokens.end() && *tokitr == "t_text") {
            ++tokitr;
            ++lexitr;
            if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                ++tokitr;
                ++lexitr;
                return true;
            }
        } else if (tokitr != tokens.end() && expr()) {
            if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                ++tokitr;
                ++lexitr;

                return true;
            }
        }
    }
    return false;
}

// Made by Jafet
bool SyntaxAnalyzer::simpleexpr() {
    if (tokitr != tokens.end() && term()) {
        if (arithop()) {
            if (tokitr != tokens.end() && term()) {
                return true;
            }
        } else if (relop()) {
            if (tokitr != tokens.end() && term()) {
                return true;
            }
        } else {
            return true;
        }
    }
    return false;
}

// Made by Jafet
bool SyntaxAnalyzer::logicop() {
    if (tokitr != tokens.end() && *tokitr == "t_and") {
        ++tokitr;
        ++lexitr;
        return true;
    }
    if (tokitr != tokens.end() && *tokitr == "t_or") {
        ++tokitr;
        ++lexitr;
        return true;
    }
    return false;
}

// Made by Abraham
bool SyntaxAnalyzer::stmtlist() {
    int result = stmt();
    while (result != -1 && result != 0) {
        result = stmt();
    }
    if (result == 0) {
        return false;
    } else {
        return true;
    }
}

// Made by Abraham
int SyntaxAnalyzer::stmt() {
    if (*tokitr == "t_integer" || *tokitr == "t_string") {
        string test = *tokitr;
        ++tokitr;
        ++lexitr;
        if (!vdecassign(test)) {
            return 0;
        } else {
            return 1;
        }
    }
    if (tokitr != tokens.end() && *tokitr == "t_if") {
        ++tokitr;
        ++lexitr;
        if (!ifstmt()) {
            return 0; 
        } else {
            return 1; 
        }
    }
    if (tokitr != tokens.end() && *tokitr == "t_while") {
        ++tokitr;
        ++lexitr;
        if (!whilestmt()) {
            return 0;
        } else {
            return 1;
        }
    }
    if (tokitr != tokens.end() && *tokitr == "t_id" && symboltable.contains(*lexitr)) {
        ++tokitr;
        ++lexitr;
        if (!assignstmt()) {
            return 0;
        } else {
            return 1;
        }
    }
    if (tokitr != tokens.end() && *tokitr == "t_input") {
        ++tokitr;
        ++lexitr;
        if (!inputstmt()) {
            return 0;
        } else {
            return 1;
        } 
    }
    if (tokitr != tokens.end() && *tokitr == "t_output") {
        ++tokitr;
        ++lexitr;
        if (!outputstmt()) {
            return 0;
        } else {
            return 1;
        }
    }
    return -1; 
}

// Made by Abraham
bool SyntaxAnalyzer::term() {
    if (tokitr != tokens.end()) {
        if (*tokitr == "t_number" || *tokitr == "t_text") {
            ++tokitr;
            ++lexitr;
            return true;
        }
        if (*tokitr == "t_id" && symboltable.contains(*lexitr)) {
            ++tokitr;
            ++lexitr;
            return true;
        }
        else if (*tokitr == "s_lparen") {
            ++tokitr;
            ++lexitr; 
            if (expr()) {
                if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                    ++tokitr;
                    ++lexitr;
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
        return false;
    }
}

// Made by Abraham
bool SyntaxAnalyzer::arithop() {
    if (tokitr != tokens.end()) {
        if (*tokitr == "s_plus" || *tokitr == "s_minus" || *tokitr == "s_div") {
            ++tokitr;
            ++lexitr;
            return true;
        }
    }
    return false;
}

// Made by Abraham
bool SyntaxAnalyzer::expr() {
    if (simpleexpr()) {
        if (tokitr != tokens.end()) {
            if (*tokitr == "t_and" || *tokitr == "t_or") {
                ++tokitr;
                ++lexitr;
                if (!simpleexpr()) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
