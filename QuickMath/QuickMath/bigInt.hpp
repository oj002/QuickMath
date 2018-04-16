#pragma once
#include <algorithm>
#include <cstdint>
#include <gsl\gsl>
#include <numeric>
#include <string>
#include <vector>

/*
	C++ implementation of the Java bigInteger class
	http://grepcode.com/file/repository.grepcode.com/java/root/jdk/openjdk/6-b14/java/math/BigInteger.java
*/

namespace qm
{
	struct NumberFormatException : public std::exception
	{
		NumberFormatException() : std::exception()  {}
		NumberFormatException(const std::string &msg) : std::exception(msg.c_str()) {}

		static NumberFormatException forInputString(std::string s)
		{
			return NumberFormatException("For input string: \"" + s + "\"");
		}
	};
	struct exeption : public std::exception
	{
		exeption(const std::string &msg, size_t line, const std::string &function, const std::string &path)
			: std::exception(("opml_exeption: " + msg + "\nat line: " + std::to_string(line) + " in function: " + function + "\nfrom file: " + path).c_str())
			, line(line)
			, function(function)
			, path(path)
		{
		}

		size_t line;
		std::string function, path;
	};
	class bigInt
	{
	private:
		int32_t signum;
		std::vector<int32_t> mag;
		int32_t bitCount{ -1 };
		int32_t bitLength{ -1 };
		int32_t lowestSetBit{ -2 };
		int32_t firstNonzeroByteNum{ -2 };
		int32_t firstNonzeroIntNum{ -2 };
		static const int64_t LONG_MASK{ 0xffffffffL };
	public:
		bigInt(const std::vector<int8_t> &val)
		{
			if (val.size() == 0) { throw NumberFormatException("Zero length BigInt"); }

			if (val[0] < 0)
			{
				mag = makePositive(val);
				signum = -1;
			}
			else
			{
				mag = stripLeadingZero(val);
				signum = (mag.size() == 0 ? 0 : 1);
			}
		}
		bigInt(int32_t _signum, const std::vector<int8_t> &magnitude)
		{
			this->mag = stripLeadingZero(magnitude);

			if (_signum < -1 || _signum > 1)
			{
				throw NumberFormatException("Invalid signum value");
			}
			if (this->mag.size() == 0)
			{
				this->signum = 0;
			}
			else
			{
				if (_signum == 0)
				{
					throw NumberFormatException("signum-magnitude mismatch");
				}
				this->signum = _signum;
			}
		}
		bigInt(int32_t _signum, const std::vector<int32_t> &magnitude)
		{
			this->mag = stripLeadingZero(magnitude);

			if (_signum < -1 || _signum > 1)
			{
				throw NumberFormatException("Invalid signum value");
			}
			if (this->mag.size() == 0)
			{
				this->signum = 0;
			}
			else
			{
				if (_signum == 0)
				{
					throw NumberFormatException("signum-magnitude mismatch");
				}
				this->signum = _signum;
			}
		}
		// http://grepcode.com/file/repository.grepcode.com/java/root/jdk/openjdk/6-b14/java/math/BigInteger.java#BigInteger.%3Cinit%3E%28java.lang.String%2Cint%29
	private:
		bigInt(const std::vector<int32_t> &val)
		{
			if (val.size() == 0) { throw NumberFormatException("Zero length BigInt"); }

			if (val[0] < 0)
			{
				mag = makePositive(val);
				signum = -1;
			}
			else
			{
				mag = trustedStripLeadingZero(val);
				signum = (mag.size() == 0 ? 0 : 1);
			}
		}


