#pragma once

#include "Includes.h"

template<typename ImplPat>
class Doctor
{
	Doctor() = default;

	template<typename Iter>
	Doctor& addPatients(Iter begin, Iter end);
	Doctor& cure();

private:
	std::array<ImplPat*, 16> m_pat;
	typename std::array<ImplPat*, 16>::iterator m_spot = m_pat.begin();
};

template<typename ImplPat>
template<typename Iter>
inline Doctor<ImplPat>& Doctor<ImplPat>::addPatients(Iter begin, Iter end)
{
	static_assert(std::is_same_v<ImplPat*, typename std::iterator_traits<Iter>::value_type>, "Doctors work only on patients.");
	
	if (std::distance(begin, end) > std::distance(m_spot, m_pat.end()))
		throw std::runtime_error("Doctor unable to handle all assigned patients.");

	std::copy(begin, end, m_spot);

	return *this;
}

template<typename ImplPat>
inline Doctor<ImplPat>& Doctor<ImplPat>::cure()
{
	for (auto iter = m_pat.begin(); iter != m_spot; ++iter)
		iter->cure();
	m_spot = m_pat.begin();

	return *this;
}
