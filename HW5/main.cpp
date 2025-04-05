//
// Created by jacob, jafet, abraham
//

#include <iostream>

#include "SyntaxAnalyzer.h"

int main() {
    ifstream test("test.txt");
    SyntaxAnalyzer syntaxAnalyzer(test);
    cout << syntaxAnalyzer.parse() << endl;
    return 0;
}
