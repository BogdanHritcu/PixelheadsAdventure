#include "map.h"

namespace gm
{
	Map::Map()
	{
		
	}

	Map::~Map()
	{

	}

	Layer::Layer()
	{
		m_VerticesContainer.setPrimitiveType(sf::PrimitiveType::Quads);
	}

	Layer::~Layer()
	{

	}

	void Layer::loadLayer(const char* fileName)
	{
		std::ifstream file(fileName);

		std::vector<short> line;

		int i, j, tileType;

		file >> m_TexAtlasCols;

		file >> m_Size.x >> m_Size.y;
		file >> m_TileSize.x >> m_TileSize.y;

		for (i = 0; i < m_Size.y; i++)
		{
			for (j = 0; j < m_Size.x; j++)
			{
				file >> tileType;
				line.push_back(tileType);
			}
			m_Matrix.push_back(line);
			line.clear();
		}

		file.close();
	}

	void Layer::loadChunk(sf::RectangleShape &renderArea)
	{
		int i, j;
		sf::Vertex vertex;

		sf::Vector2u start, end;
		start.x = int(renderArea.getPosition().x) / m_TileSize.x;
		start.y = int(renderArea.getPosition().y) / m_TileSize.y;

		end.x = int(renderArea.getPosition().x + renderArea.getSize().x) / m_TileSize.x + 1;
		end.y = int(renderArea.getPosition().y + renderArea.getSize().y) / m_TileSize.y + 1;

		if (start.x < 0)
		{
			start.x = 0;
		}

		if (end.x > m_Size.x)
		{
			end.x = m_Size.x;
		}

		if (start.y < 0)
		{
			start.y = 0;
		}

		if (end.y > m_Size.y)
		{
			end.y = m_Size.y;
		}

		m_VerticesContainer.clear();

		for (i = start.y; i < end.y; i++)
		{
			for (j = start.x; j < end.x; j++)
			{
				if (m_Matrix[i][j] >= 0)
				{

					//first point
					vertex.position.x = j * m_TileSize.x;
					vertex.position.y = i * m_TileSize.y;
					vertex.texCoords.x = m_Matrix[i][j] % m_TexAtlasCols * m_TileSize.x;// +m_Matrix[i][j] % m_TexAtlasCols;
					//vertex.texCoords.y = m_Matrix[i][j] / m_TexAtlasCols * m_TileSize.y + m_Matrix[i][j] / m_TexAtlasCols;
					vertex.texCoords.y = 0;
					m_VerticesContainer.append(vertex);

					//second point
					vertex.position.x = (j + 1) * m_TileSize.x;
					vertex.position.y = i * m_TileSize.y;
					vertex.texCoords.x = (m_Matrix[i][j] % m_TexAtlasCols + 1) * m_TileSize.x;// +m_Matrix[i][j] % m_TexAtlasCols;
					//vertex.texCoords.y = m_Matrix[i][j] / m_TexAtlasCols * m_TileSize.y + m_Matrix[i][j] / m_TexAtlasCols;
					vertex.texCoords.y = 0;
					m_VerticesContainer.append(vertex);

					//third point
					vertex.position.x = (j + 1) * m_TileSize.x;
					vertex.position.y = (i + 1) * m_TileSize.y;
					vertex.texCoords.x = (m_Matrix[i][j] % m_TexAtlasCols + 1) * m_TileSize.x;// +m_Matrix[i][j] % m_TexAtlasCols;
					//vertex.texCoords.y = (m_Matrix[i][j] / m_TexAtlasCols + 1) * m_TileSize.y + m_Matrix[i][j] / m_TexAtlasCols;
					vertex.texCoords.y = m_TileSize.y;
					m_VerticesContainer.append(vertex);

					//fourth point
					vertex.position.x = j * m_TileSize.x;
					vertex.position.y = (i + 1) * m_TileSize.y;
					vertex.texCoords.x = (m_Matrix[i][j] % m_TexAtlasCols) * m_TileSize.x;// +m_Matrix[i][j] % m_TexAtlasCols;
					//vertex.texCoords.y = (m_Matrix[i][j] / m_TexAtlasCols + 1) * m_TileSize.y + m_Matrix[i][j] / m_TexAtlasCols;
					vertex.texCoords.y = m_TileSize.y;
					m_VerticesContainer.append(vertex);

				}
			}
		}
	}

