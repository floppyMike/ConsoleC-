#pragma once

#include "Includes.h"
#include "Interfaces.h"

template<typename ImplAccDB>
class ATM
{
public:
	ATM(ImplAccDB* db)
		: m_db(db)
	{
	}

	IAccount<typename ImplAccDB::account_t>* access(const std::string_view& account, uint_fast16_t pin);

private:
	ImplAccDB* m_db;
};

//template<typename ImplAccDB>
//inline IAccount<typename ImplAccDB::account_t>* ATM<ImplAccDB>::access(const std::string_view& account, uint_fast16_t pin)
//{
//	auto* acc = &m_db->account(account);
//	if (acc->validatePin(pin))
//		return static_cast<IAccount<typename ImplAccDB::account_t>*>(acc);
//	else
//		return nullptr;
//}
