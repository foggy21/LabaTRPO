#include "Integer.h"
#include <iostream>
using namespace arbitary_precision_arithmetic;

Integer::Integer() 
{
	for (int i = 0; i < SIZE; ++i) {
		digits[i] = 0;
	}
	SIGN = 1;
}

Integer::Integer(const Integer& other)
{
	for (int i = 0; i < SIZE; ++i) {
		digits[i] = other.digits[i];
	}
	SIGN = other.SIGN;
}

Integer& Integer::operator=(const Integer& other) {
	for (int i = 0; i < SIZE; ++i) {
		digits[i] = other.digits[i];
	}
	SIGN = other.SIGN;
	return *this;
}

/* �������� */

Integer& Integer::operator+=(const Integer& other) {
	//Check if signs equal
	if (this->SIGN == other.SIGN) {
		for (int i = 0; i < SIZE; ++i) {
			this->digits[i] += other.digits[i]; // Add and ignore overflow
		}

		for (int i = 0; i < SIZE - 1; ++i) {
			if (this->digits[i] >= BASE) {
				this->digits[i] -= BASE;
				this->digits[i + 1]++;
			}
		}

		return *this;
	}
	else {
		//Subtracts from one number the second, depending on whose sign is greater
		if (this->SIGN > other.SIGN) {
			if (*this < other) this->SIGN = -1;
			for (int i = 0; i < SIZE; ++i) {
				this->digits[i] -= other.digits[i];
			}

			for (int i = 0; i < SIZE; ++i) {
				if (this->digits[i] < 0) {
					this->digits[i] += BASE;
					this->digits[i + 1]--;
				}
			}
			return *this;
		}
		else {
			Integer other(other);
			if (other < *this) other.SIGN = -1;
			for (int i = 0; i < SIZE; ++i) {
				other.digits[i] -= this->digits[i];
			}

			for (int i = 0; i < SIZE; ++i) {
				if (other.digits[i] < 0) {
					other.digits[i] += BASE;
					other.digits[i]--;
				}
			}
			return other;
		}
	}
	
}

Integer Integer::operator+(const Integer& other) const {
	// Lite operator's += version
	Integer num(*this);
	if (this->SIGN == num.SIGN) {
		num += other;
		return num;
	}
	else if (num > other) {
		num += other;
		return num;
	}
	else {
		Integer other(other);
		other += num;
		return other;
	}
}

Integer& Integer::operator++()
{
	*this+=1;
	if (this >= 0) this->SIGN = 1; // If num was equal -1 (Feature)
	return *this;
}

/* ��������� */

Integer& Integer::operator-=(const Integer& other)
{
	//If sings equal, then subtracts
	if (this->SIGN == other.SIGN) {
		for (int i = 0; i < SIZE; ++i) {
			this[i] -= other.digits[i];
		}

		for (int i = 0; i < SIZE; ++i) {
			if (this[i] < 0) {
				this[i] += BASE;
				this[i + 1]--;
			}
		}
		return *this;
	}
	else {
		//Based on the += operator, we add a negative to a positive number
		if (this->SIGN == 1) {
			return *this += other;
		}
		else {
			Integer other(other);
			return other += *this;
		}
	}
	
}

Integer Integer::operator-(const Integer& other) const
{
	//Relax
	Integer num(*this);
	num -= other;
	return num;
}

Integer& Integer::operator--() {
	*this -= 1;
	if (this <= 0) this->SIGN = -1; //Feature again.
	return *this;
}

/* ��������� */

Integer Integer::operator*(const Integer& other) const
{
	Integer num;

	if (this->SIGN == other.SIGN) num.SIGN = 1;
	else num.SIGN = -1;

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE - i; ++j) { // don't pick digits more than SIZE
			num.digits[i + j] += this->digits[i] * other.digits[j];	
		}
	}

	// Getting rid of overflow
	for (int i = 0; i < SIZE - 1; ++i) {
		num.digits[i + 1] += num.digits[i] / BASE;
		num.digits[i] %= BASE;
	}

	return num;
}

Integer& Integer::operator*=(const Integer& other) {
	*this = *this * other;
	return *this;
}

/* ������� */

Integer& Integer::operator/=(const Integer&) {
	//	Well, here my powers are all ... over ...
}

Integer Integer::operator/(const Integer&) const {
	// P.s obviously done based on the operator /=
}

Integer Integer::operator%(const Integer&) const {
	// M. Ugu.
}
Integer& Integer::operator%=(const Integer&) {
	// UGU.
}


/* ��������� */

bool Integer::operator==(const Integer& other) const {
	if (this->SIGN != other.SIGN) return false;
	for (int i = 0; i < SIZE; ++i) {
		if (this->digits[i] != other.digits[i]) return false;
	}
	return true;
}

bool Integer::operator!=(const Integer& other) const {
	for (int i = 0; i < SIZE; ++i) {
		if (this->digits[i] != other.digits[i]) return true;
	}
	return false;
}

bool Integer::operator>(const Integer& other) const {
	if (this->SIGN > other.SIGN) return true;
	for (int i = SIZE - 1; i > 0; --i) {
		if (other.digits[i] > 0 && this->digits[i] == 0) return false;
		else if (this->digits[i] > 0) {
			if (this->digits[i] > other.digits[i]) return true;
			else return false;
		}
	}
	return false;
}

bool Integer::operator>=(const Integer& other) const {
	if (this->SIGN < other.SIGN) return false;
	for (int i = SIZE - 1; i > 0; --i) {
		if (other.digits[i] > 0 && this->digits[i] == 0) return false;
		else if (this->digits[i] > 0) {
			if (this->digits[i] >= other.digits[i]) return true;
			else return false;
		}
	}
	return false;
}

bool Integer::operator<(const Integer& other) const {
	if (this->SIGN < other.SIGN) return true;
	for (int i = SIZE - 1; i > 0; --i) {
		if (this->digits[i] > 0 && other.digits[i] == 0) return false;
		else if (other.digits[i] > 0) {
			if (other.digits[i] > this->digits[i]) return true;
			else return false;
		}
	}
	return true;
}

bool Integer::operator<=(const Integer& other) const {
	if (this->SIGN > other.SIGN) return false;
	for (int i = SIZE - 1; i > 0; --i) {
		if (this->digits[i] > 0 && other.digits[0]) return false;
		else if (other.digits[i] > 0) {
			if (other.digits[i] >= this->digits[i]) return true;
			else return false;
		}
	}
}

Integer::~Integer() 
{
	delete[] digits;
}