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
	class Screen_0 : public Screen
	{
	private:
		sf::Texture menuTexAtlas;
		sf::Sprite menuSprite;

	public:
		Player * m_PlayerPtr;

		Screen_0();
		~Screen_0();

		virtual int run(sf::RenderWindow &window);
	};
}