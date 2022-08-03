#pragma once
#include <chrono>

namespace wrap
{
	class Time
	{
	private:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = clock::duration;
		using clock_rep = clock::rep;


	public:
		Time() : 
			m_startTimePoint{ clock::now() }, 
			m_frameTimePoint{ clock::now() } 
		{}
		~Time() {};

		void Tick();
		inline void Reset() { m_startTimePoint = clock::now(); }

	public:
		float deltaTime = 0.0f;
		float time = 0.0f;

	private:
		clock::time_point m_startTimePoint; // time point st start of application
		clock::time_point m_frameTimePoint; // tome point at start of frame


	};

}