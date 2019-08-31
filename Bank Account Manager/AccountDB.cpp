#include "Globals.h"

template<typename T>
T& AccountDB<T>::account(const std::string_view& str) noexcept
{
	return m_accounts.at(str);
}

template<typename T>
AccountDB<T>& AccountDB<T>::createAccount(const std::string_view& name)
{
	m_accounts.emplace(name, T());
	return *this;
}

template class AccountDB<UserAccount>;