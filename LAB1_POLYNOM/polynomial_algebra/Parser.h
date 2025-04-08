#pragma once

#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <vector>

using namespace std;

class Token
{
public:

    // Тип
    enum Type
    {
        OPERATOR,      // унарный/бинарный оператор
        L_PARANTHESIS, // открывающая скобка
        R_PARANTHESIS, // закрывающая скобка
        INT_LITERAL,   // целое число
        FLOAT_LITERAL, // число с плавающей точкой
        POLINOM_NAME,  // имя полинома
        POLINOM,       // полином
        NONE_TYPE           // неопределённое тип 
    };

    // Ассоциативность
    enum OperatorAssociativity
    {
        NONE,  // токен - не оператор
        RIGHT, // правоассоциативный
        LEFT   // левоассоциативный
    };

    Token(string token, Type type, OperatorAssociativity asc = OperatorAssociativity::NONE);

private:
    Type type;
    OperatorAssociativity opAsc;
    string str;

public:

    // Приоритет
    int getPrecendance() const;

    // Геттеры
    const Type& getType() const;
    const OperatorAssociativity& getAsc() const;
    const string& getStr() const;

    // Используется только для тестирования 
    bool operator==(const Token& other) const;

    bool operator!=(const Token& other) const;
};

class Parser {
private:
    enum State
    {
        S0, // Стартовое
        S1, // Токенизация скобки/оператора
        S2, // Запись целого числа в буфер
        S3, // Запись floating-point числа в буфер
        S4, // Запись имени полинома в буфер
        S5  // Токенизация записанного числа/имени полинома из буфера
    };
public:
    static vector<Token> Parse(const string& expr);
};
