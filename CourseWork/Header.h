#pragma once

#include <vector>
#include <map>
#include <stack>

using namespace std;

// Максимум из 2-ух элементов
#define MAX2(a, b)((a) > (b) ? (a) : (b))

// Возвращает "истина", если клетка cellMaze расположена в границах mxn
#define checkExistenceCell(m, n, i, j) (((i) >= 0) && ((i) < (m)) && ((j) >= 0) && ((j) < (n)))

#define M 20      /* Число строк лабиринта */
#define N 20      /* Число столбов лабиринта */

#define NONE_CELL_MAZE {-1, -1}

// Значения, которые могут принимать клетки лабиринта 
enum t_elMaze
{
    blank, road, wall, spawn, quit, way
};

// Клетка лабиринта
typedef pair<int, int> t_cellMaze;

// Вектор клеток лабиринта
typedef vector<t_cellMaze> t_vecCellMaze;

// Словарь:
// Ключ: клетка лабиринта
// Значение: клетка лабиринта
typedef map<t_cellMaze, t_cellMaze> t_mapCellMaze;

// Строка лабиринта
typedef vector<t_elMaze> t_rowMaze;

// Лабиринт
typedef vector<t_rowMaze> t_maze;

// Словарь свобоных соседних клеток определённой клетки:
// Ключ: клетка лабиринта
// Значение: вектор клеток лабиринта
typedef map<t_cellMaze, t_vecCellMaze> t_mapNeighborsCellMaze;
