#ifndef A_STAR_CELL_H
#define  A_STAR_CELL_H
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace A_Star
{
	class Cell
	{
	public:
		float f;
		float g;
		float h;
		sf::Vector2f position;
		std::vector<Cell> neighbors;

	public:
		explicit Cell(sf::Vector2f position);
		~Cell();
		Cell(const Cell &other);

		void AddNeighbors(std::vector<Cell> grid, int cols, int rows);
		Cell &getInstance();

		bool operator==(const Cell &other);
		Cell &operator=(const Cell &other);
	};
}
#endif // A_STAR_DISPLAY_H