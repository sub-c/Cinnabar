#pragma once

#include "AudioConstants.h"

namespace cinna
{
	struct AudioConfiguration final
	{
		float music_volume { AudioConstants::DEFAULT_MUSIC_VOLUME };
		float sound_effect_volume { AudioConstants::DEFAULT_SOUND_EFFECT_VOLUME };
	};
}
