#include "Patient.h"

Patient& Patient::cure()
{
	m_cured = true;
	return *this;
}
