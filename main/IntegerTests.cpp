#define CATCH_CONFIG_MAIN
#define BIG_NUM 1000000001000000000
#define LONG_LONG_MAX 9223372036854775807
#include "catch.hpp"
#include "Integer.h"

using namespace arbitary_precision_arithmetic;

TEST_CASE("constructor") {
	Integer num(5);
	REQUIRE(num == 5);
}

TEST_CASE("constructor v2") {
	Integer num(Integer(5));
	REQUIRE(num == 5);
}

TEST_CASE("constructor v3") {
	Integer num = LONG_LONG_MAX;
	REQUIRE(num == LONG_LONG_MAX);
}

TEST_CASE("CHECK BIG NUM MULTIPLY (LONG ARITHM CHECK)") {
	REQUIRE(Integer(LONG_LONG_MAX) * Integer(LONG_LONG_MAX) * Integer(LONG_LONG_MAX) * Integer(LONG_LONG_MAX) * Integer(LONG_LONG_MAX) == LONG_LONG_MAX * LONG_LONG_MAX * LONG_LONG_MAX * LONG_LONG_MAX * LONG_LONG_MAX);
}

TEST_CASE("multiply") {
	REQUIRE(Integer(1000000001) * Integer(1000000000) == Integer(BIG_NUM));
}

TEST_CASE("plus") {
	REQUIRE(Integer(20) + Integer(1234567) == 1234587);
}

TEST_CASE("minus = minus sign") {
	Integer num = Integer(20) - Integer(21);
	REQUIRE(num == -1);
}

TEST_CASE("minus = minus sign v2") {
	REQUIRE(Integer(1234567) - Integer(20) == -1234547);
}

TEST_CASE("plus with minus = minus sign") {
	REQUIRE(Integer(1234567) + -Integer(20) == -1234547);
}

TEST_CASE("minus sign plus minus sign = minus sign") {
	REQUIRE(-Integer(1234567) + -Integer(20) == -1234587);
}

TEST_CASE("minus sign minus minus sign = minus sign") {
	REQUIRE(-Integer(1234567) - -Integer(20) == -1234547);
}

TEST_CASE("minus sign minus minus sign = zero") {
	Integer num = Integer(-1234567) - Integer(-1234567);
	REQUIRE(num == 0);
}

TEST_CASE("min sign plus minus sign = minus sign") {
	Integer num = Integer(-1234567) + Integer(-1234567);
	REQUIRE(num == -2469134);
}

TEST_CASE("min sign multiply plus sign = minus sign") {
	Integer num = Integer(-1234567) * Integer(2);
	REQUIRE(num == -2469134);
}

TEST_CASE("min sign multiply minus sign = plus sign") {
	Integer num = Integer(-1234567) * Integer(-2);
	REQUIRE(num == 2469134);
}

TEST_CASE("lite plus") {
	Integer num(20);
	num += Integer(1234567);
	REQUIRE(num == 1234587);
}

TEST_CASE("lite multiply") {
	Integer num(1000000001);
	num *= Integer(1000000000);
	REQUIRE(num == Integer(BIG_NUM));
}

TEST_CASE("lite minus = minus sign") {
	Integer num(20);
	num -= Integer(21);
	REQUIRE(num == -1);
}

TEST_CASE("lite minus = minus sign v2") {
	Integer num(1234567);
	num -= Integer(20);
	REQUIRE(num == -1234547);
}

TEST_CASE("lite plus with minus = minus sign") {
	Integer num(1234567);
	num += Integer(-20);
	REQUIRE(num == -1234547);
}

TEST_CASE("lite minus sign plus minus sign = minus sign") {
	Integer num(-1234567);
	num += Integer(-20);
	REQUIRE(num == -1234587);
}

TEST_CASE("lite minus sign minus minus sign = minus sign") {
	Integer num(-1234567);
	num -= Integer(-20);
	REQUIRE(num == -1234547);
}

TEST_CASE("lite minus sign minus minus sign = zero") {
	Integer num(-1234567);
	num -=Integer(-1234567);
	REQUIRE(num == 0);
}

TEST_CASE("lite min sign plus minus sign = minus sign") {
	Integer num(-1234567);
	num += Integer(-1234567);
	REQUIRE(num == -2469134);
}

TEST_CASE("lite min sign multiply plus sign = minus sign") {
	Integer num(-1234567);
	num *= Integer(2);
	REQUIRE(num == -2469134);
}

TEST_CASE("lite min sign multiply minus sign = plus sign") {
	Integer num(-1234567);
	num *= Integer(-2);
	REQUIRE(num == 2469134);
}

TEST_CASE("CONVER BOOL TO FALSE") {
	Integer num(0);
	CHECK(num == false);
}

TEST_CASE("CONVER BOOL TO TRUE") {
	Integer num(5);
	CHECK((bool)num == true);
}

TEST_CASE("CONVERT CHAR TO SYM") {
	Integer num(100);
	CHECK(num == 'd');
}

TEST_CASE("CONVER ULL") {
	Integer num(LONG_LONG_MAX);
	CHECK(num == LONG_LONG_MAX);
}