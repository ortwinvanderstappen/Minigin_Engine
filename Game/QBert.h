#pragma once
#include <string>
#include "Script.h"

class ArenaTile;
class QBert : public minigen::Script
{
public:
	QBert(int playerIndex);

	void Update() override;

	void SetTile(ArenaTile* pTile);

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

	ArenaTile* m_pCurrentTile;
};

