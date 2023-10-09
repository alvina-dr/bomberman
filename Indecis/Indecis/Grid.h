#pragma once
#include "Grid.h";
#include "Node.h"
#include <array>
#include <stack>

class Transform;

class Grid
{
public:
	Grid(int gameGridWidth, int gameGridHeight)	;
	void ReadAndAddFileToGrid(std::string fileName);
	int GetGridCoordinates(int x, int y);
	int GetRandomFloorCoordinates();

	int GetXFromGridApprox(int gridCoord);
	int GetYFromGridApprox(int gridCoord);

	bool HasTransformHere(int x, int y, std::vector<Transform*>& _entityList);
	bool HasCollision(int _x, int _y, std::vector<Transform*>& _entityList);
	bool HasCollisionWallOnly(int _x, int _y);

	int *grid;
	int gameGridSize;

	//Were private before
	const int gameGridWidth = 10;
	const int gameGridHeight = 10;

	//Pathfinding related stuff
	float nodeRadius;
	float nodeDiameter;
	Node nodeGrid[];

	void CreateNodeGrid();
	std::stack<Node> GetNeighbors(Node node);

private:
	
};

