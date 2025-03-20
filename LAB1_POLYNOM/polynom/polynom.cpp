#include "polynom.h"
#include "monom.h"

void Polynom::AddMonom(const Monom& m) {
	if (monoms.isEmpty()) {
		monoms.PushFront(m);
		return;
	}

	size_t pos = 0;
	while (pos < monoms.size() && monoms[pos].degree > m.degree) {
		pos++;
	}

	if (pos < monoms.size() && monoms[pos].degree == m.degree) {
		monoms[pos].coef += m.coef;
	}
	else {
		if (pos == 0) monoms.PushFront(m);
		else monoms.PushAfter(pos - 1, m);
	}
}

Monom Polynom::ParseMonom(const string& monomStr) {
	double coef = 0;
	size_t degrees[3] = { 0, 0, 0 };
	size_t i = 0;

	// обработка знака монома
	bool isNegative = false;
	if (monomStr[i] == '-') {
		isNegative = true;
		i++;
	}
	else if (monomStr[i] == '+') i++;
	/*-------------------------------------*/

	// обработка числовой части коэффициента
	string coefStr;
	while (i < monomStr.size() && (isdigit(monomStr[i]) || monomStr[i] == '.')) {
		if (monomStr[i] == '.') coefStr += ',';
		else coefStr += monomStr[i];
		i++;
	}
	if (!coefStr.empty()) coef = stod(coefStr);
	else coef = 1;

	if (isNegative) coef = -coef;
	/*-------------------------------------*/

	// обработка степеней монома
	while (i < monomStr.size()) {
		if (monomStr[i] == 'x' || monomStr[i] == 'y' || monomStr[i] == 'z') {
			int varIndex = (monomStr[i] == 'x') ? 0 : (monomStr[i] == 'y') ? 1 : 2;
			i++;

			string degreeStr;
			if (i < monomStr.size() && monomStr[i] == '^') {
				i++;
				while (i < monomStr.size() && isdigit(monomStr[i])) {
					degreeStr += monomStr[i];
					i++;
				}
			}
			else {
				if (i < monomStr.size() && isdigit(monomStr[i])) {
					degreeStr += monomStr[i];
					i++;
				}
			}

			if (!degreeStr.empty()) {
				degrees[varIndex] = stoi(degreeStr);
			}
			else {
				degrees[varIndex] = 1;  // если степень не указана, то она равна 1
			}
		}
		else {
			throw invalid_argument("Invalid character in polynomial string");
		}
	}
	/*-------------------------------------*/

	// создание свёрнутой степени монома
	size_t degree = degrees[0] * 100 + degrees[1] * 10 + degrees[2];

	if (degrees[0] > 9 || degrees[1] > 9 || degrees[2] > 9) {
		throw invalid_argument("Degree of a variable cannot be greater than 9");
	}

	return Monom(coef, degree);
}

void Polynom::ParseFromString(const string& p) {
	vector<string> m;
	string cur_m;
	bool lastCharWasSign = true;

	for (int i = 0; i < p.size(); i++) {
		char c = p[i];
		if (c == ' ') {
			if (lastCharWasSign || (p[i + 1] == '-' || p[i + 1] == '+')) continue; // пропускаем пробелы вокруг знаков + -
			else throw invalid_argument("Invalid space in polynomial string");
		}

		if (c == '+' || c == '-') {
			if (!cur_m.empty() && !lastCharWasSign) {
				m.push_back(cur_m);
				cur_m.clear();
			}
			lastCharWasSign = true;
		}
		else lastCharWasSign = false;

		cur_m += c;
	}
	if (!cur_m.empty()) {
		m.push_back(cur_m);
	}

	for (const string& monomStr : m) {
		Monom monom = ParseMonom(monomStr);
		AddMonom(monom);
	}
}

Polynom::Polynom() {
	monoms.PushFront(Monom());
}

Polynom::Polynom(const string& polStr) {
	ParseFromString(polStr);
	monoms.PushAfter(monoms.size() - 1, Monom());
}

double Polynom::calculate(double x, double y, double z) const {
	double res = 0.0;
	for (size_t i = 0; i < monoms.size(); i++) {
		const Monom& monom = monoms[i];
		int degX = monom.degree / 100;
		int degY = (monom.degree / 10) % 10;
		int degZ = monom.degree % 10;
		res += monom.coef * pow(x, degX) * pow(y, degY) * pow(z, degZ);
	}
	return res;
}

ostream& operator<<(ostream& os, const Polynom& polinom) {
	bool isFirst = true;
	for (size_t i = 0; i < polinom.monoms.size(); ++i) {
		const Monom& monom = polinom.monoms[i];
		if (monom.coef != 0) {
			if (!isFirst) {
				os << (monom.coef > 0 ? " + " : " - ");
			}
			else if (monom.coef < 0) os << (isFirst ? "-" : " - ");

			if (abs(monom.coef) != 1 || (monom.degree == 0)) {
				os << abs(monom.coef);
			}

			int degX = monom.degree / 100;
			int degY = (monom.degree / 10) % 10;
			int degZ = monom.degree % 10;

			if (degX > 0) {
				os << "x";
				if (degX > 1) os << "^" << degX;
			}
			if (degY > 0) {
				os << "y";
				if (degY > 1) os << "^" << degY;
			}
			if (degZ > 0) {
				os << "z";
				if (degZ > 1) os << "^" << degZ;
			}
			isFirst = false;
		}
	}
	if (isFirst) {
		os << "0";
	}
	return os;
}

