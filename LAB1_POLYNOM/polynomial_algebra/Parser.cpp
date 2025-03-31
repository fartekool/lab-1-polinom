#include "Parser.h"

Token::Token(string token, Type type, OperatorAssociativity asc) : type(type), str(token) {
    // если токен - оператор, но ассоциативность не задана - ошибка (алгоритма)
    if (type == OPERATOR && asc == NONE)
        throw logic_error("Associativity required!");

    // если токен - НЕ оператор, но ассоциативность задана - ошибка
    else if (type != OPERATOR && asc != NONE)
        throw logic_error("Non-operator token can't have an associativity!");

    opAsc = asc;
}

int Token::getPrecendance() const
{
    static map<string, int> op_leftassociative =
    {
        {"+", 2},
        {"-", 2},
        {"*", 3},
    };

    static map<string, int> op_rightassociative =
    {
        {"-", 4} // унарное отрицание
    };

    // В зависимости от ассоциативности один и тот же символ означает разные операторы
    switch (opAsc)
    {
    case LEFT:
        // Если str является ключом map-а, значит мы знаем такой оператор
        if (op_leftassociative.find(str) != op_leftassociative.end()) return op_leftassociative[str];
        else throw invalid_argument("Unknown Operator!");
        break;
    case RIGHT:
        if (op_rightassociative.find(str) != op_rightassociative.end()) return op_rightassociative[str];
        else throw invalid_argument("Unknown Operator!");
        break;
    case NONE:
    {
        stringstream ss;
        ss << "Token \"" << str << "\" is not an operator, impossible.";
        throw logic_error(ss.str());
    }
    break;
    }
}

bool Token::operator==(const Token& other) const {
    return type == other.type && opAsc == other.opAsc && str == other.str;
}

bool Token:: operator!=(const Token& other) const {
    return !(*this == other);
}

const Token::Type& Token::getType() const { return type; }
const Token::OperatorAssociativity& Token::getAsc() const { return opAsc; }
const string& Token::getStr() const { return str; }

/*----------------------------------------------------------------------------*/

vector<Token> Parser::Parse(const string& expr)
{
    enum State
    {
        S0, // Стартовое
        S1, // Токенизация скобки/оператора
        S2, // Запись целого числа в буфер
        S3, // Запись floating-point числа в буфер
        S4, // Запись имени полинома в буфер
        S5  // Токенизация записанного числа/имени полинома из буфера
    };

    vector<Token> tokens;
    State state = S0;

    std::string validOperators = "+-*";

    bool isDigit, isLetter, isOp, isParanth, isPoint, isLParanth, isRParanth, isSpace, isUnderscore;

    std::string buffer;
    Token::Type bufferTokenType = Token::INT_LITERAL;

    for (auto& s : expr)
    {
        // Определяем тип символа
        isDigit = std::isdigit(s);
        isLetter = std::isalpha(s);
        isLParanth = s == '(';
        isRParanth = s == ')';
        isParanth = isLParanth || isRParanth;
        isPoint = s == '.';
        isOp = validOperators.find(s) != validOperators.npos;
        isSpace = s == ' ';
        isUnderscore = s == '_';

        // Если тип символа неопределен, значит ошибка в синтаксисе
        if (!(isDigit || isLetter || isParanth || isPoint || isOp || isSpace || isUnderscore))
        {
            cout << s << '\n';
            stringstream ss;
            ss << "Unknown symbol: " << s;
            throw invalid_argument(ss.str());
        }


        // Смена состояния
        switch (state)
        {
        case S0:
            if (isOp || isParanth)
                state = S1;
            else if (isDigit)
                state = S2;
            else if (isLetter || isUnderscore)
                state = S4;
            else if (isPoint)
            {
                stringstream ss;
                ss << "Unexpected symbol: \"" << s << "\"";
                throw invalid_argument(ss.str());
            }
            else if (isSpace)
                state = S0;
            break;
        case S1:
            if (isDigit)
                state = S2;
            else if (isLetter || isUnderscore)
                state = S4;
            else if (isPoint)
            {
                stringstream ss;
                ss << "Unexpected symbol: \"" << s << "\"";
                throw invalid_argument(ss.str());
            }
            else if (isSpace)
                state = S0;
            break;
        case S2:
            bufferTokenType = Token::INT_LITERAL;
            if (isPoint)
                state = S3;
            else if (isParanth || isOp)
                state = S5;
            else if (isLetter || isUnderscore)
            {
                stringstream ss;
                ss << "Unexpected symbol: \"" << s << "\"";
                throw invalid_argument(ss.str());
            }
            else if (isSpace)
                state = S5;
            break;
        case S3:
            bufferTokenType = Token::FLOAT_LITERAL;
            if (isParanth || isOp)
                state = S5;
            else if (isPoint || isUnderscore)
            {
                stringstream ss;
                ss << "Unexpected symbol: \"" << s << "\"";
                throw invalid_argument(ss.str());
            }
            else if (isSpace)
                state = S5;
            break;
        case S4:
            bufferTokenType = Token::POLINOM_NAME;
            if (isLParanth || isOp || isSpace || isRParanth)
                state = S5;
            else if (isPoint)
            {
                cout << s << '\n';
                stringstream ss;
                ss << "Unexpected symbol \"" << s << "\"";
                throw invalid_argument(ss.str());
            }
            break;
        case S5:
            if (isParanth || isOp)
                state = S1;
            else if (isDigit)
                state = S2;
            else if (isLetter || isUnderscore)
                state = S4;
            else if (isPoint)
            {
                stringstream ss;
                ss << "Unexpected symbol: \"" << s << "\"";
                throw invalid_argument(ss.str());
            }
            else if (isSpace)
                state = S0;
            break;
        default:
            break;
        }

        auto tokenize_Op_Paranth_Sep = [&]()
            {
                if (isOp)
                {
                    // обработка unary negation
                    if (tokens.size() == 0 || tokens[tokens.size() - 1].getType() == Token::L_PARANTHESIS)
                        tokens.push_back({ std::string{s}, Token::OPERATOR, Token::RIGHT });
                    else
                        tokens.push_back({ std::string{s}, Token::OPERATOR, Token::LEFT });
                }
                else if (isParanth)
                {
                    tokens.push_back({ std::string{s}, isRParanth ? Token::R_PARANTHESIS : Token::L_PARANTHESIS });
                }
            };

        // Действия
        switch (state)
        {
        case S1:
            tokenize_Op_Paranth_Sep();
            break;
        case S2: case S3: case S4:
            buffer.push_back(s);
            break;
        case S5:
            tokens.push_back({ buffer, bufferTokenType });
            buffer.clear();
            tokenize_Op_Paranth_Sep();
            break;
        }
    }
    if (!buffer.empty())
        tokens.push_back({ buffer, bufferTokenType });
    return tokens;
}