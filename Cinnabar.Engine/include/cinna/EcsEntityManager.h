#pragma once

#include "EcsTypes.h"

#include <array>
#include <cassert>
#include <queue>

namespace cinna
{
	class EcsEntityManager final
	{
	public:
		EcsEntityManager()
		{
			for (EcsEntity entity = 0; entity < MAX_ENTITIES; ++entity)
			{
				available_entities_.push(entity);
			}
		}

		EcsEntity create_entity()
		{
			assert(living_entity_count_ < MAX_ENTITIES && "Maximum entities exceeded.");

			auto const entity = available_entities_.front();
			available_entities_.pop();
			++living_entity_count_;
			return entity;
		}

		void destroy_entity(EcsEntity const entity)
		{
			assert(entity < MAX_ENTITIES && "Entity is out of range.");

			signatures_[entity].reset();
			available_entities_.push(entity);
			--living_entity_count_;
		}

		EcsSignature get_entity_signature(EcsEntity const entity)
		{
			assert(entity < MAX_ENTITIES && "Entity is out of range.");

			return signatures_[entity];
		}

		void set_entity_signature(EcsEntity const entity, EcsSignature const signature)
		{
			assert(entity < MAX_ENTITIES && "Entity is out of range.");

			signatures_[entity] = signature;
		}

	private:
		std::queue<EcsEntity> available_entities_ {};
		uint32_t living_entity_count_ {};
		std::array<EcsSignature, MAX_ENTITIES> signatures_ {};
	};
}
