#pragma once

#include"Header.h"

t_maze CreateMaze(const int &m, const int &n);
void ClearMaze(t_maze &maze, const int &m, const int &n);
void ClearWayMaze(t_maze &maze, const int &m, const int &n);
t_maze GenerateMaze(const int &m, const int &n);
void WriteMaze(const t_maze &maze, const int &m, const int &n);
void BuildPathMaze(t_maze &maze, const int &m, const int &n, t_mapCellMaze &visitedCellMaze, const t_cellMaze &cellFirst, const t_cellMaze &cellSecond);

bool CompasitionCellMaze(t_cellMaze cellMaze1, t_cellMaze cellMaze2);

t_cellMaze SetSpawnPos(t_maze &maze, const int &m, const int &n);
t_cellMaze SetQuitPos(t_maze &maze, const int &m, const int &n);