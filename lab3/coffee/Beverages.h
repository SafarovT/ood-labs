#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino() 
		:CCoffee("Cappuccino") 
	{}

	double GetCost() const override 
	{
		return 80; 
	}
};

// Двойное капуччино
class CDoubleCappuccino : public CCappuccino
{
	double GetCost() const override
	{
		return CCappuccino::GetCost() + 40;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte() 
		:CCoffee("Latte") 
	{}

	double GetCost() const override 
	{
		return 90; 
	}
};

// Двойное латте
class CDoubleLatte : public CLatte
{
	double GetCost() const override
	{
		return CLatte::GetCost() + 40;
	}
};

enum class TeaSort
{
	Assam,
	Ahmad,
	Akbar,
	Anchan,
};

// Чай
class CTea : public IBeverage
{
public:
	CTea(TeaSort sort) 
		: m_sort(sort)
	{}

	std::string GetDescription() const override final
	{
		switch (m_sort)
		{
		case TeaSort::Assam:
			return "Assam";
		case TeaSort::Ahmad:
			return "Ahmad";
		case TeaSort::Akbar:
			return "Akbar";
		case TeaSort::Anchan:
			return "Anchan";
		default:
			return "Tea";
		}
	}

	double GetCost() const override 
	{
		return 30; 
	}

private:
	TeaSort m_sort;
};

enum class MilkshakeSize
{
	Small,
	Medium,
	Large,
};

// Молочный коктейль
class CMilkshake : public IBeverage
{
public:
	CMilkshake(MilkshakeSize size)
		: m_size(size)
	{}

	std::string GetDescription() const override final
	{
		switch (m_size)
		{
		case MilkshakeSize::Small:
			return "Small milk shake";
		case MilkshakeSize::Medium:
			return "Mediun milk shake";
		case MilkshakeSize::Large:
			return "Large milk shake";
		default:
			return "Milk shake";
		}
	}

	double GetCost() const override 
	{ 
		switch (m_size)
		{
		case MilkshakeSize::Small:
			return 40;
		case MilkshakeSize::Medium:
			return 60;
		case MilkshakeSize::Large:
			return 80;
		default:
			return 60;
		}
	}

private:
	MilkshakeSize m_size;
};
