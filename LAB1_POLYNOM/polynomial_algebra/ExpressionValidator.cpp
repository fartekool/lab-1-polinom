#include "ExpressionValidator.h"
#include "stack.h"
#include <stdexcept>

using namespace std;

void ExpressionValidator::CheckValidCharacters(const std::string& expr) {
    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];
        if (!isdigit(c) && !isalpha(c) && !IsOperator(c) && c != '(' && c != ')'
            && c != ' ' && c != '.') {
            throw invalid_argument("Invalid character in expression");
        }
    }
}

void ExpressionValidator::CheckBrackets(const string& expr) {
    TStack<int> brStack;
    for (size_t i = 0; i < expr.size(); i++) {
        if (expr[i] == '(') {
            brStack.Push(i);
        }
        else if (expr[i] == ')') {
            if (brStack.IsEmpty()) {
                throw invalid_argument("Closing parenthesis is not matched");
            }
            brStack.Pop();
        }
    }
    if (!brStack.IsEmpty()) {
        throw invalid_argument("One or more opening parentheses are not paired");
    }
}

bool ExpressionValidator::IsOperator(char c) {
    switch (c) {
    case '+': case '-': case '*' : return true;
    default: return false;
    }
}

void ExpressionValidator::Validate(const string& expr) {
    CheckValidCharacters(expr);
    CheckBrackets(expr);
}