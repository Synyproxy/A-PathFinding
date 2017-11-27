# A* Pathfinding

## Context 
While I was working on a top down shooter bonus side project for school, I had random obstacles spawning on the field. Enemies had to walk to the player following the shortest path and avoiding obstacles. Although since the map is small it would have been possible by only doing some basic monkey checks. I took this opportunity to dive into A* algorithm and strengthen my coding skills. This project uses SFML graphics library to display the maze and path.

## Specifications
* Using C++.
* A square map is generated with random obstacles.
* An optimal path should be found and output.

## How to run the game
Visual Studio requeried.
* Download the project.
* Open the SpaceInvaders.sln file.
* Change architecture from x64 to x32.
* Run and enjoy.

## Key take aways
* Changing the neighbours list of nodes from being copied to a pointer increased DRAMATICALLY performance.
* Making a modular piece of code that could be integrated withing a larger context.

## What could be improved
Since I have worked with std::vector to store the path nodes and their neighbours, I have done a monkey trick to convert the actual coordinates of a node to an index in the vector structure. While this works for square grids, it doesn't work for rectangular grids.

## Special thanks 
A special thanks goes to the [coding train](https://www.youtube.com/watch?v=aKYlikFAV4k&t=2570s). I have followed his video for implementation idead. PLease note that he uses Javascript.

## Contact
If you have any questions please feel free to contact me on s.raouf@student.isartdigital.com
