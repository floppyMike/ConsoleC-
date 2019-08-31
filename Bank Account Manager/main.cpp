#include <iostream>
#include <string_view>
#include <map>
#include <optional>
#include <deque>
#include <string>

template<typename T>
struct crtp
{
protected:
	constexpr crtp() = default;
	constexpr auto* underlying() { return static_cast<T*>(this); }
	constexpr const auto* underlying() const { return static_cast<const T*>(this); }
};

template<typename T>
struct IAccount : public crtp<T>
{
	IAccount& deposit(float v) noexcept { this->underlying()->deposit(v); return *this; }
	IAccount& takeOut(float v) noexcept { this->underlying()->takeOut(v); return *this; }
	float balance() const noexcept { return this->underlying()->balance(); }

	IAccount& showLogs() noexcept { this->underlying()->showLogs(); return *this; }

	IAccount& setPin(size_t p) noexcept { this->underlying()->setPin(p); return *this; }

protected:
	IAccount() = default;
};

template<typename ImplMon, typename ImplLog, typename ImplSec>
class Account : public IAccount<Account<ImplMon, ImplLog, ImplSec>>
{
public:
	Account() = default;

	void deposit(float v) noexcept 
	{ 
		m_money.transform(v);
		m_logger.logDeposit(v);
	}
	void takeOut(float v) noexcept 
	{ 
		m_money.transform(-v);
		m_logger.logTakeOut(v);
	}
	auto balance() const noexcept 
	{
		return m_money.balance(); 
	}
	void showLogs() const noexcept
	{
		m_logger.printAll();
	}
	void setPin(size_t p) noexcept
	{
		m_sec.pin(p);
	}
	bool validatePin(size_t p)
	{
		return m_sec.validate(p);
	}

private:
	ImplMon m_money;
	ImplLog m_logger;
	ImplSec m_sec;
};

template<typename ImplAccDB>
class ATM
{
public:
	ATM(ImplAccDB* db)
		: m_db(db)
	{
	}

	IAccount<typename ImplAccDB::account_t>* access(const std::string_view& account, uint_fast16_t pin)
	{
		auto* acc = &m_db->account(account);
		if (acc->validatePin(pin))
			return static_cast<IAccount<typename ImplAccDB::account_t>*>(acc);
		else
			return nullptr;
	}

private:
	ImplAccDB* m_db;
};

template<typename T>
class AccountDB
{
public:
	using account_t = T;

	auto& account(const std::string_view& str) { return m_accounts[str]; }

	auto& createAccount(const std::string_view& name)
	{
		m_accounts.emplace(name, T());
		return *this;
	}

private:
	std::map<std::string_view, T> m_accounts;
};

class AccountLogger
{
public:
	AccountLogger() = default;

	void logDeposit(float v) noexcept
	{
		m_logs.emplace_back(std::to_string(v) + " deposited");
	}
	void logTakeOut(float v) noexcept
	{
		m_logs.emplace_back(std::to_string(v) + " took out");
	}
	void printAll() const noexcept
	{
		for (const auto& i : m_logs)
			std::cout << i << '\n';
	}

private:
	std::deque<std::string> m_logs;
};

class AccountMoney
{
public:
	AccountMoney() = default;

	void transform(float v) noexcept { m_mon += v; }
	auto balance() const noexcept { return m_mon; }

private:
	float m_mon = 0.f;
};

class AccountSecurity
{
public:
	AccountSecurity() = default;

	constexpr void pin(size_t p) noexcept { m_pin = p; }
	constexpr bool validate(size_t p) const noexcept { return m_pin == p; }

private:
	uint_fast16_t m_pin = 0000;
};

int main(int argc, char** argv)
{
	using UserAccount = Account<AccountMoney, AccountLogger, AccountSecurity>;

	AccountDB<UserAccount> db;
	db.createAccount("ass");

	ATM atm(&db);
	atm.access("ass", 000)->deposit(100.f)
		.takeOut(50.f)
		.deposit(25.f)
		.setPin(100);

	atm.access("ass", 100)->showLogs();

	return 0;
}