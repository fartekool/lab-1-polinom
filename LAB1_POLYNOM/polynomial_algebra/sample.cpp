#include <iostream>
#include "../polynomial_algebra/expression.h"
#include "Parser.h"
#include "InfixToPostfixConverter.h"
#include "PostfixCalculator.h"
#include "../polynom/polynom.h"
#include "../polynom/polynom.cpp"
#include "Expression.h"

#include <map>

using namespace std;



int main()
{
    string exp = "result_poly = (poly_a * poly_b - poly_c) * 2 + poly_d * (-poly_e)";
    cout << exp << '\n';
    pair<string, string> expr = splitString(exp);
    cout << "Name of new polinom: " << expr.first << '\n';
    cout << "Expression with polinom's names: " << expr.second << '\n';
    vector<Token> tokensInfix = Parser::Parse(expr.second);;
    // Красиво печатаем токены в консоль
    for (const auto& i : tokensInfix)
    {
        string type, asc;
        switch (i.getType())
        {
        case Token::OPERATOR:
            type = "OPERATOR";
            break;
        case Token::L_PARANTHESIS:
            type = "L_PARANTHESIS";
            break;
        case Token::R_PARANTHESIS:
            type = "R_PARANTHESIS";
            break;
        case Token::INT_LITERAL:
            type = "INT_LITERAL";
            break;
        case Token::FLOAT_LITERAL:
            type = "FLOAT_LITERAL";
            break;
        case Token::POLINOM_NAME:
            type = "POLINOM_NAME";
            break;
        }

        switch (i.getAsc())
        {
        case Token::NONE:
            asc = "NONE";
            break;
        case Token::RIGHT:
            asc = "RIGHT";
            break;
        case Token::LEFT:
            asc = "LEFT";
            break;
        } 
        cout << i.getStr() << "\t\t" << type << "\t\t" << asc << "\n";
    }
    vector<Token> postfix = InfixToPostfixConverter::Convert(tokensInfix);
    for (Token t : postfix) {
        cout << t.getStr() << '\n';
    }

    map<string, Polynom> pol {
    {"poly_a", Polynom("3x4 - 2x2 + 1")},
        {"poly_b", Polynom("2x3 + x - 4")},
    { "poly_c", Polynom("x3 - 5x5 + 3x3 - 2x + 6")},
    { "poly_d", Polynom("-x2 + 4x - 3")},
    { "poly_e", Polynom("2x5 - 3x3 + x")}
    };
    cout << PostfixCalculator::Calculate(postfix, pol) << '\n';

    Expression exp1("(poly_a * poly_b - poly_c) * 2 + poly_d * (-poly_e)");
    cout << exp1.Calculate(pol) << '\n';

    /*-------------------------*/

    Expression e("(pol1 + pol2) * pol3");
    map<string, Polynom> mp{
        {"pol1", Polynom("x3 + y3 + z3")},
        { "pol2", Polynom("x3 + 2xy + z") },
        { "pol3", Polynom("y2 + 3z3") }
    };
    cout << e.Calculate(mp) << '\n';
    return 0;
}

 /*
new_poly = pol1 + pol2
result = pol_a * pol_b - pol_c
my_poly_1 = 2 * polX + 3 * polY
final_result = (pol1 + pol2) * pol3
complex_poly = polA * (-5) + polB
p1 = p2 * p3 - 4 * p4
p_final=(1.2*poly1+2.3*poly2)*0.5
very_long_poly_name_2 =pol1 *pol2 +pol3 *pol4 *(-1) 
p_result_2=  ( pol_a + pol_b ) * (pol_c- pol_d)*(-0.5 )
p_final_3=(1.2*poly1+2.3*poly2)*0.5+1-1

 */