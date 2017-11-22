#include "Cell.h"
#include <iostream>

using namespace A_Star;

Cell::Cell(sf::Vector2f position) :
	f {0},
	g {0},
	h {0},
	position{position}
{
}


Cell::~Cell()
{
}

Cell::Cell(const Cell &other)
{
	this->position = other.position;
	this->f = other.f;
	this->g = other.g;
	this->h = other.h;
	this->neighbors = other.neighbors;
}


void Cell::AddNeighbors(std::vector<Cell> grid, int cols, int rows)
{
	int x = this->position.x;
	int y = this->position.y;
	int index = 0;

	if (x < cols - 1)
	{
		index = ((x + 1) * cols) + y;
		this->neighbors.push_back(grid[index]);
	}
		
	if( x > 0)
	{
		index = ((x - 1) * cols) + y;
		this->neighbors.push_back(grid[index]);
	}
		
	if (y < rows - 1)
	{
		index = (x * cols) + (y + 1);
		this->neighbors.push_back(grid[index]);
	}
		
	if (y > 0)
	{
		index = (x * cols) + (y - 1);
		this->neighbors.push_back(grid[index]);
	}
}

Cell& Cell::getInstance()
{
	return *this;
}

bool Cell::operator==(const Cell& other)
{
	return (this->position.x == other.position.x 
		&& this->position.y == other.position.y);
}

Cell& Cell::operator=(const Cell& other)
{
	this->position = other.position;
	this->f = other.f;
	this->g = other.g;
	this->h = other.h;
	this->neighbors = other.neighbors;

	return *this;
}
