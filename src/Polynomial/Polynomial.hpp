#pragma once

#include <vector>  // std::vector
#include <complex> // std::complex

typedef std::complex<double> base_t;
typedef unsigned u_t;

class Polynomial final
{
	static void removeLeadingZeros(Polynomial&);

public:
	using T = int;
	using vCoef_t = std::vector<T>;

	Polynomial()                  noexcept = default;
	Polynomial(vCoef_t)           noexcept;
	Polynomial(const Polynomial&)          = default;
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

	Polynomial& operator=(const Polynomial&) = default;
	Polynomial& operator=(Polynomial&&)      = default;

	T& at(size_t) noexcept(false);
	const T& at(size_t) const noexcept(false);

	Polynomial dir() const;
	base_t eval(const base_t&) const noexcept;

	void print() const noexcept;

private:
	vCoef_t coefs_;
};

void FFT(std::vector<base_t>&);
void IFFT(std::vector<base_t>&);
