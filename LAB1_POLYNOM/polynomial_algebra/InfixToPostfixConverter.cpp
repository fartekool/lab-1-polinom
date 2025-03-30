#include "InfixToPostfixConverter.h"

vector<Token> InfixToPostfixConverter::Convert(const std::vector<Token>& expr) {
    TStack<Token> st;
    vector<Token> out;
    Token stItem("", Token::Type::L_PARANTHESIS, Token::OperatorAssociativity::NONE);
    for (const Token& item : expr) {
        if (item.getType() == Token::Type::L_PARANTHESIS) st.Push(item);
        else if (item.getType() == Token::Type::R_PARANTHESIS) {
            stItem = st.Top(); st.Pop();
            while (stItem.getType() != Token::Type::L_PARANTHESIS) {
                out.push_back(stItem);
                stItem = st.Top(); st.Pop();
            }
        }
        else if (item.getType() == Token::Type::OPERATOR) { // проверка что item является оператором
            while (!st.IsEmpty()) {
                stItem = st.Top(); st.Pop();
                if (item.getAsc() != Token::OperatorAssociativity::NONE && stItem.getAsc() != Token::OperatorAssociativity::NONE && item.getPrecendance() <= stItem.getPrecendance())
                    out.push_back(stItem);
                else {
                    st.Push(stItem);
                    break;
                }
            }
            st.Push(item);
        }
        else {
            out.push_back(item);
        }
    }
    while (!st.IsEmpty()) {
        stItem = st.Top(); st.Pop();
        out.push_back(stItem);
    }
    return out;
}