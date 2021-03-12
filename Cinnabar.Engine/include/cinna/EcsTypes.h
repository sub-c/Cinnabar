#pragma once

#include <bitset>
#include <cstdint>

namespace cinna
{
	using EcsEntity = std::uint32_t;
	const EcsEntity MAX_ENTITIES = 5000;

	using EcsEventId = std::uint32_t;
	using EcsParamId = std::uint32_t;

	using EcsComponentType = std::uint8_t;
	const EcsComponentType MAX_COMPONENTS = 100;

	using EcsSignature = std::bitset<MAX_COMPONENTS>;
}
