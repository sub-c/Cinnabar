#pragma once

#include "PCH.h"

#include <cinna/CinnabarApp.h>

class GameApp final : public cinna::CinnabarApp
{
protected:
	void register_components() override;
	void register_systems() override;
	void update() override;
};
