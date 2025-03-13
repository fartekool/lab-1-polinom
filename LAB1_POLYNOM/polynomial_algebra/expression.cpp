#include "expression.h"
#include "stack.h"

// ExpressionValidator

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

// Parser

vector<string> Parser::Parse(const string& str) {
    vector<string> lexems;
    string cur;
    for (size_t i = 0; i < str.size(); i++) {
        // ...
    }
    return lexems;
}

map<string, int> InfixToPostfixConverter::priority = {
    {"+", 1}, {"-", 1}, {"*", 2}
};

string InfixToPostfixConverter::Convert(const string& infix) {
    string postfix;
    // ...
    return postfix;
}

Polynom PostfixCalculator::Calculate(const string& postfix) {
    Polynom res;
    // ... 
    return res;
}

Expression::Expression(const string& expr) : infix(expr) {
    ExpressionValidator::Validate(infix);
    postfix = InfixToPostfixConverter::Convert(infix);
}

string Expression::GetInfix() const { return infix; }
string Expression::GetPostfix() const { return postfix; }

vector<string> Expression::GetOperands() const {
    vector<string> op;
    // ...
    return op;
}

Polynom Expression::Calculate() {
    return PostfixCalculator::Calculate(postfix);
}

