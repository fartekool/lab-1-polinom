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

