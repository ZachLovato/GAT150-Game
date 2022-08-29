#pragma once
#include "FrameWork/Component.h"
#include "Audio/AudioChannel.h"

namespace wrap
{
	class  AudioComponent : public Component
	{
	public:
		AudioComponent () = default;
		~AudioComponent();

		CLASS_DECLARATION(AudioComponent)


		void Initialize() override;
		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Play();
		void Stop();

		AudioChannel m_channel;

		std::string sound_name;
		float volume = 1;
		float pitch = 1;
		bool play_on_start = false;
		bool loop = false;

	private:



	};
}