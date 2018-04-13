#include <iostream>
#include <string>
#include <vector>
#include "../QuickMath/QuickMath.hpp"

int main()
{
	/*qm::uintBig<unsigned int, 256> num(3, 0);
	num.data[2] = 10;
	std::cout << (num.to_string()) << std::endl;*/

	/*qm::uintBig<unsigned int, 256> num("1000232334563456666666666456457567678870812345651356543568987654354654675");
	std::cout << (num.to_string()) << std::endl;*/
	qm::rng_mt19937_std rng;
	for (size_t i = 0; i < 100; ++i)
	{
		std::cout << (rng.next<unsigned char>(0, 1)) << '\n';
		std::cout << (rng.next<unsigned char>(0, 1)) << '\n';
	}
	
	system("pause");
	return 0;
}