#include "generateMaze.h"
#include <iostream>

using namespace std;

// ���������� "������", ���� ������ cellMaze1 � cellMaze2 ������������
bool CompasitionCellMaze(const t_cellMaze &cellMaze1, const t_cellMaze &cellMaze2)
{
    return cellMaze1.first == cellMaze2.first && cellMaze1.second == cellMaze2.second;
}

// ���������� ����� ������� ������ cellMaze � ��������� maze ��������� mxn
int GetCountNeighbors(const t_maze &maze, const int &m, const int &n, const t_cellMaze &cellMaze)
{
    int cntNeighbors = 0;
    t_cellMaze neighbor = {cellMaze.first, cellMaze.second - 1};
    if (!(checkExistenceCell(m, n, neighbor.first, neighbor.second)) || (maze[neighbor.first][neighbor.second] != road))
        cntNeighbors++;

    neighbor = {cellMaze.first, cellMaze.second + 1};
    if (!(checkExistenceCell(m, n, neighbor.first, neighbor.second)) || (maze[neighbor.first][neighbor.second] != road))
        cntNeighbors++;

    neighbor = {cellMaze.first - 1, cellMaze.second};
    if (!(checkExistenceCell(m, n, neighbor.first, neighbor.second)) || (maze[neighbor.first][neighbor.second] != road))
        cntNeighbors++;

    neighbor = {cellMaze.first + 1, cellMaze.second};
    if (!(checkExistenceCell(m, n, neighbor.first, neighbor.second)) || (maze[neighbor.first][neighbor.second] != road))
        cntNeighbors++;

    return cntNeighbors;
}

// ���������� ������� ������� ������ cellMaze � ��������� maze ��������� mxn
t_vecCellMaze GetNeighbors(t_maze &maze, const int &m, const int &n, const t_cellMaze &cellMaze)
{
    maze[cellMaze.first][cellMaze.second] = blank;
    
    t_vecCellMaze neighborsCellMaze;
    t_cellMaze neighbor = {cellMaze.first, cellMaze.second - 1};
    if ((checkExistenceCell(m, n, neighbor.first, neighbor.second)) && (GetCountNeighbors(maze, m, n, neighbor) == 4) &&
        (maze[neighbor.first][neighbor.second] != road))
        neighborsCellMaze.push_back(neighbor);

    neighbor = {cellMaze.first, cellMaze.second + 1};
    if ((checkExistenceCell(m, n, neighbor.first, neighbor.second)) && (GetCountNeighbors(maze, m, n, neighbor) == 4) &&
        (maze[neighbor.first][neighbor.second] != road))
        neighborsCellMaze.push_back(neighbor);

    neighbor = {cellMaze.first - 1, cellMaze.second};
    if ((checkExistenceCell(m, n, neighbor.first, neighbor.second)) && (GetCountNeighbors(maze, m, n, neighbor) == 4) &&
        (maze[neighbor.first][neighbor.second] != road))
        neighborsCellMaze.push_back(neighbor);

    neighbor = {cellMaze.first + 1, cellMaze.second};
    if ((checkExistenceCell(m, n, neighbor.first, neighbor.second)) && (GetCountNeighbors(maze, m, n, neighbor) == 4) &&
        (maze[neighbor.first][neighbor.second] != road))
        neighborsCellMaze.push_back(neighbor);

    maze[cellMaze.first][cellMaze.second] = road;

    return neighborsCellMaze;
}

// ��������� ������ ������ cellMaze ������, ��� ��� ����� � ��������� maze ��������� mxn
void GetWallCellMaze(t_maze &maze, const int &m, const int &n, const t_cellMaze &cellMaze)
{
    t_cellMaze neighbor = {cellMaze.first, cellMaze.second - 1};
    if ((checkExistenceCell(m, n, neighbor.first, neighbor.second)) && (maze[neighbor.first][neighbor.second] != road))
        maze[neighbor.first][neighbor.second] = wall;

    neighbor = {cellMaze.first, cellMaze.second + 1};
    if ((checkExistenceCell(m, n, neighbor.first, neighbor.second)) && (maze[neighbor.first][neighbor.second] != road))
        maze[neighbor.first][neighbor.second] = wall;

    neighbor = {cellMaze.first - 1, cellMaze.second};
    if ((checkExistenceCell(m, n, neighbor.first, neighbor.second)) && (maze[neighbor.first][neighbor.second] != road))
        maze[neighbor.first][neighbor.second] = wall;

    neighbor = {cellMaze.first + 1, cellMaze.second};
    if ((checkExistenceCell(m, n, neighbor.first, neighbor.second)) && (maze[neighbor.first][neighbor.second] != road))
        maze[neighbor.first][neighbor.second] = wall;
}

// ���������� ��������� ��������, ����������� ������
t_maze CreateMaze(const int &m, const int &n)
{
    t_maze maze(m, t_rowMaze(n));
    ClearMaze(maze, m, n);

    return maze;
}

// ������� �������� �� �������� ���� � ������ ��� ������ ������
void ClearWayMaze(t_maze &maze, const int &m, const int &n)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (maze[i][j] == way)
                maze[i][j] = road;
}

// ������� �������� ��������� � ��������� ��� ��������
void ClearMaze(t_maze &maze, const int &m, const int &n)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            maze[i][j] = road;
}

// ������� �������� ��������� � ��������� ��� ��������
void FillMazeBlank(t_maze &maze, const int &m, const int &n)
{
    maze.resize(m, t_rowMaze(n, road));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            maze[i][j] = blank;
}

// ���������� ��������������� �������� maze ��������� mxn
t_maze GenerateMaze(const int &m, const int &n)
{
    t_maze maze = CreateMaze(m, n);
    FillMazeBlank(maze, m, n);
    stack<t_cellMaze> stackCellMaze;

    t_vecCellMaze neighborsCellMaze;
    t_cellMaze cellMaze = {0, 0};
    maze[cellMaze.first][cellMaze.second] = road;

    do
    {
        neighborsCellMaze = GetNeighbors(maze, m, n, cellMaze);
        if (!neighborsCellMaze.empty())
        {
            stackCellMaze.push(cellMaze);

            GetWallCellMaze(maze, m, n, cellMaze);
            cellMaze = GetRandomNeighbor(neighborsCellMaze);
            maze[cellMaze.first][cellMaze.second] = road;
        }
        else
        {
            cellMaze = stackCellMaze.top();
            stackCellMaze.pop();
        }

        neighborsCellMaze.clear();
    }
    while (!((stackCellMaze.empty()) && (cellMaze.first == 0) && (cellMaze.second == 0)));

    return maze;
}

// ���������� ���� ����� cellMazeFirst � cellMazeSecond � ��������� maze ��������� mxn
void BuildPathMaze(t_maze &maze, t_mapCellMaze &visitedCellMaze, const t_cellMaze &cellMazeFirst, const t_cellMaze &cellMazeSecond)
{
    t_cellMaze wayCellMaze = cellMazeSecond;
    while (wayCellMaze != cellMazeFirst && visitedCellMaze.find(wayCellMaze) != visitedCellMaze.end())
    {
        wayCellMaze = visitedCellMaze[wayCellMaze];
        if (wayCellMaze != cellMazeFirst)
            maze[wayCellMaze.first][wayCellMaze.second] = way;
    }
}