#pragma once
#include <random>
#include <vector>

namespace qm
{
	class rng_mt19937_std
	{
	private:
		std::random_device randomDevice;

	public:

		rng_mt19937_std() : mt(randomDevice()) { }
		explicit rng_mt19937_std(unsigned int seed) : mt(seed) { }

		template<typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
		T next(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
		{
			std::uniform_int_distribution<T> dist(min, max);
			return dist(mt);
		}
		template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
		T next(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
		{
			std::uniform_real_distribution<T> dist(min, max);
			return dist(mt);
		}

		std::mt19937 mt;
	};
}