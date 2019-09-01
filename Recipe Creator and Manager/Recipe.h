#pragma once

#include "Ingredients.h"
#include "Includes.h"

template<typename ImplCat, typename ImplIngre, typename ImplDB, typename ImplLogger>
class Recipe
{
public:
	Recipe(std::string&& name, const ImplCat& cat, std::initializer_list<ImplIngre>&& inge)
		: m_name(std::move(name))
		, m_cat(cat)
		, m_inge(std::make_move_iterator(inge.begin()), std::make_move_iterator(inge.end()))
	{
	}

	const ImplCat& catagorie() const noexcept;
	bool hasIngredient(const ImplIngre& ingre) const;

	void log() const;

private:
	std::string m_name;

	ImplCat m_cat;
	ImplDB m_inge;

	ImplLogger m_log;
};

template<typename ImplCat, typename ImplIngre, typename ImplDB, typename ImplLogger>
inline const ImplCat& Recipe<ImplCat, ImplIngre, ImplDB, ImplLogger>::catagorie() const noexcept
{
	return m_cat;
}

template<typename ImplCat, typename ImplIngre, typename ImplDB, typename ImplLogger>
inline bool Recipe<ImplCat, ImplIngre, ImplDB, ImplLogger>::hasIngredient(const ImplIngre& ingre) const
{
	return m_inge.hasIngredient(ingre);
}

template<typename ImplCat, typename ImplIngre, typename ImplDB, typename ImplLogger>
inline void Recipe<ImplCat, ImplIngre, ImplDB, ImplLogger>::log() const
{
	m_log.log(m_name, m_cat, m_inge.begin(), m_inge.end());
}
