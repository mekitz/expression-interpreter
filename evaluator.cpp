#include "evaluator.h"
#include <string>
#include <stack>
#include <cmath>
#include <stdexcept>

using namespace std;

double applyOp(double a, double b, int code)
{
    switch (code)
    {
    case 0:
        return a + b;
    case 1:
        return a - b;
    case 2:
        return a * b;
    case 3:
        if (b == 0)
        {
            throw runtime_error("Деление на ноль");
        }
        return a / b;
    case 4:
        return pow(a, b);
    case 5:
        if (a != 0 && b != 0)
        {
            return 1.0;
        }
        else
        {
            return 0.0;
        }
    case 6:
        if (a != 0 || b != 0)
        {
            return 1.0;
        }
        else
        {
            return 0.0;
        }
    case 8:
        if (a < b)
        {
            return 1.0;
        }
        else
        {
            return 0.0;
        }
    case 9:
        if (a > b)
        {
            return 1.0;
        }
        else
        {
            return 0.0;
        }
    case 10:
        if (a == b)
        {
            return 1.0;
        }
        else
        {
            return 0.0;
        }
    case 11:
        if (a != b)
        {
            return 1.0;
        }
        else
        {
            return 0.0;
        }
    default:
        throw runtime_error("Неизвестная бинарная операция");
    }
}

double applyUnaryOp(double a, int code)
{
    switch (code)
    {
    case 12:
        return -a;
    case 13:
        return a;
    case 14:
        if (a == 0)
        {
            return 1.0;
        }
        else
        {
            return 0.0;
        }
    default:
        throw runtime_error("Неизвестная унарная операция");
    }
}

double evaluateRPN(const vector<Token> &rpn)
{
    stack<double> st;

    for (const Token &token : rpn)
    {
        if (token.type == NUM)
        {
            st.push(stod(token.value));
        }
        else if (token.type == OP)
        {
            if (token.opCode == 12 || token.opCode == 13 || token.opCode == 14)
            {
                if (st.empty())
                {
                    throw runtime_error("Недостаточно операндов для унарной операции");
                }
                double a = st.top();
                st.pop();
                st.push(applyUnaryOp(a, token.opCode));
            }
            else
            {
                if (st.size() < 2)
                {
                    throw runtime_error("Недостаточно операндов для бинарной операции");
                }
                double b = st.top();
                st.pop();
                double a = st.top();
                st.pop();
                st.push(applyOp(a, b, token.opCode));
            }
        }
        else if (token.type == FUNC)
        {
            if (st.empty())
            {
                throw runtime_error("Недостаточно операндов для функции");
            }
            double a = st.top();
            st.pop();
            if (token.value == "arctg")
            {
                st.push(atan(a));
            }
            else if (token.value == "arcctg")
            {
                st.push(atan(1.0 / a));
            }
        }
    }

    if (st.empty())
    {
        throw runtime_error("Нет результата");
    }
    return st.top();
}