#pragma once

typedef long long ll_t;

struct Fraction final
{
	Fraction() noexcept;
	//Fraction(std::string_view) noexcept;
	Fraction(ll_t, ll_t)      noexcept;
	Fraction(const Fraction&) noexcept = default;
	Fraction(Fraction&&)      noexcept = default;
	~Fraction()               noexcept = default;

	const Fraction operator+(const Fraction&) const noexcept;
	const Fraction operator-(const Fraction&) const noexcept;
	const Fraction operator*(const Fraction&) const noexcept;
	const Fraction operator/(const Fraction&) const noexcept(false);

	const Fraction& operator+=(const Fraction&) noexcept;
	const Fraction& operator-=(const Fraction&) noexcept;
	const Fraction& operator*=(const Fraction&) noexcept;
	const Fraction& operator/=(const Fraction&) noexcept(false);

	Fraction& operator=(const Fraction&) noexcept = default;
	Fraction& operator=(Fraction&&)      noexcept = default;

	static void simplify(Fraction&) noexcept;

public:
	ll_t x, // Numerator
		 y; // Denominator
};

std::ostream& operator<<(std::ostream&, const Fraction&);

ll_t GSD(ll_t, ll_t) noexcept;



