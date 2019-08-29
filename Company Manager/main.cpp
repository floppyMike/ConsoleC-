#include <iostream>
#include <set>
#include <memory>
#include <thread>
#include <atomic>

class IEmployee
{
public:
	virtual IEmployee& raise(float) noexcept = 0;
	virtual IEmployee& pay() noexcept = 0;
};

class Company
{
public:
	Company& hire(IEmployee* e)
	{
		m_people.emplace(e);
		return *this;
	}

	Company& fire(IEmployee* e)
	{
		m_people.erase(e);
		return *this;
	}

	Company& raise(IEmployee* e, float amount)
	{
		e->raise(amount);
		return *this;
	}

	Company& pay(IEmployee* e)
	{
		e->pay();
		return *this;
	}

private:
	std::set<IEmployee*> m_people;
};

template<size_t startingGain>
class Employee : public IEmployee
{
	Employee& raise(float mon) noexcept override { m_gain += mon; return *this; }
	Employee& pay() noexcept override { m_money += m_gain; return *this; }

public:
	Employee()
	{
	}

private:
	float m_gain = startingGain;
	float m_money = 0.f;
};

using HourlyEmployee = Employee<1>;
using SalariedEmployee = Employee<2080>;
using Manager = Employee<10400>;
using Executive = Employee<104000>;

int main(int argc, char** argv)
{
	HourlyEmployee he;
	SalariedEmployee se;
	Manager m;
	Executive e;

	Company c;
	c.hire(&e);
	c.hire(&m);
	c.hire(&se);
	c.hire(&he);

	c.pay(&he);
	c.raise(&se, 100.f);
	c.pay(&se);
	c.fire(&m);


	return 0;
}