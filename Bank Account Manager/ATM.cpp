#include "Globals.h"

template<typename ImplAccDB>
IAccount<typename ImplAccDB::account_t>* ATM<ImplAccDB>::access(const std::string_view& account, uint_fast16_t pin)
{
	auto* acc = &m_db->account(account);
	if (acc->validatePin(pin))
		return static_cast<IAccount<typename ImplAccDB::account_t>*>(acc);
	else
		return nullptr;
}

template class ATM<AccountDB<UserAccount>>;