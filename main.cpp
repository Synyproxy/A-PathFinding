#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const int cols = 5;
const int rows = 5;
const int width = 500;
const int height = 500;
const int w = width / rows;
const int h = height / cols;

sf::RenderWindow window(sf::VideoMode(width, height), "A* Path Finding!");

class Spot
{
public:
	Spot(int x, int y): f{0}, g{0}, h{0}, position(sf::Vector2f(x , y)) {}
	~Spot(){}
	void addNeighbors(std::vector<Spot> *grid)
	{
		//Index Convertion between vector index to grid index
		int i;

		if(position.x < cols -1)
		{
			i = (((position.x + 1) * cols) + 1) + (((position.y)* rows) + 1);
			this->neighbors.push_back(*grid[i].data());
		}

		if(position.x > 0)
		{
			i = (((position.x - 1) * cols) + 1) + (((position.y)* rows) + 1);
			this->neighbors.push_back(*grid[i].data());
		}
		
		if (position.y < rows - 1) 
		{
			i = (((position.x) * cols) + 1) + (((position.y + 1)* rows) + 1);
			this->neighbors.push_back(*grid[i].data());
		}

		if (position.y > 0)
		{
			i = (((position.x) * cols) + 1) + (((position.y - 1)* rows) + 1);
			this->neighbors.push_back(*grid[i].data());
		}
	}

	float f;
	float g;
	float h;
	sf::Vector2f position;
	std::vector<Spot> neighbors;
};

void fillGrid(std::vector<Spot> *grid)
{
	for(int i = 0; i < cols; ++i)
	{
		for(int j = 0; j < rows; ++j)
		{
			Spot newSpot(i, j);
			grid->push_back(newSpot);
		}
	}
}

void fillGridNeighbours(std::vector<Spot> *grid)
{
	auto it = grid->begin();

	while(it != grid->end())
	{
		it->addNeighbors(grid);
		++it;
	}
}

void printGrid(std::vector<Spot> *grid)
{
	auto it = grid->begin();

	for (int i = 0; i < cols; ++i)
	{
		for (int j = 0; j < rows; ++j)
		{
			std::cout << "Spot " << it->position.x << "/" << it->position.y << std::endl;
			++it;
		}
	}
}

void renderSet(std::vector<Spot> *grid, sf::Color color)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(w - 1, h - 1));
	rect.setFillColor(color);
	auto it = grid->begin();

	while(it != grid->end())
	{
		rect.setPosition(sf::Vector2f(w * it->position.x, h * it->position.y));
		window.draw(rect);
		++it;
	}
}

int main(int argc, char* argv[])
{
	//Created a List of nodes
	std::vector<Spot> *grid = new std::vector<Spot>();
	fillGrid(grid);
	fillGridNeighbours(grid);

	//Open and Closed Set
	std::vector<Spot> *openSet = new std::vector<Spot>();
	std::vector<Spot> *closedSet = new std::vector<Spot>();

	//Start and End point
	Spot start(0, 0);
	Spot end(cols - 1, rows - 1);

	//Adding Start to openSet
	openSet->push_back(start);


	printGrid(grid);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (!openSet->empty())
		{
			//We can keep going
			int winner = 0;
			int i = 0;
			int openSetSize = openSet->size();

			while (i < openSetSize)
			{
				if (openSet[i].data()->f < openSet[winner].data()->f)
					winner = i;
				++i;
			}
			
			Spot current(openSet[winner].data()->position.x, openSet[winner].data()->position.y);

			if(current.position.x == end.position.x
				&& current.position.y == end.position.y)
			{
				std::cout << "Done !" << std::endl;
			}

			//openSet.remove(current);
			openSet->erase(openSet->begin() + winner);
			closedSet->push_back(current);
		}
		else
		{
			//No solution
		}

		window.clear();

		renderSet(grid, sf::Color::White);
		
		if (!closedSet->empty())
			//renderSet(closedSet, sf::Color::Red);

		if (!openSet->empty())
			renderSet(openSet, sf::Color::Green);

		window.display();
	}

	return 0;
}