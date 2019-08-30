#include <iostream>
#include <string_view>
#include <map>
#include <optional>
#include <deque>
#include <string>

template<typename T>
struct crtp
{
	constexpr crtp() = default;
	constexpr auto* underlying() { return static_cast<T*>(this); }
	constexpr const auto* underlying() const { return static_cast<const T*>(this); }
};

template<typename T>
struct IAccountLog : public crtp<T>
{
	IAccountLog& logDeposit(float v) noexcept { this->underlying()->logDeposit(v); return *this; }
	IAccountLog& logTakeOut(float v) noexcept { this->underlying()->logTakeOut(v); return *this; }

protected:
	IAccountLog() = default;
};

template<typename T>
struct IAccount : public crtp<T>
{
	IAccount& deposit(float v) noexcept { this->underlying()->deposit(v); return *this; }
	IAccount& takeOut(float v) noexcept { this->underlying()->takeOut(v); return *this; }
	float balance() const noexcept { return this->underlying()->balance(); }

protected:
	IAccount() = default;
};

template<typename ImplLog>
class Account : public IAccount<Account<ImplLog>>
{
	void deposit(float v) noexcept 
	{ 
		m_mon += v;
		m_logger.first.get().logDeposit(v);
	}
	void takeOut(float v) noexcept 
	{ 
		m_mon -= v; 
		m_logger.first.get().logTakeOut(v);
	}
	auto balance() const noexcept 
	{
		return m_mon; 
	}

public:
	Account() = default;

	friend struct IAccount<Account>;

private:
	float m_mon = 0.f;

	std::pair<std::reference_wrapper<IAccountLog<ImplLog>>, ImplLog> m_logger 
		= std::pair<std::reference_wrapper<IAccountLog<ImplLog>>, ImplLog>(m_logger.second, ImplLog());
};

template<typename T>
struct IAccountDB : public crtp<T>
{
	auto& account(const std::string_view& str) { return this->underlying()->account(str); }

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

template<typename ImplAccDB>
class ATM
{
public:
	ATM(IAccountDB<ImplAccDB>* db)
		: m_db(db)
	{
	}

	auto& access(const std::string_view& account)
	{
		return m_db->account(account);
	}

private:
	IAccountDB<ImplAccDB>* m_db;
};

class AccountLogger : public IAccountLog<AccountLogger>
{
	void logDeposit(float v) noexcept 
	{ 
		m_logs.emplace_back(std::to_string(v) + " deposited");
	}
	void logTakeOut(float v) noexcept 
	{ 
		m_logs.emplace_back(std::to_string(v) + " took out");
	}

public:
	AccountLogger() {}
	friend struct IAccountLog<AccountLogger>;

private:
	std::deque<std::string> m_logs;
};

int main(int argc, char** argv)
{
	AccountDB<Account<AccountLogger>> db;
	db.createAccount("ass");

	ATM atm(&db);
	std::cout << atm.access("ass").deposit(10.f).balance();

	return 0;
}