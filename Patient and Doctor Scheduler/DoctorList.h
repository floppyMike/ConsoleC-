#pragma once

#include "Includes.h"

template<typename ImplDoc>
class DoctorList
{
	using type = DoctorList<ImplDoc>;

public:
	using doc_t = ImplDoc;

	DoctorList() = default;

	DoctorList& add(ImplDoc* doc);
	template<typename Iter>
	DoctorList& add(Iter begin, Iter end);
	DoctorList& remov(ImplDoc* doc);

	template<typename ImplWaitList>
	void assign(ImplWaitList* p);
	void cure() noexcept;

private:
	std::vector<ImplDoc*> m_doctors;
};

template<typename ImplDoc>
inline auto DoctorList<ImplDoc>::add(ImplDoc* doc)
-> type&
{
	m_doctors.emplace_back(doc);
	return *this;
}

template<typename ImplDoc>
inline auto DoctorList<ImplDoc>::remov(ImplDoc* doc)
-> type&
{
	m_doctors.erase(std::find(m_doctors.begin(), m_doctors.end()));
	return *this;
}

template<typename ImplDoc>
inline void DoctorList<ImplDoc>::cure() noexcept
{
	for (auto& i : m_doctors)
		i->cure();
}

template<typename ImplDoc>
template<typename Iter>
inline auto DoctorList<ImplDoc>::add(Iter begin, Iter end)
-> type&
{
	m_doctors.insert(m_doctors.end(), begin, end);
	return *this;
}

template<typename ImplDoc>
template<typename ImplWaitList>
inline void DoctorList<ImplDoc>::assign(ImplWaitList* p)
{
	for (auto& i : m_doctors)
		i->assignPatient(p->get());
}
