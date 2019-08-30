#include <iostream>
#include <string_view>
#include <map>
#include <optional>

template<typename T>
struct IAccount
{
	IAccount& transform(float v) noexcept { static_cast<T*>(this)->transform(v); return *this; }
	float balance() const { return static_cast<const T*>(this)->balance(); }
};

class Account : public IAccount<Account>
{
public:
	Account& transform(float v) noexcept { m_mon += v; return *this; }
	float balance() const { return m_mon; }

public:
	Account() = default;

private:
	float m_mon = 10.f;
};

template<typename T>
struct IAccountDB
{
	//using account_t = typename T::account_t;
	auto& account(const std::string_view& str) { return static_cast<T*>(this)->account(str); }
};

template<typename T>
class AccountDB : public IAccountDB<AccountDB<T>>
{
public:
	//using account_t = T;
	T& account(const std::string_view& str) { return m_accounts[str]; }

public:
	AccountDB& createAccount(const std::string_view& name)
	{
		m_accounts.emplace(name, T());
		return *this;
	}

private:
	std::map<std::string_view, T> m_accounts;
};

template<typename ImplAccountDB>
class ATM
{
public:
	ATM(IAccountDB<ImplAccountDB>* db)
		: m_db(db)
		//, m_trans(m_trans)
	{
	}

	auto access(const std::string_view& account, size_t pin)
	{
		return m_db->account(account);
	}

private:
	IAccountDB<ImplAccountDB>* m_db;
	//ImplTransactions m_trans;
	//ImplLogger m_log;
};

template<typename IAccountDB>
class ATMTransactions
{
public:
	ATMTransactions(IAccountDB* db)
		: m_db(db)
	{
	}

private:
	IAccountDB* m_db;
};

int main(int argc, char** argv)
{
	AccountDB<Account> db;
	db.createAccount("ass");

	ATM atm(&db);
	std::cout << atm.access("ass", 1090).balance();

	return 0;
}