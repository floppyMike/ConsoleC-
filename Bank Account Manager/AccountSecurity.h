#pragma once

#include "Includes.h"

class AccountSecurity
{
public:
	AccountSecurity() = default;

	void pin(size_t p) noexcept;
	bool validate(size_t p) const noexcept;

private:
	uint_fast16_t m_pin = 0000;
};
