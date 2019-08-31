#include "Globals.h"

void AccountLogger::logDeposit(float v) noexcept
{
	m_logs.emplace_back(std::to_string(v) + " deposited");
}

void AccountLogger::logTakeOut(float v) noexcept
{
	m_logs.emplace_back(std::to_string(v) + " took out");
}

void AccountLogger::printAll() const noexcept
{
	for (const auto& i : m_logs)
		std::cout << i << '\n';
}
