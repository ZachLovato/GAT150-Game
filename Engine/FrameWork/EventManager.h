#pragma once
#include "Event.h"
#include <map>
#include <list>

namespace wrap
{
	class EventManager
	{
	public:
		struct Observer
		{
			GameObjects* receiver;
			Event::functionPtr function;
		};

		void Initialize();
		void Shutdown();
		void Update();

		void Subscribe(const std::string& name, Event::functionPtr function, GameObjects* receiver = nullptr);
		void Unsubscribe(const std::string& name, GameObjects* receiver);

		void Notify(const Event& event);

	private:
		std::map<std::string, std::list<Observer>> m_events;

	};
}