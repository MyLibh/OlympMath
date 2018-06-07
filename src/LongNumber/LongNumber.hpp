#pragma once

#include <array> // std::array
#include <string_view> // std::string_view

typedef unsigned u_t;

class LongNumber final
{
public:
	static constexpr u_t MAX_DIGITS = 100;

private:
	LongNumber(bool, std::array<char, MAX_DIGITS>, u_t) noexcept;

	void removeZeroes(LongNumber&) const noexcept;
	void dump() const noexcept;

public:
	LongNumber() noexcept;
	LongNumber(std::string_view) noexcept;
	LongNumber(long long) noexcept;
	LongNumber(const LongNumber&) noexcept;
	LongNumber(LongNumber&&) noexcept;
	~LongNumber() noexcept;

#pragma region Arithmetic operators

	const LongNumber& operator=(const LongNumber&) noexcept;
	const LongNumber& operator=(LongNumber&&) noexcept;
	const LongNumber operator+(const LongNumber&) const noexcept;
	const LongNumber operator-(const LongNumber&) const noexcept;
	const LongNumber operator+() const noexcept;
	const LongNumber operator-() const noexcept;
	const LongNumber operator*(const LongNumber&) const noexcept;
	const LongNumber operator/(const LongNumber&) const noexcept(false);
	const LongNumber operator%(const LongNumber&) const noexcept;
	const LongNumber& operator++() noexcept;
	const LongNumber operator++(int) noexcept;
	const LongNumber& operator--() noexcept;
	const LongNumber operator--(int) noexcept;

#pragma endregion

#pragma region Ñomparison operators

	const bool operator==(const LongNumber&) const noexcept;
	const bool operator!=(const LongNumber&) const noexcept;
	const bool operator>(const LongNumber&) const noexcept;
	const bool operator<(const LongNumber&) const noexcept;
	const bool operator>=(const LongNumber&) const noexcept;
	const bool operator<=(const LongNumber&) const noexcept;
	 
#pragma endregion

#pragma region Logical operators

	const bool operator!() const noexcept;

#pragma endregion 

#pragma region Bitwise operators

	const LongNumber operator~() const noexcept;
	const LongNumber operator^(const LongNumber&) const noexcept;
	const LongNumber operator|(const LongNumber&) const noexcept;
	const LongNumber operator&(const LongNumber&) const noexcept;
	const LongNumber operator<<(const LongNumber&) const noexcept;
	const LongNumber operator>>(const LongNumber&) const noexcept;

#pragma endregion 

#pragma region Compound assignment operators

	const LongNumber& operator+=(const LongNumber&) noexcept;
	const LongNumber& operator-=(const LongNumber&) noexcept;
	const LongNumber& operator*=(const LongNumber&) noexcept;
	const LongNumber& operator/=(const LongNumber&) noexcept(false);
	const LongNumber& operator%=(const LongNumber&) noexcept;
	const LongNumber& operator^=(const LongNumber&) noexcept;
	const LongNumber& operator|=(const LongNumber&) noexcept;
	const LongNumber& operator&=(const LongNumber&) noexcept;
	const LongNumber& operator<<=(const LongNumber&) noexcept;
	const LongNumber& operator>>=(const LongNumber&) noexcept;

#pragma endregion

#pragma region Other operators

	void operator()() const noexcept;
	explicit operator bool() const noexcept;
	operator std::string() const noexcept(false); 

#pragma endregion

	[[ noreturn ]]
	void print() const noexcept;

	const bool isOdd() const noexcept;
	const bool isEven() const noexcept;

	const LongNumber lastDigits(unsigned) const noexcept;
	const unsigned digits() const noexcept;

	friend void test();

private:
	bool                         sign_;
	std::array<char, MAX_DIGITS> digits_;
	u_t                          lastDigit_;
};



