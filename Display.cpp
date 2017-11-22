#include "Display.h"

using namespace A_Star;

Display::Display(int width, int height, int rows, int cols) :
	width{ width },
	height {height},
	window { new sf::RenderWindow(sf::VideoMode(width, height), "A* Path Finding") },
	rows {rows},
	cols {cols}
{
}


Display::~Display()
{
	if (this->window != nullptr)
		delete window;
}

sf::RenderWindow* Display::getWindow()
{
	return this->window;
}

void Display::DisplayGrid(std::vector<Cell> grid, sf::Color color)
{
	float w = width / cols;
	float h = height / rows;

	sf::RectangleShape rect;
	rect.setSize((sf::Vector2f( w -1, h -1)));
	rect.setFillColor(color);
	auto it = grid.begin();

	while( it != grid.end())
	{
		rect.setPosition(sf::Vector2f( w * it->position.x, h * it->position.y));
		window->draw(rect);
		++it;
	}
}
