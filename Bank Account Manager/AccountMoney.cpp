#include "Globals.h"

void AccountMoney::transform(float v) noexcept
{
	m_mon += v;
}

float AccountMoney::balance() const noexcept
{
	return m_mon;
}
