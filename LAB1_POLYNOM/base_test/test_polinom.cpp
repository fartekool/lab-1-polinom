#include "gtest.h"
#include "../polynom/polynom.h"
#include "../polynom/polynom.cpp"
TEST(Polynom, can_create_empty_polinom) {
    ASSERT_NO_THROW(Polynom());
}

TEST(Polynom, can_create_polinom_from_string) {
    ASSERT_NO_THROW(Polynom("2x^2 + 3xy + y^2 - 5z"));
}

TEST(Polynom, can_handle_single_term_polynom) {
    Polynom p("2x^2");
    ASSERT_EQ(p.calculate(1, 0, 0), 2);
}

TEST(Polynom, can_add_two_polynomials) {
    Polynom p1("2x^2 + 3xy + y^2");
    Polynom p2("x^2 - y^2 + z");
    Polynom result = p1 + p2;
    ASSERT_EQ(result.calculate(1, 1, 1), 7);
}

TEST(Polynom, can_subtract_two_polynomials) {
    Polynom p1("2x^2 + 3xy + y^2");
    Polynom p2("x^2 - y^2 + z");
    Polynom result = p1 - p2;
    ASSERT_EQ(result.calculate(1, 1, 1), 5);
}

TEST(Polynom, can_multiply_polinom_by_scalar) {
    Polynom p("x^2 + y^2 + z^2");
    Polynom result = p * 2.0;
    ASSERT_EQ(result.calculate(1, 1, 1), 6);
}

TEST(Polynom, can_multiply_scalar_by_polinom) {
    Polynom p("x^2 + y^2 + z^2");
    Polynom result = 2.0 * p;
    ASSERT_EQ(result.calculate(1, 1, 1), 6);
}

TEST(Polynom, can_multiply_two_polynomials) {
    Polynom p1("x + y");
    Polynom p2("x - y");
    Polynom result = p1 * p2;
    ASSERT_EQ(result.calculate(2, 1, 0), 3);
}

TEST(Polynom, can_calculate_derivative_with_respect_to_x) {
    Polynom p("3x^2y + 4xz + 2");
    Polynom result = p.derivative('x');
    ASSERT_EQ(result.calculate(1, 1, 1), 10);
}

TEST(Polynom, can_calculate_derivative_with_respect_to_y) {
    Polynom p("3x^2y + 4yz + 2");
    Polynom result = p.derivative('y');
    ASSERT_EQ(result.calculate(1, 1, 1), 7);
}

TEST(Polynom, can_calculate_derivative_with_respect_to_z) {
    Polynom p("3x^2z + 4yz + 2z");
    Polynom result = p.derivative('z');
    ASSERT_EQ(result.calculate(1, 1, 1), 9);
}

TEST(Polynom, can_handle_zero_polynomial) {
    Polynom p("0");
    ASSERT_EQ(p.calculate(1, 1, 1), 0);
}

TEST(Polynom, can_handle_polynomial_with_large_exponents) {
    ASSERT_THROW(Polynom("x^10"), std::invalid_argument);
}

TEST(Polynom, can_handle_single_variable_with_no_exponent) {
    Polynom p("x");
    ASSERT_EQ(p.calculate(2, 0, 0), 2);
}

TEST(Polynom, can_handle_constant_term) {
    Polynom p("5");
    ASSERT_EQ(p.calculate(1, 1, 1), 5);
}

TEST(Polynom, can_handle_invalid_character) {
    ASSERT_THROW(Polynom("2x + 3y + 4k"), std::invalid_argument);
}

TEST(Polynom, can_handle_multiple_terms_with_same_degree) {
    Polynom p("2x^2 + 3x^2");
    ASSERT_EQ(p.calculate(1, 0, 0), 5);
}

TEST(Polynom, can_handle_leading_negative_term) {
    Polynom p("-x^2 + 3x - 2");
    ASSERT_EQ(p.calculate(1, 1, 1), 0);
}

TEST(Polynom, can_handle_all_zero_coefficients) {
    Polynom p("0x^2 + 0y + 0");
    ASSERT_EQ(p.calculate(1, 1, 1), 0);
}

TEST(Polynom, can_handle_addition_with_zero_polynomial) {
    Polynom p1("2x^2 + 3xy");
    Polynom p2("0");
    Polynom result = p1 + p2;
    ASSERT_EQ(result.calculate(1, 1, 1), 5);
}

TEST(Polynom, can_handle_subtraction_with_zero_polynomial) {
    Polynom p1("2x^2 + 3xy");
    Polynom p2("0");
    Polynom result = p1 - p2;
    ASSERT_EQ(result.calculate(1, 1, 1), 5);
}

TEST(Polynom, can_handle_multiplication_with_zero_polynomial) {
    Polynom p1("2x^2 + 3xy");
    Polynom p2("0");
    Polynom result = p1 * p2;
    ASSERT_EQ(result.calculate(1, 1, 1), 0);
}

TEST(Polynom, can_handle_derivative_with_zero_polynomial) {
    Polynom p("0");
    Polynom result = p.derivative('x');
    ASSERT_EQ(result.calculate(1, 1, 1), 0);
}

TEST(Polynom, can_handle_polynomial_with_no_variables) {
    Polynom p("5 + 3");
    ASSERT_EQ(p.calculate(1, 1, 1), 8);
}

TEST(Polynom, can_handle_large_polynomial) {
    Polynom p("x^2 + y^2 + z^2 + 2xy + 2xz + 2yz + 3x + 3y + 3z + 4");
    ASSERT_EQ(p.calculate(1, 1, 1), 22);
}

TEST(Polynom, can_handle_negative_coefficients) {
    Polynom p("-2x^2 - 3xy - y^2");
    ASSERT_EQ(p.calculate(1, 1, 1), -6);
}