#include "Node.h"

Node::Node(bool _walkable, int _nodeX, int _nodeY) {
	walkable = _walkable;
	nodeX = _nodeX;
	nodeY = _nodeY;
}

int Node::fCost() {
	return gCost + hCost;
}