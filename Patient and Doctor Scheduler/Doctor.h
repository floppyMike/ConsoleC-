#pragma once

#include "Includes.h"

template<typename ImplPat>
class Doctor
{
	using type = Doctor<ImplPat>;

public:
	Doctor() = default;

	Doctor& assignPatient(ImplPat* p);
	Doctor& cure();
	bool available() const noexcept;

private:
	ImplPat* m_pat = nullptr;
};

template<typename ImplPat>
inline auto Doctor<ImplPat>::assignPatient(ImplPat* p)
-> type&
{
	m_pat = p;
	return *this;
}

template<typename ImplPat>
inline auto Doctor<ImplPat>::cure()
-> type&
{
	if (m_pat != nullptr)
	{
		m_pat->cure();
		m_pat = nullptr;
	}
	return *this;
}

template<typename ImplPat>
inline bool Doctor<ImplPat>::available() const noexcept
{
	return m_pat == nullptr;
}
