#include "Grid.h"
#include <iostream>

using namespace A_Star;

Grid::Grid(int rows, int cols, sf::Vector2f startPos, sf::Vector2f endPos):
	rows {rows},
	cols {cols},
	start {Cell(startPos)},
	end {Cell(endPos)}
{

}

Grid::~Grid()
{
}

void Grid::Setup()
{
	for(int i = 0; i < this->cols; ++i)
	{
		for (int j = 0; j < this->rows; ++j)
		{
			Cell *newCell = new Cell(sf::Vector2f(i, j));
			this->grid.push_back(*newCell);
		}
	}

	for (auto it = this->grid.begin(); it != this->grid.end(); ++it)
		it->AddNeighbors(this->grid, this->cols, this->rows);
	this->start = grid.front();
	this->end = grid.back();
	this->openSet.push_back(this->start);
}

void Grid::Update()
{
	int openSetSize = openSet.size();
	int winner = 0;

	if(!this->openSet.empty())
	{
		//Keep Going
		for(int i = 0; i < openSetSize; ++i)
		{
			if (openSet[i].f < openSet[winner].f)
				winner = i;
		}
		Cell current = openSet[winner];

		if (current == end)
		{
			std::cout << "Done" << std::endl;
		}

		Remove(current);
		this->closedSet.push_back(current);

		std::vector<Cell> neighbors = current.neighbors;
		int neighborsCount = neighbors.size();
		float tempG;

		for (int i = 0; i < neighborsCount; ++i)
		{
			Cell neighbor = neighbors[i];
			//Copy Neighbors properly 
			neighbor.AddNeighbors(this->grid, this->cols, this->rows);

			if(!Includes( this->closedSet,neighbor))
			{
				tempG = current.g + 1;

				//Its in the openSet
				if(Includes(this->openSet, neighbor))
				{
					if (tempG < neighbor.g)
					{
						neighbor.g = tempG;
					}	
				}else // Not in openSet
				{
					neighbor.g = tempG;
					this->openSet.push_back(neighbor);
				}
				neighbor.h = Heuristic(neighbor, this->end);
				neighbor.f = neighbor.g + neighbor.h;
			}
		}
	}
	else
	{
		// No Solution
	}
}

std::vector<Cell> Grid::getGrid() const
{
	return this->grid;
}

std::vector<Cell> Grid::getOpenSet() const
{
	return this->openSet;
}

std::vector<Cell> Grid::getClosedSet() const
{
	return this->closedSet;
}

void Grid::Remove(Cell element)
{
	auto it = this->openSet.begin();
	int index = 0;
	bool found = false;
	
	while(it != this->openSet.end())
	{
		if( *it == element)
		{
			found = true;
		}
		if (!found)
			++index;
		++it;
	}

	this->openSet.erase(this->openSet.begin() + index);
}

bool Grid::Includes(std::vector<Cell> grid, Cell element)
{
	auto it = grid.begin();

	while (it != grid.end())
	{
		if (*it == element)
			return true;
		++it;
	}
	return false;
}

float Grid::Heuristic(Cell current, Cell end)
{
	//Manhatan Distance 
	return (abs(current.position.x - end.position.x) + abs(current.position.y - end.position.y));
}
