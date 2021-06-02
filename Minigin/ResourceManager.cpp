#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void minigen::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<minigen::Texture2D> minigen::ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_DataPath + file;
	SDL_Surface* pSurface = IMG_Load(fullPath.c_str());
	
	if(pSurface == nullptr)
	{
		std::cerr << "ResourceManager:: Failed to find texture with path: " << fullPath << "\n";
		return nullptr;
	}
	
	return std::make_shared<Texture2D>(pSurface);
}

std::shared_ptr<minigen::Font> minigen::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_DataPath + file, size);
}

std::shared_ptr<DaeAudio> minigen::ResourceManager::LoadSound(const std::string& file)
{
	// Create the sound if it doesn't exist yet
	if(m_spSounds.find(file) == m_spSounds.end())
	{
		Audio* pAudio = createAudio(file.c_str(), 0, 0);
		std::shared_ptr<DaeAudio> spDaeAudio = std::make_shared<DaeAudio>(pAudio);
		m_spSounds.insert(std::make_pair(file, spDaeAudio));
	}
	
	return m_spSounds[file];
}
