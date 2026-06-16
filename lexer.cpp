#include "lexer.h"
#include <cctype>
#include <string>

using namespace std;
// проверка строки, является ли она числом
bool isNumber(const string &s)
{
    for (char c : s)
    {
        if (!isdigit(c) && c != '.' && c != '-')
        {
            return false;
        }
        if (c == '-' && s.size() > 1)
        {
            return false;
        }
    }
    return !s.empty();
}
// проверка на arctg или arcctg
bool isFunction(const string &s)
{
    return s == "arctg" || s == "arcctg";
}
// проверка на разрешенные операторы
bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ||
           c == '&' || c == '!' || c == '~' || c == '<' || c == '>' ||
           c == '=' || c == '#';
}
// разбивает на токены (NUM, OP, FUNC, LPAREN, RPAREN)
vector<Token> tokensize(const string &expr)
{
    vector<Token> tokens;
    int i = 0;

    while (i < expr.length())
    {
        if (isspace(expr[i]))
        {
            i++;
            continue;
        }

        // Функции
        if (expr.substr(i, 5) == "arctg")
        {
            tokens.push_back({FUNC, "arctg", 0});
            i += 5;
            continue;
        }

        if (expr.substr(i, 6) == "arcctg")
        {
            tokens.push_back({FUNC, "arcctg", 0});
            i += 6;
            continue;
        }

        // Числа
        if (isdigit(expr[i]) || expr[i] == '.')
        {
            string current;
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.'))
            {
                current += expr[i++];
            }
            tokens.push_back({NUM, current, 0});
            continue;
        }

        // Операторы (включая & для конъюнкции)
        if (isOperator(expr[i]))
        {
            string op(1, expr[i++]);

            bool isUnary = false;
            if ((op == "+" || op == "-" || op == "~") && (tokens.empty() || tokens.back().type == LPAREN || (tokens.back().type == OP && tokens.back().value != ")")))
            {
                isUnary = true;
                if (op == "+")
                    op = "u+";
                else if (op == "-")
                    op = "u-";
                else if (op == "~")
                    op = "u~";
            }
            int code;
            if (op == "+")
                code = 0;
            else if (op == "-")
                code = 1;
            else if (op == "*")
                code = 2;
            else if (op == "/")
                code = 3;
            else if (op == "^")
                code = 4;
            else if (op == "&")
                code = 5;
            else if (op == "!")
                code = 6;
            else if (op == "~")
                code = 7;
            else if (op == "<")
                code = 8;
            else if (op == ">")
                code = 9;
            else if (op == "=")
                code = 10;
            else if (op == "#")
                code = 11;
            else if (op == "u-")
                code = 12;
            else if (op == "u+")
                code = 13;
            else if (op == "u~")
                code = 14;
            else
                code = 0;

            tokens.push_back({OP, op, code});
            continue;
        }

        // Скобки
        if (expr[i] == '(')
        {
            tokens.push_back({LPAREN, "(", 0});
            i++;
            continue;
        }

        if (expr[i] == ')')
        {
            tokens.push_back({RPAREN, ")", 0});
            i++;
            continue;
        }

        i++;
    }
    return tokens;
}