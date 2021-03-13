#pragma once

#include "PCH.h"

#include "EcsTypes.h"

namespace cinna
{
	class EcsAgent;

	class EcsSystem
	{
	public:
		shared_ptr<EcsAgent> ecs_agent { nullptr };
		set<EcsEntity> entities {};
	};
}
