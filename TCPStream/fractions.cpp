/*
 * fraction_13kpl2.cpp
 *
 *  Created on: Oct 14, 2016
 *      Author: Kyle
 */

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include "fractions.h"

using namespace std;

FractionException::FractionException(const string& message) {
	this->message = message;
}

string& FractionException::what() {
	return message;
}

Fraction::Fraction() : num(0), den(1) { }
Fraction::Fraction(int n) : num(n), den(1) { }  // Conversion constructor

Fraction::Fraction(int n, int d) {
	if(d == 0) {
		throw FractionException("Cannot divide by zero");
	} // end if
	int cd = GCD(abs(n), abs(d));
	num = n / cd;
	den = d / cd;
	if(num < 0 && den < 0) {
		den *= -1;
	} // end if
	else if(num > 0 && den < 0) {
		den *= -1;
		num *= -1;
	} // end else if
}

int Fraction::numerator() {
	return num;
}

int Fraction::denominator() {
	return den;
}

int Fraction::GCD(int n, int m) {
	if(m <= n && (n % m) == 0) {
		return m;
	} else if (n < m) {
		return GCD(m,n);
	} else {
		return GCD(m, n % m);
	}  // end if
}  // end GCD()

int Fraction::compare(const Fraction& left, const Fraction& right) const {
	double l = double(left.num) / left.den;
	double r = double(right.num) / left.den;
	if(l > r) {
		return 1;
	} else if(l < r) {
		return -1;
	} else {
		return 0;
	}
}

Fraction Fraction::operator-() const {
	return Fraction(num * -1, den);
}

Fraction& Fraction::operator+=(const Fraction& right) {
	int cd = den * right.den;
	num = num * right.den + right.num * den;
	den = cd;
	return *this;
}

Fraction& Fraction::operator++() {
	num += den;  // Increment by 1
	return *this;
}

Fraction Fraction::operator++(int unused) {
	Fraction clone(num, den);
	num += den;  // Increment by 1
	return clone;
}

Fraction operator+(const Fraction& left, const Fraction& right) {
	int cd = left.den * right.den;
	return Fraction(left.num * right.den + right.num * left.den, cd);
}

Fraction operator-(const Fraction& left, const Fraction& right) {
	int cd = left.den * right.den;
	return Fraction(left.num * right.den - right.num * left.den, cd);
}

Fraction operator*(const Fraction& left, const Fraction& right) {
	return Fraction(left.num * right.num, left.den * right.den);
}

Fraction operator/(const Fraction& left, const Fraction& right) {
	return Fraction(left.num * right.den, left.den * right.num);
}

ostream& operator<<(ostream& out, const Fraction& value) {
	out << value.num << "/" << value.den;
	return out;
}

istream& operator>>(istream& in, Fraction& value) {
	string line;
	int loc, top, bottom;
	in >> line;
	loc = line.find("/");
	if(loc == -1) {
		top = atoi(line.c_str());
		bottom = 1;
	}
	else {
		top = atoi(line.substr(0,loc).c_str());
		bottom = atoi(line.substr(loc+1).c_str());
	}
	if(bottom == 0) {
		throw FractionException("Cannot divide by zero");
	}
	value.num = top;
	value.den = bottom;
	return in;
}

bool operator<(const Fraction& left, const Fraction& right) {
	if(left.compare(left, right) < 0) {
		return true;
	}
	else {
		return false;
	}
}

bool operator<=(const Fraction& left, const Fraction& right) {
	if(left.compare(left, right) <= 0) {
		return true;
	}
	else {
		return false;
	}
}

bool operator==(const Fraction& left, const Fraction& right) { // fix this
	if(left.compare(left, right) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool operator!=(const Fraction& left, const Fraction& right) { // fix this
	if(left.compare(left, right) != 0) {
		return true;
	}
	else {
		return false;
	}
}

bool operator>=(const Fraction& left, const Fraction& right) {
	if(left.compare(left, right) >= 0) {
		return true;
	}
	else {
		return false;
	}
}

bool operator>(const Fraction& left, const Fraction& right) {
	if(left.compare(left, right) > 0) {
		return true;
	}
	else {
		return false;
	}
}
