#pragma once

#include "Includes.h"
#include "Ingredients.h"

class RecipeLogger
{
public:
	RecipeLogger() = default;
	
	template<typename Cat, typename Iter>
	void log(const std::string_view& name, const Cat& cat, Iter begin, Iter end) const;
};

template<typename Cat, typename Iter>
inline void RecipeLogger::log(const std::string_view& name, const Cat& cat, Iter begin, Iter end) const
{
	std::cout << "Recipe list for " << name << " with the catagorie " << cat.toString() << ":\n";
	for (; begin != end; ++begin)
		std::cout << begin->toString() << '\n';
}
