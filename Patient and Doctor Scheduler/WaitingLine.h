#pragma once

#include "Includes.h"

template<typename ImplPat>
class WaitingLine
{
	using type = WaitingLine<ImplPat>;

public:
	using patient_t = ImplPat;

	WaitingLine() = default;

	WaitingLine& joinList(ImplPat* pat);
	template<typename Iter>
	WaitingLine& joinList(Iter begin, Iter end);
	ImplPat* get();

private:
	std::deque<ImplPat*> m_line;
};

template<typename ImplPat>
inline auto WaitingLine<ImplPat>::joinList(ImplPat* pat)
-> type&
{
	m_line.emplace_back(pat);
	return *this;
}

template<typename ImplPat>
inline ImplPat* WaitingLine<ImplPat>::get()
{
	if (!m_line.empty())
	{
		auto* pat = m_line.front();
		m_line.pop_front();

		return pat;
	}
	else
		return nullptr;
}

template<typename ImplPat>
template<typename Iter>
inline auto WaitingLine<ImplPat>::joinList(Iter begin, Iter end)
-> type&
{
	static_assert(std::is_same_v<ImplPat*, std::iterator_traits<Iter>::value_type>, "Doctors operate on patients.");

	m_line.insert(m_line.end(), begin, end);
	return *this;
}
