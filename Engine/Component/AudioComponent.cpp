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

	bool AudioComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool AudioComponent::Read(const rapidjson::Value& value)
	{
		return false;
	}

}

