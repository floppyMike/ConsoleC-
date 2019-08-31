#pragma once

#include "Includes.h"
#include "Interfaces.h"

template<typename ImplMon, typename ImplLog, typename ImplSec>
class Account : public IAccount<Account<ImplMon, ImplLog, ImplSec>>
{
public:
	Account() = default;

	void deposit(float v) noexcept;
	void takeOut(float v) noexcept;
	auto balance() const noexcept;
	void showLogs() const noexcept;
	void setPin(size_t p) noexcept;
	bool validatePin(size_t p);

private:
	ImplMon m_money;
	ImplLog m_logger;
	ImplSec m_sec;
};

//template<typename ImplMon, typename ImplLog, typename ImplSec>
//inline void Account<ImplMon, ImplLog, ImplSec>::deposit(float v) noexcept
//{
//	m_money.transform(v);
//	m_logger.logDeposit(v);
//}
//
//template<typename ImplMon, typename ImplLog, typename ImplSec>
//inline void Account<ImplMon, ImplLog, ImplSec>::takeOut(float v) noexcept
//{
//	m_money.transform(-v);
//	m_logger.logTakeOut(v);
//}
//
//template<typename ImplMon, typename ImplLog, typename ImplSec>
//inline auto Account<ImplMon, ImplLog, ImplSec>::balance() const noexcept
//{
//	return m_money.balance();
//}
//
//template<typename ImplMon, typename ImplLog, typename ImplSec>
//inline void Account<ImplMon, ImplLog, ImplSec>::showLogs() const noexcept
//{
//	m_logger.printAll();
//}
//
//template<typename ImplMon, typename ImplLog, typename ImplSec>
//inline void Account<ImplMon, ImplLog, ImplSec>::setPin(size_t p) noexcept
//{
//	m_sec.pin(p);
//}
//
//template<typename ImplMon, typename ImplLog, typename ImplSec>
//inline bool Account<ImplMon, ImplLog, ImplSec>::validatePin(size_t p)
//{
//	return m_sec.validate(p);
//}
