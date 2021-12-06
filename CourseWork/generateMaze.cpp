#include "generateMaze.h"
#include <iostream>

using namespace std;

bool CompasitionCellMaze(t_cellMaze cellMaze1, t_cellMaze cellMaze2)
{
    return cellMaze1.first == cellMaze2.first && cellMaze1.second == cellMaze2.second;
}

// ������������� ������ ������ ���������
t_cellMaze SetSpawnPos(t_maze &maze, const int &m, const int &n)
{
    t_cellMaze spawnPos; /* ������� ������ ������ ������ ��������� */
    cout << "������� ���������� ������, � ������� ����� ���������� ������ ���������. ������� ���������: " << m
        << 'x' << n << endl;
    cin >> spawnPos.first >> spawnPos.second;
    spawnPos.first--;
    spawnPos.second--;

    while (!checkExistenceCell(m, n, spawnPos.first, spawnPos.second) || maze[spawnPos.first][spawnPos.second] != road)
    {
        cout << "���� � ������������ � ����� ������������ �� ����� ���� ������. ����������, ������� ������ ����������" << endl;
        cin >> spawnPos.first >> spawnPos.second;
        spawnPos.first--;
        spawnPos.second--;
    }

    maze[spawnPos.first][spawnPos.second] = spawn;

    return spawnPos;
}

// ������������� ����� ������ ���������
t_cellMaze SetQuitPos(t_maze &maze, const int &m, const int &n)
{
    t_cellMaze quitPos; /* ������� ������ ����� ������ ��������� */
    cout << "������� ���������� ������, � ������� ����� ���������� ����� ���������. ������� ���������: " << m << 'x'
        << n << endl;
    cin >> quitPos.first >> quitPos.second;
    quitPos.first--;
    quitPos.second--;

    while (!checkExistenceCell(m, n, quitPos.first, quitPos.second) || maze[quitPos.first][quitPos.second] != road)
    {
        cout << "���� � ������������ � ����� ������������ �� ����� ���� ������. ����������, ������� ������ ����������" << endl;
        cin >> quitPos.first >> quitPos.second;
        quitPos.first--;
        quitPos.second--;
    }

    maze[quitPos.first][quitPos.second] = quit;

    return quitPos;
}

// ���������� ����� ������� ������ cellMaze � ��������� maze ��������� mxn
int GetCountNeighbors(const t_maze &maze, const int &m, const int &n, const t_cellMaze &cellMaze)
{
    t_vecCellMaze neighborsCellMaze;
    int cntNeighbors = 0;

    t_cellMaze leftNeighbor = {cellMaze.first, cellMaze.second - 1};
    if (!(checkExistenceCell(m, n, leftNeighbor.first, leftNeighbor.second)) || (maze[leftNeighbor.first][leftNeighbor.second] != road))
    {
        cntNeighbors++;
    }

    t_cellMaze rightNeighbor = {cellMaze.first, cellMaze.second + 1};
    if (!(checkExistenceCell(m, n, rightNeighbor.first, rightNeighbor.second)) || (maze[rightNeighbor.first][rightNeighbor.second] != road))
    {
        cntNeighbors++;
    }

    t_cellMaze topNeighbor = {cellMaze.first - 1, cellMaze.second};
    if (!(checkExistenceCell(m, n, topNeighbor.first, topNeighbor.second)) || (maze[topNeighbor.first][topNeighbor.second] != road))
    {
        cntNeighbors++;
    }

    t_cellMaze downNeighbor = {cellMaze.first + 1, cellMaze.second};
    if (!(checkExistenceCell(m, n, downNeighbor.first, downNeighbor.second)) || (maze[downNeighbor.first][downNeighbor.second] != road))
    {
        cntNeighbors++;
    }

    return cntNeighbors;
}

