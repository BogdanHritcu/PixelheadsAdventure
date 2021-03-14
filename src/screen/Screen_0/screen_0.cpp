#include "screen_0.h"

namespace gm
{
	Screen_0::Screen_0()
	{
		menuTexAtlas.loadFromFile("textures/menu.png");
		menuSprite.setTexture(menuTexAtlas);
		menuSprite.setPosition(0, 0);
	}

	Screen_0::~Screen_0()
	{

	}

	int Screen_0::run(sf::RenderWindow &window)
	{
		sf::Vector2f scale;
		scale.x = float(window.getSize().x) / menuTexAtlas.getSize().x;
		scale.y = float(window.getSize().y) / menuTexAtlas.getSize().y;
		menuSprite.setScale(scale);

		menuSprite.setPosition(window.getView().getCenter().x - window.getSize().x / 2, window.getView().getCenter().y - window.getSize().y / 2);
		bool running = true;

		while (running)
		{
			sf::Event event;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_PlayerPtr->exportInfo("player_info/player_info.txt");
					return -1;
				}

				if (event.type == sf::Event::KeyReleased)
				{
					if (event.text.unicode == sf::Keyboard::Escape)
					{
						m_PlayerPtr->exportInfo("player_info/player_info.txt");
						return -1;
					}
				}

				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Return)
					{
						return 1;
					}
				}

				if (event.type == sf::Event::Resized)
				{
					window.setSize(sf::Vector2u(event.size.width, event.size.height));
					//mainView.setSize(event.size.width,event.size.height);
					//window.setView(mainView);
					//renderArea.setSize(sf::Vector2f(window.getSize()));
				}

			}

			window.clear();

			window.draw(menuSprite);

			window.display();
		}
	}
}