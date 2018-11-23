//{ Mod

template<long long Mod>
class mod
{
public:
	using ll_t = long long;

public:
	mod() noexcept = default;

	mod(ll_t arg) noexcept :
		x{ }
	{
		arg %= Mod;

		x = arg + (arg < 0 ? Mod : 0);
	}

	mod& operator+=(const mod &other) noexcept
	{
		x += other.x;

		if (x >= Mod)
			x -= Mod;

		return (*this);
	}

	mod& operator*=(const mod &other) noexcept
	{
		x = (x * other.x) % Mod;

		return (*this);
	}

	mod& operator-=(const mod &other) noexcept
	{
		x += Mod - other.x;

		if (x >= Mod)
			x -= Mod;

		return (*this);
	}

	template<class T>
	mod operator^=(T arg) noexcept
	{
		if (arg == 0) return 1;
		if (arg == 1) return x;

		auto t = *this ^ (arg >> 1);
		t *= t;

		if (arg & 1) t *= *this;

		return t;
	}

	mod operator+(const mod &other) const noexcept
	{
		mod tmp{ *this };
		tmp += other;

		return (tmp);
	}

	mod operator-(const mod &other) const noexcept
	{
		mod tmp{ *this };
		tmp -= other;

		return (tmp);
	}

	mod operator*(const mod &other) const noexcept
	{
		mod tmp{ *this };
		tmp *= other;

		return (tmp);
	}


	mod operator^(const mod &other) const noexcept
	{
		mod tmp{ *this };
		tmp ^= other;

		return (tmp);
	}

	operator short() const noexcept
	{
		return static_cast<short>(x);
	}

	operator int() const noexcept
	{
		return static_cast<int>(x);
	}

	operator long() const noexcept
	{
		return static_cast<long>(x);
	}

	operator long long() const noexcept
	{
		return static_cast<long long>(x);
	}

	mod& operator++() noexcept
	{
		++x;

		if (x == Mod)
			x = 0ll;

		return (*this);
	}

	mod& operator--() noexcept
	{
		if (!x)
			x = Mod - 1ll;
		else
			--x;

		return (*this);
	}

	mod operator++(int) noexcept
	{
		mod tmp{ *this };
		++*this;

		return tmp;
	}

	mod operator--(int) noexcept
	{
		mod tmp{ *this };
		--*this;

		return tmp;
	}

	bool operator==(const mod &other) const noexcept
	{
		return (x == other.x);
	}

	bool operator!=(const mod &other) const noexcept
	{
		return !(x == other.x);
	}

	mod inv() const noexcept // works clearly only when 'm' is prime number
	{
		return ((*this) ^ (Mod - 2));
	}

	bool isOdd() const noexcept
	{
		return (x & 1);
	}

	bool isEven() const noexcept
	{
		return !isOdd();
	}

private:
	ll_t x;
};

//}
