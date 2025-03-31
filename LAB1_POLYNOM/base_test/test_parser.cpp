#include "gtest.h"
#include "../polynomial_algebra/parser.h"
#include "../polynomial_algebra/parser.cpp"

// Тесты для класса Token
TEST(Token, can_create_operator_token_with_associativity) {
    ASSERT_NO_THROW(Token("+", Token::OPERATOR, Token::LEFT));
}

TEST(Token, throws_if_operator_token_without_associativity) {
    ASSERT_THROW(Token("+", Token::OPERATOR), std::logic_error);
}

TEST(Token, throws_if_non_operator_token_with_associativity) {
    ASSERT_THROW(Token("123", Token::INT_LITERAL, Token::LEFT), std::logic_error);
}

TEST(Token, can_create_literal_token) {
    ASSERT_NO_THROW(Token("123", Token::INT_LITERAL));
}

TEST(Token, can_create_parenthesis_token) {
    ASSERT_NO_THROW(Token("(", Token::L_PARANTHESIS));
    ASSERT_NO_THROW(Token(")", Token::R_PARANTHESIS));
}

TEST(Token, can_get_precedence_of_operator) {
    Token plus("+", Token::OPERATOR, Token::LEFT);
    ASSERT_EQ(plus.getPrecendance(), 2);

    Token minus_unary("-", Token::OPERATOR, Token::RIGHT);
    ASSERT_EQ(minus_unary.getPrecendance(), 4);
}

TEST(Token, throws_if_get_precedence_of_non_operator) {
    Token literal("123", Token::INT_LITERAL);
    ASSERT_THROW(literal.getPrecendance(), std::logic_error);
}

TEST(Token, can_get_type_of_token) {
    Token plus("+", Token::OPERATOR, Token::LEFT);
    ASSERT_EQ(plus.getType(), Token::OPERATOR);

    Token literal("123", Token::INT_LITERAL);
    ASSERT_EQ(literal.getType(), Token::INT_LITERAL);
}

TEST(Token, can_get_associativity_of_token) {
    Token plus("+", Token::OPERATOR, Token::LEFT);
    ASSERT_EQ(plus.getAsc(), Token::LEFT);

    Token literal("123", Token::INT_LITERAL);
    ASSERT_EQ(literal.getAsc(), Token::NONE);
}

TEST(Token, can_get_string_of_token) {
    Token plus("+", Token::OPERATOR, Token::LEFT);
    ASSERT_EQ(plus.getStr(), "+");

    Token literal("123", Token::INT_LITERAL);
    ASSERT_EQ(literal.getStr(), "123");
}

// Тесты для класса Parser
TEST(Parser, can_parse_simple_expression) {
    std::vector<Token> tokens = Parser::Parse("1 + 2 * 3");
    ASSERT_EQ(tokens.size(), 5);
    ASSERT_EQ(tokens[0].getStr(), "1");
    ASSERT_EQ(tokens[1].getStr(), "+");
    ASSERT_EQ(tokens[2].getStr(), "2");
    ASSERT_EQ(tokens[3].getStr(), "*");
    ASSERT_EQ(tokens[4].getStr(), "3");
}

TEST(Parser, can_parse_expression_with_parentheses) {
    std::vector<Token> tokens = Parser::Parse("( 1 + 2 ) * 3");
    ASSERT_EQ(tokens.size(), 7);
    ASSERT_EQ(tokens[0].getStr(), "(");
    ASSERT_EQ(tokens[1].getStr(), "1");
    ASSERT_EQ(tokens[2].getStr(), "+");
    ASSERT_EQ(tokens[3].getStr(), "2");
    ASSERT_EQ(tokens[4].getStr(), ")");
    ASSERT_EQ(tokens[5].getStr(), "*");
    ASSERT_EQ(tokens[6].getStr(), "3");
}

TEST(Parser, can_parse_expression_with_unary_minus) {
    std::vector<Token> tokens = Parser::Parse("-5 + 3");
    ASSERT_EQ(tokens.size(), 4);
    ASSERT_EQ(tokens[0].getStr(), "-");
    ASSERT_EQ(tokens[1].getStr(), "5");
    ASSERT_EQ(tokens[2].getStr(), "+");
    ASSERT_EQ(tokens[3].getStr(), "3");
}

TEST(Parser, can_parse_expression_with_float_literal) {
    std::vector<Token> tokens = Parser::Parse("1.5 + 2");
    ASSERT_EQ(tokens.size(), 3);
    ASSERT_EQ(tokens[0].getStr(), "1.5");
    ASSERT_EQ(tokens[1].getStr(), "+");
    ASSERT_EQ(tokens[2].getStr(), "2");
}

TEST(Parser, can_parse_expression_with_polinom_name) {
    std::vector<Token> tokens = Parser::Parse("polinom1 + 2");
    ASSERT_EQ(tokens.size(), 3);
    ASSERT_EQ(tokens[0].getStr(), "polinom1");
    ASSERT_EQ(tokens[1].getStr(), "+");
    ASSERT_EQ(tokens[2].getStr(), "2");
}

TEST(Parser, throws_on_invalid_symbol) {
    ASSERT_THROW(Parser::Parse("1 + @"), std::invalid_argument);
}

TEST(Parser, throws_on_unexpected_point) {
    ASSERT_THROW(Parser::Parse(".1 + 2"), std::invalid_argument);
}

TEST(Parser, throws_on_unexpected_underscore) {
    ASSERT_THROW(Parser::Parse("1_ + 2"), std::invalid_argument);
}

TEST(Parser, throws_on_float_with_multiple_points) {
    ASSERT_THROW(Parser::Parse("1.1.1 + 2"), std::invalid_argument);
}

TEST(Parser, throws_on_polinom_name_with_points) {
    ASSERT_THROW(Parser::Parse("poli.nom + 2"), std::invalid_argument);
}