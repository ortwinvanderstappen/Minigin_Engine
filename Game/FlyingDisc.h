#pragma once
#include <Script.h>
#include <string>

struct Point2f;

class FlyingDisc : public minigen::Script
{
public:
	FlyingDisc();

	void Initialize() override;
	void SetPosition(const Point2f& pos) const;
private:
	void InitializeSprite();

	std::string m_FlyingDiscImagePath;
	bool m_IsUsed;
};

