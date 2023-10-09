#pragma once
class Node
{
public:
	bool walkable;
	int nodeX;
	int nodeY;

	int gCost;
	int hCost;
	Node* parent;

	Node(bool _walkable, int _nodeX, int _nodeY);
	int fCost();
};

