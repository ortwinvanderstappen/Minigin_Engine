#pragma once
#include <Component.h>
#include <functional>
class GameArena;
class ArenaTile;

class TileMovementComponent : public minigen::Component
{
public:
	typedef std::function<void ()> CommandCallback;
	
	// Make sure down is 0 and right is 1!
	enum class MovementType
	{
		down = 0,
		right = 1,
		left,
		up
	};
	
	TileMovementComponent(GameArena* pArena, ArenaTile* pStartTile, float movementCooldown = .5f);

	void Initialize() override;
	void Update() override;
	bool Move(MovementType movement);

	void SetTile(ArenaTile* pTile);
	ArenaTile* GetTile() const;
	
	void SetParentPosition() const;

	void SubscribeToMoved(const CommandCallback& movedCallback);

private:
	void TileMoved();
	
	GameArena* m_pArena;
	ArenaTile* m_pTile;
	float m_MovementCooldown;
	float m_MovementTimer;

	std::vector<CommandCallback> m_MovedCallbacks;
};

