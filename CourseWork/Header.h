#pragma once

#include <vector>
#include <map>
#include <stack>

using namespace std;

// �������� �� 2-�� ���������
#define MAX2(a, b)((a) > (b) ? (a) : (b))

// ���������� "������", ���� ������ cellMaze ����������� � �������� mxn
#define checkExistenceCell(m, n, i, j) (((i) >= 0) && ((i) < (m)) && ((j) >= 0) && ((j) < (n)))

#define M 20      /* ����� ����� ��������� */
#define N 20      /* ����� ������� ��������� */

#define NONE_CELL_MAZE {-1, -1}

// ��������, ������� ����� ��������� ������ ���������
enum t_elMaze
{
    blank, road, wall, spawn, quit, way
};

// ������ ���������
typedef pair<int, int> t_cellMaze;

// ������ ������ ���������
typedef vector<t_cellMaze> t_vecCellMaze;

// �������:
// ����: ������ ���������
// ��������: ������ ���������
typedef map<t_cellMaze, t_cellMaze> t_mapCellMaze;

// ������ ���������
typedef vector<t_elMaze> t_rowMaze;

// ��������
typedef vector<t_rowMaze> t_maze;

// ������� �������� �������� ������ ����������� ������:
// ����: ������ ���������
// ��������: ������ ������ ���������
typedef map<t_cellMaze, t_vecCellMaze> t_mapNeighborsCellMaze;
