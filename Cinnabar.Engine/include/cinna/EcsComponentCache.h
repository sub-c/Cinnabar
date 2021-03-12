#pragma once

#include "EcsTypes.h"

#include <array>
#include <cassert>
#include <unordered_map>

namespace cinna
{
	class IEcsComponentCache
	{
	public:
		virtual ~IEcsComponentCache() = default;
		virtual void entity_destroyed(EcsEntity entity) = 0;
	};

	template <typename T>
	class EcsComponentCache final : public IEcsComponentCache
	{
	public:
		void entity_destroyed(EcsEntity const entity) override
		{
			if (entity_to_index_map_.find(entity) != entity_to_index_map_.end())
			{
				remove_component(entity);
			}
		}

		T& get_component(EcsEntity const entity)
		{
			assert(entity_to_index_map_.find(entity) != entity_to_index_map_.end() && "Attempting to retrieve a component the entity does not have.");

			return _cache[entity_to_index_map_[entity]];
		}

		void insert_component(EcsEntity const entity, T component)
		{
			assert(entity_to_index_map_.find(entity) == entity_to_index_map_.end() && "Attempting to add a component to the entity more than once.");

			auto new_index = size_of_entries_;
			entity_to_index_map_[entity] = new_index;
			index_to_entity_map_[new_index] = entity;
			_cache[new_index] = component;
			++size_of_entries_;
		}

		void remove_component(EcsEntity const entity)
		{
			assert(entity_to_index_map_.find(entity) != entity_to_index_map_.end() && "Attempting to remove a component the entity does not have.");

			auto index_of_removed_entity = entity_to_index_map_[entity];
			auto index_of_last_element = static_cast<size_t>(size_of_entries_ - 1);
			_cache[index_of_removed_entity] = _cache[index_of_last_element];

			auto const entity_of_last_element = index_to_entity_map_[index_of_last_element];
			entity_to_index_map_[entity_of_last_element] = index_of_removed_entity;
			index_to_entity_map_[index_of_removed_entity] = entity_of_last_element;

			entity_to_index_map_.erase(entity);
			index_to_entity_map_.erase(index_of_last_element);
			--size_of_entries_;
		}

	private:
		std::array<T, MAX_ENTITIES> _cache {};
		std::unordered_map<EcsEntity, size_t> entity_to_index_map_ {};
		std::unordered_map<size_t, EcsEntity> index_to_entity_map_ {};
		size_t size_of_entries_ {};
	};
}
