#pragma once

#include <string>

using namespace std;

class ExpressionValidator {
    static void CheckValidCharacters(const string& expr);
    static void CheckBrackets(const string& expr);

public:
    static bool IsOperator(char c);

    static void Validate(const string& expr);
};


bool ValidateName(const string& name);