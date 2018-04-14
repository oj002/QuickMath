#pragma once
#include <random>

namespace qm
{
	class rng_mt19937_std
	{
	public:
		rng_mt19937_std() noexcept : mt(randomDevice()) { }
		explicit rng_mt19937_std(unsigned int seed) : mt(seed) { }

		template<typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
		T next(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
		{
			const std::uniform_int_distribution<T> dist(min, max);
			return dist(mt);
		}
		template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
		T next(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
		{
			const std::uniform_real_distribution<T> dist(min, max);
			return dist(mt);
		}

	public:
		std::random_device randomDevice;
		std::mt19937 mt;
	};
}  // namespace qm