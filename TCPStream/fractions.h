/*
 * fraction_13kpl2.h
 *
 *  Created on: Oct 14, 2016
 *      Author: Kyle
 */

#pragma once

using namespace std;

class Fraction {
public:
	Fraction();  // No parameter constructor; 0/1 fraction
	Fraction(int num);  // Single parameter conversion constructor; num/1 fraction
	Fraction(int num, int den);  // Double parameter constructor; num/den fraction
	int numerator();  // Accessor for the numerator
	int denominator();  //Accessor for the denominator
	Fraction operator-() const;  // Fraction overload for the negation operation
	Fraction& operator+=(const Fraction& right);  // Fraction overload for the assign and add operator
	Fraction& operator++();  // Fraction overload for the pre-increment operator
	Fraction operator++(int);  // Fraction overload for the post-increment operator
	int compare(const Fraction& left, const Fraction& right) const;  // Compare the left and right fraction; 1 if left > right; -1 if left < right; 0 otherwise
private:
	int num;  // The numerator for the fraction
	int den;  // The denominator for the fraction
	int GCD(int n, int m);  // Find the greatest common denominator between n and m

friend Fraction operator+(const Fraction& left, const Fraction& right);  // Fraction overload for the addition operator; Adds the two fractions together
friend Fraction operator-(const Fraction& left, const Fraction& right);  // Fraction overload for the subtraction operator; Subtract the right from the left
friend Fraction operator*(const Fraction& left, const Fraction& right);  // Fraction overload for the multiplication operator; Multiple the two fractions together
friend Fraction operator/(const Fraction& left, const Fraction& right);  // Fraction overload for the division operator; Divide the right from the left
friend ostream& operator<<(ostream& out, const Fraction& value);  // Output stream overload for Fractions; Prints the fraction as 'NUM/DEN'
friend istream& operator>>(istream& in, Fraction& value);  // Input stream overload for Fractions; Accept both 'NUM/DEN' or 'NUM' input
};  // end Fraction class

class FractionException {
public:
	FractionException(const string& message);  // Fraction cannot have a zero denominator
	string& what();  // Return error message for catch block
private:
	string message;  // Message the exception will display
};  // end FractionException class

bool operator<(const Fraction& left, const Fraction& right);  // Overload of the less than operator; Determine if left Fraction is less than right Fraction
bool operator<=(const Fraction& left, const Fraction& right);  // Overload of the less than or equal operator; Determine if left Fraction is less than or equal to right Fraction
bool operator==(const Fraction& left, const Fraction& right);  // Overload of the equals operator; Determine if left Fraction is equal to the right Fraction
bool operator!=(const Fraction& left, const Fraction& right);  // Overload of the not equal to operator; Determine if left Fraction not equal to the right Fraction
bool operator>=(const Fraction& left, const Fraction& right);  // Overload of the greater than or equal to operator; Determine if left Fraction is greater than or equal to right Fraction
bool operator>(const Fraction& left, const Fraction& right);  // Overload of the greater than operator; Determine if left Fraction is greater than right Fraction
