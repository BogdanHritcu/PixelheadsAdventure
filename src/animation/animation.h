#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "../utils/utils.h"

namespace gm
{
	class Animation
	{
	private:
		float m_FramesPerSecond;
		int m_CurrFrame;
		int m_MaxFrames;
		std::vector<sf::IntRect> m_FrameRectangles;
		float m_DisplayTime;
		float m_Speed;
		sf::Clock m_Timer;
		sf::VertexArray *m_VertexArrayPtr;
		bool m_Paused;

	public:
		Animation();
		~Animation();

		//
		void setVertexArray(sf::VertexArray *VertexArrayPtr);
		void setFrameRate(float frameRate);
		void setMaxFrames(int maxFrames);
		void appendFrame(sf::IntRect frameRect);
		void setSpeed(float speed);
		void update();
		void playWhole();
		void restart();
		void pause();
		void resume();
	};

	/*class Animation
	{
	private:
		int m_CurrentFrame;
		float m_Delay;
		sf::Clock m_Timer;
		
	public:
		float m_FramesPerSecond;
		int m_TotalFrames;
		sf::Vector2f m_FrameSize;

	public:
		Animation();
		~Animation();

		void changeFrame(sf::VertexArray &vertexArray, sf::Clock &timer);
	};*/

	
}