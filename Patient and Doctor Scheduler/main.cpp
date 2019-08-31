#include "Globals.h"

int main()
{
	std::array<Doctor<Patient>, 2> docs;
	std::array<Patient, 100> patients;

	Scheduler<DoctorList<Doctor<Patient>>, WaitingLine<Patient>> s;

	for (auto& i : docs)
		s.addDoctor(&i);

	for (auto& i : patients)
		s.addPatient(&i);

	size_t min = 0;

	while (true)
	{
		s.tick();
		std::this_thread::sleep_for(std::chrono::seconds(1));

		std::clog << (min += 30) << " minutes have passed.\n";
		for (size_t i = 0; i < patients.size(); ++i)
			std::clog << "Patient " << i << " is healed: " << patients[i].cured() << '\n';
		std::clog << "\n\n";
	}

	return 0;
}