	/*void Map::loadMap(const char* fileName)
	{
		std::ifstream file(fileName);

		std::vector<short> line;

		int i, j, tileType;

		file >> m_TexAtlasCols;

		file >> m_MapSize.x >> m_MapSize.y;
		file >> m_TileSize.x >> m_TileSize.y;

		for (i = 0; i < m_MapSize.y; i++)
		{
			for (j = 0; j < m_MapSize.x; j++)
			{
				file >> tileType;
				line.push_back(tileType);
			}
			m_Matrix.push_back(line);
			line.clear();
		}

		file.close();
	}

	void Map::loadChunk(sf::RectangleShape &renderArea)
	{
		int i, j;
		sf::Vertex vertex;

		sf::Vector2u start, end;
		start.x = int(renderArea.getPosition().x) / m_TileSize.x;
		start.y = int(renderArea.getPosition().y) / m_TileSize.y;

		end.x = int(renderArea.getPosition().x + renderArea.getSize().x) / m_TileSize.x + 1;
		end.y = int(renderArea.getPosition().y + renderArea.getSize().y) / m_TileSize.y + 1;

		if (start.x < 0)
		{
			start.x = 0;
		}

		if (end.x > m_MapSize.x)
		{
			end.x = m_MapSize.x;
		}

		if (start.y < 0)
		{
			start.y = 0;
		}

		if (end.y > m_MapSize.y)
		{
			end.y = m_MapSize.y;
		}

		m_VerticesContainer.clear();

		for (i = start.y; i < end.y; i++)
		{
			for (j = start.x; j < end.x; j++)
			{
				//first point
				vertex.position.x = j * m_TileSize.x;
				vertex.position.y = i * m_TileSize.y;
				vertex.texCoords.x = m_Matrix[i][j] % m_TexAtlasCols * m_TileSize.x + m_Matrix[i][j] % m_TexAtlasCols;
				//vertex.texCoords.y = m_Matrix[i][j] / m_TexAtlasCols * m_TileSize.y + m_Matrix[i][j] / m_TexAtlasCols;
				vertex.texCoords.y = 0;
				m_VerticesContainer.append(vertex);

				//second point
				vertex.position.x = (j + 1) * m_TileSize.x;
				vertex.position.y = i * m_TileSize.y;
				vertex.texCoords.x = (m_Matrix[i][j] % m_TexAtlasCols + 1) * m_TileSize.x + m_Matrix[i][j] % m_TexAtlasCols;
				//vertex.texCoords.y = m_Matrix[i][j] / m_TexAtlasCols * m_TileSize.y + m_Matrix[i][j] / m_TexAtlasCols;
				vertex.texCoords.y = 0;
				m_VerticesContainer.append(vertex);

				//third point
				vertex.position.x = (j + 1) * m_TileSize.x;
				vertex.position.y = (i + 1) * m_TileSize.y;
				vertex.texCoords.x = (m_Matrix[i][j] % m_TexAtlasCols + 1) * m_TileSize.x + m_Matrix[i][j] % m_TexAtlasCols;
				//vertex.texCoords.y = (m_Matrix[i][j] / m_TexAtlasCols + 1) * m_TileSize.y + m_Matrix[i][j] / m_TexAtlasCols;
				vertex.texCoords.y = m_TileSize.y;
				m_VerticesContainer.append(vertex);

				//fourth point
				vertex.position.x = j * m_TileSize.x;
				vertex.position.y = (i + 1) * m_TileSize.y;
				vertex.texCoords.x = (m_Matrix[i][j] % m_TexAtlasCols) * m_TileSize.x + m_Matrix[i][j] % m_TexAtlasCols;
				//vertex.texCoords.y = (m_Matrix[i][j] / m_TexAtlasCols + 1) * m_TileSize.y + m_Matrix[i][j] / m_TexAtlasCols;
				vertex.texCoords.y = m_TileSize.y;
				m_VerticesContainer.append(vertex);
			}
		}
	}*/
}
