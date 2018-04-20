#pragma once
#include <chrono>
#include <iostream>

namespace qm
{
	struct ExecutionTimer
	{
		using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady, std::chrono::high_resolution_clock, std::chrono::steady_clock>;

		ExecutionTimer(): m_begin(Clock::now()), m_end(m_begin)
		{
		}

		~ExecutionTimer()
		{
			if (m_begin == m_end)
			{
				m_end = Clock::now();
			}
			const std::chrono::duration<double> elapsedTime{ m_end - m_begin };
			std::cout << "Time took: " << elapsedTime.count() << "s" << std::endl;
			system("pause");
		}

		void start()
		{
			if (m_begin == m_end)
			{
				m_begin = Clock::now();
				m_end = m_begin;
			}
			else
			{
				m_begin = Clock::now();
			}
		}

		void end()
		{
			m_end = Clock::now();
		}

		void stop()
		{
			Clock::time_point tmp = Clock::now();
			if (m_begin == m_end)
			{
				m_end = Clock::now();
			}
			const std::chrono::duration<double> elapsedTime{ m_end - m_begin };
			std::cout << "Time took: " << elapsedTime.count() << "s" << std::endl;
			system("pause");
			m_end = m_end + (Clock::now() - tmp);
		}

		Clock::time_point m_begin;
		Clock::time_point m_end;
	};

}  // namespace qm