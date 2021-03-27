#include "MiniginPCH.h"
#include "DaeAudio.h"

Audio* DaeAudio::GetAudio() const
{
	return m_pAudio;
}

DaeAudio::DaeAudio(Audio* pAudio) :m_pAudio(pAudio)
{}

DaeAudio::~DaeAudio()
{
	freeAudio(m_pAudio);
}
