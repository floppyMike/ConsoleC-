#pragma once

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