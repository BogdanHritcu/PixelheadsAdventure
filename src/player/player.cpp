#include "player.h"

namespace gm
{
	Player::Player()
	{
		m_Rectangle.setFillColor(sf::Color::White);
		m_Rectangle.setPosition(sf::Vector2f(450, 300));
		m_Rectangle.setSize(sf::Vector2f(192, 192));

		m_HitBoxRect.setSize(sf::Vector2f(32, 32));
		m_HitBoxRect.setFillColor(sf::Color::Red);
		m_FeetRect.setSize(sf::Vector2f(32, 24));
		m_FeetRect.setFillColor(sf::Color::Green);
		setRects();

		m_CurrDirection = 0;
		m_Attacking = false;
		m_Class = Player::PlayerClass::Warrior;


		m_VerticesContainer.setPrimitiveType(sf::PrimitiveType::Quads);
		m_VerticesContainer.resize(4);

		//animations
		m_MoveUpAnimation.setVertexArray(&m_VerticesContainer);
		m_MoveLeftAnimation.setVertexArray(&m_VerticesContainer);
		m_MoveDownAnimation.setVertexArray(&m_VerticesContainer);
		m_MoveRightAnimation.setVertexArray(&m_VerticesContainer);

		m_MoveUpAnimation.setFrameRate(10);
		m_MoveLeftAnimation.setFrameRate(10);
		m_MoveDownAnimation.setFrameRate(10);
		m_MoveRightAnimation.setFrameRate(10);

		m_MoveUpAnimation.setMaxFrames(9);
		m_MoveLeftAnimation.setMaxFrames(9);
		m_MoveDownAnimation.setMaxFrames(9);
		m_MoveRightAnimation.setMaxFrames(9);

		m_AttackUpAnimation.setVertexArray(&m_VerticesContainer);
		m_AttackLeftAnimation.setVertexArray(&m_VerticesContainer);
		m_AttackDownAnimation.setVertexArray(&m_VerticesContainer);
		m_AttackRightAnimation.setVertexArray(&m_VerticesContainer);

		m_AttackUpAnimation.setFrameRate(10);
		m_AttackLeftAnimation.setFrameRate(10);
		m_AttackDownAnimation.setFrameRate(10);
		m_AttackRightAnimation.setFrameRate(10);

		m_AttackUpAnimation.setMaxFrames(6);
		m_AttackLeftAnimation.setMaxFrames(6);
		m_AttackDownAnimation.setMaxFrames(6);
		m_AttackRightAnimation.setMaxFrames(6);

		int i;
		for (i = 0; i < 9; i++)
		{
			m_MoveUpAnimation.appendFrame(sf::IntRect(i * 192, 0 * 192, 192, 192));
			m_MoveLeftAnimation.appendFrame(sf::IntRect(i * 192, 1 * 192, 192, 192));
			m_MoveDownAnimation.appendFrame(sf::IntRect(i * 192, 2 * 192, 192, 192));
			m_MoveRightAnimation.appendFrame(sf::IntRect(i * 192, 3 * 192, 192, 192));
		}

		for (i = 9; i < 15; i++)
		{
			m_AttackUpAnimation.appendFrame(sf::IntRect(i * 192, 0 * 192, 192, 192));
			m_AttackLeftAnimation.appendFrame(sf::IntRect(i * 192, 1 * 192, 192, 192));
			m_AttackDownAnimation.appendFrame(sf::IntRect(i * 192, 2 * 192, 192, 192));
			m_AttackRightAnimation.appendFrame(sf::IntRect(i * 192, 3 * 192, 192, 192));
		}

		m_Attributes.strength = 4;
		m_Attributes.intellect = 1;
		m_Attributes.stamina = 4;
		m_Attributes.vitality = 3;
		m_Attributes.health = 600;
		m_Attributes.max_health = 600;
		m_Attributes.mana = (10 + m_Attributes.intellect) * m_Attributes.intellect;
		m_Attributes.defence = 8;
		m_Attributes.melee_attack = (1 + m_Attributes.strength ) * 2;
		m_Attributes.magical_attack = 1 + m_Attributes.intellect;
		m_Attributes.ranged_attack = (1 + m_Attributes.strength) * 1.5;
		m_Attributes.critical_chance = 0;
		m_Attributes.movement_speed = 60;
		m_Attributes.attack_speed = 0.5f;

		m_Weapon.attack_speed = 1;
		m_Weapon.melee_attack = 20;
		m_Weapon.hitBox.setFillColor(sf::Color::Magenta);

		loadInfo("player_info/player_info.txt");
		setVertices();
	}

