#include "utils.h"

namespace gm
{
	Hexagon::Hexagon()
	{
		m_Circle.setRadius(100);
		m_Circle.setPointCount(6);
		m_Circle.setFillColor(sf::Color::Red);
		m_Circle.setOrigin(sf::Vector2f(m_Circle.getRadius(), m_Circle.getRadius()));
		m_Circle.setRotation(90);
		m_Circle.setPosition(sf::Vector2f(m_Circle.getRadius(), m_Circle.getRadius() / 2 * 1.73));
	}

	Hexagon::~Hexagon()
	{

	}

	HexagonMap::HexagonMap()
	{
		m_Position = sf::Vector2f(300, 300);
		m_CompHexagonSideLength = 20;
		m_SideLength = 3;
	}

	HexagonMap::~HexagonMap()
	{

	}

	sf::Vector2f Hexagon::getCenter()
	{
		return m_Circle.getPosition();
	}

	float Hexagon::getSideLength()
	{
		return m_Circle.getRadius();
	}

	float Hexagon::getApothem()
	{
		return m_Circle.getRadius() / 2 * 1.73;
	}
	
	void Hexagon::setCenter(sf::Vector2f pos)
	{
		m_Circle.setPosition(pos);
	}

	void Hexagon::setPosition(sf::Vector2f pos)
	{
		setCenter(sf::Vector2f(getSideLength(), getApothem()) + pos);
	}

	void Hexagon::setSideLength(float length)
	{	
		sf::Vector2f pos = sf::Vector2f(getCenter().x - getSideLength(), getCenter().y - getApothem());
		m_Circle.setRadius(length);
		m_Circle.setOrigin(sf::Vector2f(length, length));
		setCenter(pos + sf::Vector2f(getSideLength(), getApothem()));
	}

	void Hexagon::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Circle);
	}

	void HexagonMap::setCenter(sf::Vector2f pos)
	{
		if (m_HexagonArray.size() > 0)
		{
			m_Position = sf::Vector2f(pos.x, pos.y - (m_SideLength + 1) * m_HexagonArray[0].getApothem());
			build(m_SideLength, m_CompHexagonSideLength);
		}
	}

	void HexagonMap::build(int sideLength, float compHexagonSideLength)
	{
		m_HexagonArray.clear();

		Hexagon hexagon;
		hexagon.setSideLength(compHexagonSideLength);

		m_SideLength = sideLength;
		m_CompHexagonSideLength = compHexagonSideLength;

		int i, j, k;

		k = 0;
		for (i = 2 * sideLength - 1; i >= sideLength; i--)
		{
			for (j = 0; j < i; j++)
			{
				hexagon.setCenter(m_Position + sf::Vector2f(hexagon.getSideLength() * k * 3.0f / 2, (2 * j + k) * hexagon.getApothem()));

				m_HexagonArray.push_back(hexagon);
			
				hexagon.setCenter(m_Position + sf::Vector2f(-hexagon.getSideLength() * k * 3.0f / 2, (2 * j + k) * hexagon.getApothem()));

				m_HexagonArray.push_back(hexagon);
			}
			
			k++;
		}
	}
	
	void HexagonMap::buildFit(int sideLength, float radius)
	{
		m_HexagonArray.clear();

		Hexagon hexagon;

		m_SideLength = sideLength;
		m_CompHexagonSideLength = (radius / (2 * sideLength - 1)) * 2 / 1.73;
		hexagon.setSideLength(m_CompHexagonSideLength);

		int i, j, k;

		k = 0;
		for (i = 2 * sideLength - 1; i >= sideLength; i--)
		{
			for (j = 0; j < i; j++)
			{
				hexagon.setCenter(m_Position + sf::Vector2f(hexagon.getSideLength() * k * 3.0f / 2, (2 * j + k) * hexagon.getApothem()));

				m_HexagonArray.push_back(hexagon);

				hexagon.setCenter(m_Position + sf::Vector2f(-hexagon.getSideLength() * k * 3.0f / 2, (2 * j + k) * hexagon.getApothem()));

				m_HexagonArray.push_back(hexagon);
			}

			k++;
		}
	}
	
	void HexagonMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		int i;
		for (i = 0; i < m_HexagonArray.size(); i++)
		{
			target.draw(m_HexagonArray[i]);
		}
	}

	int randBetween(int min, int max)
	{
		if (min == max)
		{
			return min;
		}

		if (max < min)
		{
			return rand() % (min - max) + max;
		}

		return rand() % (max - min) + min;
	}

	void swap(float *a, float *b)
	{
		float aux = *a;
		*a = *b;
		*b = aux;
	}

	void swap(int *a, int *b)
	{
		int aux = *a;
		*a = *b;
		*b = aux;
	}

	void swap(sf::Vertex *a, sf::Vertex *b)
	{
		sf::Vertex aux;
		aux = *a;
		*a = *b;
		*b = aux;
	}
	
	void quickSortMiddle(float *array, int left, int right)
	{
		if (left >= right) return;
		int leftI = left;
		int rightI = right;
		int pivot = array[(left + right) / 2];
		while (leftI <= rightI)
		{
			while (array[leftI] < pivot)
			{
				leftI++;
			}

			while (array[rightI] > pivot)
			{
				rightI--;
			}

			if (leftI <= rightI)
			{
				swap(&array[leftI], &array[rightI]);
				leftI++;
				rightI--;
			}
		}
		if (left < rightI)
		{
			quickSortMiddle(array, left, rightI);
		}
		if (leftI < right)
		{
			quickSortMiddle(array, leftI, right);
		}
	}

	void quickSortMiddle(int *array, int left, int right)
	{
		if (left >= right) return;
		int leftI = left;
		int rightI = right;
		int pivot = array[(left + right) / 2];
		while (leftI <= rightI)
		{
			while (array[leftI] < pivot)
			{
				leftI++;
			}

			while (array[rightI] > pivot)
			{
				rightI--;
			}

			if (leftI <= rightI)
			{
				swap(&array[leftI], &array[rightI]);
				leftI++;
				rightI--;
			}
		}
		if (left < rightI)
		{
			quickSortMiddle(array, left, rightI);
		}
		if (leftI < right)
		{
			quickSortMiddle(array, leftI, right);
		}
	}

	void quickSortMiddle(sf::VertexArray &vertexArray, int left, int right)
	{
		if (left >= right) return;
		int leftI = left;
		int rightI = right;
		sf::Vertex pivot = vertexArray[(left + right) / 2];

		while (leftI <= rightI)
		{
			while (vertexArray[leftI].position.y < pivot.position.y)
			{
				leftI++;
			}

			while (vertexArray[rightI].position.y > pivot.position.y)
			{
				rightI--;
			}

			if (leftI <= rightI)
			{
				swap(&vertexArray[leftI], &vertexArray[rightI]);
				leftI++;
				rightI--;
			}
		}
		if (left < rightI)
		{
			quickSortMiddle(vertexArray, left, rightI);
		}
		if (leftI < right)
		{
			quickSortMiddle(vertexArray, leftI, right);
		}
	}
}