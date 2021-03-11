#include "PCH.h"

#include "CinnabarApp.h"
#include "CinnabarException.h"

namespace Cinnabar
{
	void CinnabarApp::Run()
	{
		SetupAllegro();

		ShutdownAllegro();
	}

	// Private functions //////////////////////////////////////////////////////////////////////////

	void CinnabarApp::EnsureAllegroSystemSuccess(bool system_result, string_view const system_name)
	{
		if (!system_result)
		{
			stringstream ss;
			ss << "Could not initialize Allegro system: " << system_name;
			throw CinnabarException(ss.str());
		}
	}

	void CinnabarApp::SetupAllegro()
	{
		EnsureAllegroSystemSuccess(al_init(), "Core");
	}

	void CinnabarApp::ShutdownAllegro()
	{
		al_uninstall_system();
	}
}