	private:
		static std::vector<int32_t> trustedStripLeadingZero(const std::vector<int32_t> &a)
		{
			int32_t aLength{ a.size() };
			int32_t keep; // TODO: initialize at construction
			for (keep = 0; keep < aLength && a[keep] == 0; ++keep) {}

			if (keep > 0)
			{
				std::vector<int32_t> result(aLength - keep);
				for (int32_t i{ 0 }; i < aLength - keep; ++i)
				{
					result[i] = a[keep + i];
				}
				return result;
			}
			return a;
		}
		static std::vector<int32_t> stripLeadingZero(const std::vector<int32_t> &a)
		{
			int32_t aLength{ a.size() };
			int32_t keep; // TODO: initialize at construction
			for (keep = 0; keep < aLength && a[keep] == 0; ++keep) {}

			int32_t resLength{ aLength - keep };
			std::vector<int32_t> result(resLength);
			for (int32_t i{ 0 }; i < resLength; ++i)
			{
				result[i] = a[keep + i];
			}
			return result;
		}
		static std::vector<int32_t> stripLeadingZero(const std::vector<int8_t> &a)
		{
			int32_t byteLength{ a.size() };
			int32_t keep; // TODO: initialize at construction
			for (keep = 0 ; keep < byteLength && a[keep] == 0; ++keep) {}

			int32_t intLength{ ((byteLength - keep) + 3) / 4 };
			std::vector<int32_t> result(intLength);
			int32_t b{ byteLength - 1 };
			for (int32_t i{ intLength - 1 }; i >= 0; --i)
			{
				result[i] = a[b--] & 0xff;
				int32_t bytesRemaining{ b - keep + 1 };
				int32_t bytesToTransfer{ std::min(3, bytesRemaining) };
				for (int32_t j{ 8 }; j <= 8 * bytesToTransfer; j += 8)
				{
					result[i] |= ((a[b--] & 0xff) << j);
				}
			}
		}
		static std::vector<int32_t> makePositive(const std::vector<int8_t> &a)
		{
			int32_t keep, k; // TODO: initialize at construction
			int32_t byteLength{ a.size() };

			for (keep = 0; keep < byteLength && a[k] == 0; ++k) {}
			for (k = keep; k < byteLength && a[k] == 0; k++) {}

			int32_t extraByte{ (k == byteLength) ? 1 : 0 };
			int32_t intLength{ (byteLength - keep + extraByte) + 3) / 4 };
			std::vector<int32_t> result(intLength);

			int32_t b{ byteLength - 1 };
			for (int32_t i{ intLength - 1 }; i >= 0; --i)
			{
				result[i] = a[b--] & 0xff ;
				int32_t numBytesToTransfer{ std::min(3, b - keep + 1 )};
				if (numBytesToTransfer < 0)
				{
					numBytesToTransfer = 0;
				}
				for (int32_t j{ 8 }; j <= 8 * numBytesToTransfer; j += 8)
				{
					result[i] |= ((a[b--] & 0xff) << j);
				}

				int32_t mask{ static_cast<int32_t>(static_cast<uint32_t>(-1) >> (8 * (3 - numBytesToTransfer))) };
				result[i] = ~result[i] & mask;
			}

			for (int32_t i = result.size() - 1; i >= 0; --i)
			{
				result[i] = static_cast<int32_t>((result[i] & LONG_MASK) + 1);
				if (result[i] != 0) { break; }
			}
			
			return result;
		}
		static std::vector<int32_t> makePositive(const std::vector<int32_t> &a)
		{
			int32_t keep, j; // TODO: initialize at construction
			int32_t aLength{ a.size() };

			for (keep = 0; keep < aLength && a[keep] == -1; ++keep) {}
			for (j = keep; j < aLength && a[j] == 0; ++j) {}


			int32_t extraInt{ (j == aLength) ? 1 : 0 };
			int32_t resSize{ aLength - keep + extraInt };
			std::vector<int32_t> result(resSize);

			for (int32_t i{ keep }; i < aLength; ++i)
			{
				result[i - keep + extraInt] = ~a[i];
			}

			for (int32_t i{ resSize - 1}; ++result[i] == 0; --i) {}

			return result;
		}
	};
}  // namespace qm