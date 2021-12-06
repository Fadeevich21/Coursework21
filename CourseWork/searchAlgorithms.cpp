#include "searchAlgorithms.h"
#include <queue>
#include <cmath>

// Элемент лабиринта - дорога лабиринта
#define IsRoad(elMaze) (elMaze == road)

// Элемент лабиринта - вход в лабиринт
#define IsSpawnPos(elMaze) (elMaze == spawn)

// Элемент лабиринта - выход из лабиринта
#define IsQuitPos(elMaze) (elMaze == quit)

// Манхеттенское расстояние
#define ManhattanDistance(cellMaze1, cellMaze2) (2 * (abs((cellMaze1.first) - (cellMaze2.first)) + abs((cellMaze1.second) - (cellMaze2.second))))

// Евклидово расстояние
#define EuclideanMetric(cellMaze1, cellMaze2) (pow((cellMaze1.first) - (cellMaze2.first), 2) + pow((cellMaze1.second) - (cellMaze2.second), 2))

// Расстояние Чебышёва
#define ChebyshevDistance(cellMaze1, cellMaze2)(MAX2(abs((cellMaze1.first) - (cellMaze2.first)), abs((cellMaze1.first) - (cellMaze2.first))))

// Возвращает минимальный ключ словаря _map
#define MinKeyMap(_map)(min_element(_map.begin(), _map.end(), [](const auto &a, const auto &b){return a.second < b.second; })->first)

// Получение словаря клеток лабиринта maze
t_mapNeighborsCellMaze GetMapNeighborsMaze(const t_maze &maze, const int &m, const int &n)
{
    t_mapNeighborsCellMaze mapNeighborsMaze;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            if (checkExistenceCell(m, n, i + 1, j) &&
                (IsRoad(maze[i + 1][j]) || IsSpawnPos(maze[i + 1][j]) || IsQuitPos(maze[i + 1][j])))
                mapNeighborsMaze[{i, j}].push_back({i + 1, j});

            if (checkExistenceCell(m, n, i, j + 1) &&
                (IsRoad(maze[i][j + 1]) || IsSpawnPos(maze[i][j + 1]) || IsQuitPos(maze[i][j + 1])))
                mapNeighborsMaze[{i, j}].push_back({i, j + 1});

            if (checkExistenceCell(m, n, i - 1, j) &&
                (IsRoad(maze[i - 1][j]) || IsSpawnPos(maze[i - 1][j]) || IsQuitPos(maze[i - 1][j])))
                mapNeighborsMaze[{i, j}].push_back({i - 1, j});

            if (checkExistenceCell(m, n, i, j - 1) &&
                (IsRoad(maze[i][j - 1]) || IsSpawnPos(maze[i][j - 1]) || IsQuitPos(maze[i][j - 1])))
                mapNeighborsMaze[{i, j}].push_back({i, j - 1});
        }

    return mapNeighborsMaze;
}

// Итеративный алгоритм поиска в ширину в лабиринте maze размером mxn, где spawnPos - начальная точка, quitPos - конечная точка
t_mapCellMaze BFS(const t_maze &maze, const int &m, const int &n, const t_cellMaze &spawnPos,
                  const t_cellMaze &quitPos)
{
    t_mapNeighborsCellMaze mapNeighborsCellMaze = GetMapNeighborsMaze(maze, m, n);

    queue<t_cellMaze> searchQueue;
    searchQueue.push(spawnPos);

    t_cellMaze checkCellMaze;
    t_mapCellMaze mapVisitedCellMaze;
    mapVisitedCellMaze[spawnPos] = spawnPos;
    while (!searchQueue.empty())
    {
        checkCellMaze = searchQueue.front();
        searchQueue.pop();

        if (checkCellMaze == quitPos)
            break;

        for (t_cellMaze cellMaze : mapNeighborsCellMaze[checkCellMaze])
            if (mapVisitedCellMaze.find(cellMaze) == mapVisitedCellMaze.end())
            {
                searchQueue.push(cellMaze);
                mapVisitedCellMaze[cellMaze] = checkCellMaze;
            }
    }

    return mapVisitedCellMaze;
}

// Итеративный алгоритм поиска в глубину в лабиринте maze размером mxn, где spawnPos - начальная точка, quitPos - конечная точка
t_mapCellMaze DFS_iterative(const t_maze &maze, const int &m, const int &n, const t_cellMaze &spawnPos,
                            const t_cellMaze &quitPos)
{
    t_mapNeighborsCellMaze mapNeighborsCellMaze = GetMapNeighborsMaze(maze, m, n);

    stack<t_cellMaze> searchStack;
    searchStack.push(spawnPos);

    t_cellMaze checkCellMaze;
    t_mapCellMaze mapVisitedCellMaze;
    mapVisitedCellMaze[spawnPos] = spawnPos;
    while (!searchStack.empty())
    {
        checkCellMaze = searchStack.top();
        searchStack.pop();
        
        if (checkCellMaze == quitPos)
            break;
        
        for (t_cellMaze cellMaze : mapNeighborsCellMaze[checkCellMaze])
        {
            if (mapVisitedCellMaze.find(cellMaze) == mapVisitedCellMaze.end())
            {
                searchStack.push(cellMaze);
                mapVisitedCellMaze[cellMaze] = checkCellMaze;
            }
        }
    }

    return mapVisitedCellMaze;
}

