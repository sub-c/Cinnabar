#pragma once

#include "PCH.h"

namespace Cinnabar
{
	class CinnabarException final : public exception
	{
	public:
		CinnabarException(char const* message) : exception(message)
		{
		}

		CinnabarException(string const message) : exception(message.c_str())
		{
		}
	};
}
