#include <iostream> // std::cout, std::cerr 
#include <algorithm> // std::max
#include <cassert> // assert

#include "LongNumber.hpp"

LongNumber::LongNumber(bool sign, std::array<char, MAX_DIGITS> digits, size_t lastDigit) noexcept :
	sign_(sign),
	digits_(digits),
	lastDigit_(lastDigit)
{
	digits_.fill('0');
}

void LongNumber::removeZeroes(LongNumber &rLongNumber) const noexcept
{
	while (rLongNumber.digits_[rLongNumber.lastDigit_] == '0')
		if (rLongNumber.lastDigit_)
			rLongNumber.lastDigit_--;

	if (!rLongNumber.lastDigit_ && !rLongNumber.digits_[0])
		rLongNumber.sign_ = true;
}

void LongNumber::dump() const noexcept
{
	try
	{
		std::cout<<"\t[LONG NUMBER DUMP]\n";

		std::cout << "LongNumber [0x" << this << "]\n"
			      << "{\n\tbuffer [" << lastDigit_ + 1 << "/" << MAX_DIGITS << "] = 0x" << &digits_ << "\n\t{\n";
		
		for (auto &x : digits_) 
			std::cout << "\t\t" << x << std::endl;

		std::cout << "\t}\n}\n\n";
		
	}
	catch (...)
	{
		std::cerr << "Something went wrong in \"" << __FUNCTION__ << "\"! Continue...\n";
	}
}

LongNumber::LongNumber() noexcept :
	sign_(true),
	digits_({}),
	lastDigit_(0)
{
	digits_.fill('0');
}

LongNumber::LongNumber(std::string_view str) noexcept :
	sign_(true),
	digits_({}),
	lastDigit_(0)
{
	digits_.fill('0');
}

LongNumber::LongNumber(long long x) noexcept :
	sign_(x >= 0 ? true : false),
	digits_({}),
	lastDigit_(0)
{
	digits_.fill('0');

	if (x < 0)
		x = -x;

	while (x)
	{
		digits_[lastDigit_] = '0' + x % 10;
		lastDigit_++;

		x /= 10;
	}

	lastDigit_--;
}

LongNumber::LongNumber(const LongNumber &crLongNumber) noexcept :
	sign_(crLongNumber.sign_),
	digits_(crLongNumber.digits_),
	lastDigit_(crLongNumber.lastDigit_)
{
}

LongNumber::LongNumber(LongNumber &&rrLongNumber) noexcept :
	sign_(std::move(rrLongNumber.sign_)),
	digits_(std::move(rrLongNumber.digits_)),
	lastDigit_(std::move(rrLongNumber.lastDigit_))
{
}

LongNumber::~LongNumber() noexcept
{
}

#pragma region Arithmetic operators

const LongNumber& LongNumber::operator=(const LongNumber &crLongNumber) noexcept
{
	if (*this != crLongNumber)
	{
		sign_ = crLongNumber.sign_;
		digits_ = crLongNumber.digits_;
		lastDigit_ = crLongNumber.lastDigit_;
	}

	return (*this);
}

const LongNumber& LongNumber::operator=(LongNumber &&rrLongNumber) noexcept
{
	assert(*this != rrLongNumber);

	sign_      = std::move(rrLongNumber.sign_);
	digits_    = std::move(rrLongNumber.digits_);
	lastDigit_ = std::move(rrLongNumber.lastDigit_);

	return (*this);
}

const LongNumber LongNumber::operator+(const LongNumber &crLongNumber) const noexcept
{
	if (sign_ != crLongNumber.sign_)
		if (!sign_)
			return { crLongNumber - (+*this) };
		else
			return { *this - (+crLongNumber) };

	LongNumber c(sign_, {}, std::max(lastDigit_, crLongNumber.lastDigit_) + 1);
	for (auto i{ 0u }, carry{ 0u }; i <= c.lastDigit_; ++i)
	{
		auto tmp{ digits_[i] + crLongNumber.digits_[i] + carry - 2 * '0' };

		c.digits_[i] = '0' + tmp % 10;

		carry = tmp / 10;
	}

	removeZeroes(c);

	return (c);
}

const LongNumber LongNumber::operator-(const LongNumber &crLongNumber) const noexcept
{
	if (sign_ != crLongNumber.sign_)
		return { *this + LongNumber{ !crLongNumber.sign_, crLongNumber.digits_, crLongNumber.lastDigit_ } };

	if (crLongNumber > *this)
		return (-LongNumber{ crLongNumber - *this });

	LongNumber c{ true, {}, std::max(lastDigit_, crLongNumber.lastDigit_) };
	bool borrow{};
	for (auto i{ 0u }; i < c.lastDigit_; ++i)
	{
		int v{ digits_[i] - borrow - crLongNumber.digits_[i] };
		if (digits_[i])
			borrow = false;
		if (v < 0)
		{
			v += 10;

			borrow = true;
		}

		c.digits_[i] = v % 10;
	}

	removeZeroes(c);

	return (c);
}