// Рекурсивный алгоритм проверки, является ли клетка лабиринта его концом
bool rec_DFS(t_mapCellMaze &mapVisitedCellMaze, t_mapNeighborsCellMaze &mapNeighborsCellMaze,
             const t_cellMaze &quitPos, const t_cellMaze &cellMaze)
{
    if (cellMaze == quitPos)
        return true;

/*
        stack<t_cellMaze> searchStack;
        for (t_cellMaze cellMaze1 : mapNeighborsCellMaze[cellMaze])
            if (mapVisitedCellMaze.find(cellMaze1) == mapVisitedCellMaze.end())
            {
                searchStack.push(cellMaze1);
                mapVisitedCellMaze[cellMaze1] = cellMaze;
            }

        while (!searchStack.empty())
        {
            t_cellMaze checkCellMaze = searchStack.top();
            searchStack.pop();
            if (rec_DFS(mapVisitedCellMaze, mapNeighborsCellMaze, quitPos, checkCellMaze))
                return true;
        }
*/

        for (t_cellMaze checkCellMaze : mapNeighborsCellMaze[cellMaze])
            if (mapVisitedCellMaze.find(checkCellMaze) == mapVisitedCellMaze.end())
            {
                mapVisitedCellMaze[checkCellMaze] = cellMaze;
                if (rec_DFS(mapVisitedCellMaze, mapNeighborsCellMaze, quitPos, checkCellMaze))
                    return true;
            }

        return false;
}

// Рекурсивный алгоритм поиска в глубину в лабиринте maze размером mxn, где spawnPos - начальная точка, quitPos - конечная точка
t_mapCellMaze DFS_recursive(const t_maze &maze, const int &m, const int &n, const t_cellMaze &spawnPos,
                            const t_cellMaze &quitPos)
{
    t_mapCellMaze mapVisitedCellMaze;
    mapVisitedCellMaze[spawnPos] = spawnPos;
    t_mapNeighborsCellMaze mapNeighborsCellMaze = GetMapNeighborsMaze(maze, m, n);
    rec_DFS(mapVisitedCellMaze, mapNeighborsCellMaze, quitPos, spawnPos);

    return mapVisitedCellMaze;
}

// Поиск A Star (итеративный)
t_mapCellMaze AStar(const t_maze &maze, const int &m, const int &n,
                    const t_cellMaze &spawnPos, const t_cellMaze &quitPos)
{
    t_mapCellMaze mapVisitedCellMaze;
    t_mapNeighborsCellMaze mapNeighborsCellMaze = GetMapNeighborsMaze(maze, m, n);
    t_weightCellMaze weightCellMaze;
    t_costCellMaze costCellMaze;

    costCellMaze[spawnPos] = 0;
    weightCellMaze[spawnPos] = costCellMaze[spawnPos] + ManhattanDistance(spawnPos, quitPos);
    mapVisitedCellMaze[spawnPos] = spawnPos;

    t_cellMaze current;
    while (!weightCellMaze.empty())
    {
        current = MinKeyMap(weightCellMaze);
        weightCellMaze.erase(current);

        if (current == quitPos)
            break;

        for (t_cellMaze cellMaze : mapNeighborsCellMaze[current])
        {
            if (mapVisitedCellMaze.find(cellMaze) == mapVisitedCellMaze.end())
            {
                costCellMaze[cellMaze] = costCellMaze[current] + 1;
                weightCellMaze[cellMaze] = costCellMaze[cellMaze] + ManhattanDistance(cellMaze, quitPos);
                mapVisitedCellMaze[cellMaze] = current;
            }
        }
    }

    return mapVisitedCellMaze;
}

// Алгоритм Дейкстры
t_mapCellMaze Dijkstra(const t_maze &maze, const int &m, const int &n,
                       const t_cellMaze &spawnPos, const t_cellMaze &quitPos)
{
    t_mapCellMaze mapVisitedCellMaze;
    t_mapNeighborsCellMaze mapNeighborsCellMaze = GetMapNeighborsMaze(maze, m, n);
    t_weightCellMaze weightCellMaze;
    t_costCellMaze costCellMaze;

    costCellMaze[spawnPos] = 0;
    weightCellMaze[spawnPos] = costCellMaze[spawnPos];
    mapVisitedCellMaze[spawnPos] = spawnPos;

    t_cellMaze current;
    while (!weightCellMaze.empty())
    {
        current = MinKeyMap(weightCellMaze);
        weightCellMaze.erase(current);

        if (current == quitPos)
            break;

        for (t_cellMaze cellMaze : mapNeighborsCellMaze[current])
            if (mapVisitedCellMaze.find(cellMaze) == mapVisitedCellMaze.end())
            {
                costCellMaze[cellMaze] = costCellMaze[current] + 1;
                weightCellMaze[cellMaze] = costCellMaze[cellMaze];
                mapVisitedCellMaze[cellMaze] = current;
            }
    }

    return mapVisitedCellMaze;
}

   // Поиск по первому наилучшему совпадению (лучший — первый)
t_mapCellMaze GBS(const t_maze &maze, const int &m, const int &n,
                  const t_cellMaze &spawnPos, const t_cellMaze &quitPos)
{
    t_mapCellMaze mapVisitedCellMaze;
    t_mapNeighborsCellMaze mapNeighborsCellMaze = GetMapNeighborsMaze(maze, m, n);
    t_weightCellMaze weightCellMaze;

    weightCellMaze[spawnPos] = ManhattanDistance(spawnPos, quitPos);
    mapVisitedCellMaze[spawnPos] = spawnPos;

    t_cellMaze current;
    while (!weightCellMaze.empty())
    {
        current = MinKeyMap(weightCellMaze);
        weightCellMaze.erase(current);

        if (current == quitPos)
            break;

        for (t_cellMaze cellMaze : mapNeighborsCellMaze[current])
            if (mapVisitedCellMaze.find(cellMaze) == mapVisitedCellMaze.end())
            {
                weightCellMaze[cellMaze] = ManhattanDistance(cellMaze, quitPos);
                mapVisitedCellMaze[cellMaze] = current;
            }
    }

    return mapVisitedCellMaze;
}