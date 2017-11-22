#include <SFML/Graphics.hpp>
#include <iostream>
#include "Display.h"
#include "Grid.h"

using namespace A_Star;

int main(int argc, char* argv[])
{
	sf::Time delay = sf::seconds(1);
	int width = 1000;
	int height = 1000;
	int rows = 5;
	int cols = 5;
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

		grid.Update();

		window->clear();
		display.DisplayGrid(grid.getGrid(), sf::Color::White);
		display.DisplayGrid(grid.getClosedSet(), sf::Color::Red);
		display.DisplayGrid(grid.getOpenSet(), sf::Color::Green);
		window->display();
		//sf::sleep(delay);
	}

	return 0;
}
