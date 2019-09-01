#include "Globals.h"

int main()
{
	using C = Catagorie;
	using I = Ingredient;

	using R = Recipe<C, I, IngredientDB<I>, RecipeLogger>;

	R r1("R1", C(C::MAIN_COURSE), { I::BEEF, I::CARROT });
	R r2("R2", C(C::DESERT), { I::CARROT, I::POTATO });
	R r3("R3", C(C::MAIN_COURSE), { I::BEEF, I::SALT });
	R r4("R4", C(C::DESERT), { I::WATER, I::SUGAR });
	R r5("R5", C(C::MAIN_COURSE), { I::BEEF, I::CARROT });

	RecipeManager<R, C, I> man({ &r1, &r2, &r3, &r4, &r5 });
	man.printRecipes();

	man.sortByCatagorie(C{ C::MAIN_COURSE });
	man.printRecipes();

	man.sortByIngredient(I{ I::BEEF });
	man.printRecipes();

	return 0;
}