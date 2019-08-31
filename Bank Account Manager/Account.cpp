#include "Globals.h"

template<typename ImplMon, typename ImplLog, typename ImplSec>
void Account<ImplMon, ImplLog, ImplSec>::deposit(float v) noexcept
{
	m_money.transform(v);
	m_logger.logDeposit(v);
}

template<typename ImplMon, typename ImplLog, typename ImplSec>
void Account<ImplMon, ImplLog, ImplSec>::takeOut(float v) noexcept
{
	m_money.transform(-v);
	m_logger.logTakeOut(v);
}

template<typename ImplMon, typename ImplLog, typename ImplSec>
auto Account<ImplMon, ImplLog, ImplSec>::balance() const noexcept
{
	return m_money.balance();
}

template<typename ImplMon, typename ImplLog, typename ImplSec>
void Account<ImplMon, ImplLog, ImplSec>::showLogs() const noexcept
{
	m_logger.printAll();
}

template<typename ImplMon, typename ImplLog, typename ImplSec>
void Account<ImplMon, ImplLog, ImplSec>::setPin(size_t p) noexcept
{
	m_sec.pin(p);
}

template<typename ImplMon, typename ImplLog, typename ImplSec>
bool Account<ImplMon, ImplLog, ImplSec>::validatePin(size_t p)
{
	return m_sec.validate(p);
}

template class Account<AccountMoney, AccountLogger, AccountSecurity>;