#pragma once
#include <string>
#include "Script.h"

class ArenaHexScript;
class QBertScript : public minigen::Script
{
public:
	QBertScript(int playerIndex);

	void Update() override;

	void SetTile(ArenaHexScript* pTile);

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
	void ProcessInput();
	
	std::string m_QbertImagePath;
	int m_PlayerIndex;

	ArenaHexScript* m_pCurrentTile;
};

