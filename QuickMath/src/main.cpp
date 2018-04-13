#include <iostream>
#include <string>
#include <vector>
#include "../QuickMath/QuickMath.hpp"

int main()
{
	/*qm::uintBig<unsigned int, 256> num(3, 0);
	num.data[2] = 10;
	std::cout << (num.to_string()) << std::endl;*/

	qm::uintBig<unsigned int, 256> num("112233445566778899");
	std::cout << (num.to_string()) << '\n';
	num.set("123456789");
	std::cout << (num.to_string()) << '\n';
	num.set("00123");
	std::cout << (num.to_string()) << std::endl;
	
	system("pause");
	return 0;
}