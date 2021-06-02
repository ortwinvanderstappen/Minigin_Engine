#pragma once
#include <string>

#include "Script.h"

class QBertScript : public minigen::Script
{
public:
	QBertScript(int playerIndex);

	void Update() override;

protected:
	void Initialize() override;
private:
	enum class InputId
	{
		up,
		right,
		down,
		left
	};
	
	void InitializeSprite();
	void InitializeControls();
	
	std::string m_QbertImagePath;
	int m_PlayerIndex;

	int m_TileIndex;
};

