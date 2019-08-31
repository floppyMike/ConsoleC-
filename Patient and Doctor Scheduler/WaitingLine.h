#pragma once

#include "Includes.h"

template<typename ImplPat>
class WaitingLine
{
	WaitingLine() = default;

	WaitingLine& joinList(ImplPat* pat);
	std::initializer_list<ImplPat*> get(size_t amount);
	size_t size() const noexcept;

private:
	std::deque<ImplPat*> m_line;
};

template<typename ImplPat>
inline WaitingLine<ImplPat>& WaitingLine<ImplPat>::joinList(ImplPat* pat)
{
	m_line.emplace_back(pat);
	return *this;
}

template<typename ImplPat>
inline std::initializer_list<ImplPat*> WaitingLine<ImplPat>::get(size_t amount)
{
	std::initializer_list<ImplPat*> list = { m_line.begin(), m_line.begin() + amount };
	m_line.erase(m_line.begin(), m_line.begin() + amount);

	return list;
}

template<typename ImplPat>
inline size_t WaitingLine<ImplPat>::size() const noexcept
{
	return m_line.size();
}
