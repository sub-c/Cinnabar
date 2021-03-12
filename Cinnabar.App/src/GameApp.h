#pragma once

#include "PCH.h"

#include <cinna/CinnabarApp.h>

class GameApp final : public cinna::CinnabarApp
{
protected:
	virtual void register_components() override;
	virtual void register_systems() override;
	virtual void update() override;
};
