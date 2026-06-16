#include "shunting_yard.h"
#include <stack>
#include <string>

using namespace std;

int getPriority(const string &op, bool isUnary = false)
{
    if (isUnary)
        return 5;
    if (op == "^")
        return 4;
    if (op == "*" || op == "/" || op == "&")
        return 3;
    if (op == "+" || op == "-" || op == "!")
        return 2;
    if (op == "<" || op == ">" || op == "=" || op == "#")
        return 1;
    return 0;
}

bool isRightAssociative(const string &op)
{
    //правые: *, <, >, =, #, !
    return op == "*" || op == "<" || op == ">" || op == "=" || op == "#" || op == "!";
}

vector<Token> shuntingYard(const vector<Token> &tokens)
{
    vector<Token> output;
    stack<Token> opStack;

    for (const Token &token : tokens)
    {
        if (token.type == NUM)
        {
            output.push_back(token);
        }
        else if (token.type == FUNC)
        {
            opStack.push(token);
        }
        else if (token.type == OP)
        {
            bool isUnary = (token.opCode == 12 || token.opCode == 13 || token.opCode == 14);
            int priority = getPriority(token.value, isUnary);

            while (!opStack.empty() && opStack.top().type == OP)
            {
                Token top = opStack.top();
                bool topUnary = (top.opCode == 12 || top.opCode == 13 || top.opCode == 14);
                int topPriority = getPriority(top.value, topUnary);

                if (topPriority > priority || (topPriority == priority && !isRightAssociative(top.value)))
                {
                    output.push_back(top);
                    opStack.pop();
                }
                else
                    break;
            }
            opStack.push(token);
        }
        else if (token.type == LPAREN)
        {
            opStack.push(token);
        }
        else if (token.type == RPAREN)
        {
            while (!opStack.empty() && opStack.top().type != LPAREN)
            {
                output.push_back(opStack.top());
                opStack.pop();
            }
            if (!opStack.empty())
                opStack.pop();

            if (!opStack.empty() && opStack.top().type == FUNC)
            {
                output.push_back(opStack.top());
                opStack.pop();
            }
        }
    }

    while (!opStack.empty())
    {
        output.push_back(opStack.top());
        opStack.pop();
    }

    return output;
}