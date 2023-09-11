#ifndef LAB01_SIMUDUCK_IDANCEBEHAVIOR_H
#define LAB01_SIMUDUCK_IDANCEBEHAVIOR_H

class IDanceBehavior
{
public:
	virtual void Dance() const = 0;
	virtual ~IDanceBehavior() {};
};

#endif