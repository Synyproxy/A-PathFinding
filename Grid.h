#ifndef A_STAR_GRID_H
#define  A_STAR_GRID_H

#include <SFML/Graphics.hpp>
#include "Cell.h"

namespace  A_Star
{
	class Grid
	{
	private:
		std::vector<Cell> grid;
		std::vector<Cell>openSet;
		std::vector<Cell> closedSet;
		Cell start;
		Cell end;
		int rows;
		int cols;

	public:
		Grid(int rows, int cols, sf::Vector2f startPos, sf::Vector2f endPos);
		~Grid();

		void Setup();
		void Update();

		void Remove(Cell element);
		bool Includes(std::vector<Cell> grid, Cell element);
		float Heuristic(Cell current, Cell end);


		std::vector<Cell> getGrid() const;
		std::vector<Cell> getOpenSet() const;
		std::vector<Cell> getClosedSet() const;
	};
}
#endif