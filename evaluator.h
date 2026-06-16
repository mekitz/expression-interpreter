#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include "token.h"
using namespace std;

double evaluateRPN(const vector<Token> &rpn);

#endif