#pragma once

#include "../polynom/polynom.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Parser { 
public:
	static vector<string> Parse(const string& str);
};

class InfixToPostfixConverter { 
public:
	static map<string, int> priority;

	static string Convert(const string& infix);
};

class PostfixCalculator { 
public:
    static Polynom Calculate(const string& postfix);
};

class Expression {
    string infix;
    string postfix;
    map<string, Polynom> operands; // возможно пригодится для хранения полиномов которые присутствуют в выражении
public:
    Expression(const string& expr = "");
    string GetInfix() const;
    string GetPostfix() const;
    vector<string> GetOperands() const;
    Polynom Calculate();
};
