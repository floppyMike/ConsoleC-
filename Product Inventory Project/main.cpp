#include <iostream>
#include <vector>
#include <array>

class IProduct
{
public:
	virtual double price() const = 0;
	virtual size_t id() const = 0;
	virtual size_t quantity() const = 0;
};

class Product : public IProduct
{
public:
	constexpr Product(double p, size_t id, size_t q)
		: m_price(p)
		, m_id(id)
		, m_quantity(q)
	{
	}

	double price() const { return m_price; }
	size_t id() const { return m_id; }
	size_t quantity() const { return m_quantity; }

private:
	double m_price;
	size_t m_id;
	size_t m_quantity;
};

class Inventory
{
public:
	Inventory& addProduct(IProduct* p)
	{
		m_products.emplace_back(p);
		return *this;
	}

	double totalValue() const
	{
		double sum = 0.;
		for (const auto& i : m_products)
			sum += i->price();
		return sum;
	}

private:
	std::vector<IProduct*> m_products;
};

int main(int argc, char** argv)
{
	Inventory inv;

	Product pro1(1., 3, 4);
	Product pro2(10., 5, 3);

	inv.addProduct(&pro1)
		.addProduct(&pro2);

	std::cout << inv.totalValue();

	return 0;
}