#pragma once
#include "FrameWork/Component.h"

namespace wrap
{
	class  AudioComponent : public Component
	{
	public:
		AudioComponent () = default;

		void Update() override;
		void Play();
		void Stop();


		std::string m_soundName;
		bool m_playOnAwake = false;;
		bool m_loop = false;
		float m_volume = 0.5f;
		float m_pitch = 0.5f;

		// Inherited via Component
		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

	private:



	};
}