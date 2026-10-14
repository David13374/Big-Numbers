#include<gtest/gtest.h>
#include<sstream>
#include<string>
#include "Big-Numbers.h"

template<typename T>
static std::string GetDigits(T in) {
	return GetDigits(BigInt(in));
}

/* CONSTRUCTORS */
TEST(BigIntConstructor, FromULL) {
	EXPECT_EQ(GetDigits(0ULL), "0");
	EXPECT_EQ(GetDigits(3564353242346ULL), "3564353242346");
}

TEST(BigIntConstructor, FromString) {
	std::string test1 = "";
	EXPECT_EQ(GetDigits(test1), test1);
	std::string test2 = "0";
	EXPECT_EQ(GetDigits(test2), test2);
	std::string test3 = "3564353242346";
	EXPECT_EQ(GetDigits(test3), test3);
}

TEST(BigIntConstructor, FromCString) {
	EXPECT_EQ(GetDigits(""), "");
	EXPECT_EQ(GetDigits("0"), "0");
	EXPECT_EQ(GetDigits("3564353242346"), "3564353242346");
}

TEST(BigIntConstructor, FromBigInt) {
	BigInt test1 = BigInt("");
	EXPECT_EQ(GetDigits(test1), "");
	BigInt test2 = BigInt("0");
	EXPECT_EQ(GetDigits(test2), "0");
	BigInt test3 = BigInt("3564353242346");
	EXPECT_EQ(GetDigits(test3), "3564353242346");
}

/* COPY, ASSIGN, ERRORS */

TEST(BigIntMisc, CopyAndAssign) {
	BigInt a("321512421");
	BigInt b(a);
	BigInt c;
	c = a;

	EXPECT_EQ(GetDigits(a), "321512421");
	EXPECT_EQ(GetDigits(b), "321512421");
	EXPECT_EQ(GetDigits(c), "321512421");
}

TEST(BigIntMisc, ERROR) {
	EXPECT_ANY_THROW(BigInt("12a21"));
}

/* COMPARISONS */

TEST(BigIntComparison, Basics) {
	BigInt a("100"), b("99"), c("100");

	EXPECT_TRUE(a > b);
	EXPECT_TRUE(b < a);
	EXPECT_TRUE(a == c);
	EXPECT_TRUE(a != b);
	EXPECT_TRUE(a >= c);
	EXPECT_TRUE(a <= c);
	EXPECT_FALSE(a < c);
	EXPECT_FALSE(a == b);
	EXPECT_FALSE(b > a);
	EXPECT_FALSE(a != c);
}

/* OPERATIONS */

TEST(BigIntOperations, Increment) {
	BigInt a("999");
	a++;
	EXPECT_EQ(GetDigits(a), "1000");
}

TEST(BigIntOperations, Decrement) {
	BigInt a("1000");
	a--;
	EXPECT_EQ(GetDigits(a), "999");
}

TEST(BigIntOperations, Addition) {
	BigInt a("34");
	BigInt b("66");
	
	BigInt c;
	BigInt d;
	c = a + b;
	d = a;
	d += b;

	EXPECT_EQ(GetDigits(c), "100");
	EXPECT_EQ(GetDigits(d), "100");
}

TEST(BigIntOperations, Subtraction) {
	BigInt a("156");
	BigInt b("64");

	BigInt c;
	BigInt d;

	d = a;

	c = a - b;
	d -= b;

	EXPECT_EQ(GetDigits(c), "92");
	EXPECT_EQ(GetDigits(d), "92");
	EXPECT_ANY_THROW(b - a);
}

TEST(BigIntOperations, Multiplication) {
	BigInt a("64");
	BigInt b("42");

	BigInt c;
	BigInt d;

	d = a;

	c = a * b;
	d *= b;

	EXPECT_EQ(GetDigits(c), "2688");
	EXPECT_EQ(GetDigits(d), "2688");
}

TEST(BigIntOperations, Division) {
	BigInt a("264");
	BigInt b("12");
	BigInt c("10");
	BigInt d("13");
	BigInt e("0");

	EXPECT_EQ(GetDigits(a / b), "22");
	EXPECT_EQ(GetDigits(a / c), "26");
	EXPECT_EQ(GetDigits(a / d), "20");
	EXPECT_ANY_THROW(a / e);
}

TEST(BigIntOperations, Modulo) {
	BigInt a("254");
	BigInt b("2");
	BigInt c("10");

	EXPECT_EQ(GetDigits(a % b), "0");
	EXPECT_EQ(GetDigits(a % c), "4");
	EXPECT_ANY_THROW(a % BigInt("0"));
}

TEST(BigIntOperations, Exponentiation) {
	BigInt a("3");
	BigInt b("4");
	BigInt c("0");
	BigInt d;

	EXPECT_EQ(GetDigits(a ^ b), "81");
	EXPECT_EQ(GetDigits(a ^ c), "1");
}

TEST(BigIntOperations, Sqrt) {
	BigInt a("121");

	EXPECT_EQ(GetDigits(sqrt(a)), "11");
}