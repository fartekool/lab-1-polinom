#pragma once

#include <map>
#include <string>
#include <vector>
#include "stack.h"
#include "Parser.h"

using namespace std;

class InfixToPostfixConverter {
public:
    static vector<Token> Convert(const std::vector<Token>& expr);
};