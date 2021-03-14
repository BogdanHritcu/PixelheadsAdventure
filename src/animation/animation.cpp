#include "animation.h"

namespace gm
{
	Animation::Animation()
	{
		m_CurrFrame = 0;
		m_Speed = 1;
		m_VertexArrayPtr = nullptr;

		setFrameRate(0);
	}

	Animation::~Animation()
	{

	}

	void Animation::setVertexArray(sf::VertexArray *VertexArrayPtr)
	{
		m_VertexArrayPtr = VertexArrayPtr;
	}

	void Animation::update()
	{
		if (m_Paused == false)
		{
			if (m_CurrFrame >= m_MaxFrames)
			{
				m_CurrFrame = 0;
			}

			if (m_CurrFrame < m_MaxFrames)
			{
				(*m_VertexArrayPtr)[0].texCoords.x = m_FrameRectangles[m_CurrFrame].left;
				(*m_VertexArrayPtr)[0].texCoords.y = m_FrameRectangles[m_CurrFrame].top;

				(*m_VertexArrayPtr)[1].texCoords.x = m_FrameRectangles[m_CurrFrame].left + m_FrameRectangles[m_CurrFrame].width;
				(*m_VertexArrayPtr)[1].texCoords.y = m_FrameRectangles[m_CurrFrame].top;

				(*m_VertexArrayPtr)[2].texCoords.x = m_FrameRectangles[m_CurrFrame].left + m_FrameRectangles[m_CurrFrame].width;
				(*m_VertexArrayPtr)[2].texCoords.y = m_FrameRectangles[m_CurrFrame].top + m_FrameRectangles[m_CurrFrame].height;

				(*m_VertexArrayPtr)[3].texCoords.x = m_FrameRectangles[m_CurrFrame].left;
				(*m_VertexArrayPtr)[3].texCoords.y = m_FrameRectangles[m_CurrFrame].top + m_FrameRectangles[m_CurrFrame].height;
			}

			if (m_Timer.getElapsedTime().asSeconds() >= m_DisplayTime / m_Speed && m_DisplayTime != 0)
			{
				m_CurrFrame++;
				m_Timer.restart();
			}
		}
	}

	void Animation::playWhole()
	{
		while (m_CurrFrame < m_MaxFrames)
		{
			update();
		}
	}

	void Animation::restart()
	{
		m_CurrFrame = 0;
	}

	void Animation::pause()
	{
		m_Paused = true;
	}

	void Animation::resume()
	{
		m_Paused = false;
	}

	void Animation::setFrameRate(float frameRate)
	{
		if (frameRate <= 0)
		{
			m_FramesPerSecond = 0;
			m_DisplayTime = 0;
		}
		else
		{
			m_FramesPerSecond = frameRate;
			m_DisplayTime = 1.0f / m_FramesPerSecond;
		}
	}

	void Animation::setMaxFrames(int maxFrames)
	{
		if (maxFrames < 0)
		{
			m_MaxFrames = 0;
		}
		else
		{
			m_MaxFrames = maxFrames;
		}
	}

	void Animation::setSpeed(float speed)
	{
		if (speed <= 0.25)
		{
			m_Speed = 0.25;
		}
		else
			if (speed >= 4)
			{
				m_Speed = 4;
			}
			else
			{
				m_Speed = speed;
			}
	}

	void Animation::appendFrame(sf::IntRect frameRect)
	{
		m_FrameRectangles.push_back(frameRect);
	}
}