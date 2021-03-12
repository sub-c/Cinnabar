#pragma once

#include "EcsTypes.h"

#include <any>
#include <unordered_map>

namespace cinna
{
	class EcsEvent final
	{
	public:
		EcsEvent() = delete;

		explicit EcsEvent(EcsEventId const type)
			: type_(type)
		{
		}

		template<typename T>
		void set_param(EcsEventId const id, T value)
		{
			data_[id] = value;
		}

		template<typename T>
		T get_param(EcsEventId const id)
		{
			return std::any_cast<T>(data_[id]);
		}

		[[nodiscard]] EcsEventId get_type() const
		{
			return type_;
		}

	private:
		EcsEventId type_ {};
		std::unordered_map<EcsEventId, std::any> data_ {};
	};
}
