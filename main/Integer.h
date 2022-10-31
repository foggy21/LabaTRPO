#pragma once
#include<string>
#include <climits>
// Arbitrary-precision arithmetic representation of integers
namespace arbitary_precision_arithmetic {
class Integer final {
  
 public:
  Integer();
  Integer(const Integer&);
  // Integer(Integer&&); // -__-

  Integer& operator=(const Integer&);
  // Integer& operator=(Integer&&);  // -__-

  // These constructors could be rewritten using templates
  // It's simple to use it in this task:
  // - Just try to use it,
  // - Remove repeating code &
  // - Don't forget to test it with different types
  // Oh, yeah, don't forget to specialize constructor from Integer type
  Integer(char unsigned);
  Integer(char);

  Integer(short unsigned);
  Integer(short);

  Integer(unsigned int);
  Integer(int);

  Integer(long unsigned);
  Integer(long);

  Integer(long long unsigned);
  Integer(long long);

  ~Integer();

  // arithmetic operators

  // arithmetic unary operators
  Integer operator-() const;
  Integer& operator--();
  Integer operator--(int);

  Integer operator+() const;
  Integer& operator++();
  Integer operator++(int);

  // arithmetic binary operators
  [[nodiscard]] Integer operator-(const Integer&) const;
  Integer& operator-=(const Integer&);

  [[nodiscard]] Integer operator+(const Integer&) const;
  Integer& operator+=(const Integer&);

  [[nodiscard]] Integer operator*(const Integer&) const;
  Integer& operator*=(const Integer&);

  [[nodiscard]] Integer operator/(const Integer&) const;
  Integer& operator/=(const Integer&);
  
  [[nodiscard]] Integer operator%(const Integer&) const;
  Integer& operator%=(const Integer&);  

  // Conversion operators... Why don't you still use the templates?
  [[nodiscard]] explicit operator bool() const;
  [[nodiscard]] explicit operator char unsigned() const;
  [[nodiscard]] explicit operator char() const;
  [[nodiscard]] explicit operator short unsigned int() const;
  [[nodiscard]] explicit operator short int() const;
  [[nodiscard]] explicit operator unsigned int() const;
  [[nodiscard]] explicit operator int() const;
  [[nodiscard]] explicit operator long unsigned int() const;
  [[nodiscard]] explicit operator long int() const;
  [[nodiscard]] explicit operator long long unsigned int() const;
  [[nodiscard]] explicit operator long long int() const;

  // Comparators
  [[nodiscard]] bool operator==(const Integer&) const;
  [[nodiscard]] bool operator!=(const Integer&) const;
  [[nodiscard]] bool operator<(const Integer&) const;
  [[nodiscard]] bool operator<=(const Integer&) const;
  [[nodiscard]] bool operator>(const Integer&) const;
  [[nodiscard]] bool operator>=(const Integer&) const;
   /*...or you could read about operator<=> and implement it instead of
   implementation of comparators above*/

   //Output stream print helper
  template <typename OStream>
  friend OStream&& operator<<(OStream&&, const Integer&);

private:
	static const unsigned long long BASE = ULLONG_MAX; // Размер рязряда
	static const unsigned long long BASE_SIZE = 10; // Кол-во разрядов
	unsigned long long size;
	unsigned long long* digits = nullptr;
	signed char sign; //Знак: +1 или -1
};

template <typename OStream>
OStream&& operator<<(OStream&& out, const Integer& num) {
    std::string result;
    Integer zero(0);

    if (num == zero) {
        out << '0';
        return out;
    }

    bool leadZero = true;

    for (unsigned __int64 i = num.size - 1; i >= 0; --i) {

        if (num.digits[i] == 0 && leadZero) continue;
        else if (num.digits[i] != 0 && leadZero) {
            leadZero = false;
            if (num.sign == -1)
            {
                result += "-";
            }
            result += std::to_string(num.digits[i]);
        }
        else if (!leadZero) result += std::to_string(num.digits[i]);
    }

    out << result;
    return out;
}

 //also you could implement your own string-literal for this type
 //Integer ""_li(const char*);

}  // namespace arbitary_precision_arithmetic
