#include "AudioSystem.h"
#include "Core/Logger.h"
#include <fmod.hpp>
#include <algorithm>

namespace wrap
{
	void AudioSystem::Initialize()
	{
		FMOD::System_Create(&m_fmodSystem);

		void* extradriverdata = nullptr;
		m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	}

	void AudioSystem::Shutdown()
	{
		// !! use range based for-loop to iterate through m_sounds, call release on each element 
		// !! call clear() on m_sounds to remove all elements 
		// !! call close() on the fmod system 
		// !! call release() on the fmod system 


		for (auto sound : m_sounds) 
		{
			sound.second->release();
		}
			m_sounds.clear();
			m_fmodSystem->close();
			m_fmodSystem->release();
	}

	void AudioSystem::Update()
	{
		// !! call update() on the fmod system 
		m_fmodSystem->update();
	}

	void AudioSystem::AddAudio(const std::string& name, const std::string& filename)
	{
		if (m_sounds.find(name) == m_sounds.end())// !! use find() on m_sounds to see if element exists, only set sound if it does not 
		{
			FMOD::Sound* sound = nullptr;
			m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);

			if (sound == nullptr)
			{
				LOG("Error Creating Sound %s", filename.c_str());
			}
			m_sounds[name] = sound;
		}
	}

	void AudioSystem::PlayAudio(const std::string& name)
	{
		auto iter = m_sounds.find(name);// !! use find() on m_sounds and return the iterator 
		
		if (iter == m_sounds.end())
		{
			LOG("Error Could Not Find Sound %s", name.c_str());
		}
		
		if (iter != m_sounds.end()) // !! if iterator is not m_sounds.end() 
			{

				FMOD::Sound* sound = iter->second;
				sound->setMode(FMOD_LOOP_OFF);

				FMOD::Channel* channel;
				m_fmodSystem->playSound(sound, 0, false, &channel);
			}

	}
	void AudioSystem::PlayMusic(const std::string& name)
	{
		auto iter = m_sounds.find(name);// !! use find() on m_sounds and return the iterator 
		
		if (iter == m_sounds.end())
		{
			LOG("Error Could Not Find Sound %s", name.c_str());
		}

		if (iter != m_sounds.end()) // !! if iterator is not m_sounds.end() 
		{

			FMOD::Sound* sound = iter->second;
			sound->setMode(FMOD_LOOP_NORMAL);

			FMOD::Channel* channel;
			m_fmodSystem->playSound(sound, 0, false, &channel);
		}
	}
}