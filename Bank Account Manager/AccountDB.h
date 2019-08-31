#pragma once

#include "Includes.h"

template<typename T>
class AccountDB
{
public:
	using account_t = T;

	T& account(const std::string_view& str) noexcept;
	AccountDB& createAccount(const std::string_view& name);

private:
	std::map<std::string_view, T> m_accounts;
};

//template<typename T>
//inline T& AccountDB<T>::account(const std::string_view& str) const noexcept 
//{
//	return m_accounts[str];
//}
//
//template<typename T>
//inline AccountDB<T>& AccountDB<T>::createAccount(const std::string_view& name)
//{
//	m_accounts.emplace(name, T());
//	return *this;
//}
