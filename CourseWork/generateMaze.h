#pragma once

#include"Header.h"

// ¬озвращает рандомного соседа из вектора соседей 
#define GetRandomNeighbor(neighborsCellMaze) neighborsCellMaze.at(rand() % neighborsCellMaze.size())

t_maze CreateMaze(const int &m, const int &n);
void ClearMaze(t_maze &maze, const int &m, const int &n);
void ClearWayMaze(t_maze &maze, const int &m, const int &n);
t_maze GenerateMaze(const int &m, const int &n);
void WriteMaze(const t_maze &maze, const int &m, const int &n);
void BuildPathMaze(t_maze &maze, t_mapCellMaze &visitedCellMaze, const t_cellMaze &cellFirst, const t_cellMaze &cellSecond);

bool CompasitionCellMaze(const t_cellMaze &cellMaze1, const t_cellMaze &cellMaze2);