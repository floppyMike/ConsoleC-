#pragma once

#include "Includes.h"

template<typename ImplDoc, typename ImplPat, typename ImplWait>
class Scheduler
{
	Scheduler() = default;

	Scheduler& addDoctor(ImplDoc* doc);
	Scheduler& removDoctor(ImplDoc* doc);

	Scheduler& tick();

	Scheduler& addPatient(ImplPat* pat);

private:
	std::vector<ImplDoc*> m_doctors;
	ImplWait m_wait;
};

template<typename ImplDoc, typename ImplPat, typename ImplWait>
inline Scheduler<ImplDoc, ImplPat, ImplWait>& Scheduler<ImplDoc, ImplPat, ImplWait>::addDoctor(ImplDoc* doc)
{
	m_doctors.emplace_back(doc);
	return *this;
}

template<typename ImplDoc, typename ImplPat, typename ImplWait>
inline Scheduler<ImplDoc, ImplPat, ImplWait>& Scheduler<ImplDoc, ImplPat, ImplWait>::removDoctor(ImplDoc* doc)
{
	m_doctors.erase(std::find(m_doctors.begin(), m_doctors.end()));
	return *this;
}

template<typename ImplDoc, typename ImplPat, typename ImplWait>
inline Scheduler<ImplDoc, ImplPat, ImplWait>& Scheduler<ImplDoc, ImplPat, ImplWait>::tick()
{
	
}

template<typename ImplDoc, typename ImplPat, typename ImplWait>
inline Scheduler<ImplDoc, ImplPat, ImplWait>& Scheduler<ImplDoc, ImplPat, ImplWait>::addPatient(ImplPat* pat)
{
	m_wait.joinList(pat);
	return *this;
}
