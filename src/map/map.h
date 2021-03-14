#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>

#include "../utils/utils.h"

namespace gm
{
	class Layer
	{
	public:
		std::vector<std::vector<short>>m_Matrix;
		sf::VertexArray m_VerticesContainer;
		sf::Texture *m_TexAtlas;

	private:
		int m_TexAtlasCols;

	public:
		sf::Vector2u m_TileSize;
		sf::Vector2u m_Size;
		void loadLayer(const char* fileName);
		void loadChunk(sf::RectangleShape &renderArea);

		Layer();
		~Layer();
	};
	
	class Map
	{
	public:
		//contains the vertices of the current chunks
		Layer m_BG_Layer;
		Layer m_Solids_Layer;

	public:
		Map();
		~Map();
	};

	/*class Map
	{
	public:
		//contains the vertices of the current chunks
		sf::VertexArray m_VerticesContainer;
		sf::Texture *m_TexAtlas;

		std::vector<std::vector<short>>m_Matrix;

	private:
		sf::Vector2u m_MapSize;
		sf::Vector2u m_TileSize;
		int m_TexAtlasCols;

	public:
		Map();
		~Map();

		void loadMap(const char* fileName);
		void loadChunk(sf::RectangleShape &renderArea);
	};*/

}
