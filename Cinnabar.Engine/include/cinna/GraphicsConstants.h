#pragma once

#include "PCH.h"

namespace cinna::GraphicsConstants
{
	constexpr int DEFAULT_DISPLAY_BUFFER_RESOLUTION_HEIGHT { 1080 };
	constexpr int DEFAULT_DISPLAY_BUFFER_RESOLUTION_WIDTH { 1920 };
	constexpr float DEFAULT_DISPLAY_CLEAR_COLOR_B { 0.4f };
	constexpr float DEFAULT_DISPLAY_CLEAR_COLOR_G { 0.2f };
	constexpr float DEFAULT_DISPLAY_CLEAR_COLOR_R { 0.8f };
	constexpr bool DEFAULT_DISPLAY_FULLSCREEN { false };
	constexpr int DEFAULT_DISPLAY_RESOLUTION_HEIGHT { 1080 };
	constexpr int DEFAULT_DISPLAY_RESOLUTION_WIDTH { 1920 };
	constexpr bool const DEFAULT_DISPLAY_VSYNC { false };
	constexpr char const* DEFAULT_DISPLAY_WINDOW_TITLE { "Cinnabar App" };
}
