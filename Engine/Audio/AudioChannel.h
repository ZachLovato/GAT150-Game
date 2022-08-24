#pragma once
//#include "Engine.h"
//#include "fmod.hpp"

namespace FMOD
{
	// !! forward declare FMOD Channel 
	class Channel;
}

namespace wrap
{
	class AudioChannel
	{
	public:
		AudioChannel() {}
		AudioChannel(FMOD::Channel* channel) { m_channel = channel; }// !! set m_channel 

		bool IsPlaying();
		void Stop();

		// !! create SetPitch/GetPitch (takes float, returns float) 
		// !! create SetVolume/GetVolume (takes float, returns float) 
		void SetPitch(float pitch);
		float GetPitch();
		void SetVolume(float volume);
		float GetVolume();

	private:
		FMOD::Channel* m_channel = nullptr;
	};
}