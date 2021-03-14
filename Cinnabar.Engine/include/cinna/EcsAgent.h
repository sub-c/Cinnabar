#pragma once

#include "EcsComponentManager.h"
#include "EcsEntityManager.h"
#include "EcsEventManager.h"
#include "EcsSystem.h"
#include "EcsSystemManager.h"
#include "EcsTypes.h"

#include <functional>
#include <memory>

namespace cinna
{
	class EcsAgent final : public std::enable_shared_from_this<EcsAgent>
	{
	public:
		EcsAgent()
		{
			component_manager_ = std::make_unique<EcsComponentManager>();
			entity_manager_ = std::make_unique<EcsEntityManager>();
			event_manager_ = std::make_unique<EcsEventManager>();
			singleton_entity_ = entity_manager_->create_entity();
			system_manager_ = std::make_unique<EcsSystemManager>();
		}

		template <typename T>
		void add_component(T component)
		{
			add_component<T>(singleton_entity_, component);
		}

		template <typename T>
		void add_component(EcsEntity const entity, T component)
		{
			component_manager_->add_component<T>(entity, component);

			auto signature = entity_manager_->get_entity_signature(entity);
			signature.set(component_manager_->get_component_type<T>(), true);
			entity_manager_->set_entity_signature(entity, signature);

			system_manager_->entity_signature_changed(entity, signature);
		}

		void add_event_listener(EcsEventId const event_id, std::function<void(EcsEvent&)> const& listener) const
		{
			event_manager_->add_listener(event_id, listener);
		}

		EcsEntity create_entity() const
		{
			return entity_manager_->create_entity();
		}

		void destroy_entity(EcsEntity const entity) const
		{
			entity_manager_->destroy_entity(entity);
			component_manager_->entity_destroyed(entity);
			system_manager_->entity_destroyed(entity);
		}

		template <typename T>
		T& get_component()
		{
			return component_manager_->get_component<T>(singleton_entity_);
		}

		template <typename T>
		T& get_component(EcsEntity const entity)
		{
			return component_manager_->get_component<T>(entity);
		}

		template <typename T>
		EcsComponentType get_component_type()
		{
			return component_manager_->get_component_type<T>();
		}

		template <typename T>
		bool is_component_registered()
		{
			return component_manager_->is_component_registered<T>();
		}

		template <typename T>
		void register_component()
		{
			component_manager_->register_component<T>();
		}

		template <typename T>
		std::shared_ptr<T> register_system()
		{
			auto new_system = system_manager_->register_system<T>();

			auto ecs_system = static_cast<std::shared_ptr<EcsSystem>>(new_system);
			ecs_system->ecs_agent = shared_from_this();

			return new_system;
		}

		template <typename T>
		void remove_component(EcsEntity const entity)
		{
			component_manager_->remove_component<T>(entity);

			auto signature = entity_manager_->get_entity_signature(entity);
			signature.set(component_manager_->get_component_type<T>(), false);
			entity_manager_->set_entity_signature(entity, signature);

			system_manager_->entity_signature_changed(entity, signature);
		}

		void send_event(EcsEvent& event) const
		{
			event_manager_->send_event(event);
		}

		void send_event(EcsEventId const event_id) const
		{
			event_manager_->send_event(event_id);
		}

		template <typename T>
		void set_system_signature(EcsSignature const signature)
		{
			system_manager_->set_system_signature<T>(signature);
		}

	private:
		std::unique_ptr<EcsComponentManager> component_manager_;
		std::unique_ptr<EcsEntityManager> entity_manager_;
		std::unique_ptr<EcsEventManager> event_manager_;
		EcsEntity singleton_entity_;
		std::unique_ptr<EcsSystemManager> system_manager_;
	};
}
