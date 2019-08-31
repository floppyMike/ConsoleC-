#pragma once

#include "Includes.h"

template<typename ImplDocList, typename ImplPatList>
class Scheduler
{
	using type = Scheduler<ImplDocList, ImplPatList>;

	using patient_t = typename ImplPatList::patient_t;
	using doctor_t = typename ImplDocList::doc_t;

public:
	Scheduler() = default;

	Scheduler& addPatient(patient_t* p);
	template<typename Iter>
	Scheduler& addPatient(Iter begin, Iter end);
	Scheduler& addDoctor(doctor_t* d);
	Scheduler& removDoctor(doctor_t* d);

	Scheduler& tick();

private:
	ImplDocList m_doctors;
	ImplPatList m_wait;
};

template<typename ImplDocList, typename ImplPatList>
inline auto Scheduler<ImplDocList, ImplPatList>::addPatient(patient_t* p)
-> type&
{
	m_wait.joinList(p);
	return *this;
}

template<typename ImplDocList, typename ImplPatList>
inline auto Scheduler<ImplDocList, ImplPatList>::addDoctor(doctor_t* d)
-> type&
{
	m_doctors.add(d);
	return *this;
}

template<typename ImplDocList, typename ImplPatList>
inline auto Scheduler<ImplDocList, ImplPatList>::removDoctor(doctor_t* d)
-> type&
{
	m_doctors.remov(d);
	return *this;
}

template<typename ImplDocList, typename ImplPatList>
inline auto Scheduler<ImplDocList, ImplPatList>::tick()
-> type&
{
	m_doctors.cure();
	m_doctors.assign(&m_wait);

	return *this;
}

template<typename ImplDocList, typename ImplPatList>
template<typename Iter>
inline auto Scheduler<ImplDocList, ImplPatList>::addPatient(Iter begin, Iter end)
-> type&
{
	m_wait.joinList(begin, end);
	return *this;
}
