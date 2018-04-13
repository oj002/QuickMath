#include <string>
#include <numeric>
#include <vector>

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
		uintBig(size_t size, T default_val = 0) : data(size, default_val)
		{
			if (t_base > t_max) { throw std::invalid_argument(typeid(class_t).name() + std::string(" template parameter two base cant be bigger than std::numeric_limits<T>")); }
		}

		template<typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
		uintBig(const std::string &val) : data((val.size() % t_base) + 1, 0)
		{
			if (t_base > t_max) { throw std::invalid_argument(typeid(class_t).name() + std::string(" template parameter two base cant be bigger than std::numeric_limits<T>")); }
			std::vector<T> dataBase10;
			dataBase10.resize(val.length());
			for (size_t i = 0; i < val.length(); ++i) { dataBase10.emplace_back(std::atoi(val.substr(i, 1).c_str())); }
			this->data = convertBase<T>(dataBase10, 10, t_base);
		}

		template<typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
		uintBig(const std::wstring &val) : data((val.size() % t_base) + 1, 0)
		{
			if (t_base > t_max) { throw std::invalid_argument(typeid(class_t).name() + std::string(" template parameter two base cant be bigger than std::numeric_limits<T>")); }
			std::vector<T> dataBase10;
			dataBase10.resize(val.length());
			for (size_t i = 0; i < val.length(); ++i) { dataBase10.emplace_back(std::atoi(val.substr(i, 1).c_str())); }
			this->data = convertBase<T>(dataBase10, 10, t_base);
		}

		class_t add(const class_t &other)
		{
			bool carry{ false };
			for (size_t i = 0; i < this->data.size(); ++i)
			{
				if (t_max - this->data[i] < other.data[i]) { carry = true; }
			}
		}


	public: // Getter
		std::string to_string(size_t base = 10)
		{
			// https://cs.stackexchange.com/a/85982
			std::string ret;
			std::vector<T> num(convertBase<T>(this->data, t_base, base));
			for (T d: num) { ret += this->to_base_c[d]; }
			return ret;
		}
		std::wstring to_wstring(size_t base = 10)
		{
			std::wstring ret;
			std::vector<T> num(convertBase<T>(this->data, t_base, base));
			for (T d : num) { ret += this->to_base_wc[d]; }
			return ret;
		}
	public: // Setter
		void set(std::string val, size_t base = 10)
		{
			data.resize((val.size() % t_base) + 1, 0);
			std::vector<T> dataBase10;
			dataBase10.resize(val.length());
			for (size_t i = 0; i < val.length(); ++i) { dataBase10.emplace_back(std::atoi(val.substr(i, 1).c_str())); }
			this->data = convertBase<T>(dataBase10, 10, t_base);
		}
		void set(std::wstring val, size_t base = 10)
		{
			data.resize((val.size() % t_base) + 1, 0);
			std::vector<T> dataBase10;
			dataBase10.resize(val.length());
			for (size_t i = 0; i < val.length(); ++i) { dataBase10.emplace_back(std::atoi(val.substr(i, 1).c_str())); }
			this->data = convertBase<T>(dataBase10, 10, t_base);
		}

	private:
		char to_base_c[36] = {
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
			'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
			'U', 'V', 'W', 'X', 'Y', 'Z'
		};
		wchar_t to_base_wc[36] = {
			L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9',
			L'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H', L'I', L'J',
			L'K', L'L', L'M', L'N', L'O', L'P', L'Q', L'R', L'S', L'T',
			L'U', L'V', L'W', L'X', L'Y', L'Z'
		};

	public:
		data_t data;
	};
}