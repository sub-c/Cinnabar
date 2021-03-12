#pragma once

#include "EcsTypes.h"

#include <memory>
#include <set>

namespace cinna
{
	class EcsAgent;

	class EcsSystem
	{
	public:
		std::shared_ptr<EcsAgent> ecs_agent { nullptr };
		std::set<EcsEntity> entities {};
	};
}
