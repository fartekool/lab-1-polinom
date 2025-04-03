#pragma once

#include "../polynom/polynom.h"
#include <string>
#include <vector>
#include <map>
#include "ExpressionValidator.h"
#include "InfixToPostfixConverter.h"
#include "PostfixCalculator.h"
#include "Parser.h"
using namespace std;


pair<string, string> splitString(const string& input);


class Expression {
    string infix;
    string postfix;
    vector<string> names; // ����� ��������� ������� ������������ � ���������
    vector<Token> tokens; // ������, ����� ������ ��� ������ Calculate
public:
    Expression(const string& expr = "");
    string GetInfix() const;
    string GetPostfix() const;
    vector<string> GetOperands() const;
    Polynom Calculate(map<string, Polynom>);
};


