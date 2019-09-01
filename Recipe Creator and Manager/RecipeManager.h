#pragma once

#include "Includes.h"
#include "Recipe.h"

template<typename ImplRecipe, typename ImplCat, typename ImplIngre>
class RecipeManager
{
public:
	RecipeManager(std::initializer_list<ImplRecipe*>&& l)
		: m_recipes(std::make_move_iterator(l.begin()), std::make_move_iterator(l.end()))
	{
	}

	void sortByCatagorie(const ImplCat& cat);
	void sortByIngredient(const ImplIngre& ingre);

	void printRecipes() const;

private:
	std::vector<ImplRecipe*> m_recipes;
};

template<typename ImplRecipe, typename ImplCat, typename ImplIngre>
inline void RecipeManager<ImplRecipe, ImplCat, ImplIngre>::sortByCatagorie(const ImplCat& cat)
{
	std::partition(m_recipes.begin(), m_recipes.end(), [&cat](ImplRecipe* x)
		{
			return x->catagorie().get() == cat.get();
		});
}

template<typename ImplRecipe, typename ImplCat, typename ImplIngre>
inline void RecipeManager<ImplRecipe, ImplCat, ImplIngre>::sortByIngredient(const ImplIngre& ingre)
{
	std::partition(m_recipes.begin(), m_recipes.end(), [&ingre](ImplRecipe* x)
		{
			return x->hasIngredient(ingre);
		});
}

template<typename ImplRecipe, typename ImplCat, typename ImplIngre>
inline void RecipeManager<ImplRecipe, ImplCat, ImplIngre>::printRecipes() const
{
	for (auto* i : m_recipes)
	{
		i->log();
		std::cout.write("\n\n", 2);
	}
}

