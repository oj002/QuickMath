#pragma once
#include <algorithm>
#include <cstdint>
#include <gsl\gsl>
#include <numeric>
#include <string>
#include <vector>

namespace qm
{
	class uintBig
	{
	public:
		using internal_t = uint32_t;
		using internal_size_t = uint64_t;
		using data_t = std::vector<internal_t>;
		static constexpr internal_t t_max = std::numeric_limits<internal_t>::max();
		static constexpr internal_t t_base = std::numeric_limits<internal_t>::max();

	public:
		uintBig() = default;

		explicit uintBig(const std::string &val) : data((val.size() % t_base) + 1, 0)
		{
			data_t dataBase10;
			dataBase10.resize(val.length());
			for (const char i : val)
			{ 
				dataBase10.push_back(i - '0');
			}
			this->data = convertBase(dataBase10, 10, t_base);
		}
		explicit uintBig(const std::wstring &val) : data((val.size() % t_base) + 1, 0)
		{
			data_t dataBase10;
			dataBase10.resize(val.length());
			for (internal_size_t i = 0; i < val.length(); ++i)
			{ 
				dataBase10.push_back(std::stoi(val.substr(i, 1))); 
			}
			this->data = convertBase(dataBase10, 10, t_base);
		}

		/*uintBig add(const uintBig &other)
		{
			bool carry{ false };
			for (internal_size_t i = 0; i < this->data.size(); ++i)
			{
				if (t_max - this->data[i] < other.data[i]) 
				{
					carry = true;
				}
			}
		}*/


	public: // Getter
		std::string to_string(size_t base = 10)
		{
			// https://cs.stackexchange.com/a/85982
			data_t num{ this->data };
			std::string digits;
			while (!is_zero(num))
			{
				digits += gsl::at(uintBig::to_base_c, modulo_div(&num, t_base, base));
			}
			std::reverse(digits.begin(), digits.end());
			return digits;
		}
		std::wstring to_wstring(internal_size_t base = 10)
		{
			data_t num{ this->data };
			std::wstring digits;
			while (!is_zero(num))
			{
				
				digits += gsl::at(uintBig::to_base_wc, modulo_div(&num, t_base, base));
			}
			std::reverse(digits.begin(), digits.end());
			return digits;
		}
	public: // Setter
		void set(std::string val)
		{
			data.resize((val.size() % t_base) + 1, 0);
			data_t dataBase10;
			dataBase10.resize(val.length());
			for (const char i : val)
			{ 
				dataBase10.push_back(i - '0');
			}
			this->data = convertBase(dataBase10, 10, t_base);
		}
		void set(const std::wstring& val)
		{
			data.resize((val.size() % t_base) + 1, 0);
			data_t dataBase10;
			dataBase10.resize(val.length());
			for (internal_size_t i = 0; i < val.length(); ++i)
			{ 
				dataBase10.push_back(std::stoi(val.substr(i, 1)));
			}
			this->data = convertBase(dataBase10, 10, t_base);
		}
	private:
		bool is_zero(const std::vector<internal_t> &num) const noexcept
		{
			for (const internal_t &n : num)
			{
				if (n != 0) { return false; }
			}
			return true;
		}

		internal_t modulo_div(gsl::not_null<std::vector<internal_t>*> num, internal_size_t original_base, internal_size_t destination_base) const
		{
			internal_t carry{ 0 };
			for (internal_t &n : *num)
			{
				internal_size_t d{ n };
				d += original_base * carry;
				carry = gsl::narrow<internal_t>(d % destination_base);
				n = gsl::narrow<internal_t>(d / destination_base);
			}
			return carry;
		}

		std::vector<internal_t> convertBase(std::vector<internal_t> num, internal_size_t original_base, internal_size_t destination_base) const
		{
			std::vector<internal_t> digits;
			while (!is_zero(num))
			{
				digits.push_back(modulo_div(&num, original_base, destination_base));
			}
			std::reverse(digits.begin(), digits.end());
			return digits;
		}

	private:
		static const char to_base_c[36];
		static const wchar_t to_base_wc[36];

	public:
		data_t data;
	};

	const char uintBig::to_base_c[] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z'
	};
	const wchar_t uintBig::to_base_wc[] = {
		L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9',
		L'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H', L'I', L'J',
		L'K', L'L', L'M', L'N', L'O', L'P', L'Q', L'R', L'S', L'T',
		L'U', L'V', L'W', L'X', L'Y', L'Z'
	};
}  // namespace qm