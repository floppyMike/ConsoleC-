#pragma once

#include "Includes.h"

class Ingredient
{
public:
	enum _
	{
		CHICKEN,
		CARROT,
		BEEF,
		POTATO,
		WATER,
		SUGAR,
		SALT
	};

	constexpr Ingredient(_ init) noexcept
		: m_inge(init)
	{
	}

	std::string_view toString() const;

	constexpr bool operator==(const Ingredient& x) const noexcept
	{
		return x.m_inge == m_inge;
	}

private:
	_ m_inge;
};

class Catagorie
{
public:
	enum _
	{
		DESERT,
		MAIN_COURSE
	};

	explicit constexpr Catagorie(_ init) noexcept
		: m_cat(init)
	{
	}

	std::string_view toString() const;

	constexpr bool operator==(const Catagorie& x) const noexcept
	{
		return x.m_cat == m_cat;
	}

	constexpr const _ get() const noexcept { return m_cat; }

private:
	_ m_cat;
};