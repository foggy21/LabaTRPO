#include "Integer.h"
#include <iostream>
#include <string>
using namespace arbitary_precision_arithmetic;

Integer::Integer() 
{
	size = BASE_SIZE;
	digits = new unsigned long long[size];
	SIGN = 1;
}

Integer::Integer(const Integer& other)
{
	for (int i = 0; i < BASE_SIZE; ++i) {
		digits[i] = other.digits[i];
	}

	SIGN = other.SIGN;
}

Integer::Integer(char unsigned other) {
	SIGN = 1;
	digits[0] = other;
}

Integer::Integer(char other) {
	if (other < 0) SIGN = -1;
	else SIGN = 1;
	digits[0] = abs(other);
}

Integer::Integer(short unsigned other) {
	SIGN = 1;
	digits[0] = other;
}

Integer::Integer(short other) {
	if (other < 0) SIGN = -1;
	else SIGN = 1;
	digits[0] = abs(other);
}

Integer::Integer(unsigned int other) {
	SIGN = 1;
	digits[0] = other;
}

Integer::Integer(int other) {
	if (other < 0) SIGN = -1;
	else SIGN = 1;
	digits[0] = abs(other);
}

Integer::Integer(long unsigned other) {
	SIGN = 1;
	digits[0] = other;
}

Integer::Integer(long other) {
	if (other < 0) SIGN = -1;
	else SIGN = 1;
	digits[0] = abs(other);
}

Integer::Integer(long long unsigned other) {
	SIGN = 1;
	digits[0] = other;
}

Integer::Integer(long long other) {
	if (other < 0) SIGN = -1;
	else SIGN = 1;
	digits[0] = abs(other);
}

Integer& Integer::operator=(const Integer& other) {
	size = other.size;
	digits = new unsigned long long[size];
	for (int i = 0; i < size; ++i) {
		digits[i] = other.digits[i];
	}
	SIGN = other.SIGN;
	return *this;
}

/* �������� */

Integer& Integer::operator+=(const Integer& other) {
	//Check if signs equal
	if (this->SIGN == other.SIGN) {
		for (int i = 0; i < BASE_SIZE; ++i) {
			this->digits[i] += other.digits[i]; // Add and ignore overflow
		}

		for (int i = 0; i < BASE_SIZE - 1; ++i) {
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
			for (int i = 0; i < BASE_SIZE; ++i) {
				this->digits[i] -= other.digits[i];
			}

			for (int i = 0; i < BASE_SIZE; ++i) {
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
			for (int i = 0; i < BASE_SIZE; ++i) {
				other.digits[i] -= this->digits[i];
			}

			for (int i = 0; i < BASE_SIZE; ++i) {
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
		for (int i = 0; i < BASE_SIZE; ++i) {
			this->digits[i] -= other.digits[i];
		}

		for (int i = 0; i < BASE_SIZE; ++i) {
			if (this->digits[i] < 0) {
				this->digits += BASE;
				this->digits[i + 1]--;
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

	for (int i = 0; i < BASE_SIZE; ++i) {
		for (int j = 0; j < BASE_SIZE - i; ++j) { // don't pick digits more than BASE_SIZE
			num.digits[i + j] += this->digits[i] * other.digits[j];	
		}
	}

	// Getting rid of overflow
	for (int i = 0; i < BASE_SIZE - 1; ++i) {
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
	for (int i = 0; i < BASE_SIZE; ++i) {
		if (this->digits[i] != other.digits[i]) return false;
	}
	return true;
}

bool Integer::operator!=(const Integer& other) const {
	for (int i = 0; i < BASE_SIZE; ++i) {
		if (this->digits[i] != other.digits[i]) return true;
	}
	return false;
}

bool Integer::operator>(const Integer& other) const {
	if (this->SIGN > other.SIGN) return true;
	for (int i = BASE_SIZE - 1; i > 0; --i) {
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
	for (int i = BASE_SIZE - 1; i > 0; --i) {
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
	for (int i = BASE_SIZE - 1; i > 0; --i) {
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
	for (int i = BASE_SIZE - 1; i > 0; --i) {
		if (this->digits[i] > 0 && other.digits[0]) return false;
		else if (other.digits[i] > 0) {
			if (other.digits[i] >= this->digits[i]) return true;
			else return false;
		}
	}
}

explicit Integer::operator bool() const{
	return true ? this != 0 : false;
}

explicit Integer::operator char unsigned() const {
	return this->digits[0];
}


explicit Integer::operator char() const {
	return this->digits[0];
}

explicit Integer::operator short unsigned int() const {
	return this->digits[0];
}


explicit Integer::operator short int() const {
	return this->digits[0];
}

explicit Integer::operator unsigned int() const {
	return this->digits[0];
}

explicit Integer::operator int() const {
	return this->digits[0];
}

explicit Integer::operator long unsigned int() const {
	return this->digits[0];
}

explicit Integer::operator long int() const {
	return this->digits[0];
}

explicit Integer::operator long long unsigned int() const {
	return this->digits[0];
}

explicit Integer::operator long long int() const {
	return this->digits[0];
}

template <typename OStream>
OStream&& operator<<(OStream&& out, const Integer& num) {
	std::string result;
	
	char buffer[10];

	for(int i = Integer::BASE_SIZE - 1; i >= 0; --i) {
		sprintf(buffer, "%09d", num.digits[i]);
		result += buffer;
	}

	int first_idx = result.find_first_not_of("0");
	if (first_idx == std::string::npos) {
		out << '0';
	}
	else {
		out << result.substr(first_idx);
	}

	return out;
}

Integer::~Integer() 
{
	delete[] digits;
}