#include <iostream>
#include <string_view>
#include <map>
#include <optional>

template<typename T>
struct IAccount
{
	auto& deposit(float v) noexcept { static_cast<T*>(this)->deposit(v); return *this; }
	auto& takeOut(float v) noexcept { static_cast<T*>(this)->takeOut(v); return *this; }
	auto balance() const noexcept { return static_cast<const T*>(this)->balance(); }

protected:
	IAccount() = default;
};

class Account : public IAccount<Account>
{
	auto& deposit(float v) noexcept { m_mon += v; return *this; }
	auto& takeOut(float v) noexcept { m_mon -= v; return *this; }
	auto balance() const { return m_mon; }

public:
	Account() = default;
	friend struct IAccount<Account>;

private:
	float m_mon = 10.f;
};

template<typename T>
struct IAccountDB
{
	auto& account(const std::string_view& str) { return static_cast<T*>(this)->account(str); }

protected:
	IAccountDB() = default;
};

template<typename T>
class AccountDB : public IAccountDB<AccountDB<T>>
{
	auto account(const std::string_view& str) -> IAccount<T>& { return m_accounts[str]; }

public:
	auto& createAccount(const std::string_view& name)
	{
		m_accounts.emplace(name, T());
		return *this;
	}

	friend struct IAccountDB<AccountDB<T>>;

private:
	std::map<std::string_view, T> m_accounts;
};

template</*typename ImplTrans, typename ImplLog, */typename ImplAccDB>
class ATM
{
public:
	ATM(IAccountDB<ImplAccDB>* db)
		: m_db(db)
		//, m_trans(db)
	{
	}

	auto& access(const std::string_view& account)
	{
		return m_db->account(account);
	}

private:
	IAccountDB<ImplAccDB>* m_db;
	//ImplTrans m_trans;
	//ImplLog m_log;
};

//template<typename IAccountDB>
//class ATMTransactions
//{
//public:
//	ATMTransactions(IAccountDB* db)
//		: m_db(db)
//	{
//	}
//
//private:
//	IAccountDB* m_db;
//};
//
//template<typename IAccountDB>
//class ATMLogger
//{
//public:
//	ATMTransactions(IAccountDB* db)
//		: m_db(db)
//	{
//	}
//
//private:
//	IAccountDB* m_db;
//};

int main(int argc, char** argv)
{
	AccountDB<Account> db;
	db.createAccount("ass");

	ATM atm(&db);
	std::cout << atm.access("ass").balance();

	return 0;
}