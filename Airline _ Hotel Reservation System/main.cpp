#include <iostream>
#include <vector>
#include <algorithm>
#include <string_view>

struct ISection
{
	virtual void reserve(size_t) = 0;
	virtual void free(size_t) = 0;
};

class Reservations
{
public:
	Reservations(ISection* firstC, ISection* buisnessC, ISection* ecoC)
		: m_firstC(firstC)
		, m_buisnessC(buisnessC)
		, m_ecoC(ecoC)
	{
	}

	auto& reserveF(size_t amount) { m_firstC->reserve(amount); return *this; }
	auto& freeF(size_t amount) { m_firstC->free(amount); return *this; }

	auto& reserveB(size_t amount) { m_buisnessC->reserve(amount); return *this; }
	auto& freeB(size_t amount) { m_buisnessC->free(amount); return *this; }

	auto& reserveE(size_t amount) { m_ecoC->reserve(amount); return *this; }
	auto& freeE(size_t amount) { m_ecoC->free(amount); return *this; }

private:
	ISection* m_firstC;
	ISection* m_buisnessC;
	ISection* m_ecoC;
};

struct ILogger
{
	virtual size_t used() = 0;
	virtual size_t total() = 0;
	virtual float cost() = 0;
	virtual std::string_view name() = 0;
};

class Logger
{
public:
	Logger() = default;

	auto& set(ILogger* log) { m_log = log; return *this; }
	void print()
	{
		std::cout << m_log->name() << ": Total " << m_log->total() << ", used " 
			<< m_log->used() << ", total " << m_log->total() << ", cost " << m_log->cost() << '\n';
	}

private:
	ILogger* m_log = nullptr;
};

class Section : public ISection, public ILogger
{
	void reserve(size_t r) override 
	{
		const auto temp = m_used + r;
		if (temp > m_total)
			std::clog << "Over reserved!\n";

		m_used = temp;
	}
	void free(size_t f) override 
	{ 
		if (f > m_used)
			std::clog << "Not enought reservations to free!\n";
		else
			m_used -= f; 
	}

	size_t used() override { return m_used; }
	size_t total() override { return m_total; }
	float cost() override { return m_cost; }
	std::string_view name() override { return m_name; }

public:
	Section(size_t total, float cost, const std::string_view& name)
		: m_total(total)
		, m_cost(cost)
		, m_name(name)
	{
	}

private:
	size_t m_total;
	size_t m_used = 0;
	float m_cost;
	std::string_view m_name;
};

int main(int argc, char** argv)
{
	Section f(5, 80.f, "First Class");
	Section b(10, 40.f, "Buisness Class");
	Section e(20, 20.f, "Economy Class");

	Reservations res(&f, &b, &e);
	Logger log;

	log.set(&f).print();
	log.set(&b).print();
	log.set(&e).print();

	res.reserveB(6);
	res.reserveF(60);
	res.reserveE(1);

	log.set(&f).print();
	log.set(&b).print();
	log.set(&e).print();

	res.freeB(5);
	res.freeF(5);
	res.freeE(100);

	log.set(&f).print();
	log.set(&b).print();
	log.set(&e).print();
	

	return 0;
}