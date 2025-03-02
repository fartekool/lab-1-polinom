#pragma once

#include <iostream>

struct Monom {
    double coef;
    size_t degree;
    Monom(double c = 0, size_t d = 0) : coef(c), degree(d) {}
};