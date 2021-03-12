#pragma once

#include "EcsTypes.h"
#include "EcsEvent.h"

#include <functional>
#include <list>
#include <unordered_map>

namespace cinna
{
	class EcsEventManager final
	{
	public:
		void add_listener(EcsEventId const eventId, std::function<void(EcsEvent&)> const& listener)
		{
			listeners_[eventId].push_back(listener);
		}

		void send_event(EcsEvent& event)
		{
			auto const type = event.get_type();

			for (auto const& listener : listeners_[type])
			{
				listener(event);
			}
		}

		void send_event(EcsEventId eventId)
		{
			EcsEvent event(eventId);
			for (auto const& listener : listeners_[eventId])
			{
				listener(event);
			}
		}

	private:
		std::unordered_map<EcsEventId, std::list<std::function<void(EcsEvent&)>>> listeners_ {};
	};
}
