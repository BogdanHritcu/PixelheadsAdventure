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
	class Screen_1 : public Screen
	{
	public:
		sf::RenderWindow *m_Window;
	
	public:
		//view
		sf::View mainView;

		//loading screen
		sf::Texture loadingScreenTex;
		sf::Vector2f scale;
		sf::Sprite loadingSprite;

		//render area
		sf::RectangleShape renderArea;

		//frame time
		sf::Clock loopTimer;
		float frameTime;

		//fps
		int fpsCounter;
		
		//background texture atlas
		sf::Texture bgTexAtlas;

		//solids texture atlas
		sf::Texture solidsTexAtlas;

		//map
		Map tileMap;



		//player
		gm::Player player;
		sf::Texture playerTextures;

		//slime
		std::vector<gm::Slime> slimeArray;
		sf::Texture slimeTextures;
		sf::VertexArray currSlimeVerticesContainer;
		int slimeNr;

		//texts
		sf::Text player_hp;
		sf::Font font1;

	public:
		Screen_1(sf::RenderWindow &window);
		~Screen_1();

		virtual int run(sf::RenderWindow &window);
	};
}