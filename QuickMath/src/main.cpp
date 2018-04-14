#include <iostream>
#include <string>
#include <vector>
#include "../QuickMath/QuickMath.hpp"

int main()
{
	qm::rng_mt19937_std rng;
	std::string str;
	qm::uintBig num;
	for (size_t i = 0; i < 100000; ++i)
	{
		str += std::to_string(rng.next<unsigned short>(0, 9));
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