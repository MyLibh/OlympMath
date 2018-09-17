#define _USE_MATH_DEFINES // M_PI
#include <cmath>     // std::sin, std::cos
#include <algorithm> // std::min, std::max
#include <iostream>  // std::cout
#include <cassert>   // assert

#include "Polynomial.hpp"

void Polynomial::removeLeadingZeros(Polynomial &rPolynomial)
{
	size_t count{};
	for (auto it = rPolynomial.coefs_.rbegin(); it != rPolynomial.coefs_.rend(); ++it)
		if (!*it)
			count++;
		else
			break;

	rPolynomial.coefs_.resize(rPolynomial.coefs_.size() - count);
}

Polynomial::Polynomial(vCoef_t coefs) noexcept :
	coefs_(coefs)
{
}

const Polynomial Polynomial::operator+(const Polynomial &crPolynomial) const noexcept
{
	Polynomial res(*this);
	if (coefs_.size() < crPolynomial.coefs_.size())
		res.coefs_.resize(crPolynomial.coefs_.size());

	for (auto i{ 0ull }; i < crPolynomial.coefs_.size(); ++i)
		res.coefs_[i] += crPolynomial.coefs_[i];

	return (res);
}

const Polynomial Polynomial::operator-(const Polynomial &crPolynomial) const noexcept
{
	Polynomial res(*this);
	if (coefs_.size() < crPolynomial.coefs_.size())
		res.coefs_.resize(crPolynomial.coefs_.size());

	for (auto i{ 0ull }; i < crPolynomial.coefs_.size(); ++i)
		res.coefs_[i] -= crPolynomial.coefs_[i];

	return (res);
}

const Polynomial Polynomial::operator*(const Polynomial &crPolynomial) const noexcept
{
	std::vector<base_t> a(coefs_.begin(), coefs_.end()),
		                b(crPolynomial.coefs_.begin(), crPolynomial.coefs_.end());

	size_t n{ 1 };
	while (n < std::max(coefs_.size(), crPolynomial.coefs_.size()))
		n <<= 1;

	n <<= 1;
	a.resize(n);
	b.resize(n);

	FFT(a);
	FFT(b);
	for (auto i{ 0ull }; i < n; ++i)
		a[i] *= b[i];

	IFFT(a);

	Polynomial res{ vCoef_t(n) };
	for (auto i{ 0ull }; i < n; ++i)
		res.coefs_[i] = static_cast<Polynomial::T>(a[i].real() + .5); // TODO: fix on negatives

	removeLeadingZeros(res);

	return (res);
}

const Polynomial Polynomial::operator/(const Polynomial &crPolynomial) const noexcept(false)
{
	const auto crPolySize_dec{ crPolynomial.coefs_.size() - 1 }, // crPolynomial.coefs_.size() - 1
		       tmpSize_dec{ coefs_.size() - 1 },                 // coefs_.size() - 1
		       resSize_dec{ crPolySize_dec + tmpSize_dec + 2 };  // + 2 because of 2 * dec
	vCoef_t tmp{ coefs_ },
		    res(resSize_dec + 1);
	for (auto i{ 0ull }; i < resSize_dec + 1; ++i)
	{
		res[resSize_dec - i] = tmp[tmpSize_dec - i] / crPolynomial.coefs_[crPolySize_dec];
		for (auto j{ 0ull }; j < crPolySize_dec + 1; ++j)
			tmp[tmpSize_dec - i - j] -= crPolynomial.coefs_[crPolySize_dec - j] * res[resSize_dec - i];
	}

	if (tmp.size())
		std::cout << "!!! Lost remainder !!!\n";

	return { res };
}

const Polynomial& Polynomial::operator+=(const Polynomial &crPolynomial) noexcept
{
	return (*this = *this + crPolynomial);
}

const Polynomial& Polynomial::operator-=(const Polynomial &crPolynomial) noexcept
{
	return (*this = *this - crPolynomial);
}

const Polynomial& Polynomial::operator*=(const Polynomial &crPolynomial) noexcept
{
	return (*this = *this * crPolynomial);
}

const Polynomial& Polynomial::operator/=(const Polynomial &crPolynomial) noexcept(false)
{
	return (*this = *this / crPolynomial);
}

Polynomial::T& Polynomial::at(size_t n) noexcept(false)
{
	return (coefs_.at(n));
}

const Polynomial::T& Polynomial::at(size_t n) const noexcept(false)
{
	return (coefs_.at(n));
}

Polynomial Polynomial::dir() const
{
	vCoef_t vec(coefs_.size() - 1);
	for (size_t i{ vec.size() }; i; --i)
		vec[i - 1] = coefs_[i] * static_cast<T>(i);

	return { vec };
}

size_t Polynomial::deg() const noexcept
{
	assert(coefs_.size() >= 2);

	return (coefs_.size() - 1);
}

base_t Polynomial::eval(const base_t &x) const noexcept
{
	if (coefs_.size() == 1)
		return (coefs_[0]);

	base_t res = coefs_.back();
	const auto size{ coefs_.size() };
	for (auto i{ 1ull }; i <= size - 1; ++i)
	{
		res = res * x;
		res += coefs_[size - 1 - i];
	}

	return (res);
}

void Polynomial::print() const noexcept
{
	assert(coefs_.size() != 0);

	std::cout << "P(x) = ";
	if (coefs_[0])
		std::cout << coefs_[0];

	const auto size = coefs_.size();
	for (auto i{ 1ull }; i < size; ++i)
		if (coefs_[i])
		{
			if (i == 1 && !coefs_[0])
			{
				if (std::abs(coefs_[i]) != 1)
					std::cout << coefs_[i];
			}
			else
			{
				if(coefs_[i] > 0)
					std::cout << " + ";
				else
					std::cout << " - ";

				if(std::abs(coefs_[i]) != 1)
					std::cout << std::abs(coefs_[i]) << " * ";			
			}
			std::cout << "x^" << i;
		}

	std::cout << std::endl;
}

void FFT(std::vector<base_t> &A)
{
	auto N = A.size();
	if (N == 1)
		return;

	std::vector<base_t> A0(N >> 1),
		                A1(N >> 1);
	for (auto i{ 0ull }, j{ 0ull }; i < N; i += 2, ++j)
	{
		A0[j] = A[i];
		A1[j] = A[i + 1];
	}
	
	FFT(A0);
	FFT(A1);

	double alf = 2 * M_PI / static_cast<double>(N);

	N >>= 1;

	base_t w{ 1 },
		   wn{ std::cos(alf), std::sin(alf) };
	for (auto i{ 0ull }; i < N; ++i)
	{
		A[i    ] = A0[i] + w * A1[i];
		A[i + N] = A0[i] - w * A1[i];

		w *= wn;
	}
}

void IFFT(std::vector<base_t> &A)
{
	auto N = A.size();
	if (N == 1)
		return;

	std::vector<base_t> A0(N >> 1),
		                A1(N >> 1);
	for (auto i{ 0ull }, j{ 0ull }; i < N; i += 2, ++j)
	{
		A0[j] = A[i];
		A1[j] = A[i + 1];
	}
	
	IFFT(A0);
	IFFT(A1);

	double alf = -2 * M_PI / static_cast<double>(N);

	N >>= 1;

	base_t w{ 1 },
		   wn{ std::cos(alf), std::sin(alf) };
	for (auto i{ 0ull }; i < N; ++i)
	{
		A[i]     = (A0[i] + w * A1[i]) / 2.;
		A[i + N] = (A0[i] - w * A1[i]) / 2.;

		w *= wn;
	}
}
