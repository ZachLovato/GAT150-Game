#include "AudioComponent.h"
#include "Engine.h"

namespace wrap
{
	void wrap::AudioComponent::Update()
	{
	
	}

	void AudioComponent::Play()
	{
		g_audio.PlayAudio(m_soundName);
	}

	void AudioComponent::Stop()
	{

	}

}

