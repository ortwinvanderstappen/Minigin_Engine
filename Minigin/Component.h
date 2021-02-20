#pragma once
class Component
{
public:
	virtual void Update() = 0;
protected:
	Component();
	virtual ~Component();
};
