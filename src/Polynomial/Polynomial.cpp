#include <algorithm> // std::min
#include <iostream>  // std::cout

#include "Polynomial.hpp"

const Polynomial Polynomial::operator+(const Polynomial &crPolynomial) const noexcept
{
	bool       greater{ coefs_.size() > crPolynomial.coefs_.size() };
	const auto minSize{ std::min(coefs_.size(), crPolynomial.coefs_.size()) };

	Polynomial res(greater ? *this : crPolynomial);
	for (auto i{ 0u }; i < minSize; ++i)
		res.coefs_[i] += (greater ? crPolynomial.coefs_[i] : coefs_[i]);

	return (res);
}

base_t& Polynomial::at(u_t n) noexcept(false)
{
	return (coefs_.at(n));
}

const base_t& Polynomial::at(u_t n) const noexcept(false)
{
	return (coefs_.at(n));
}

void Polynomial::print() const noexcept
{
	const auto size = coefs_.size();
	for (auto i{ 0u }; i < size; ++i)
		std::cout << coefs_[i] << " * x^" << i << " + ";
}
