#pragma once
#include <memory>
#include <vector>

namespace minigen
{
	class Component;
	class ComponentHolder
	{
	public:
		ComponentHolder() = default;
		virtual ~ComponentHolder() = default;
		
		template <typename T>
		std::shared_ptr<T> GetComponent() const;
		
		virtual void AddComponent(std::shared_ptr<Component> spComponent);
		const std::vector<std::shared_ptr<Component>>& GetComponents() const;

	protected:
		std::vector<std::shared_ptr<Component>> m_spComponents{};
	};

	template <typename T>
	std::shared_ptr<T> ComponentHolder::GetComponent() const
	{
		for (const std::shared_ptr<Component>& component : m_spComponents)
		{
			std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);

			if (castedComponent)
				return castedComponent;
		}

		// No component found
		return nullptr;
	}
}

