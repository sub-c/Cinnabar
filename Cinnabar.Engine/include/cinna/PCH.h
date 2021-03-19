#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include <exception>
#include <memory>
#include <set>
#include <sstream>
#include <string_view>
#include <string>
#include <vector>

namespace cinna
{
	// Types
	using std::exception;
	using std::set;
	using std::shared_ptr;
	using std::string;
	using std::string_view;
	using std::stringstream;
	using std::unique_ptr;
	using std::vector;

	// Functions
	using std::make_shared;
	using std::make_unique;
}
