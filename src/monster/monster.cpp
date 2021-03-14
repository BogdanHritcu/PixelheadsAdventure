#include "monster.h"

namespace gm
{
	Slime::Slime()
	{
		m_Rectangle.setPosition(sf::Vector2f(450, 450));
		m_Rectangle.setSize(sf::Vector2f(32, 32));
		m_Rectangle.setFillColor(sf::Color::Blue);
		m_FollowRange.setPointCount(10);
		m_FollowRange.setRadius(100);
		m_FollowRange.setOrigin(sf::Vector2f(m_FollowRange.getRadius(), m_FollowRange.getRadius()));
		m_Following = false;
		m_Alive = true;

		m_CurrDirection = 0;

		m_VerticesContainer.setPrimitiveType(sf::PrimitiveType::Quads);
		m_VerticesContainer.resize(4);

		m_MoveAnimation.setFrameRate(10);
		m_MoveAnimation.setMaxFrames(3);

		int i;
		for (i = 0; i < 3; i++)
		{
			m_MoveAnimation.appendFrame(sf::IntRect(0, i * 32, 32, 32));
		}

		m_Attributes.strength = 4;
		m_Attributes.intellect = 1;
		m_Attributes.stamina = 4;
		m_Attributes.vitality = 3;
		m_Attributes.health = (20 + m_Attributes.vitality) * m_Attributes.vitality;
		m_Attributes.mana = (10 + m_Attributes.intellect) * m_Attributes.intellect;
		m_Attributes.defence = 8;
		m_Attributes.melee_attack = (1 + m_Attributes.strength) * 2;
		m_Attributes.magical_attack = 1 + m_Attributes.intellect;
		m_Attributes.ranged_attack = (1 + m_Attributes.strength) * 1.5;
		m_Attributes.critical_chance = 0;
		m_Attributes.movement_speed = 30;
		m_Attributes.attack_speed = 0.5f;
	}

	Slime::~Slime()
	{
		
	}

	void Slime::setVertices()
	{
		//first point
		m_VerticesContainer[0].position.x = m_Rectangle.getPosition().x;
		m_VerticesContainer[0].position.y = m_Rectangle.getPosition().y;

		//second point
		m_VerticesContainer[1].position.x = m_Rectangle.getPosition().x + m_Rectangle.getSize().x;
		m_VerticesContainer[1].position.y = m_Rectangle.getPosition().y;

		//third point
		m_VerticesContainer[2].position.x = m_Rectangle.getPosition().x + m_Rectangle.getSize().x;
		m_VerticesContainer[2].position.y = m_Rectangle.getPosition().y + m_Rectangle.getSize().y;

		//fourth point
		m_VerticesContainer[3].position.x = m_Rectangle.getPosition().x;
		m_VerticesContainer[3].position.y = m_Rectangle.getPosition().y + m_Rectangle.getSize().y;
	}

