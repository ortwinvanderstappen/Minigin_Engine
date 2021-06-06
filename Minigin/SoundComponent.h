#pragma once
#include "Component.h"

namespace minigen {
	class SoundComponent : public Component
	{
	public:
		SoundComponent(const std::string& soundPath);

		void PlaySoundEffect() const;
		void Update() override{};
	private:
		std::string m_SoundPath;
	};
}

