#include <utility>  // std::swap
#include <iostream> // std::cout
#include <sstream>  // std::stringstream

#include "Fraction.hpp"

Fraction::Fraction() noexcept :
	x(0),
	y(1)
{
}

Fraction::Fraction(std::string_view str) noexcept :
	x(0),
	y(1)
{
	std::stringstream sstr(str.data());
	char c{};
	sstr >> x >> c >> y;
}

Fraction::Fraction(ll_t num, ll_t den) noexcept :
	x(num),
	y(den)
{
	Fraction::simplify(*this);
}

const Fraction Fraction::operator+(const Fraction &crFraction) const noexcept
{
	Fraction res{ x * crFraction.y + crFraction.x * y, y * crFraction.y };

	Fraction::simplify(res);

	return res;
}

const Fraction Fraction::operator-(const Fraction &crFraction) const noexcept
{
	Fraction res{ x * crFraction.y - crFraction.x * y, y * crFraction.y };

	Fraction::simplify(res);

	return res;
}

const Fraction Fraction::operator*(const Fraction &crFraction) const noexcept
{
	Fraction res{ x * crFraction.x, y * crFraction.y };

	Fraction::simplify(res);

	return res;
}

const Fraction Fraction::operator/(const Fraction &crFraction) const noexcept(false)
{
	Fraction res{ x * crFraction.y, crFraction.x * y };
	if (!res.y)
		throw std::invalid_argument("Division by zero\n");

	Fraction::simplify(res);

	return res;
}

const Fraction & Fraction::operator+=(const Fraction &crFraction) noexcept
{
	return (*this = *this + crFraction);
}

const Fraction & Fraction::operator-=(const Fraction &crFraction) noexcept
{
	return (*this = *this - crFraction);
}

const Fraction & Fraction::operator*=(const Fraction &crFraction) noexcept
{
	return (*this = *this * crFraction);
}

const Fraction & Fraction::operator/=(const Fraction &crFraction) noexcept(false)
{
	return (*this = *this / crFraction);
}

void Fraction::simplify(Fraction &rFraction) noexcept
{
	for (auto gsd{ GSD(rFraction.x, rFraction.y) }; gsd != 1; gsd = GSD(rFraction.x, rFraction.y))
	{
		rFraction.x /= gsd;
		rFraction.y /= gsd;
	}
}

long double Fraction::eval() const noexcept(false)
{
	if (!y)
		throw std::invalid_argument("Division by zero\n");

	return static_cast<long double>(x / y);
}

std::ostream & operator<<(std::ostream &rOstr, const Fraction &crFraction)
{
	rOstr << crFraction.x << "/" << crFraction.y;

	return rOstr;
}

ll_t GSD(ll_t a, ll_t b) noexcept
{
	if (!a)
		return b;
	if (!b)
		return a;

	ll_t shift{};
	for (; !((a | b) & 1); ++shift)
	{
		a >>= 1;
		b >>= 1;
	}

	while (!(a & 1))
		a >>= 1;

	do
	{
		while (!(b & 1))
			b >>= 1;

		if (a > b)
			std::swap(a, b);

		b -= a;
	} while (b);

	return (a << shift);
}

