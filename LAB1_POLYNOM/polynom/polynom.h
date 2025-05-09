#pragma once

#include "monom.h"
#include <iostream>
#include "list.h"
#include <string>
#include <vector>
#include <sstream>

class Polynom {
private:

	List<Monom> monoms;

	void AddMonom(const Monom& m);

	Monom ParseMonom(const string& monomStr);

	void ParseFromString(const string& p);

	void generateString(ostream& os) const;

	mutable string infix;

	mutable bool infixChanged;
public:
	Polynom();

	Polynom(const string& polStr);

	double calculate(double x, double y, double z) const;

	friend ostream& operator<<(ostream& os, const Polynom& polinom);

	Polynom& operator=(const Polynom& other);

	Polynom operator+(const Polynom& other) const;

	Polynom operator-(const Polynom& other) const;

	Polynom operator*(double c) const;

	friend Polynom operator* (double c, const Polynom& p);

	Polynom operator*(const Polynom& other);

	Polynom derivative(char var) const;

	Polynom integrate(char var) const;

	string GetInfix() const;

};
