#include "Grid.h"
#include <iostream>

using namespace A_Star;

Grid::Grid(int rows, int cols, sf::Vector2f startPos, sf::Vector2f endPos):
	rows {rows},
	cols {cols},
	start {new Cell(startPos)},
	end {new Cell(endPos)},
	searching {true}
{
}

Grid::~Grid()
{
}

void Grid::Setup()
{
	for(int i = 0; i < this->cols; ++i)
		for (int j = 0; j < this->rows; ++j)
			this->grid.push_back(new Cell(sf::Vector2f(i, j)));

	for (auto it = this->grid.begin(); it != this->grid.end(); ++it)
		(*it)->AddNeighbors(this->grid, this->cols, this->rows);

	this->start = this->grid.front();
	this->end = this->grid.back();
	
	this->openSet.push_back(this->start);
}

void Grid::Update()
{
	int openSetSize = this->openSet.size();
	int winner = 0;  // Counter
	Cell *current = nullptr;	// Current Node
	std::vector<Cell*> neighbors; //Neighbors
	int neighborsCount = 0;
	Cell *neighbor = nullptr;
	float tempG = 0;
	Cell* pathNode;
	bool newPath = false;

	if(!this->openSet.empty())
	{
		//Keep Going
		for(int i = 0; i < openSetSize; ++i)
			if (this->openSet[i]->f < this->openSet[winner]->f)
				winner = i;
				
		current = this->openSet[winner];

		this->path.clear();
		pathNode = current;
		this->path.push_back(pathNode);
		while (pathNode->previous)
		{
			this->path.push_back(pathNode->previous);
			pathNode = pathNode->previous;
		}

		//FoundSolution
		if (current == this->end)
		{
			pathNode = current;
			this->path.push_back(pathNode);
			while (pathNode->previous)
			{
				this->path.push_back(pathNode->previous);
				pathNode = pathNode->previous;
			}
			this->searching = false;
		}

		Remove(current);
		this->closedSet.push_back(current);

		neighbors = current->neighbors;
		neighborsCount = neighbors.size();
		
		for (int i = 0; i < neighborsCount; ++i)
		{
			neighbor = neighbors[i];

			//These are not possible spots
			if(!Includes( this->closedSet,neighbor) && !neighbor->wall)
			{
				tempG = current->g + 1;

				//Its in the openSet
				if(Includes(this->openSet, neighbor))
				{
					if (tempG < neighbor->g)
					{
						neighbor->g = tempG;
						newPath = true;
					}	
						
				}else // Not in openSet
				{
					neighbor->g = tempG;
					newPath = true;
					this->openSet.push_back(neighbor);
				}
				if(newPath)
				{
					neighbor->h = Heuristic(neighbor, this->end);
					neighbor->f = neighbor->g + neighbor->h;
					neighbor->previous = current;
				}
			}
		}
	}
	else
	{
		// No Solution
	}
}

std::vector<Cell*> Grid::getGrid() const
{
	return this->grid;
}

std::vector<Cell*> Grid::getOpenSet() const
{
	return this->openSet;
}

std::vector<Cell*> Grid::getClosedSet() const
{
	return this->closedSet;
}

std::vector<Cell*> Grid::getpath() const
{
	return this->path;
}

void Grid::Remove(Cell *element)
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

bool Grid::Includes(std::vector<Cell*> grid, Cell *element)
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

float Grid::Heuristic(Cell *current, Cell *end)
{
	//Euclidian Distance
	int distX = abs(end->position.x - current->position.x);
	int distY = abs(end->position.y - current->position.y);

	int distance = sqrt(distX * distX + distY * distY);

	return distance;

	//Manhatan Distance 
	//return (abs(current->position.x - end->position.x) + abs(current->position.y - end->position.y));
}

bool Grid::IsSearching()
{
	return this->searching;
}
