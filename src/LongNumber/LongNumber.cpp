#include <iostream>   // std::cout, std::cerr 
#include <algorithm>  // std::max
#include <cassert>    // assert
#include <string>     // std::string
#include <functional> // std::function

#include "LongNumber.hpp"

LongNumber::LongNumber(bool sign, std::array<char, MAX_DIGITS> digits, size_t lastDigit) noexcept :
	sign_(sign),
	digits_(digits),
	lastDigit_(lastDigit)
{
	std::for_each(digits_.begin(), digits_.end(), [](auto &c) { if (c == '\0') c = '0'; });
}

void LongNumber::removeZeroes(LongNumber &rLongNumber) const noexcept
{
	while (rLongNumber.digits_[rLongNumber.lastDigit_] == '0')
		if (rLongNumber.lastDigit_)
			rLongNumber.lastDigit_--;
		else
			break;

	if (!rLongNumber.lastDigit_ && !rLongNumber.digits_[0])
		rLongNumber.sign_ = true;
}

void LongNumber::shiftDigit(LongNumber &rLongNumber, u_t d) const noexcept
{
	if (!rLongNumber.lastDigit_ && rLongNumber.digits_[0] == '0')
		return;

	for (long i = static_cast<long>(rLongNumber.lastDigit_); i >= 0; --i)
		rLongNumber.digits_.at(i + d) = rLongNumber.digits_.at(i);

	std::for_each(rLongNumber.digits_.begin(), rLongNumber.digits_.begin() + d, [](auto &c) { c = '0'; });

	rLongNumber.lastDigit_ += d;
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
	lastDigit_(str.length())
{
	digits_.fill('0');

	assert(lastDigit_ < LongNumber::MAX_DIGITS);
	if (lastDigit_)
	{
		if (str.front() == '-')
			sign_ = false;

		if(!isdigit(str.front()))
			str.remove_prefix(1);

		unsigned i{};
		for (auto &&c : str)
			digits_[lastDigit_ - i++] = c;	
	}
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

	if(lastDigit_)
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

#pragma region Arithmetic operators

const LongNumber& LongNumber::operator=(const LongNumber &crLongNumber) noexcept
{
	if (*this != crLongNumber)
	{
		sign_      = crLongNumber.sign_;
		digits_    = crLongNumber.digits_;
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
			return { crLongNumber - (-*this) };
		else
			return { *this - (-crLongNumber) };

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
		return { *this + (-crLongNumber) };

	if ((sign_ && crLongNumber > *this) || (!sign_ && crLongNumber < *this))
		return (-LongNumber{ crLongNumber - *this });

	LongNumber c{ sign_, {}, std::max(lastDigit_, crLongNumber.lastDigit_) };
	bool borrow{};
	for (auto i{ 0u }; i <= c.lastDigit_; ++i)
	{
		int v{ digits_[i] - borrow - crLongNumber.digits_[i] };
		if (digits_[i])
			borrow = false;
		if (v < 0)
		{
			v += 10;

			borrow = true;
		}

		c.digits_[i] = '0' + v % 10;
	}

	removeZeroes(c);

	return (c);
}

inline const LongNumber LongNumber::operator+() const noexcept
{
	return { sign_, digits_, lastDigit_ };
}

inline const LongNumber LongNumber::operator-() const noexcept
{
	return { !sign_, digits_, lastDigit_ };
}

const LongNumber LongNumber::operator*(const LongNumber &crLongNumber) const noexcept
{
	LongNumber c{}, 
		       row{*this};
	for (auto i{ 0u }; i <= crLongNumber.lastDigit_; i++)
	{
		for (char j{ '1' }; j <= crLongNumber.digits_[i]; ++j)
			c += row;

		shiftDigit(row, 1ll);
	}

	c.sign_ = (sign_ == crLongNumber.sign_);

	removeZeroes(c);

	return (c);
}

const LongNumber LongNumber::operator/(const LongNumber &crLongNumber) const noexcept(false)
{
	if (!crLongNumber)
		throw std::invalid_argument("Division by zero\n");

	bool swap{};
	if (!crLongNumber.sign_)
	{
		const_cast<LongNumber&>(crLongNumber).sign_ = !crLongNumber.sign_;

		swap = true;
	}

	LongNumber c{},
		       row{};
	for (long i = static_cast<long>(lastDigit_); i >= 0; --i)
	{
		shiftDigit(row, 1);
		row.digits_[0] = digits_[i];

		c.digits_[i] = '0';
		while (!(row < crLongNumber))
		{
			c.digits_[i]++;

			row -= crLongNumber;
		}
	}

	if (swap)
		const_cast<LongNumber&>(crLongNumber).sign_ = !crLongNumber.sign_;
	
	c.sign_ = (sign_ == crLongNumber.sign_);

	removeZeroes(c);

	return (c);
}

const LongNumber LongNumber::operator%(const LongNumber &crLongNumber) const noexcept
{
	LongNumber res{ *this - (*this / crLongNumber) * crLongNumber };

	if (!res.sign_)
		res += crLongNumber;

	return (res);
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

const bool LongNumber::operator==(const LongNumber &crLongNumber) const noexcept
{
	if (sign_ != crLongNumber.sign_ || lastDigit_ != crLongNumber.lastDigit_)
		return false;

	return std::equal(digits_.begin(), digits_.begin() + lastDigit_ + 1, crLongNumber.digits_.begin());
}

const bool LongNumber::operator!=(const LongNumber &crLongNumber) const noexcept
{
	return !(*this == crLongNumber);
}

const bool LongNumber::operator>(const LongNumber &crLongNumber) const noexcept
{
	if (sign_ != crLongNumber.sign_)
		return (sign_ > crLongNumber.sign_);

	if (lastDigit_ != crLongNumber.lastDigit_)
		return (lastDigit_ > crLongNumber.lastDigit_);

	const auto length = LongNumber::MAX_DIGITS - lastDigit_ - 1;
	auto[it1, it2] = std::mismatch(digits_.rbegin() + length, digits_.rend(), crLongNumber.digits_.rbegin() + length);
	return (it1 == digits_.rend() ? false : (sign_ ? (*it1 > *it2) : (*it1 < *it2)));
}

const bool LongNumber::operator<(const LongNumber &crLongNumber) const noexcept
{
	return !(*this >= crLongNumber);
}

const bool LongNumber::operator>=(const LongNumber &crLongNumber) const noexcept
{
	return (*this > crLongNumber || *this == crLongNumber);
}

const bool LongNumber::operator<=(const LongNumber &crLongNumber) const noexcept
{
	return !(*this > crLongNumber);
}

#pragma endregion

#pragma region Logical operators

const bool LongNumber::operator!() const noexcept
{
	return (*this == LongNumber{ 0ll });
}

#pragma endregion  

#pragma region Bitwise operators

const LongNumber LongNumber::operator~() const noexcept
{
	return {};
}

const LongNumber LongNumber::operator^(const LongNumber &) const noexcept
{
	return {};
}

const LongNumber LongNumber::operator|(const LongNumber&) const noexcept
{
	return {};
}

const LongNumber LongNumber::operator&(const LongNumber &crLongNumber) const noexcept
{
	return {};
}

const LongNumber LongNumber::operator<<(const LongNumber &) const noexcept
{
	return {};
}

const LongNumber LongNumber::operator>>(const LongNumber &) const noexcept
{
	return {};
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
	return (*this > LongNumber{ 0 });
}

LongNumber::operator std::string() const noexcept(false)
{
	std::string res(sign_ ? "+" : "-");

	//std::rotate_copy(digits_.begin(), digits_.begin() + 2/*+ (lastDigit_ + 1) / 2 - ((lastDigit_  )% 2)*/, digits_.begin() + lastDigit_ + 1, std::back_inserter(res));
	const auto length = LongNumber::MAX_DIGITS - lastDigit_ - 1;
	std::copy(digits_.rbegin() + length, digits_.rend(), std::inserter(res, res.end()));

	return res;
}

#pragma endregion

/* [[ noreturn ]] */
void LongNumber::print(bool showPlus /* = false */) const noexcept
{
	try
	{
		if (!sign_)
			std::cout << '-';
		else if (showPlus)
			std::cout << '+';
		
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

const bool LongNumber::isOdd() const noexcept
{
	return ((digits_[0] - '0') & 1);
}

const bool LongNumber::isEven() const noexcept
{
	return (!isOdd());
}

const LongNumber LongNumber::power(LongNumber &crLongNumber) const noexcept
{
	LongNumber a(*this),
		b(crLongNumber),
		res(1);
	while (b != 0)
	{
		if (b.isOdd()) 
			res *= a;

		a *= a;
		b /= 2;
	}

	return res;
}

const LongNumber LongNumber::factorial() const noexcept
{
	auto res{ *this };
	std::function<LongNumber(const LongNumber&)> fact = [&fact](const LongNumber &x) -> LongNumber
	{
		if (x < 0)
			return { 0 };
		else if (!x || x == 1)
			return { 1 };
		else
			return { x * fact(x - 1) };
	};
	
	return fact(res);
}

const LongNumber LongNumber::lastDigits(u_t n) const noexcept
{
	assert(n < LongNumber::MAX_DIGITS && n <= lastDigit_ + 1 && n-- != 0);

	LongNumber c{ true, {}, n};
	std::copy(digits_.begin(), digits_.begin() + n + 1, c.digits_.begin());

	return (c);
}

const u_t LongNumber::digits() const noexcept
{
	return (lastDigit_ + 1u);
}

std::ostream& operator<<(std::ostream &rOstr, const LongNumber &crLongNumber)
{ 
	rOstr << crLongNumber.operator std::string();

	return rOstr;
}