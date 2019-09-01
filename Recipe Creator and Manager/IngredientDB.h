#pragma once

#include "Includes.h"

template<typename ImplIngre>
class IngredientDB
{
public:
	template<typename... T>
	IngredientDB(T&&... arg)
		: m_ingre(std::forward<T>(arg)...)
	{
	}

	auto begin() const { return m_ingre.begin(); }
	auto end() const { return m_ingre.end(); }

	bool hasIngredient(const ImplIngre& ingre) const;

private:
	std::vector<ImplIngre> m_ingre;
};

template<typename ImplIngre>
inline bool IngredientDB<ImplIngre>::hasIngredient(const ImplIngre& ingre) const
{
	return std::find(m_ingre.begin(), m_ingre.end(), ingre) != m_ingre.end();
}
