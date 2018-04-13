#include <string>
#include <numeric>
#include <vector>
#include <algorithm>
#include <iostream>

namespace qm
{
	template<typename T>
	bool is_zero(std::vector<T> &num)
	{
		for (T &n : num)
		{
			if (n != 0) { return false; }
		}
		return true;
	}

	template<typename T>
	size_t modulo_div(std::vector<T> &num, size_t original_base, size_t destination_base)
	{
		size_t carry{ 0 };
		for (T &n : num)
		{
			size_t d{ n };
			d += original_base * carry;
			carry = d % destination_base;
			d /= destination_base;
			n = d;
		}
		return carry;
	}

	template<typename T>
	std::vector<T> convertBase(std::vector<T> num, size_t original_base, size_t destination_base)
	{
		std::vector<T> digits;
		while (!is_zero(num))
		{
			digits.insert(digits.begin(), modulo_div(num, original_base, destination_base));
		}
		return digits;
	}

	template<typename T, size_t t_base = std::numeric_limits<T>::max()>
	class uintBig
	{
	public:
		typedef uintBig<T> class_t;
		typedef std::vector<T> data_t;
		static constexpr size_t t_max = std::numeric_limits<T>::max();
	public:
		template<typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
		uintBig(size_t size, T default_val = 0)
			: data(size, default_val)
		{
			if (t_base > t_max)
			{
				throw std::invalid_argument(typeid(class_t).name() + std::string(" template parameter two base cant be bigger than std::numeric_limits<T>"));
			}
		}

		template<typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
		uintBig(const std::string &val)
			: data((val.size() % t_base) + 1)
		{
			if (t_base > t_max)
			{
				throw std::invalid_argument(typeid(class_t).name() + std::string(" template parameter two base cant be bigger than std::numeric_limits<T>"));
			}
			std::vector<T> dataBase10;
			dataBase10.resize(val.length());
			for (size_t i = 0; i < val.length(); ++i)
			{
				dataBase10.emplace_back(std::atoi(val.substr(i, 1).c_str()));
			}
			this->data = convertBase<T>(dataBase10, 10, t_base);
		}

		class_t add(const class_t &other)
		{
			bool carry{ false };
			for (size_t i = 0; i < this->data.size(); ++i)
			{
				if (t_max - this->data[i] < other.data[i])
				{
					carry = true;
				}
			}
		}

	public: // Getter
		std::string to_string(size_t base = 10)
		{
			std::string ret;
			std::vector<T> num(convertBase<T>(this->data, t_base, base));
			for (T d: num)
			{
				ret += this->to_base[d];
			}
			return ret;

			// https://cs.stackexchange.com/a/85982
		}
		std::wstring to_wstring(size_t base = 10)
		{

		}
	public: // Setter
		void set(std::string, size_t base = 10)
		{
			/*
				n = 0
				for d in digits:
					n = b * n + d
				return n
			*/
		}
		void set(std::wstring, size_t base = 10)
		{
		}

	private:
		char to_base[36] = {
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
			'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
			'U', 'V', 'W', 'X', 'Y', 'Z'
		};
	

	public:
		data_t data;
	};
}