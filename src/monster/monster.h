#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../utils/utils.h"
#include "../animation/animation.h"
#include "../player/player.h"
#include "../map/map.h"

namespace gm
{

	class Slime
	{
	enum MonsterAction { Attack, Still, Heal, MoveUP, MoveDOWN, MoveRIGHT, MoveLEFT };
	
	public:
		sf::RectangleShape m_Rectangle;
		sf::VertexArray m_VerticesContainer;
		Attributes m_Attributes;
		float *m_LoopTime;
		sf::Clock m_DirClock;
		short m_CurrDirection;
		sf::CircleShape m_FollowRange;
		bool m_Following;
		sf::Clock m_FollowClock;
		sf::Clock m_AttackClock;
		sf::Clock m_TakeDamageClock;
		bool m_Alive;
		sf::Clock m_RespawnClock;
		Player *m_PlayerTarget;

		Map *m_MapPtr;
		sf::VertexArray *m_SolidsVertexContainerPtr;

		//animations
		gm::Animation m_MoveAnimation;
		
	public:
		Slime();
		~Slime();

		//
		void setVertices();
		void getInput();
		void moveMonster();
		bool hasTarget();
		bool intersects(sf::VertexArray &vertexArray);
	};

	void spawnSlime(std::vector<Slime> &slimeVector);
	void killSlime(std::vector<Slime> &slimeVector);
}