#pragma once

#include "EcsComponentCache.h"
#include "EcsTypes.h"

#include <any>
#include <cassert>
#include <memory>
#include <unordered_map>

namespace cinna
{
	class EcsComponentManager final
	{
	public:
		template <typename T>
		void add_component(EcsEntity entity, T component)
		{
			auto componentCache = get_component_cache<T>();
			componentCache->insert_component(entity, component);
		}

		void entity_destroyed(EcsEntity const entity)
		{
			for (auto const& component_cache_pair : component_caches_)
			{
				component_cache_pair.second->entity_destroyed(entity);
			}
		}

		template <typename T>
		T& get_component(EcsEntity entity)
		{
			auto component_cache = get_component_cache<T>();
			return component_cache->get_component(entity);
		}

		template <typename T>
		EcsComponentType get_component_type()
		{
			auto const type_name = typeid(T).name();

			assert(component_types_.find(type_name) != component_types_.end() && "Component not registered before use.");

			return component_types_[type_name];
		}

		template <typename T>
		void register_component()
		{
			auto const type_name = typeid(T).name();

			assert(component_types_.find(type_name) == component_types_.end() && "Registering the component more than once.");

			component_types_.insert({ type_name, next_component_type_ });
			component_caches_.insert({ type_name, std::make_shared<EcsComponentCache<T>>() });
			++next_component_type_;
		}

		template <typename T>
		void remove_component(EcsEntity entity)
		{
			auto component_cache = get_component_cache<T>();
			component_cache->remove_component(entity);
		}

	private:
		std::unordered_map<const char*, std::shared_ptr<IEcsComponentCache>> component_caches_ {};
		std::unordered_map<const char*, EcsComponentType> component_types_ {};
		EcsComponentType next_component_type_ {};

		template <typename T>
		std::shared_ptr<EcsComponentCache<T>> get_component_cache()
		{
			auto const type_name = typeid(T).name();

			assert(component_types_.find(type_name) != component_types_.end() && "Component not registered before use.");

			return std::static_pointer_cast<EcsComponentCache<T>>(component_caches_[type_name]);
		}
	};
}
