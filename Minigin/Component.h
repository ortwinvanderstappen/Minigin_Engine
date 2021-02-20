#pragma once
class Component
{
public:
	virtual void FixedUpdate() = 0;
protected:
	Component();
	virtual ~Component();
};
