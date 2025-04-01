

#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H



#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class SyntaxAnalyzer {
private:
    vector<string> lexemes;
    vector<string> tokens;
    vector<string>::iterator lexitr;
    vector<string>::iterator tokitr;

    map<string, string> symboltable; // map of variables and their datatype

    // Private methods
    bool vdec();
    int vars();
    bool stmtlist();
    int stmt();
    bool ifstmt();
    bool elsepart();
    bool whilestmt();
    bool assignstmt();
    bool inputstmt();
    bool outputstmt();
    bool expr();
    bool simpleexpr();
    bool term();
    bool logicop();
    bool arithop();
    bool relop();

public:
    SyntaxAnalyzer(istream& infile);

    bool parse();
};

#endif