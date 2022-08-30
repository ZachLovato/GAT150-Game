#include "EventManager.h"

namespace wrap
{
	void wrap::EventManager::Initialize()
	{
		//
	}

	void wrap::EventManager::Shutdown()
	{
		//
	}

	void wrap::EventManager::Update()
	{
		//
	}

	void wrap::EventManager::Subscribe(const std::string& name, Event::functionPtr function, GameObjects* receiver)
	{
		Observer observer;
		observer.receiver = receiver;
		observer.function = function;

		m_events[name].push_back(observer);
	}

	void wrap::EventManager::Unsubscribe(const std::string& name, GameObjects* receiver)
	{
		//
	}

	void wrap::EventManager::Notify(const Event& event)
	{
		auto observers = m_events[event.name];
		for (auto& observer : observers)
		{
			if (event.receiver == nullptr || event.receiver == observer.receiver)
			{
				observer.function(event);
			}
		}
	}
}

