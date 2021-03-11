#pragma once

#include "PCH.h"

namespace Cinnabar
{
	class CinnabarApp
	{
	public:
		void Run();

	private:
		void EnsureAllegroSystemSuccess(bool system_result, string_view const system_name);
		void SetupAllegro();
		void ShutdownAllegro();
	};
}
