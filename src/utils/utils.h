#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include <iostream>

namespace gm
{
	class Hexagon : public sf::Drawable
	{
	private:
		sf::CircleShape m_Circle;

	public:
		Hexagon();
		~Hexagon();

		void setCenter(sf::Vector2f pos);
		void setPosition(sf::Vector2f pos);
		void setSideLength(float length);
		sf::Vector2f getCenter();
		float getSideLength();
		float getApothem();

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

	class HexagonMap : public sf::Drawable
	{
	private:
		std::vector<Hexagon>m_HexagonArray;
		sf::Vector2f m_Position;
		int m_SideLength;
		float m_CompHexagonSideLength;

	public:
		HexagonMap();
		~HexagonMap();

		void setCenter(sf::Vector2f pos);
		void build(int sideLength, float compHexagonSideLength);
		void buildFit(int sideLength, float radius);

	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	};
	
	int randBetween(int min, int max);

	void swap(float *a, float *b);
	void swap(int *a, int *b);
	void swap(sf::VertexArray *a, sf::VertexArray *b);
	void quickSortMiddle(float *array, int left, int right);
	void quickSortMiddle(int *array, int left, int right);
	void quickSortMiddle(sf::VertexArray &vertexArray, int left, int right);
}