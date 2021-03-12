#include "PCH.h"

#include "CinnabarApp.h"
#include "CinnabarException.h"
#include "GraphicsContext.h"

namespace cinna
{
	CinnabarApp::CinnabarApp()
	{

	}

	CinnabarApp::~CinnabarApp()
	{

	}

	void CinnabarApp::run()
	{
		setup_allegro();
		register_engine_components();
		register_engine_systems();

		shutdown_allegro();
	}

	// Private functions //////////////////////////////////////////////////////////////////////////

	void CinnabarApp::ensure_allegro_system_success(bool system_result, string_view const system_name)
	{
		if (!system_result)
		{
			stringstream ss;
			ss << "Could not initialize Allegro system: " << system_name;
			throw CinnabarException(ss.str());
		}
	}

	void CinnabarApp::register_engine_components()
	{

	}

	void CinnabarApp::register_engine_systems()
	{

	}

	void CinnabarApp::setup_allegro()
	{
		ensure_allegro_system_success(al_init(), "Core");
	}

	void CinnabarApp::shutdown_allegro()
	{
		al_uninstall_system();
	}
}
