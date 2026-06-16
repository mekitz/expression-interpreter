#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <vector>
#include "token.h"
using namespace std;

vector<Token> shuntingYard(const vector<Token> &tokens);

#endif