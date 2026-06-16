#include <iostream>
#include <fstream>
#include <string>
#include "lexer.h"
#include "shunting_yard.h"
#include "evaluator.h"

using namespace std;

int main(int argc, char* argv[])
{
    string expr;

    if (argc > 1) {
        ifstream file(argv[1]);
        if (!file) {
            cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
            return 1;
        }
        getline(file, expr);
        file.close();
        cout << "Выражение из файла: " << expr << endl;
    } else {
        // Читаем с клавиатуры
        cout << "Введите выражение: ";
        getline(cin, expr);
    }

    try {
        vector<Token> tokens = tokensize(expr);
        vector<Token> rpn = shuntingYard(tokens);

        cout << "ОПЗ: ";
        for (const Token& token : rpn) {
            cout << token.value << " ";
        }
        cout << endl;

        double result = evaluateRPN(rpn);
        cout << "Результат: " << result << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}