#pragma once

#include "Header.h"

// ����� � ������ (�����������)
t_mapCellMaze BFS(const t_maze &maze, const int &m, const int &n,
                  const t_cellMaze &spawnPos, const t_cellMaze &quitPos);

// ����� � ������� (�����������)
t_mapCellMaze DFS_iterative(const t_maze &maze, const int &m, const int &n,
                            const t_cellMaze &spawnPos, const t_cellMaze &quitPos);

// ����� � ������� (�����������)
t_mapCellMaze DFS_recursive(const t_maze &maze, const int &m, const int &n,
                            const t_cellMaze &spawnPos, const t_cellMaze &quitPos);

// �� ���� "�������", ��� "����" - ������ ���������, � "��������" - ��� ������ ������
typedef map<t_cellMaze, int> t_weightCellMaze;

// �� ���� "�������", ��� "����" - ������ ���������, � "��������" - ���� ������ ������
typedef map<t_cellMaze, int> t_costCellMaze;

// ����� A Star (�����������)
t_mapCellMaze AStar(const t_maze &maze, const int &m, const int &n,
                            const t_cellMaze &spawnPos, const t_cellMaze &quitPos);

// �������� ��������
t_mapCellMaze Dijkstra(const t_maze &maze, const int &m, const int &n,
                    const t_cellMaze &spawnPos, const t_cellMaze &quitPos);

// ����� �� ������� ���������� ���������� (������ � ������)
t_mapCellMaze GBS(const t_maze &maze, const int &m, const int &n,
                       const t_cellMaze &spawnPos, const t_cellMaze &quitPos);