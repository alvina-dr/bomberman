#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Definitions.h"
#include "Grid.h"
#include "Transform.h"

Grid::Grid(int gameGridWidth, int gameGridHeight) : gameGridWidth(gameGridWidth), gameGridHeight(gameGridHeight), gameGridSize(0) {
    gameGridSize = gameGridWidth * gameGridHeight;
    grid = new int[gameGridSize];
    nodeRadius = 2;
    nodeDiameter = nodeRadius * 2;
}

void Grid::ReadAndAddFileToGrid(std::string fileName) {
    //Recuperer le contenu du fichier, regarde quel type d'objet c'est et affiche le char
    //dans le buffer en consequence
    std::ifstream input;
    input.open(fileName);
    char value;

    int Width = gameGridWidth;
    int Height = gameGridHeight;

    for (int i = 0; i < gameGridHeight; i++) {
        for (int j = 0; j < gameGridWidth; j++) {
            if (input.fail()) break;
            input >> value;
            int gridPos = (i * gameGridWidth) + j;
            grid[gridPos] = int(value - '0');
        }
    }
    input.close();
}

int Grid::GetGridCoordinates(int x, int y) {
    int coordinates = y * gameGridWidth + x;
    return coordinates;
}

int Grid::GetRandomFloorCoordinates() {
    int coordinates;
    int x;
    int y;
    do {
        x = rand() % gameGridHeight;
        y = rand() % gameGridWidth;
        coordinates = y * gameGridWidth + x;
    } while (HasCollisionWallOnly(x,y));
    return coordinates;
}

int Grid::GetXFromGridApprox(int gridCoord) {
    int x;
    x = gridCoord - gameGridWidth;
    return x;
}

int Grid::GetYFromGridApprox(int gridCoord) {
    int y;
    y = gridCoord / gameGridWidth;
    return y;
}

bool Grid::HasTransformHere(int _x, int _y, std::vector<Transform*>& _entityList) {
    for (int i = 0; i < _entityList.size(); i++)
    {
        if (_entityList[i]->position.x == _x && _entityList[i]->position.y == _y) {
            return true;
        }
    }
    return false;
}

bool Grid::HasCollision(int _x, int _y, std::vector<Transform*>& _entityList) {
    int nextStep = GetGridCoordinates(_x, _y);
    if (grid[nextStep] == 0) { // si il n'y a pas de mur
        if (HasTransformHere(_x, _y, _entityList)) // si il y a un transform
            return true;
        else return false; // si il n'y a pas de transform
    }
    else // si il y a un mur
        return true;
}

bool Grid::HasCollisionWallOnly(int _x, int _y) {
    int nextStep = GetGridCoordinates(_x, _y);
    if (grid[nextStep] == 1) {
        return true;
    }
    else {
        return false;
    }
}

void Grid::CreateNodeGrid() {
    for (int x = 0; x < gameGridHeight; x++) {
        for (int y = 0; y < gameGridWidth; y++) {
            int gridCoord = GetGridCoordinates(x, y);
            bool walkable = !(Grid::HasCollisionWallOnly(x,y));
            nodeGrid[gridCoord] = (Node(walkable, x, y));
        }
    }
}

std::stack<Node> Grid::GetNeighbors(Node node) {
    std::stack<Node> neighbours;

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0)
                continue;

            int checkX = node.nodeX + x;
            int checkY = node.nodeY + y;

            if (checkX >= 0 && checkX < gameGridHeight && checkY >= 0 && checkY < gameGridWidth) {
                int gridCoord = GetGridCoordinates(checkX, checkY);
                neighbours.push(nodeGrid[gridCoord]);
            }
        }
    }

    return neighbours;
}
