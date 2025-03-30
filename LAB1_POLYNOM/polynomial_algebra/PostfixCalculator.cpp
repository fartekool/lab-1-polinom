#include "PostfixCalculator.h"

Polynom PostfixCalculator::Calculate(const vector<Token>& expr, const map<string, Polynom>& pol) {
    TStack<Polynom> st;
    Polynom leftOp, rightOp;

    for (const Token& token : expr) {
        string lexem = token.getStr();
        switch (token.getType()) {
        case Token::OPERATOR:
            if (lexem == "+") {
                rightOp = st.Top(); st.Pop();
                leftOp = st.Top(); st.Pop();
                st.Push(leftOp + rightOp);
            }
            else if (lexem == "-" && token.getAsc() == Token::OperatorAssociativity::LEFT) {
                rightOp = st.Top(); st.Pop();
                leftOp = st.Top(); st.Pop();
                st.Push(leftOp - rightOp);
            }
            else if (lexem == "*") {
                rightOp = st.Top(); st.Pop();
                leftOp = st.Top(); st.Pop();
                st.Push(leftOp * rightOp);
            }
            else if (lexem == "-") { // Обработка унарного минуса
                rightOp = st.Top(); st.Pop();
                st.Push((-1) * rightOp);
            }
            else {
                throw runtime_error("Unknown operator: " + lexem);
            }
            break;
        case Token::POLINOM_NAME:
            if (pol.find(lexem) != pol.end()) {
                st.Push(pol.at(lexem));
            }
            else {
                throw runtime_error("Polynom not found: " + lexem);
            }
            break;
        case Token::INT_LITERAL:
        case Token::FLOAT_LITERAL:
            st.Push(Polynom(lexem));
            break;

        default:
            throw runtime_error("Unexpected token type.");
        }
    }

    return st.Top();
}