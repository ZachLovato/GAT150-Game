#pragma once
#include "Event.h"
#include "GameObject.h"
#include <map>
#include <list>

namespace wrap
{
	class EventManager
	{
	public:
		struct Observer
		{
			GameObject* receiver;
			Event::functionPtr function;
		};

		void Initialize();
		void Shutdown();
		void Update();

		void Subscribe(const std::string& name, Event::functionPtr function, GameObject* receiver = nullptr);
		void Unsubscribe(const std::string& name, GameObject* receiver);

		void Notify(const Event& event);

	private:
		std::map<std::string, std::list<Observer>> m_events;

	};
}