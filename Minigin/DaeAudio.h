#pragma once
#include <audio.h>

/**
* Simple RAII wrapper for an Audio
*/
class DaeAudio
{
public:
	Audio* GetAudio() const;
	explicit DaeAudio(Audio* pAudio);
	~DaeAudio();

	DaeAudio(const DaeAudio&) = delete;
	DaeAudio(DaeAudio&&) = delete;
	DaeAudio& operator= (const DaeAudio&) = delete;
	DaeAudio& operator= (const DaeAudio&&) = delete;
private:
	Audio* m_pAudio;
};

