#define _USE_MATH_DEFINES // M_PI
#include <cmath>     // std::sin, std::cos
#include <algorithm> // std::min, std::max
#include <iostream>  // std::cout

#include "Polynomial.hpp"

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
		res.coefs_[i] = static_cast<int>(a[i].real() + .5);

	return (res);
}

const Polynomial Polynomial::operator/(const Polynomial &) const noexcept(false)
{
	return Polynomial();
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

void Polynomial::print() const noexcept
{
	const auto size = coefs_.size();
	for (auto i{ 0ull }; i < size; ++i)
	{
		std::cout << coefs_[i];
		
		if (i)
			std::cout << "x^" << i;

		if(i + 1 < size)
			std::cout << " + ";
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
