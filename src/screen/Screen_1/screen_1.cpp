#include "screen_1.h"

namespace gm
{
	Screen_1::Screen_1(sf::RenderWindow &window)
	{
		//window
		m_Window = &window;
		//view
		mainView.setViewport(sf::FloatRect(0, 0, 1, 1));
		mainView.setSize(m_Window->getSize().x, m_Window->getSize().y);
		mainView.setCenter(mainView.getSize().x / 2, mainView.getSize().y / 2);
		m_Window->setView(mainView);


		//load texture loading screen
		loadingScreenTex.loadFromFile("textures/loading_screen.png");

		//display the loading screen
		scale.x = float(m_Window->getSize().x) / loadingScreenTex.getSize().x;
		scale.y = float(m_Window->getSize().y) / loadingScreenTex.getSize().y;
		loadingSprite.setTexture(loadingScreenTex);
		loadingSprite.setScale(scale);
		m_Window->draw(loadingSprite);
		m_Window->display();

		//set the render area
		renderArea.setSize(sf::Vector2f(m_Window->getSize()));

		//variables for measuring loop time
		frameTime = 0.008f;

		//aux for fps
		fpsCounter = 0;

		//load texture atlas for background
		bgTexAtlas.loadFromFile("textures/bg_texture_atlas.png");

		//load texture atlas for solids
		solidsTexAtlas.loadFromFile("textures/solids_texture_atlas.png");
		
		//map
		tileMap.m_BG_Layer.m_TexAtlas = &bgTexAtlas;
		tileMap.m_BG_Layer.loadLayer("map_files/bg_layer.txt");

		tileMap.m_Solids_Layer.loadLayer("map_files/solids_layer.txt");
		tileMap.m_Solids_Layer.m_TexAtlas = &solidsTexAtlas;


		//set the player
		player.m_LoopTime = &frameTime;
		player.m_SolidsVertexContainerPtr = &tileMap.m_Solids_Layer.m_VerticesContainer;
		playerTextures.loadFromFile("textures/knight_longsword.png");
	
		//slime
		gm::Slime slime;
		slime.m_SolidsVertexContainerPtr = &tileMap.m_Solids_Layer.m_VerticesContainer;
		slimeTextures.loadFromFile("textures/slime_textures.png");
		slime.m_LoopTime = &frameTime;
		slime.m_PlayerTarget = &player;
		slime.m_MapPtr = &tileMap;
		slime.m_Alive = false;
		slime.m_Rectangle.setPosition(sf::Vector2f(-100, -100));

		slimeNr = 10000;
		int i;

		for (i = 0; i < slimeNr; i++)
		{
			slimeArray.push_back(slime);
		}

		for (i = 0; i < slimeNr; i++)
		{
			slimeArray[i].m_MoveAnimation.setVertexArray(&slimeArray[i].m_VerticesContainer);
		}

		currSlimeVerticesContainer.setPrimitiveType(sf::Quads);

		//player hp
		font1.loadFromFile("fonts/font1.ttf");
		player_hp.setFont(font1);
		player_hp.setCharacterSize(14);
		player_hp.setFillColor(sf::Color::Magenta);
	}

	Screen_1::~Screen_1()
	{

	}

