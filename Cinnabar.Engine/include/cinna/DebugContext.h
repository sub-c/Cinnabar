#pragma once

#include "PCH.h"

namespace cinna
{
	struct DebugContext
	{
		bool enabled { false };
		ALLEGRO_FONT* font { nullptr };
		shared_ptr<vector<string>> text_lines { make_shared<vector<string>>(std::initializer_list<string>{ "", "", "", "", "", "" }) };
	};
}
