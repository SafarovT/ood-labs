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
	Duck(const Strategy& flyBehavior,
		std::unique_ptr<IQuackBehavior>&& quackBehavior,
		Strategy danceBehavior)
		: m_quackBehavior(std::move(quackBehavior))
		, m_danceBehavior(danceBehavior)
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		SetFlyBehavior(flyBehavior);
	}

	void Quack() const
	{
		m_quackBehavior->Quack();
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

	void SetFlyBehavior(Strategy flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = flyBehavior;
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	Strategy m_flyBehavior;
	Strategy m_danceBehavior;
};

#endif