Polynom Polynom::operator+(const Polynom& other) const {
	Polynom result;
	size_t i = 0, j = 0;

	while (i < monoms.size() && j < other.monoms.size()) {
		const Monom& monom1 = monoms[i];
		const Monom& monom2 = other.monoms[j];

		if (monom1.degree > monom2.degree) {
			result.AddMonom(monom1);
			i++;
		}
		else if (monom1.degree < monom2.degree) {
			result.AddMonom(monom2);
			j++;
		}
		else {
			double newCoef = monom1.coef + monom2.coef;
			if (newCoef != 0) {
				result.AddMonom(Monom(newCoef, monom1.degree));
			}
			i++;
			j++;
		}
	}

	// добавляем оставшиеся мономы из текущего полинома
	while (i < monoms.size()) {
		result.AddMonom(monoms[i]);
		i++;
	}

	// добавляем оставшиеся мономы из другого полинома
	while (j < other.monoms.size()) {
		result.AddMonom(other.monoms[j]);
		j++;
	}

	return result;
}

Polynom Polynom::operator-(const Polynom& other) const {
	Polynom result;
	size_t i = 0, j = 0;

	while (i < monoms.size() && j < other.monoms.size()) {
		const Monom& monom1 = monoms[i];
		const Monom& monom2 = other.monoms[j];

		if (monom1.degree > monom2.degree) {
			result.AddMonom(monom1);
			i++;
		}
		else if (monom1.degree < monom2.degree) {
			result.AddMonom(Monom(-monom2.coef, monom2.degree)); // вычитаем моном из второго полинома
			j++;
		}
		else {
			double newCoef = monom1.coef - monom2.coef;
			if (newCoef != 0) {
				result.AddMonom(Monom(newCoef, monom1.degree)); // степени одинаковые, вычитаем коэффициенты
			}
			i++;
			j++;
		}
	}

	// добавляем оставшиеся мономы из текущего полинома
	while (i < monoms.size()) {
		result.AddMonom(monoms[i]);
		i++;
	}

	// вычитаем оставшиеся мономы из другого полинома
	while (j < other.monoms.size()) {
		result.AddMonom(Monom(-other.monoms[j].coef, other.monoms[j].degree));
		j++;
	}

	return result;
}

Polynom Polynom::operator*(double c) const {
	Polynom res;
	for (size_t i = 0; i < monoms.size(); i++) {
		const Monom& monom = monoms[i];
		res.AddMonom(Monom(monom.coef * c, monom.degree));
	}

	return res;
}

Polynom operator*(double c, const Polynom& p) {
	return p * c;
}

Polynom Polynom::operator*(const Polynom& other) {
	Polynom res;
	for (size_t i = 0; i < monoms.size(); i++) {
		for (size_t j = 0; j < other.monoms.size(); j++) {
			double newCoef = monoms[i].coef * other.monoms[j].coef;

			int degX = monoms[i].degree / 100, degX1 = other.monoms[j].degree / 100;
			int degY = (monoms[i].degree / 10) % 10, degY1 = (other.monoms[j].degree / 10) % 10;
			int degZ = monoms[i].degree % 10, degZ1 = other.monoms[j].degree % 10;

			if ((degX + degX1) > 9 || (degY + degY1) > 9 || (degZ + degZ1) > 9)
				throw overflow_error("The resulting degree of the monome variable exceeds the allowed limit");

			size_t newDegree = (degX + degX1) * 100 + (degY + degY1) * 10 + (degZ + degZ1);
			res.AddMonom(Monom(newCoef, newDegree));
		}
	}
	return res;
}


Polynom Polynom::derivative(char var) const {
	Polynom res;
	for (int i = 0; i < monoms.size(); i++) {
		const Monom& monom = monoms[i];

		if (monom.degree == 0) continue; // производная от const равна 0, поэтому не добавляем

		double newCoef = monom.coef;
		size_t newDegree = monom.degree;

		switch (var) {
		case 'x':
			if ((newDegree / 100) > 0) {
				newCoef *= (newDegree / 100);
				newDegree -= 100;
			}
			else newCoef = 0;
			break;
		case 'y':
			if (((newDegree / 10) % 10) > 0) {
				newCoef *= ((newDegree / 10) % 10);
				newDegree -= 10;
			}
			else newCoef = 0;
			break;
		case 'z':
			if ((newDegree % 10) > 0) {
				newCoef *= (newDegree % 10);
				newDegree -= 1;
			}
			else newCoef = 0;
			break;
		default:
			throw invalid_argument("Invalid variable");
		}
		if (newCoef != 0) res.AddMonom(Monom(newCoef, newDegree));
	}
	return res;
}

//Polynom Polynom::integrate(char var) const {
//	Polynom res;
//	for (int i = 0; i < monoms.size(); i++) {
//		const Monom& monom = monoms[i];
//
//		double newCoef = monom.coef;
//		size_t newDegree = monom.degree;
//
//		switch (var) {
//		case 'x':
//			int degX = newDegree / 100;
//			if (degX < 9) {
//				newDegree += 100;
//				newCoef /= (degX + 1);
//			}
//			break;
//		case 'y':
//			int degY = (newDegree / 10) % 10;
//			if (degY < 9) {
//				newDegree += 10;
//				newCoef /= (degY + 1);
//			}
//			break;
//		case 'z':
//			int degZ = newDegree % 10;
//			if (degZ < 9) {
//				newDegree += 1;
//				newCoef /= (degZ + 1);
//			}
//			break;
//		default:
//			throw invalid_argument("Invalid variable");
//		}
//		res.AddMonom(Monom(newCoef, newDegree));
//	}
//	return res;
//}