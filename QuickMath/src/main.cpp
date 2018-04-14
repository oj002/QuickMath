#include <iostream>
#include <string>
#include <vector>
#include "../QuickMath/QuickMath.hpp"

int main()
{
	/*qm::uintBig<unsigned int, 256> num(3, 0);
	num.data[2] = 10;
	std::cout << (num.to_string()) << std::endl;*/
	qm::rng_mt19937_std rng;
	std::string str;
	qm::uintBig num;
	for (size_t i = 0; i < 100000; ++i)
	{
		str += std::to_string(rng.next<unsigned int>(0, 9));
		num.set(str);
		printf("\r%d", i);
		if (num.to_string() != str)
		{
			std::puts("shit!");
		}
	}
	
	
	system("pause");
	return 0;
}