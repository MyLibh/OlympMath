#pragma once

#include <vector>  // std::vector
#include <complex> // std::complex

typedef std::complex<double> base_t;
typedef unsigned u_t;

class Polynomial final
{
public:
	using vCoef_t = std::vector<base_t>;

	Polynomial()                  noexcept = default;
	Polynomial(vCoef_t)           noexcept;
	Polynomial(const Polynomial&) noexcept = default;
	Polynomial(Polynomial&&)      noexcept = default;
	~Polynomial()                 noexcept = default;

	const Polynomial operator+(const Polynomial&) const noexcept;
	const Polynomial operator-(const Polynomial&) const noexcept;
	const Polynomial operator*(const Polynomial&) const noexcept;
	const Polynomial operator/(const Polynomial&) const noexcept(false);

	const Polynomial& operator+=(const Polynomial&) noexcept;
	const Polynomial& operator-=(const Polynomial&) noexcept;
	const Polynomial& operator*=(const Polynomial&) noexcept;
	const Polynomial& operator/=(const Polynomial&) noexcept(false);

	base_t& at(u_t) noexcept(false);
	const base_t& at(u_t) const noexcept(false);

	void print() const noexcept;

private:
	vCoef_t coefs_;
};