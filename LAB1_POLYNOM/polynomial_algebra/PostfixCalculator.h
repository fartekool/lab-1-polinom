#pragma once

#include "../polynom/polynom.h"
#include <vector>
#include "Parser.h"
#include "stack.h"

class PostfixCalculator {
public:
    static Polynom Calculate(const vector<Token>& expr, const map<string, Polynom>& pol);
};