#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

#include "../animation/animation.h"
#include "../utils/utils.h"

namespace gm
{
	struct Attributes
	{
		int strength;
		int intellect;
		int stamina;
		int vitality;
		float health;
		float max_health;
		float mana;
		float defence;
		float melee_attack;
		float magical_attack;
		float ranged_attack;
		float critical_chance;
		float movement_speed;
		float attack_speed;
	};
	
	struct Weapon
	{
		sf::RectangleShape hitBox;
		float attack_speed;
		float melee_attack;
		float ranged_attack;
		float critical_chance;
	};

	class Player
	{	
	enum PlayerAction { Attack, Still, Heal, MoveUP, MoveDOWN, MoveRIGHT, MoveLEFT };
	enum PlayerClass { Warrior, Mage, Priest, Beast };

	public:
		//rectangles
		sf::RectangleShape m_Rectangle;
		sf::RectangleShape m_FeetRect;
		sf::RectangleShape m_HitBoxRect;
		
		//vertices container
		sf::VertexArray m_VerticesContainer;
		
		//player characteristics
		PlayerClass m_Class;
		Attributes m_Attributes;

		//equipment
		Weapon m_Weapon;
		
		//duration of a game loop
		float *m_LoopTime;

		//curret direction of the player
		short m_CurrDirection;

		//bool for attacking
		bool m_Attacking;

		//timers
		sf::Clock m_AttackTimer;
		sf::Clock m_HealTimer;

		//pointers to monsters and solids for collisions
		sf::VertexArray *m_SolidsVertexContainerPtr;
		sf::VertexArray *m_MonsterVertexContainerPtr;

		//animations
		gm::Animation m_MoveUpAnimation;
		gm::Animation m_MoveLeftAnimation;
		gm::Animation m_MoveDownAnimation;
		gm::Animation m_MoveRightAnimation;
		gm::Animation m_AttackUpAnimation;
		gm::Animation m_AttackLeftAnimation;
		gm::Animation m_AttackDownAnimation;
		gm::Animation m_AttackRightAnimation;

	public:
		Player();
		~Player();
		
		//
		PlayerAction getInput();
		void attack();
		void heal();
		void loadInfo(const char* fileName);
		void exportInfo(const char* fileName);
		void movePlayer(PlayerAction action);
		void setVertices();
		void setRects();
		bool intersects(sf::VertexArray &vertexArray);
	};
}