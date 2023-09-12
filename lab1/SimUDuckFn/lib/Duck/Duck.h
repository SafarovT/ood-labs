#ifndef DUCK_H
#define DUCK_H

#include "Quack/IQuakBehavior.h"
#include "Strategy/StrategyFn.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

class Duck
{
public:
	Duck(FlyStrategy&& flyBehavior,
		QuackStrategy&& quackBehavior,
		DanceStrategy&& danceBehavior)
		: m_quackBehavior(std::move(quackBehavior))
		, m_danceBehavior(std::move(danceBehavior))
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		SetFlyBehavior(std::move(flyBehavior));
	}

	void Quack() const
	{
		m_quackBehavior();
	}

	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
		m_flyBehavior();
	}

	virtual void Dance()
	{
		m_danceBehavior();
	}

	void SetFlyBehavior(FlyStrategy&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = std::move(flyBehavior);
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	QuackStrategy m_quackBehavior;
	FlyStrategy m_flyBehavior;
	DanceStrategy m_danceBehavior;
};

#endif
