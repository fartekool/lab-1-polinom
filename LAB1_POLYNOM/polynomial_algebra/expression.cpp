#include "Expression.h"

Expression::Expression(const string& expr) : infix(expr) {
    ExpressionValidator::Validate(infix);
    tokens = InfixToPostfixConverter::Convert(Parser::Parse(infix));
    for (int i = 0; i < tokens.size(); i++) {
        postfix += (tokens[i].getStr() + " ");
        if (tokens[i].getType() == Token::Type::POLINOM_NAME)
            names.push_back(tokens[i].getStr());
    }
}

string Expression::GetInfix() const { return infix; }
string Expression::GetPostfix() const { return postfix; }

vector<string> Expression::GetOperands() const {
    return names;
}

Polynom Expression::Calculate(std::map<string, Polynom> pol) {
    return PostfixCalculator::Calculate(tokens, pol);
}


pair<string, string> splitString(const string& input) {
    string left, right;
    size_t equalSignPos = input.find('=');

    if (equalSignPos != string::npos) {
        left = input.substr(0, equalSignPos);
        right = input.substr(equalSignPos + 1);
    }
    else {
        // Если знак '=' не найден, левая часть - вся строка, правая - пустая
        left = input;
    }

    return { left, right };
}
