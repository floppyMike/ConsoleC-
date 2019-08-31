#include "Patient.h"

Patient& Patient::cure()
{
	m_cured = true;
	return *this;
}

bool Patient::cured() const noexcept
{
	return m_cured;
}