	Player::~Player()
	{

	}

	Player::PlayerAction Player::getInput()
	{
		//stop getting input if the player is attacking
		if (m_Attacking == true)
		{
			return PlayerAction::Attack;
		}

		PlayerAction action = PlayerAction::Still;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			//update direction and animation
			m_CurrDirection = 0;
			action = PlayerAction::MoveUP;
			m_MoveUpAnimation.update();

			//check for collision
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
					action = PlayerAction::Still;
					break;
				}
			}
		}
		else
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_CurrDirection = 1;
				action = PlayerAction::MoveLEFT;
				m_MoveLeftAnimation.update();

				//check for collision
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
						action = PlayerAction::Still;
						break;
					}
				}
			}
			else
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					m_CurrDirection = 2;
					action = PlayerAction::MoveDOWN;
					m_MoveDownAnimation.update();

					//check for collision
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
							action = PlayerAction::Still;
							break;
						}
					}
				}
				else
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					{
						m_CurrDirection = 3;
						action = PlayerAction::MoveRIGHT;
						m_MoveRightAnimation.update();

						//check for collision
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
								action = PlayerAction::Still;
								break;
							}
						}
					}
					else
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							if (m_AttackTimer.getElapsedTime().asSeconds() >= m_Attributes.attack_speed)
							{
								m_AttackTimer.restart();
								action = PlayerAction::Attack;
								m_Attacking = true;
							}
						}
						else
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
							{
								if (m_HealTimer.getElapsedTime().asSeconds() >= 5)
								{
									m_HealTimer.restart();
									action = PlayerAction::Heal;
								}
							}

		return action;
	}

	void Player::loadInfo(const char* fileName)
	{
		std::ifstream file(fileName);
		
		sf::Vector2f pos;
		file >> pos.x >> pos.y;
		m_Rectangle.setPosition(pos);
		setRects();

		file >> m_Attributes.health;

		if (m_Attributes.health > m_Attributes.max_health)
		{
			m_Attributes.health = m_Attributes.max_health;
		}

		if (m_Attributes.health <= 0)
		{
			m_Attributes.health = 1;
		}

		file.close();
	}

	void Player::exportInfo(const char* fileName)
	{
		std::ofstream file(fileName);

		file << m_Rectangle.getPosition().x << " " << m_Rectangle.getPosition().y << std::endl;
		file << m_Attributes.health;

		file.close();
	}

	void Player::attack()
	{
		//0-UP
		//1-LEFT
		//2-DOWN
		//3-RIGHT

		if (m_CurrDirection == 0)
		{
			m_AttackUpAnimation.update();

			m_Weapon.hitBox.setSize(sf::Vector2f(m_Rectangle.getSize().x / 2, m_Rectangle.getSize().y / 4));
			m_Weapon.hitBox.setPosition(sf::Vector2f(m_Rectangle.getPosition().x + m_Rectangle.getSize().x / 2 - m_Weapon.hitBox.getSize().x / 2, m_Rectangle.getPosition().y + m_Rectangle.getSize().y / 2 - m_Weapon.hitBox.getSize().y));
		}
		else
			if (m_CurrDirection == 1)
			{
				m_AttackLeftAnimation.update();

				m_Weapon.hitBox.setSize(sf::Vector2f(m_Rectangle.getSize().x / 3, m_Rectangle.getSize().y / 2));
				m_Weapon.hitBox.setPosition(sf::Vector2f(m_Rectangle.getPosition().x + m_Rectangle.getSize().x / 2 - m_Weapon.hitBox.getSize().x, m_Rectangle.getPosition().y + m_Rectangle.getSize().y / 2 - m_Weapon.hitBox.getSize().y / 2));
			}
			else
				if (m_CurrDirection == 2)
				{
					m_AttackDownAnimation.update();

					m_Weapon.hitBox.setSize(sf::Vector2f(m_Rectangle.getSize().x / 2, m_Rectangle.getSize().y / 4));
					m_Weapon.hitBox.setPosition(sf::Vector2f(m_Rectangle.getPosition().x + m_Rectangle.getSize().x / 2 - m_Weapon.hitBox.getSize().x / 2, m_Rectangle.getPosition().y + m_Rectangle.getSize().y / 2));
				}
				else
					if (m_CurrDirection == 3)
					{
						m_AttackRightAnimation.update();

						m_Weapon.hitBox.setSize(sf::Vector2f(m_Rectangle.getSize().x / 3, m_Rectangle.getSize().y / 2));
						m_Weapon.hitBox.setPosition(sf::Vector2f(m_Rectangle.getPosition().x + m_Rectangle.getSize().x / 2, m_Rectangle.getPosition().y + m_Rectangle.getSize().y / 2 - m_Weapon.hitBox.getSize().y / 2));
					}


		//exit the attack
		if (m_AttackTimer.getElapsedTime().asSeconds() >= m_Attributes.attack_speed)
		{
			m_Attacking = false;
			m_AttackUpAnimation.restart();
			m_AttackLeftAnimation.restart();
			m_AttackDownAnimation.restart();
			m_AttackRightAnimation.restart();
		}
		
	}

	void Player::setVertices()
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

	void Player::setRects()
	{
		m_HitBoxRect.setPosition(sf::Vector2f(m_Rectangle.getPosition().x + m_Rectangle.getSize().x / 2 - m_HitBoxRect.getSize().x / 2, m_Rectangle.getPosition().y + m_Rectangle.getSize().y / 2 - m_HitBoxRect.getSize().y / 2));

		m_FeetRect.setPosition(sf::Vector2f(m_Rectangle.getPosition().x + m_Rectangle.getSize().x / 2 - m_FeetRect.getSize().x / 2, m_Rectangle.getPosition().y + m_Rectangle.getSize().y / 2));
	}

	void Player::heal()
	{
		m_Attributes.health += 20;

		if (m_Attributes.health > m_Attributes.max_health)
		{
			m_Attributes.health = m_Attributes.max_health;
		}
	}

	void Player::movePlayer(PlayerAction action)
	{
		switch (action)
		{
		case PlayerAction::Still:
			switch (m_CurrDirection)
			{
			case 0:
				m_MoveUpAnimation.restart();
				m_MoveUpAnimation.update();
				break;

			case 1:
				m_MoveLeftAnimation.restart();
				m_MoveLeftAnimation.update();
				break;

			case 2:
				m_MoveDownAnimation.restart();
				m_MoveDownAnimation.update();
				break;

			case 3:
				m_MoveRightAnimation.restart();
				m_MoveRightAnimation.update();
				break;

			default:
				break;
			}
			break;

		case PlayerAction::Attack:
			attack();
			setVertices();
			break;

		case PlayerAction::Heal:
			heal();
			setVertices();
			break;

		case PlayerAction::MoveUP:
			m_Rectangle.move(0, -m_Attributes.movement_speed * (*m_LoopTime));
			setRects();
			setVertices();
			m_MoveUpAnimation.update();
			break;

		case PlayerAction::MoveLEFT:
			m_Rectangle.move(-m_Attributes.movement_speed * (*m_LoopTime), 0);
			setRects();
			setVertices();
			m_MoveLeftAnimation.update();
			break;
		
		case PlayerAction::MoveDOWN:
			m_Rectangle.move(0, m_Attributes.movement_speed * (*m_LoopTime));
			setRects();
			setVertices();
			m_MoveDownAnimation.update();
			break;

		case PlayerAction::MoveRIGHT:
			m_Rectangle.move(m_Attributes.movement_speed * (*m_LoopTime), 0);
			setRects();
			setVertices();
			m_MoveRightAnimation.update();
			break;


		default:
			break;
		}

		//reset weapon
		if (m_AttackTimer.getElapsedTime().asSeconds() >= m_Attributes.attack_speed)
		{
			m_Weapon.hitBox.setPosition(sf::Vector2f(-500, 600));
		}
	}

	bool Player::intersects(sf::VertexArray &vertexArray)
	{
		sf::RectangleShape rectangle;
		//may require changes
		rectangle.setSize(m_FeetRect.getSize());// -sf::Vector2f(8, 4));
		rectangle.setPosition(m_FeetRect.getPosition());

		//0-UP
		//1-LEFT
		//2-DOWN
		//3-RIGHT


		switch (m_CurrDirection)
		{
		case 0:
			rectangle.move(0, -m_Attributes.movement_speed * (*m_LoopTime));
			break;

		case 1:
			rectangle.move(-m_Attributes.movement_speed * (*m_LoopTime), 0);
			break;

		case 2:
			rectangle.move(0, m_Attributes.movement_speed * (*m_LoopTime));
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
}
