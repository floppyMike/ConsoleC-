#include "Globals.h"

void AccountSecurity::pin(size_t p) noexcept
{
	m_pin = p;
}

bool AccountSecurity::validate(size_t p) const noexcept
{
	return m_pin == p;
}
