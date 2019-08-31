#pragma once

#include "Includes.h"

class AccountMoney
{
public:
	AccountMoney() = default;

	void transform(float v) noexcept;
	float balance() const noexcept;

private:
	float m_mon = 0.f;
};
