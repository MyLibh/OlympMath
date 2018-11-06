//{ KMP

#ifndef _STRING_
	#ifdef __has_include
		#if __has_include(<string>)
			#include <string>
		#else
			#error "Missing <string>"
		#endif /* if __has_include(<string>) */
	#else
		#include <string>
	#endif /* ifdef __has_include */
#endif /* ifndef _STRING_ */

#ifndef _VECTOR_
	#ifdef __has_include
		#if __has_include(<vector>)
			#include <vector>
		#else
			#error "Missing <vector>"
		#endif /* if __has_include(<vector>) */
	#else
		#include <vector>
	#endif /* ifdef __has_include */
#endif /* ifndef _VECTOR_ */

std::string::size_type KMP(const string &str, long long from, const std::string &pattern)
{
	auto pat_length{ pattern.length() };
	std::vector<long long> pf (pat_length);

	pf[0] = 0;
	for (long long k{ }, i{ 1 }; i < pat_length; ++i)
	{
		while ((k > 0) && (pattern[i] != pattern[k]))
			k = pf[k - 1];

		if (pattern[i] == pattern[k])
			k++;

		pf[i] = k;
	}

	auto str_length{ str.length() };
	for (long long k{ }, i{ from }; i < str_length; ++i)
	{
		while ((k > 0) && (pattern[k] != str[i]))
			k = pf[k-1];

		if (pattern[k] == str[i])
			k++;

		if (k == pat_length)
			return (i - pat_length + 1);
	}

	return (string::npos);
}

//}
