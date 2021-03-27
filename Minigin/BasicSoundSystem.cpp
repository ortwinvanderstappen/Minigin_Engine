#include "MiniginPCH.h"
#include "BasicSoundSystem.h"

#include <audio.h>
#include <thread>

#include "ResourceManager.h"

void BasicSoundSystem::ProcessQueue()
{
	while (m_IsRunning)
	{
		std::unique_lock<std::mutex> threadLock{ m_Mutex };
		if (!m_SoundQueue.empty())
		{
			std::cout << "Sound queue size: " << m_SoundQueue.size() << "\n";
			const std::pair<std::string, int>& pair = m_SoundQueue.front();

			Audio* pSound = dae::ResourceManager::GetInstance().LoadSound(pair.first)->GetAudio();

			if (pSound != nullptr)
			{
				const int volume = std::clamp(pair.second, 0, m_MaxVolume);
				playSoundFromMemory(pSound, volume);
			}

			m_SoundQueue.pop();
		} else
		{
			m_PlayCondition.wait(threadLock);
		}
	}
}

void BasicSoundSystem::PlaySound(const std::string& soundName, int volume)
{
	std::lock_guard<std::mutex> threadLock{ m_Mutex };
	if (!m_IsMuted)
	{
		m_SoundQueue.push(std::make_pair(soundName, volume));
		m_PlayCondition.notify_one();
	}
}

void BasicSoundSystem::PlayMusic(const std::string&, const int)
{}

void BasicSoundSystem::Mute()
{
	m_IsMuted = true;
}

void BasicSoundSystem::Unmute()
{
	m_IsMuted = false;
}

void BasicSoundSystem::Stop()
{
	m_IsRunning = false;
	m_PlayCondition.notify_one();
}
