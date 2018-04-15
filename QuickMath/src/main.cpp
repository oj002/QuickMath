#include "../QuickMath/QuickMath.hpp"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

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

	/*qm::rng_mt19937_std rng;
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
	qm::uintBig a("123");
	qm::uintBig b("987");
	std::cout << (a.mul(b)).to_string() << '\n';// a.to_string() << '\n' << b.to_string() << '\n' << a.add(b).to_string() << std::endl;
	*/
	int n{ 0 };
	qm::uintBig factorial("1");

	std::cout << "Enter a positive integer: ";
	std::cin >> n;

	executionTimer et;
	for (int i = 1; i <= n; ++i)
	{
		factorial = factorial.mul(qm::uintBig(std::to_string(i)));
	}

	std::cout << "Factorial of " << n << " = " << factorial.to_string(10) << std::endl;
	return 0;
}