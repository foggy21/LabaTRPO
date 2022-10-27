#include "Integer.h"
#include <iostream>
#include <string>
using namespace arbitary_precision_arithmetic;

Integer::Integer() 
{
	size = BASE_SIZE;
	digits = new unsigned long long[size]{0};
	sign = 1;
}

Integer::Integer(const Integer& other)
{
	size = other.size;
	digits = new unsigned long long[size] {0};
	for (int i = 0; i < size; ++i) {
		digits[i] = other.digits[i];
	}
	sign = other.sign;
}

Integer::Integer(char unsigned other) : Integer::Integer() {
	digits[0] = other;
}

Integer::Integer(char other) : Integer::Integer() {
	if (other < 0) sign = -1;
	else sign = 1;
	digits[0] = abs(other);
}

Integer::Integer(short unsigned other) : Integer::Integer() {
	digits[0] = other;
}

Integer::Integer(short other) : Integer::Integer() {
	if (other < 0) sign = -1;
	else sign = 1;
	digits[0] = abs(other);
}

Integer::Integer(unsigned int other) : Integer::Integer() {
	digits[0] = other;
}

Integer::Integer(int other) : Integer::Integer() {
	if (other < 0) sign = -1;
	else sign = 1;
	digits[0] = abs(other);
}

Integer::Integer(long unsigned other) : Integer::Integer() {
	digits[0] = other;
}

Integer::Integer(long other) : Integer::Integer() {
	if (other < 0) sign = -1;
	else sign = 1;
	digits[0] = abs(other);
}

Integer::Integer(long long unsigned other) : Integer::Integer() {
	digits[0] = other;
}

Integer::Integer(long long other) : Integer::Integer() {
	if (other < 0) sign = -1;
	else sign = 1;
	digits[0] = abs(other);
}

Integer& Integer::operator=(const Integer& other) {
	if (other.size > size) {
		delete[] digits;
		size = other.size;
	}
	digits = new unsigned long long[size] {0};
	for (int i = 0; i < size; ++i) {
		digits[i] = other.digits[i];
	}
	sign = other.sign;
	return *this;
}

/* Сложение */

Integer& Integer::operator+=(const Integer& other) {
	//Check if signs equal
	if (this->sign == other.sign) {
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
		if (this->sign > other.sign) {
			if (*this < other) this->sign = -1;
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
			if (other < *this) other.sign = -1;
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
	if (this->sign == num.sign) {
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

Integer Integer::operator+() const {
	Integer other(*this);
	return other;
}

Integer& Integer::operator++()
{
	*this+=1;
	if (this >= 0) this->sign = 1; // If num was equal -1 (Feature)
	return *this;
}

Integer Integer::operator++(int) {
	*this += 1;
	if (this >= 0) this->sign = 1; // If num was equal -1 (Feature)
	return *this;
}

/* Вычитание */

Integer& Integer::operator-=(const Integer& other)
{
	//If sings equal, then subtracts
	if (this->sign == other.sign) {
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
		if (this->sign == 1) {
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

Integer Integer::operator-() const {
	Integer other(*this);
	other.sign = -other.sign;
	return other;
}

Integer& Integer::operator--() {
	*this -= 1;
	if (this <= 0) this->sign = -1; //Feature again.
	return *this;
}

Integer Integer::operator--(int) {
	*this -= 1;
	if (this <= 0) this->sign = -1; //Feature again.
	return *this;
}

/* Умножение */

Integer Integer::operator*(const Integer& other) const
{
	Integer num;

	if (this->sign == other.sign) num.sign = 1;
	else num.sign = -1;

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

/* Деление */

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


/* Сравнение */

bool Integer::operator==(const Integer& other) const {
	if (this->sign != other.sign) return false;
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
	if (this->sign > other.sign) return true;
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
	if (this->sign < other.sign) return false;
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
	if (this->sign < other.sign) return true;
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
	if (this->sign > other.sign) return false;
	for (int i = BASE_SIZE - 1; i > 0; --i) {
		if (this->digits[i] > 0 && other.digits[0]) return false;
		else if (other.digits[i] > 0) {
			if (other.digits[i] >= this->digits[i]) return true;
			else return false;
		}
	}
}

explicit Integer::operator bool() const{
	return true ? *this != Integer(0) : false;
}

explicit Integer::operator char unsigned() const {
	return static_cast<char>(this->digits[0] % UINT32_MAX);
}

explicit Integer::operator char() const {
	return static_cast<char>(this->digits[0] % INT32_MAX) ? this->sign > 0 : -static_cast<char>(this->digits[0] % INT32_MAX);
}

explicit Integer::operator short unsigned int() const {
	return this->digits[0] % UINT16_MAX;
}

explicit Integer::operator short int() const {
	return this->digits[0] % INT16_MAX ? this->sign > 0 : -(this->digits[0] % INT16_MAX);
}

explicit Integer::operator unsigned int() const {
	return this->digits[0] % UINT32_MAX;
}

explicit Integer::operator int() const {
	return this->digits[0] % INT32_MAX ? this->sign > 0 : -(this->digits[0] % INT32_MAX);
}

explicit Integer::operator long unsigned int() const {
	return this->digits[0] % UINT32_MAX;
}

explicit Integer::operator long int() const {
	return this->digits[0] % INT32_MAX ? this->sign > 0 : -(this->digits[0] % INT32_MAX);
}

explicit Integer::operator long long unsigned int() const {
	return this->digits[0] % UINT64_MAX;
}

explicit Integer::operator long long int() const {
	return this->digits[0] % INT64_MAX ? this->sign > 0 : -(this->digits[0] % INT64_MAX);
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