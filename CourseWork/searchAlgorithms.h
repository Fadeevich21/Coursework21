#pragma once

#include "Header.h"

// Поиск в ширину (итеративный)
t_mapCellMaze BFS(const t_maze &maze, const int &m, const int &n,
                  const t_cellMaze &spawnPos, const t_cellMaze &quitPos);

// Поиск в глубину (итеративный)
t_mapCellMaze DFS_iterative(const t_maze &maze, const int &m, const int &n,
                            const t_cellMaze &spawnPos, const t_cellMaze &quitPos);

// Поиск в глубину (рекурсивный)
t_mapCellMaze DFS_recursive(const t_maze &maze, const int &m, const int &n,
                            const t_cellMaze &spawnPos, const t_cellMaze &quitPos);

// СД типа "Словарь", где "ключ" - клетка лабиринта, а "значение" - вес данной клетки
typedef map<t_cellMaze, int> t_weightCellMaze;

// СД типа "Словарь", где "ключ" - клетка лабиринта, а "значение" - цена данной клетки
typedef map<t_cellMaze, int> t_costCellMaze;

// Поиск A Star (итеративный)
t_mapCellMaze AStar(const t_maze &maze, const int &m, const int &n,
                            const t_cellMaze &spawnPos, const t_cellMaze &quitPos);

// Алгоритм Дейкстры
t_mapCellMaze Dijkstra(const t_maze &maze, const int &m, const int &n,
                    const t_cellMaze &spawnPos, const t_cellMaze &quitPos);

// Поиск по первому наилучшему совпадению (лучший — первый)
t_mapCellMaze GBS(const t_maze &maze, const int &m, const int &n,
                       const t_cellMaze &spawnPos, const t_cellMaze &quitPos);