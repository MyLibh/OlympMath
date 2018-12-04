#include <vector>

class HammingCode
{
public:
	using ll_t = long long;

public:
	static std::vector<bool> encode(const std::vector<bool> data /* , std::size_t block_size */)
	{
		ll_t pow{ 0 };
		while (data.size() > 1ll << ++pow);
		--pow;

		std::vector<bool> res(data.size() + pow);
		auto it = data.begin();
		for (ll_t i{}; i < res.size(); ++i)
			res[i] = !(i & (i + 1ll)) ? 0 : *it++;

		for (ll_t p{ 1 }; p < pow; ++p)
		{
			ll_t idx{ 1ll << (p - 1) };
			ll_t ans{};
			for (ll_t i{ idx }; i < res.size(); i += (idx << 1ll) + 1ll)
				for (ll_t j{ i }; j < i + idx; ++j)
					ans ^= res[j];
			
			res[idx] = ans;
		}

		return res;
	}

	static std::vector<bool> decode(const std::vector<bool> data /* , std::size_t block_size */)
	{

	}
};