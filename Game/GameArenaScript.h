#pragma once
#pragma warning (push)
#pragma warning(disable: 4201)
#include "RenderComponent.h"
#pragma warning(pop)

#include "ArenaHexScript.h"
#include "structs.h"

class GameArenaScript : public minigen::RenderComponent
{
public:
	GameArenaScript(int baseWidth);
	~GameArenaScript() override;

	void Initialize();
	void InitializeArena();
	
	void Update() override;
	void Render() const override;

	const Color3i& GetPrimaryColor() const;
	const Color3i& GetSecondaryColor() const;
private:
	int CalculateArenaHexCount () const;

	std::vector<ArenaHexScript> m_ArenaHexex{};
	
	int m_BaseWidth = -1;

	Color3i m_PrimaryColor{};
	Color3i m_SecondaryColor{};
};