	bool Slime::hasTarget()
	{
		if (m_PlayerTarget->m_Rectangle.getGlobalBounds().intersects(m_FollowRange.getGlobalBounds()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Slime::getInput()
	{
		if (m_DirClock.getElapsedTime().asSeconds() >= 1)
		{
			m_CurrDirection = randBetween(0, 10);
			m_DirClock.restart();
		}

		int i;
		sf::VertexArray box;
		box.setPrimitiveType(sf::PrimitiveType::Quads);
		box.resize(4);

		if (m_CurrDirection == 1)
		{
			for (i = 0; i < m_SolidsVertexContainerPtr->getVertexCount(); i += 4)
			{
				box[0].position = (*m_SolidsVertexContainerPtr)[i].position;
				box[1].position = (*m_SolidsVertexContainerPtr)[i + 1].position;
				box[2].position = (*m_SolidsVertexContainerPtr)[i + 2].position;
				box[3].position = (*m_SolidsVertexContainerPtr)[i + 3].position;

				if (this->intersects(box))
				{
					m_CurrDirection = -1;
					break;
				}
			}
		}
		else
			if (m_CurrDirection == 0)
			{
				for (i = 0; i < m_SolidsVertexContainerPtr->getVertexCount(); i += 4)
				{
					box[0].position = (*m_SolidsVertexContainerPtr)[i].position;
					box[1].position = (*m_SolidsVertexContainerPtr)[i + 1].position;
					box[2].position = (*m_SolidsVertexContainerPtr)[i + 2].position;
					box[3].position = (*m_SolidsVertexContainerPtr)[i + 3].position;

					if (this->intersects(box))
					{
						m_CurrDirection = -1;
						break;
					}
				}
			}
			else
				if (m_CurrDirection == 3)
				{
					for (i = 0; i < m_SolidsVertexContainerPtr->getVertexCount(); i += 4)
					{
						box[0].position = (*m_SolidsVertexContainerPtr)[i].position;
						box[1].position = (*m_SolidsVertexContainerPtr)[i + 1].position;
						box[2].position = (*m_SolidsVertexContainerPtr)[i + 2].position;
						box[3].position = (*m_SolidsVertexContainerPtr)[i + 3].position;

						if (this->intersects(box))
						{
							m_CurrDirection = -1;
							break;
						}
					}
				}
				else
					if (m_CurrDirection == 2)
					{
						for (i = 0; i < m_SolidsVertexContainerPtr->getVertexCount(); i += 4)
						{
							box[0].position = (*m_SolidsVertexContainerPtr)[i].position;
							box[1].position = (*m_SolidsVertexContainerPtr)[i + 1].position;
							box[2].position = (*m_SolidsVertexContainerPtr)[i + 2].position;
							box[3].position = (*m_SolidsVertexContainerPtr)[i + 3].position;

							if (this->intersects(box))
							{
								m_CurrDirection = -1;
								break;
							}
						}
					}
	}

	void Slime::moveMonster()
	{
		if (m_FollowClock.getElapsedTime().asSeconds() >= 3)
		{
			m_Following = hasTarget();
		}

		if (m_Following == false)
		{
			getInput();

			//0-DOWN
			//1-UP
			//2-LEFT
			//3-UP

			switch (m_CurrDirection)
			{
			case -1:
				m_Rectangle.move(0, 0);
				m_MoveAnimation.update();
				setVertices();
				break;

			case 0:
				m_Rectangle.move(0, m_Attributes.movement_speed * (*m_LoopTime));
				m_MoveAnimation.update();
				setVertices();
				break;

			case 1:
				m_Rectangle.move(0, -m_Attributes.movement_speed * (*m_LoopTime));
				m_MoveAnimation.update();
				setVertices();
				break;

			case 2:
				m_Rectangle.move(-m_Attributes.movement_speed * (*m_LoopTime), 0);
				m_MoveAnimation.update();
				setVertices();
				break;

			case 3:
				m_Rectangle.move(m_Attributes.movement_speed * (*m_LoopTime), 0);
				m_MoveAnimation.update();
				setVertices();
				break;

			default:
				break;
			}
		}
		else
		{
			sf::Vector2f player_pos;
			sf::Vector2f monster_pos(m_Rectangle.getPosition().x + m_Rectangle.getSize().x / 2, m_Rectangle.getPosition().y + m_Rectangle.getSize().y / 2);

			switch (m_PlayerTarget->m_CurrDirection)
			{
			case 0:
				player_pos = sf::Vector2f(m_PlayerTarget->m_HitBoxRect.getPosition().x + m_PlayerTarget->m_HitBoxRect.getSize().x / 2, m_PlayerTarget->m_HitBoxRect.getPosition().y + m_PlayerTarget->m_HitBoxRect.getSize().y);
				break;

			case 1:
				player_pos = sf::Vector2f(m_PlayerTarget->m_HitBoxRect.getPosition().x + m_PlayerTarget->m_HitBoxRect.getSize().x, m_PlayerTarget->m_HitBoxRect.getPosition().y + m_PlayerTarget->m_HitBoxRect.getSize().y / 2);
				break;

			case 2:
				player_pos = sf::Vector2f(m_PlayerTarget->m_HitBoxRect.getPosition().x + m_PlayerTarget->m_HitBoxRect.getSize().x / 2, m_PlayerTarget->m_HitBoxRect.getPosition().y);
				break;

			case 3:
				player_pos = sf::Vector2f(m_PlayerTarget->m_HitBoxRect.getPosition().x, m_PlayerTarget->m_HitBoxRect.getPosition().y + m_PlayerTarget->m_HitBoxRect.getSize().y / 2);
				break;

			default:
				break;
			}

			sf::Vector2f direction = sf::Vector2f(player_pos - monster_pos);


			float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
			if (direction.x == 0 || direction.y == 0)
			{
				distance += 0.2;
			}

			sf::Vector2f offset = sf::Vector2f(direction.x / distance * m_Attributes.movement_speed * (*m_LoopTime), direction.y / distance * m_Attributes.movement_speed * (*m_LoopTime));

			int i;
			sf::VertexArray box;
			box.setPrimitiveType(sf::PrimitiveType::Quads);
			box.resize(4);

			for (i = 0; i < m_SolidsVertexContainerPtr->getVertexCount(); i += 4)
			{
				box[0].position = (*m_SolidsVertexContainerPtr)[i].position;
				box[1].position = (*m_SolidsVertexContainerPtr)[i + 1].position;
				box[2].position = (*m_SolidsVertexContainerPtr)[i + 2].position;
				box[3].position = (*m_SolidsVertexContainerPtr)[i + 3].position;

				if (this->intersects(box))
				{
					m_Following = false;
					m_FollowClock.restart();
					return;
					break;
				}
			}

			//check for collision with player
			if (m_Rectangle.getGlobalBounds().intersects(m_PlayerTarget->m_HitBoxRect.getGlobalBounds()))
			{
				if (m_AttackClock.getElapsedTime().asSeconds() >= 1)
				{
					m_PlayerTarget->m_Attributes.health -= m_Attributes.melee_attack;
					//std::cout << m_PlayerTarget->m_Attributes.health << std::endl;
					m_AttackClock.restart();
				}

			}

			if (m_Rectangle.getGlobalBounds().intersects(m_PlayerTarget->m_Weapon.hitBox.getGlobalBounds()))
			{
				if (m_TakeDamageClock.getElapsedTime().asSeconds() >= 1.0f / m_PlayerTarget->m_Weapon.attack_speed)
				{
					m_Attributes.health -= m_PlayerTarget->m_Weapon.melee_attack;
					std::cout << -m_PlayerTarget->m_Weapon.melee_attack << std::endl;
					m_TakeDamageClock.restart();
				}
			}

			m_MoveAnimation.update();

			m_Rectangle.move(offset);
			setVertices();
		}

		//set the follow range of the monster
		m_FollowRange.setPosition(m_Rectangle.getPosition().x + m_Rectangle.getSize().x / 2, m_Rectangle.getPosition().y + m_Rectangle.getSize().y / 2);
	}

	bool Slime::intersects(sf::VertexArray &vertexArray)
	{
		sf::RectangleShape rectangle;
		//may require changes
		rectangle.setSize(m_Rectangle.getSize());
		rectangle.setPosition(m_Rectangle.getPosition());

		//0-DOWN
		//1-UP
		//2-LEFT
		//3-UP


		switch (m_CurrDirection)
		{
		case 0:
			rectangle.move(0, m_Attributes.movement_speed * (*m_LoopTime));
			break;

		case 1:
			rectangle.move(0, -m_Attributes.movement_speed * (*m_LoopTime));
			break;

		case 2:
			rectangle.move(-m_Attributes.movement_speed * (*m_LoopTime), 0);
			break;

		case 3:
			rectangle.move(m_Attributes.movement_speed * (*m_LoopTime), 0);
			break;

		default:
			break;
		}

		if (rectangle.getGlobalBounds().intersects(vertexArray.getBounds()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void spawnSlime(std::vector<Slime> &slimeVector)
	{
		std::vector<Slime>::iterator it;

		for (it = slimeVector.begin(); it != slimeVector.end(); it++)
		{
			if (it->m_Alive == false && it->m_RespawnClock.getElapsedTime().asSeconds() >= 10)
			{
				int i, j;
				i = randBetween(0, it->m_MapPtr->m_Solids_Layer.m_Size.x);
				j = randBetween(0, it->m_MapPtr->m_Solids_Layer.m_Size.y);

				while (it->m_MapPtr->m_Solids_Layer.m_Matrix[i][j] != -1)
				{
					i = randBetween(0, it->m_MapPtr->m_Solids_Layer.m_Size.y);
					j = randBetween(0, it->m_MapPtr->m_Solids_Layer.m_Size.x);
				}

				it->m_Rectangle.setPosition(sf::Vector2f(j * it->m_MapPtr->m_Solids_Layer.m_TileSize.x, i * it->m_MapPtr->m_Solids_Layer.m_TileSize.y));
				it->m_Alive = true;
				it->m_Attributes.health = 100;
			}
		}
	}

	void killSlime(std::vector<Slime> &slimeVector)
	{
		std::vector<Slime>::iterator it;

		for (it = slimeVector.begin(); it != slimeVector.end(); it++)
		{
			if (it->m_Alive == true && it->m_Attributes.health <= 0)
			{
				it->m_Alive = false;
				it->m_Rectangle.setPosition(-100, -100);
				it->setVertices();
				it->m_RespawnClock.restart();
			}

		}
	}
	
}