// ���������� ������� ������� ������ cellMaze � ��������� maze ��������� mxn
t_vecCellMaze GetNeighbors(t_maze &maze, const int &m, const int &n, const t_cellMaze &cellMaze)
{
    t_vecCellMaze neighborsCellMaze;

    maze[cellMaze.first][cellMaze.second] = blank;

    t_cellMaze leftNeighbor = {cellMaze.first, cellMaze.second - 1};
    if ((checkExistenceCell(m, n, leftNeighbor.first, leftNeighbor.second)) && (GetCountNeighbors(maze, m, n, leftNeighbor) == 4) &&
        (maze[leftNeighbor.first][leftNeighbor.second] != road))
    {
        neighborsCellMaze.push_back(leftNeighbor);
    }

    t_cellMaze rightNeighbor = {cellMaze.first, cellMaze.second + 1};
    if ((checkExistenceCell(m, n, rightNeighbor.first, rightNeighbor.second)) && (GetCountNeighbors(maze, m, n, rightNeighbor) == 4) &&
        (maze[rightNeighbor.first][rightNeighbor.second] != road))
    {
        neighborsCellMaze.push_back(rightNeighbor);
    }

    t_cellMaze topNeighbor = {cellMaze.first - 1, cellMaze.second};
    if ((checkExistenceCell(m, n, topNeighbor.first, topNeighbor.second)) && (GetCountNeighbors(maze, m, n, topNeighbor) == 4) &&
        (maze[topNeighbor.first][topNeighbor.second] != road))
    {
        neighborsCellMaze.push_back(topNeighbor);
    }

    t_cellMaze downNeighbor = {cellMaze.first + 1, cellMaze.second};
    if ((checkExistenceCell(m, n, downNeighbor.first, downNeighbor.second)) && (GetCountNeighbors(maze, m, n, downNeighbor) == 4) &&
        (maze[downNeighbor.first][downNeighbor.second] != road))
    {
        neighborsCellMaze.push_back(downNeighbor);
    }

    maze[cellMaze.first][cellMaze.second] = road;

    return neighborsCellMaze;
}

// ���������� ���������� ������ �� ������� ������� neighborCellMaze
t_cellMaze GetRandomNeighbor(const t_vecCellMaze &neighborsCellMaze)
{
    return neighborsCellMaze.at(rand() % neighborsCellMaze.size());
}

// ��������� ������ ������ cellMaze ������, ��� ��� ����� � ��������� maze ��������� mxn
void GetWallCellMaze(t_maze &maze, const int &m, const int &n, const t_cellMaze &cellMaze)
{
    t_cellMaze leftNeighbor = {cellMaze.first, cellMaze.second - 1};
    if ((checkExistenceCell(m, n, leftNeighbor.first, leftNeighbor.second)) && (maze[leftNeighbor.first][leftNeighbor.second] != road))
    {
        maze[leftNeighbor.first][leftNeighbor.second] = wall;
    }

    t_cellMaze rightNeighbor = {cellMaze.first, cellMaze.second + 1};
    if ((checkExistenceCell(m, n, rightNeighbor.first, rightNeighbor.second)) && (maze[rightNeighbor.first][rightNeighbor.second] != road))
    {
        maze[rightNeighbor.first][rightNeighbor.second] = wall;
    }

    t_cellMaze topNeighbor = {cellMaze.first - 1, cellMaze.second};
    if ((checkExistenceCell(m, n, topNeighbor.first, topNeighbor.second)) && (maze[topNeighbor.first][topNeighbor.second] != road))
    {
        maze[topNeighbor.first][topNeighbor.second] = wall;
    }

    t_cellMaze downNeighbor = {cellMaze.first + 1, cellMaze.second};
    if ((checkExistenceCell(m, n, downNeighbor.first, downNeighbor.second)) && (maze[downNeighbor.first][downNeighbor.second] != road))
    {
        maze[downNeighbor.first][downNeighbor.second] = wall;
    }
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
void BuildPathMaze(t_maze &maze, const int &m, const int &n, t_mapCellMaze &visitedCellMaze, const t_cellMaze &cellMazeFirst, const t_cellMaze &cellMazeSecond)
{
    t_cellMaze wayCellMaze = cellMazeSecond;
    while (wayCellMaze != cellMazeFirst)
    {
        wayCellMaze = visitedCellMaze[wayCellMaze];
        if (wayCellMaze != cellMazeFirst)
            maze[wayCellMaze.first][wayCellMaze.second] = way;
    }
}