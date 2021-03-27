#pragma once

#include "DaeAudio.h"
#include "Singleton.h"
#include <unordered_map>

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;

		std::shared_ptr<DaeAudio> LoadSound(const std::string& file);
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;

		std::unordered_map<std::string, std::shared_ptr<DaeAudio>> m_spSounds{};
	};
}
