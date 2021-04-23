#include "MiniginPCH.h"
#include "OpenGameSceneCommand.h"

#include "SceneManager.h"

bool OpenGameSceneCommand::Execute()
{
	minigen::SceneManager::GetInstance().SetActiveScene("GameScene");

	return true;
}
