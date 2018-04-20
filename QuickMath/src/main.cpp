#include "../QuickMath/QuickMath.hpp"

// https://rosettacode.org/wiki/Lucas-Lehmer_test
// https://rosettacode.org/wiki/Mersenne_primes
// https://www.mersenne.org/primes/
static bool isSmaller(std::string str1, std::string str2)
{
	// Calculate lengths of both string
	int n1 = str1.length(), n2 = str2.length();

	if (n1 < n2) {
		return true;
	}
	if (n1 > n2) {
		return false;
	}

	for (int i = 0; i<n1; i++)
	{
		if (str1[i] < str2[i]) {
			return true;
		} if (str1[i] > str2[i]) {
			return false;
		}
	}
	return false;
}

// Function for finding difference of larger numbers
static std::string findDiff(std::string a, std::string b)
{
	// Before proceeding further, make sure str1
	// is not smaller
	if (isSmaller(a, b)) {
		std::swap(a, b);
	}

	// Take an empty string for storing result
	std::string str = str;

	// Calculate lengths of both string
	int n1 = a.length(), n2 = b.length();
	int diff = n1 - n2;

	// Initially take carry zero
	int carry = 0;

	// Traverse from end of both strings
	for (int i = n2 - 1; i >= 0; i--)
	{
		// Do school mathematics, compute difference of
		// current digits and carry
		int sub = ((a[i + diff] - '0') -
			(b[i] - '0') -
			carry);
		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else {
			carry = 0;
		}

		str.push_back(sub + '0');
	}

	// subtract remaining digits of s[]
	for (int i = n1 - n2 - 1; i >= 0; i--)
	{
		if (a[i] == '0' && (carry != 0))
		{
			str.push_back('9');
			continue;
		}
		int sub = ((a[i] - '0') - carry);
		if (i>0 || sub>0) { // remove preceding 0's
			str.push_back(sub + '0');
		}
		carry = 0;

	}

	// reverse resultant string
	std::reverse(str.begin(), str.end());

	return str;
}
int main()
{
	qm::rng_mt19937_std rng;

	qm::ExecutionTimer et;
	std::string strA{"1"};
	std::string strB{"1"};
	for (size_t i = 0; i < 1000; ++i)
	{
		int32_t num{ rng.next<int32_t>(0, 4) };
		if (num == 0 || num == 1)
		{
			for (size_t j = 0; j < rng.next<int32_t>(0, 20); ++j)
			{
				strA += std::to_string(rng.next<int>(0, 9));
			}
		}
		else if (num == 2 || num == 3)
		{
			for (size_t j = 0; j < rng.next<int32_t>(0, 20); ++j)
			{
				strB += std::to_string(rng.next<int32_t>(0, 9));
			}
		}
		else
		{
			std::swap(strA, strB);
		}
		std::string firstRes{ findDiff(strA, strB) };
		qm::uintBig a(strA);
		qm::uintBig b(strB);
		std::string secondRes{ a.difference(b).to_string() };
		std::cout << '\r' << i;
		if (qm::uintBig(firstRes).to_string() != secondRes)
		{
			std::puts("\nfuck");
		}
	}
	
	std::cout << "\n";
	/*int n{ 0 };
	qm::uintBig factorial("1");

	std::cout << "Enter a positive integer: ";
	std::cin >> n;
	
	et.sart();

	for (int i = 2; i <= n; ++i)
	{
		factorial = factorial.mul(qm::uintBig(std::to_string(i)));
	}
	std::string str{ factorial.to_string() };

	et.end();

	std::cout << "Factorial of " << n << " =\n";
	std::puts(factorial.to_string().c_str());*/
	

	return 0;
}