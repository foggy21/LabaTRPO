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
	if (size != other.size) {
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
	//*this = Resize(this, other); // Equal size with other if this->size less then other.size
	if (this->sign == other.sign) {
		for (int i = 0; i < this->size; ++i) {
			this->digits[i] += other.digits[i]; // Add and ignore overflow
		}

		for (int i = 0; i < this->size - 1; ++i) {
			if (this->digits[i] >= BASE) {
				this->digits[i] -= BASE;
				this->digits[i + 1]++;
			}
		}
		if (this->digits[this->size - 1] >= BASE) {
			this->digits[this->size - 1] -= BASE;
			//ResizeThis(this);
			this->digits[this->size - 1]++;
		}
		return *this;
	}
	else {
		//Subtracts from one number the second
		this->sign = *this < other ? -1 : 1;
		for (int i = 0; i < this->size; ++i) {
			this->digits[i] -= other.digits[i];
		}

		for (int i = 0; i < this->size-1; ++i) {
			if (this->digits[i] < 0) {
				this->digits[i] += BASE;
				this->digits[i + 1]--;
			}
		}
		return *this;
	}
}

Integer Integer::operator+(const Integer& other) const {
	// Lite operator's += version
	Integer num(*this);
	num += other;
	return num;
}

Integer Integer::operator+() const {
	Integer other(*this);
	return other;
}

Integer& Integer::operator++()
{
	*this+=1;
	if (*this >= 0) this->sign = 1; // If num was equal -1 (Feature)
	return *this;
}

Integer Integer::operator++(int) {
	*this += 1;
	if (*this >= 0) this->sign = 1; // If num was equal -1 (Feature)
	return *this;
}

/* Вычитание */

Integer& Integer::operator-=(const Integer& other)
{	
	//*this = Resize(this, other);
	//If sings equal, then subtracts
	if (this->sign == other.sign) {
		this->sign = *this >= other ? 1 : -1;
		for (int i = 0; i < this->size; ++i) {
			if (this->digits[i] >= *other.digits)
				this->digits[i] -= other.digits[i];
			else
				this->digits[i] = other.digits[i] - this->digits[i];
		}

		for (int i = 0; i < this->size; ++i) {
			if (this->digits[i] < 0) {
				this->digits += BASE;
				this->digits[i + 1]--;
			}
		}
		return *this;
	}
	else {
		//Based on the += operator, we add a negative to a positive number
		return *this += other;
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
	if (*this <= 0) this->sign = -1; //Feature again.
	return *this;
}

Integer Integer::operator--(int) {
	*this -= 1;
	if (*this <= 0) this->sign = -1; //Feature again.
	return *this;
}

/* Умножение */

Integer& Integer::operator*=(const Integer& other) {
	//num = ResizeThisWithNewDigits(&num, this->size + other.size);
	Integer& num(*this);
	if (this->sign == other.sign) num.sign = 1;
	else num.sign = -1;

	for (int i = 0; i < num.size; ++i) {
		for (int j = 0; j < num.size - i; ++j) { // don't pick digits more than BASE_SIZE
			num.digits[i + j] = this->digits[i] * other.digits[j];
		}
	}

	// Getting rid of overflow
	for (int i = 0; i < num.size - 1; ++i) {
		num.digits[i + 1] += num.digits[i] / BASE;
		num.digits[i] %= BASE;
	}

	return num;
}

Integer Integer::operator*(const Integer& other) const
{
	Integer num(*this);
	num *= other;
	return num;
}

/* Сравнение */

bool Integer::operator==(const Integer& other) const {
	if (this->sign == other.sign){
		for (int i = 0; i < this->size; ++i) {
			if (this->digits[i] != other.digits[i]) return false;
		}
	}
	return true;
}

bool Integer::operator!=(const Integer& other) const {
	if (this->sign != other.sign){
		for (int i = 0; i < BASE_SIZE; ++i) {
			if (this->digits[i] != other.digits[i]) return true;
		}
	}
	return false;
}

bool Integer::operator>(const Integer& other) const {
	if (this->sign >= other.sign){
		for (int i = this->size - 1; i > 0; --i) {
			if (other.digits[i] > 0 && this->digits[i] == 0) return false;
			else if (this->digits[i] > 0) {
				if (this->digits[i] > other.digits[i]) return true;
				else return false;
			}
		}
	}
	return false;
}

bool Integer::operator>=(const Integer& other) const {
	if (this->sign >= other.sign) {
		for (int i = BASE_SIZE - 1; i > 0; --i) {
			if (other.digits[i] > 0 && this->digits[i] == 0) return false;
			else if (this->digits[i] > 0) {
				if (this->digits[i] >= other.digits[i]) return true;
				else return false;
			}
		}
	}
	return false;
}

bool Integer::operator<(const Integer& other) const {
	if (this->sign <= other.sign){
		for (int i = this->size - 1; i > 0; --i) {
			if (this->digits[i] > 0 && other.digits[i] == 0) return false;
			else if (other.digits[i] > 0) {
				if (other.digits[i] > this->digits[i]) return true;
				else return false;
			}
		}
	}
	return true;
}

bool Integer::operator<=(const Integer& other) const {
	if (this->sign <= other.sign) {
		for (int i = this->size - 1; i > 0; --i) {
			if (this->digits[i] > 0 && other.digits[0]) return false;
			else if (other.digits[i] > 0) {
				if (other.digits[i] >= this->digits[i]) return true;
				else return false;
			}
		}
	}
	return false;
}

Integer::operator bool() const{
	return true ? this != 0 : false;
}

Integer::operator char unsigned() const {
	return static_cast<char unsigned>(this->digits[0] % std::numeric_limits<unsigned char>::max());
}

Integer::operator char() const {
	return static_cast<char>(this->digits[0] % std::numeric_limits<char>::max()) ? this->sign > 0 : -static_cast<char>(this->digits[0] % std::numeric_limits<char>::max());
}

Integer::operator short unsigned int() const {
	return static_cast<short unsigned int>(this->digits[0] % std::numeric_limits<short unsigned int>::max());
}

Integer::operator short int() const {
	return static_cast<short int>(this->digits[0] % std::numeric_limits<short int>::max()) ? this->sign > 0 : -static_cast<short int>(this->digits[0] % std::numeric_limits<short int>::max());
}

Integer::operator unsigned int() const {
	return static_cast<unsigned int>(this->digits[0] % std::numeric_limits<unsigned int>::max());
}

Integer::operator int() const {
	return static_cast<int>(this->digits[0] % std::numeric_limits<int>::max()) ? this->sign > 0 : -static_cast<int>(this->digits[0] % std::numeric_limits<int>::max());
}

Integer::operator long unsigned int() const {
	return static_cast<long unsigned int>(this->digits[0] % std::numeric_limits<long unsigned int>::max());
}

Integer::operator long int() const {
	return static_cast<long int>(this->digits[0] % std::numeric_limits<long int>::max()) ? this->sign > 0 : -static_cast<long int>(this->digits[0] % std::numeric_limits<long int>::max());
}

Integer::operator long long unsigned int() const {
	return static_cast<long long unsigned int>(this->digits[0] % std::numeric_limits<long long unsigned int>::max());
}

Integer::operator long long int() const {
	return static_cast<long long int>(this->digits[0] % std::numeric_limits<long long int>::max()) ? this->sign > 0 : -static_cast<long long int>(this->digits[0] % std::numeric_limits<long long int>::max());
}

Integer::~Integer() 
{
	delete[] digits;
}