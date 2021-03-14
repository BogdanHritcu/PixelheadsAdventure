#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "src/utils/utils.h"
#include "src/monster/monster.h"
#include "src/player/player.h"
#include "src/map/map.h"
#include "src/screen/screens.h"

int main()
{
	//seed the rand function
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(800, 600), "Pixelhead's adventure", sf::Style::Default);
	sf::Image icon;
	icon.loadFromFile("textures/window_icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	window.setActive(true);

	std::vector<gm::Screen*>screenArray;

	gm::Screen_1 screen_1(window);
	gm::Screen_0 screen_0;
	screen_0.m_PlayerPtr = &screen_1.player;
	screenArray.push_back(&screen_0);

	screenArray.push_back(&screen_1);

	int screen = 0;
	
	while (screen >= 0)
	{
		screen = screenArray[screen]->run(window);
	}

	return 0;
}
