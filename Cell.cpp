#include <iostream>
#include "Cell.h"
#include <random>

using namespace A_Star;

Cell::Cell(sf::Vector2f position) :
	f {0},
	g {0},
	h {0},
	position{position}
{
	this->wall = false;
	///*
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, 3); // define the range
	
	if (distr(eng) % 3 == 0)
		this->wall = true;
	//*/
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


void Cell::AddNeighbors(std::vector<Cell*> grid, int cols, int rows)
{
	//TODO This only works with square grids
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

	if( x > 0 && y > 0 )
	{
		index = ((x  - 1) * cols) + (y - 1);
		this->neighbors.push_back(grid[index]);
	}

	if (x < cols - 1 && y > 0)
	{
		index = ((x + 1) * cols) + (y - 1);
		this->neighbors.push_back(grid[index]);
	}

	if (x > 0 && y < rows - 1)
	{
		index = ((x - 1) * cols) + (y + 1);
		this->neighbors.push_back(grid[index]);
	}

	if (x < cols - 1 && y < rows - 1)
	{
		index = ((x + 1) * cols) + (y + 1);
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
