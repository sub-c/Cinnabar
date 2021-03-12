#pragma once

#include "EcsTypes.h"
#include "EcsSystem.h"

#include <cassert>
#include <memory>
#include <unordered_map>

namespace cinna
{
	class EcsSystemManager final
	{
	public:
		void entity_destroyed(EcsEntity const entity)
		{
			for (auto const& systemPair : systems_)
			{
				systemPair.second->entities.erase(entity);
			}
		}

		void entity_signature_changed(EcsEntity const entity, EcsSignature const entity_signature)
		{
			for (auto const& systemPair : systems_)
			{
				auto const& system_type_name = systemPair.first;
				auto const& system = systemPair.second;
				auto const& system_signature = signatures_[system_type_name];
				if ((entity_signature & system_signature) == system_signature)
				{
					system->entities.insert(entity);
				}
				else
				{
					system->entities.erase(entity);
				}
			}
		}

		template <typename T>
		std::shared_ptr<T> register_system()
		{
			auto type_name = typeid(T).name();

			assert(systems_.find(type_name) == systems_.end() && "Registering a system more than once.");

			auto new_system = std::make_shared<T>();
			systems_.insert({ type_name, new_system });
			return new_system;
		}

		template <typename T>
		void set_system_signature(EcsSignature signature)
		{
			auto type_name = typeid(T).name();

			assert(systems_.find(type_name) != systems_.end() && "System not registered before use.");

			signatures_.insert({ type_name, signature });
		}

	private:
		std::unordered_map<const char*, EcsSignature> signatures_ {};
		std::unordered_map<const char*, std::shared_ptr<EcsSystem>> systems_ {};
	};
}
