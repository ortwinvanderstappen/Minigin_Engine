#pragma once
#include <memory>
#include <vector>
#include <algorithm>

namespace minigen
{
	class Component;
	class ComponentHolder
	{
	public:
		ComponentHolder() = default;
		virtual ~ComponentHolder() = default;
		ComponentHolder(const ComponentHolder& other) = delete;
		ComponentHolder(ComponentHolder&& other) = delete;
		ComponentHolder& operator=(const ComponentHolder& other) = delete;
		ComponentHolder& operator=(ComponentHolder&& other) = delete;

		template <typename T>
		std::shared_ptr<T> GetComponent() const;

		template <typename T>
		void RemoveComponent();

		virtual void AddComponent(std::shared_ptr<Component> spComponent);
		const std::vector<std::shared_ptr<Component>>& GetComponents() const;

	protected:
		std::vector<std::shared_ptr<Component>> m_spComponents{};
	};

	template <typename T>
	std::shared_ptr<T> ComponentHolder::GetComponent() const
	{
		for (const std::shared_ptr<Component>& spComponent : m_spComponents)
		{
			std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(spComponent);

			if (castedComponent)
				return castedComponent;
		}

		// No component found
		return nullptr;
	}

	template <typename T>
	void ComponentHolder::RemoveComponent()
	{
		//std::vector<std::shared_ptr<Component>> spComponentsToRemove{};

		//for (const std::shared_ptr<Component>& spComponent : m_spComponents)
		//{
		//	std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(spComponent);

		//	if (castedComponent)
		//		return castedComponent;
		//}

		//for (const std::shared_ptr<Component>& spComponent : m_spComponents)
		//{
		//	std::shared_ptr<T> spCastedComponent = std::dynamic_pointer_cast<T>(spComponent);
		//	if (spCastedComponent)
		//	{
		//		spComponentsToRemove.push_back(spCastedComponent);
		//	}
		//}

		//m_spComponents.erase(std::remove_if(m_spComponents.begin(), m_spComponents.end(),
		//	[this](const std::shared_ptr<Component>& spComponentToDelete)
		//	{
		//		const auto findIt = std::find(m_spComponents.begin(), m_spComponents.end(), spComponentToDelete);
		//		return findIt != m_spComponents.end();
		//	}
		//), m_spComponents.end());

		m_spComponents.erase(std::remove_if(m_spComponents.begin(), m_spComponents.end(),
			[](const std::shared_ptr<Component>& spComponent)
			{
				std::shared_ptr<T> spCastedComponent = std::dynamic_pointer_cast<T>(spComponent);
				return spCastedComponent != nullptr;
			}
		), m_spComponents.end());
	}
}

