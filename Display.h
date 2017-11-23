#ifndef A_STAR_DISPLAY_H
#define  A_STAR_DISPLAY_H

#include <SFML/Graphics.hpp>
#include "Grid.h"

namespace A_Star
{
	class Display
	{
	public:
		int width;
		int height;

	private:
		sf::RenderWindow *window;
		int rows;
		int cols;

	public:
		explicit Display(int width, int height, int rows, int cols);
		~Display();
		sf::RenderWindow *getWindow();
		void DisplayGrid(std::vector<Cell*> grid, sf::Color color);
	};
}
#endif // A_STAR_DISPLAY_H