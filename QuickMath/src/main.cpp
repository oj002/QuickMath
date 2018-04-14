#include "../QuickMath/QuickMath.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

struct executionTimer
{
	executionTimer() noexcept
		: begin(std::chrono::high_resolution_clock::now())
	{}

	~executionTimer()
	{
		const std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

		std::cout << "Time took: " << duration << " microseconds" << std::endl;
		system("pause");
	}
	const std::chrono::high_resolution_clock::time_point begin;
};

int main()
{
	executionTimer et;

	qm::rng_mt19937_std rng;
	std::string str;
	qm::uintBig num;
	for (size_t i = 0; i < 2000; ++i)
	{
		str += std::to_string(rng.next<uint16_t>(0, 9));
		num.set(str);
		// printf("\r%zu", i);
		if (num.to_string() != str)
		{
			std::puts("shit!");
		}
	}
	return 0;
}