#pragma once

#include "Includes.h"

class AccountLogger
{
public:
	AccountLogger() = default;

	void logDeposit(float v) noexcept;
	void logTakeOut(float v) noexcept;
	void printAll() const noexcept;

private:
	std::deque<std::string> m_logs;
};

