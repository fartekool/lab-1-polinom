#include "gtest.h"
#include "../polynomial_algebra/InfixToPostfixConverter.h"
#include "../polynomial_algebra/InfixToPostfixConverter.cpp"

TEST(InfixToPostfixConverter, Convert_simple_expression) {
    std::vector<Token> infix = {
        Token("1", Token::INT_LITERAL),
        Token("+", Token::OPERATOR, Token::LEFT),
        Token("2", Token::INT_LITERAL),
        Token("*", Token::OPERATOR, Token::LEFT),
        Token("3", Token::INT_LITERAL)
    };
    std::vector<Token> postfix = InfixToPostfixConverter::Convert(infix);
    std::vector<Token> expected = {
        Token("1", Token::INT_LITERAL),
        Token("2", Token::INT_LITERAL),
        Token("3", Token::INT_LITERAL),
        Token("*", Token::OPERATOR, Token::LEFT),
        Token("+", Token::OPERATOR, Token::LEFT)
    };
    ASSERT_EQ(postfix, expected);
}

TEST(InfixToPostfixConverter, Convert_expression_with_parentheses) {
    std::vector<Token> infix = {
        Token("(", Token::L_PARANTHESIS),
        Token("1", Token::INT_LITERAL),
        Token("+", Token::OPERATOR, Token::LEFT),
        Token("2", Token::INT_LITERAL),
        Token(")", Token::R_PARANTHESIS),
        Token("*", Token::OPERATOR, Token::LEFT),
        Token("3", Token::INT_LITERAL)
    };
    std::vector<Token> postfix = InfixToPostfixConverter::Convert(infix);
    std::vector<Token> expected = {
        Token("1", Token::INT_LITERAL),
        Token("2", Token::INT_LITERAL),
        Token("+", Token::OPERATOR, Token::LEFT),
        Token("3", Token::INT_LITERAL),
        Token("*", Token::OPERATOR, Token::LEFT)
    };
    ASSERT_EQ(postfix, expected);
}

TEST(InfixToPostfixConverter, Convert_expression_with_unary_minus) {
    std::vector<Token> infix = {
        Token("-", Token::OPERATOR, Token::RIGHT),
        Token("5", Token::INT_LITERAL),
        Token("+", Token::OPERATOR, Token::LEFT),
        Token("3", Token::INT_LITERAL)
    };
    std::vector<Token> postfix = InfixToPostfixConverter::Convert(infix);
    std::vector<Token> expected = {
        Token("5", Token::INT_LITERAL),
        Token("-", Token::OPERATOR, Token::RIGHT),
        Token("3", Token::INT_LITERAL),
        Token("+", Token::OPERATOR, Token::LEFT)
    };
    ASSERT_EQ(postfix, expected);
}

TEST(InfixToPostfixConverter, Convert_expression_with_float_and_polinom) {
    std::vector<Token> infix = {
        Token("1.5", Token::FLOAT_LITERAL),
        Token("+", Token::OPERATOR, Token::LEFT),
        Token("polinom1", Token::POLINOM_NAME),
        Token("*", Token::OPERATOR, Token::LEFT),
        Token("2", Token::INT_LITERAL)
    };
    std::vector<Token> postfix = InfixToPostfixConverter::Convert(infix);
    std::vector<Token> expected = {
        Token("1.5", Token::FLOAT_LITERAL),
        Token("polinom1", Token::POLINOM_NAME),
        Token("2", Token::INT_LITERAL),
        Token("*", Token::OPERATOR, Token::LEFT),
        Token("+", Token::OPERATOR, Token::LEFT)
    };
    ASSERT_EQ(postfix, expected);
}

TEST(InfixToPostfixConverter, Convert_complex_expression) {
    std::vector<Token> infix = {
        Token("(", Token::L_PARANTHESIS),
        Token("1", Token::INT_LITERAL),
        Token("+", Token::OPERATOR, Token::LEFT),
        Token("2", Token::INT_LITERAL),
        Token(")", Token::R_PARANTHESIS),
        Token("*", Token::OPERATOR, Token::LEFT),
        Token("(", Token::L_PARANTHESIS),
        Token("3", Token::INT_LITERAL),
        Token("-", Token::OPERATOR, Token::LEFT),
        Token("4", Token::INT_LITERAL),
        Token(")", Token::R_PARANTHESIS)
    };
    std::vector<Token> postfix = InfixToPostfixConverter::Convert(infix);
    std::vector<Token> expected = {
        Token("1", Token::INT_LITERAL),
        Token("2", Token::INT_LITERAL),
        Token("+", Token::OPERATOR, Token::LEFT),
        Token("3", Token::INT_LITERAL),
        Token("4", Token::INT_LITERAL),
        Token("-", Token::OPERATOR, Token::LEFT),
        Token("*", Token::OPERATOR, Token::LEFT)
    };
    ASSERT_EQ(postfix, expected);
}