	int Screen_1::run(sf::RenderWindow &window)
	{
		
		bool running = true;
		int i;
		loopTimer.restart();

		for (i = 0; i < slimeNr; i++)
		{
			slimeArray[i].m_TakeDamageClock.restart();
			slimeArray[i].m_AttackClock.restart();
			slimeArray[i].m_DirClock.restart();
			slimeArray[i].m_FollowClock.restart();
		}

		///////////
		HexagonMap hexagonMap;
		hexagonMap.setCenter(sf::Vector2f(300, 300));
		hexagonMap.buildFit(6, 100);
		hexagonMap.setCenter(sf::Vector2f(100, 100));
		while (running)
		{
			sf::Event event;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					return 0;
				}

				if (event.type == sf::Event::KeyReleased)
				{
					if (event.text.unicode == sf::Keyboard::Escape)
					{
						running = false;
						return 0;
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

			//get input for player and test for collisions with solids
			player.movePlayer(player.getInput());

			//kill slimes that have 0 health
			killSlime(slimeArray);
			
			//spawn slimes
			spawnSlime(slimeArray);

			//get input for slimes and test for collisions with solids and the player
			currSlimeVerticesContainer.clear();
			for (i = 0; i < slimeNr; i++)
			{
				if (renderArea.getGlobalBounds().intersects(slimeArray[i].m_Rectangle.getGlobalBounds()))
				{
					slimeArray[i].getInput();
					slimeArray[i].moveMonster();

					currSlimeVerticesContainer.append(slimeArray[i].m_VerticesContainer[0]);
					currSlimeVerticesContainer.append(slimeArray[i].m_VerticesContainer[1]);
					currSlimeVerticesContainer.append(slimeArray[i].m_VerticesContainer[2]);
					currSlimeVerticesContainer.append(slimeArray[i].m_VerticesContainer[3]);
				}
			}

			//set the main view
			if (player.m_Rectangle.getPosition().x + player.m_Rectangle.getSize().x / 2 > mainView.getSize().x / 2 && player.m_Rectangle.getPosition().x + player.m_Rectangle.getSize().x / 2 < tileMap.m_BG_Layer.m_Size.x * tileMap.m_BG_Layer.m_TileSize.x - mainView.getSize().x / 2)
			{
				mainView.setCenter(player.m_Rectangle.getPosition().x + player.m_Rectangle.getSize().x / 2, mainView.getCenter().y);
				window.setView(mainView);
			}

			if (player.m_Rectangle.getPosition().y + player.m_Rectangle.getSize().y / 2 > mainView.getSize().y / 2 && player.m_Rectangle.getPosition().y + player.m_Rectangle.getSize().y / 2 < tileMap.m_BG_Layer.m_Size.y * tileMap.m_BG_Layer.m_TileSize.y - mainView.getSize().y / 2)
			{
				mainView.setCenter(mainView.getCenter().x, player.m_Rectangle.getPosition().y + player.m_Rectangle.getSize().y / 2);
				window.setView(mainView);
			}

			renderArea.setPosition(sf::Vector2f(mainView.getCenter() - sf::Vector2f(mainView.getSize().x / 2, mainView.getSize().y / 2)));

			player_hp.setPosition(renderArea.getPosition()+sf::Vector2f(10, 10));
			player_hp.setString(std::to_string(int(player.m_Attributes.health)));

			if (player.m_Attributes.health <= 0)
			{
				player.loadInfo("player_info/player_info.txt");
				player.m_Attributes.health = player.m_Attributes.max_health;
			}

			//load chunks
			tileMap.m_BG_Layer.loadChunk(renderArea);
			tileMap.m_Solids_Layer.loadChunk(renderArea);

			//calculate the fps
			fpsCounter++;
			if (fpsCounter >= int(1 / frameTime))
			{
				std::cout << "FPS:" << int(1 / frameTime) << std::endl;
				fpsCounter = 0;
			}


			window.clear();

			//draw background
			window.draw(tileMap.m_BG_Layer.m_VerticesContainer, tileMap.m_BG_Layer.m_TexAtlas);

			//draw solids
			window.draw(tileMap.m_Solids_Layer.m_VerticesContainer, tileMap.m_Solids_Layer.m_TexAtlas);

			//draw aux
			//window.draw(player.m_Rectangle);
			//window.draw(player.m_Weapon.hitBox);
			//window.draw(player.m_HitBoxRect);
			//window.draw(player.m_FeetRect);

			window.draw(hexagonMap);

			//draw slimes
			window.draw(currSlimeVerticesContainer, &slimeTextures);

			//draw player
			window.draw(player.m_VerticesContainer, &playerTextures);

			window.draw(player_hp);

			window.display();

			//measure the duration of a loop
			frameTime = loopTimer.getElapsedTime().asSeconds();
			loopTimer.restart();
		}
	}
}