inline const LongNumber LongNumber::operator+() const noexcept
{
	return { true, digits_, lastDigit_ };
}

inline const LongNumber LongNumber::operator-() const noexcept
{
	return { false, digits_, lastDigit_ };
}

const LongNumber LongNumber::operator*(const LongNumber &) const noexcept
{
	return LongNumber();
}

const LongNumber LongNumber::operator/(const LongNumber &) const noexcept(false)
{
	return LongNumber();
}

const LongNumber LongNumber::operator%(const LongNumber &) const noexcept
{
	return LongNumber();
}

inline const LongNumber& LongNumber::operator++() noexcept
{
	return (*this += 1ll);
}

inline const LongNumber LongNumber::operator++(int) noexcept
{
	*this += 1ll;

	return { *this - LongNumber{ 1ll } };
}
 
inline const LongNumber& LongNumber::operator--() noexcept
{
	return  (*this -= 1);
}

inline const LongNumber LongNumber::operator--(int) noexcept
{
	*this -= 1;

	return { *this + LongNumber{ 1ll } };
}

#pragma endregion

#pragma region Ñomparison operators

const bool LongNumber::operator==(const LongNumber &) const noexcept
{
	return false;
}

const bool LongNumber::operator!=(const LongNumber &) const noexcept
{
	return false;
}

const bool LongNumber::operator>(const LongNumber &) const noexcept
{
	return false;
}

const bool LongNumber::operator<(const LongNumber &) const noexcept
{
	return false;
}

const bool LongNumber::operator>=(const LongNumber &) const noexcept
{
	return false;
}

const bool LongNumber::operator<=(const LongNumber &) const noexcept
{
	return false;
}

#pragma endregion

#pragma region Logical operators

const bool LongNumber::operator!() const noexcept
{
	return false;
}

#pragma endregion  

#pragma region Bitwise operators

const LongNumber LongNumber::operator~() const noexcept
{
	return LongNumber();
}

const LongNumber LongNumber::operator^(const LongNumber &) const noexcept
{
	return LongNumber();
}

const LongNumber LongNumber::operator|(const LongNumber &) const noexcept
{
	return LongNumber();
}

const LongNumber LongNumber::operator&(const LongNumber &) const noexcept
{
	return LongNumber();
}

const LongNumber LongNumber::operator<<(const LongNumber &) const noexcept
{
	return LongNumber();
}

const LongNumber LongNumber::operator>>(const LongNumber &) const noexcept
{
	return LongNumber();
}

#pragma endregion

#pragma region Compound assignment operators

const LongNumber& LongNumber::operator+=(const LongNumber &crLongNumber) noexcept
{
	return (*this = *this + crLongNumber);
}

const LongNumber& LongNumber::operator-=(const LongNumber &crLongNumber) noexcept
{
	return (*this = *this - crLongNumber);
}

const LongNumber& LongNumber::operator*=(const LongNumber &crLongNumber) noexcept
{
	return (*this = *this * crLongNumber);
}

const LongNumber& LongNumber::operator/=(const LongNumber &crLongNumber) noexcept(false)
{
	return (*this = *this / crLongNumber);
}

const LongNumber & LongNumber::operator%=(const LongNumber &crLongNumber) noexcept
{
	return (*this = *this % crLongNumber);
}

const LongNumber & LongNumber::operator^=(const LongNumber &crLongNumber) noexcept
{
	return (*this = *this ^ crLongNumber);
}

const LongNumber & LongNumber::operator|=(const LongNumber &crLongNumber) noexcept
{
	return (*this = *this | crLongNumber);
}

const LongNumber & LongNumber::operator&=(const LongNumber &crLongNumber) noexcept
{
	return (*this = *this & crLongNumber);
}

const LongNumber & LongNumber::operator<<=(const LongNumber &crLongNumber) noexcept
{
	return (*this = *this << crLongNumber);
}

const LongNumber & LongNumber::operator>>=(const LongNumber &crLongNumber) noexcept
{
	return (*this = *this >> crLongNumber);
}

#pragma endregion 

#pragma region Other operators

void LongNumber::operator()() const noexcept
{
	dump();
}

LongNumber::operator bool() const noexcept
{
	return false;
}

LongNumber::operator std::string() const noexcept(false)
{
	return {};
}

#pragma endregion

/* [[ noreturn ]] */
void LongNumber::print() const noexcept
{
	try
	{
		std::cout << (sign_ ? '+' : '-');
		for (auto i{ 0u }; i <= lastDigit_; ++i)
			std::cout << digits_.at(lastDigit_ - i);

		std::cout << std::endl;
	}
	catch (...)
	{
		std::cerr << "Something went wrong in \"" << __FUNCTION__ << "\"! Goodbye!!!\n";

		std::terminate();
	}
}
