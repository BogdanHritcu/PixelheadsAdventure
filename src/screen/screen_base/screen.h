#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../screen_base/screen.h"
#include "../../utils/utils.h"
#include "../../monster/monster.h"
#include "../../player/player.h"
#include "../../map/map.h"
#include "../../animation/animation.h"

namespace gm
{
	class Screen
	{
	public:
		Screen();
		~Screen();

		//
		virtual int run(sf::RenderWindow &window) = 0;
	};
}