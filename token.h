#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

enum TokenType
{
    NUM,
    FUNC,
    OP,
    LPAREN,
    RPAREN
};

struct Token
{
    TokenType type;
    string value;
    int opCode;
};

#endif