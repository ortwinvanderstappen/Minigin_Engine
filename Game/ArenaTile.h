#pragma once
#include <RenderComponent.h>
#include <structs.h>
#include <Subject.h>

#include "GameManager.h"

class FlyingDisc;
class GameArena;
class ArenaTile : minigen::RenderComponent, public minigen::Subject
{
public:
	ArenaTile(GameArena* pArena,int index, float size, const Point2f& position, bool isNullTile, GameManager::StageSettings* pStageSettings);

	void Update() override;
	void Render() const override;

	Point2f GetCenter() const;
	Point2f GetLoweredCenter() const;
	const Point2f& GetPosition() const;

	int GetIndex() const;
	GameArena* GetArena() const;

	bool IsNullTile() const;
	bool HasDisc() const;
	
	void Activate();
	void Revert();
	bool IsComplete() const;

	void AttachFlyingDisc(const std::shared_ptr<FlyingDisc>& spDisc);
	
private:
	void DrawHex(Point2f center, float size) const;
	Point2f GetHexPoint(Point2f center, float size, int i) const;

	GameArena* m_pArena;
	int m_Index;
	float m_Size;
	Point2f m_Position;
	bool m_IsNullTile;
	GameManager::StageSettings* m_pStageSettings;
	
	int m_ColorState;
	std::shared_ptr<FlyingDisc> m_spDisc;
};

