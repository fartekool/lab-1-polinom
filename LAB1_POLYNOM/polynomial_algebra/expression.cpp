#include "expression.h"
#include "stack.h"

#include <sstream>

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
    bool LastWasOperator = true;
    for (size_t i = 0; i < str.size(); i++) {
        char c = str[i];
        if (isdigit(c) || (c == '.' && !cur.empty() && isdigit(cur.back()))) {
            cur += c;
            LastWasOperator = false;
        }
        else if (isalpha(c) || (c == '_' && !cur.empty() && isalpha(cur.back()))) {
            cur += c;
            LastWasOperator = false;
        }
        else if (ExpressionValidator::IsOperator(c) || c == '(' || c == ')' || c == '=') {
            if (!cur.empty()) {
                lexems.push_back(cur);
                cur.clear();
            }
            if (c == '-' && (LastWasOperator || lexems.empty()))
                lexems.push_back("_");
            else
                lexems.push_back(string(1, c));
            LastWasOperator = (c != ')');
        }
        else if (c == ' ' && !cur.empty()) {
            lexems.push_back(cur);
            cur.clear();
        }
    }
    if (!cur.empty())
        lexems.push_back(cur);
    return lexems;
}

map<string, int> InfixToPostfixConverter::priority = {
    {"=", 0}, {"+", 1}, {"-", 1}, {"*", 2}
};

string InfixToPostfixConverter::Convert(const string& infix) {
    string postfix;
    vector<string> lexems = Parser::Parse(infix);
    TStack<string> st;
    string stItem;
    for (const string& item : lexems) {
        if (item == "(") st.Push(item);
        else if (item == ")") {
            stItem = st.Top(); st.Pop();
            while (stItem != "(") {
                postfix += stItem + " ";
                stItem = st.Top(); st.Pop();
            }
        }
        else if (priority.count(item)) { // проверка что item является оператором
            while (!st.IsEmpty()) {
                stItem = st.Top(); st.Pop();
                if (priority[item] <= priority[stItem])
                    postfix += stItem + " ";
                else {
                    st.Push(stItem);
                    break;
                }
            }
            st.Push(item);
        }
        else {
            postfix += item + " ";
        }
    }
    while (!st.IsEmpty()) {
        stItem = st.Top(); st.Pop();
        postfix += stItem + " ";
    }
    return postfix;
}

Polynom PostfixCalculator::Calculate(const string& postfix) {
    // Необходима реализация таблиц для того чтобы искать полиномы по ключу а уже после их использовать
    /*TStack<Polynom> st;
    stringstream ss(postfix);
    string lexem;
    Polynom leftOp, rightOp;
    while (ss >> lexem) {
        if (lexem == "+") {
            rightOp = Polynom(st.Top()); st.Pop();
            leftOp = Polynom(st.Top()); st.Pop();
            st.Push(leftOp + rightOp);
        }
        else if (lexem == "-") {
            rightOp = Polynom(st.Top()); st.Pop();
            leftOp = Polynom(st.Top()); st.Pop();
            st.Push(leftOp - rightOp);
        }
        else if (lexem == "*") {
            rightOp = Polynom(st.Top()); st.Pop();
            leftOp = Polynom(st.Top()); st.Pop();
            st.Push(leftOp * rightOp);
        }
        else if (lexem == "_") {
            rightOp = Polynom(st.Top());
            st.Pop();
            st.Push((-1) * rightOp);
        }
        else {
            Polynom value = Polynom(lexem);
            st.Push(value);
        }
    }
    return st.Top();*/
}

Expression::Expression(const string& expr) : infix(expr) {
    ExpressionValidator::Validate(infix);
    postfix = InfixToPostfixConverter::Convert(infix);
}

string Expression::GetInfix() const { return infix; }
string Expression::GetPostfix() const { return postfix; }

//vector<string> Expression::GetOperands() const {
//    vector<string> op;
//    // ...
//    return op;
//}

//Polynom Expression::Calculate() {
//    return PostfixCalculator::Calculate(postfix);
//}

