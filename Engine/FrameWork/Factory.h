#pragma once
#include "SimpleTon.h"
#include <memory>
#include <map>
#include <string>

namespace wrap
{
	class GameObject;

	class CreateBase
	{
	public:
		virtual std::unique_ptr<GameObject> Create() = 0;
	};

	template <typename T>
	class Creator : public CreateBase
	{
		std::unique_ptr<GameObject> Create() override
		{
			return std::make_unique<T>();
		}
	};

	class Factory : public Singleton<Factory>
	{
	public:
		template <typename T>
		void Register(const std::string& key);

		template <typename T>
		std::unique_ptr<T> Create(const std::string& key);

	private:
		std::map<std::string, std::unique_ptr <CreateBase>> m_registry;

	};

	template<typename T>
	inline void Factory::Register(const std::string& key)
	{
		m_registry[key] = std::make_unique<Creator<T>>();
	}

	template<typename T>
	inline std::unique_ptr<T> Factory::Create(const std::string& key)
	{
		auto iter = m_registry.find(key);

		if (iter != m_registry.end())
		{
			return std::unique_ptr<T>(dynamic_cast<T*>(iter->second->Create().release()));
		}

		return std::unique_ptr<T>();
	}

}