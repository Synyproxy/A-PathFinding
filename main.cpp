#include <SFML/Graphics.hpp>
#include <iostream>
#include "Display.h"
#include "Grid.h"

using namespace A_Star;

int main(int argc, char* argv[])
{
	sf::Time delay = sf::seconds(0.1f);
	int width = 1000;
	int height = 1000;
	int rows = 100;
	int cols = 100;
	sf::Vector2f star(0, 0);
	sf::Vector2f end( rows -1, cols -1);

	Display display(width, height, rows, cols);
	sf::RenderWindow *window = display.getWindow();

	Grid grid(rows, cols, star, end);
	grid.Setup();

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		if(grid.IsSearching())
			grid.Update();

		window->clear();
		display.DisplayGrid(grid.getGrid(), sf::Color::White);
		display.DisplayGrid(grid.getOpenSet(), sf::Color::Green);
		display.DisplayGrid(grid.getClosedSet(), sf::Color::Red);
		display.DisplayGrid(grid.getpath(), sf::Color::Blue);
		window->display();
		//sf::sleep(delay);
	}

	return 0;
}
