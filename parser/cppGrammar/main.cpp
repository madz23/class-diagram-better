// Run the parser
// author: madz
// 17 October 2022
#include <iostream>

#include "antlr4-runtime.h"
#include "CPP14Lexer.h"
#include "CPP14Parser.h"

using namespace antlr4;

int main(int argc, char const *argv[])
{
    ANTLRInputStream input("3-1");
    CPP14Lexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    return 0;
}

