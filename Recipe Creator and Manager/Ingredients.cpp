#include "Globals.h"

std::string_view Catagorie::toString() const
{
	switch (m_cat)
	{
	case Catagorie::DESERT:		 return "Desert";
	case Catagorie::MAIN_COURSE: return "Main Course";
	default: 					 return "ERROR";
	}
}

std::string_view Ingredient::toString() const
{
	switch (m_inge)
	{
	case CHICKEN: return "Chicken";
	case CARROT:  return "Carrot";
	case BEEF:	  return "Beef";
	case POTATO:  return "Potato";
	case WATER:	  return "Water";
	case SUGAR:	  return "Sugar";
	case SALT:	  return "Salt";
	default:	  return "ERROR";
	}
}
