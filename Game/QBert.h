#pragma once
#include <string>
#include "Script.h"

class GameArena;
class ArenaTile;
class QBert : public minigen::Script
{
public:
	QBert(GameArena* pArena, int playerIndex);

	void Update() override;

	void SetTile(ArenaTile* pTile);

	void OnCollisionEnter(minigen::GameObject* const pOtherGameObject) override;
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

	GameArena* m_pArena;
	std::string m_QbertImagePath;
	int m_PlayerIndex;

	ArenaTile* m_pCurrentTile;
};

