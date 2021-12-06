/* TODO:
 *  1. Добавить кнопки для выбора блока: Старт лабиринта, конец лабиринта, стена
 *  2. Добавить список для выбора эвристики
 *  3. Добавить комментарии к коду
 *  4. Проверить алгоритмы на большом кол-ве тестах (сделать симуляцию)
 */


#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <ctime>
#include <algorithm>
#include "Header.h"
#include "searchAlgorithms.h"
#include "generateMaze.h"

// СД типа "Функция поиска выхода из лабиринта"
typedef t_mapCellMaze(*t_searchAlgotithm)(const t_maze &maze, const int &m, const int &n, const t_cellMaze &spawnPos,
                                          const t_cellMaze &quitPos);

t_searchAlgotithm ChoosingSearchAlgorithm(unsigned select);
t_elMaze ChoosingElMaze(unsigned select);

#define CNT_LINE 20
#define CNT_SHAPE 20

#define HEIGHT_COMBOBOX_ALGORITHMS 40
#define HEIGHT_COMBOBOX_EL_MAZE 130

using namespace sf;

typedef struct
{
    RectangleShape _Shape;
    Text _Text;
} _Button;                          /* СД типа "Кнопка" */

typedef struct
{
    vector<_Button> Elements;
    unsigned selectedElement;
    bool showElements;
} ComboBox;                         /* СД типа "Выпадающий список" */

#define WIDTH_MAZE 500
#define HEIGHT_MAZE 500

void Draw(RenderWindow &window, vector<_Button> vecButton, vector<ComboBox> vecComboBox, vector<Text> vecText, t_maze maze);

int main() {
    SetConsoleCP(1251);         /* Кодировка для вывода символов русского алфавита на экран */
    SetConsoleOutputCP(1251);   /* Кодировка для ввода символов русского алфавита с клавиатуры в консоль */
    srand(time(nullptr));       /* Сид рандома */

    int m = M, n = N;
    t_maze maze = CreateMaze(m, n);
    t_cellMaze spawnPos = NONE_CELL_MAZE;
    t_cellMaze quitPos = NONE_CELL_MAZE;

    t_searchAlgotithm searchAlgorithm = BFS;
    t_elMaze elMaze = wall;

    RenderWindow window(VideoMode(750, 500), L"Поиск пути в лабиринте");

    Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        cout << "can't load font" << endl;
    }

    // Кнопка очищения лабиринта
    _Button buttonClear;
    buttonClear._Shape.setSize(Vector2f(100.f, 35.f));
    buttonClear._Shape.setFillColor(Color(185, 185, 185));
    buttonClear._Shape.setPosition(Vector2f(575, 300));

    buttonClear._Text.setFont(font);
    buttonClear._Text.setString("Clear");
    buttonClear._Text.setCharacterSize(20);
    buttonClear._Text.setFillColor(Color::Black);
    buttonClear._Text.setPosition(Vector2f(600, 305));

    // Кнопка генерирования лабиринта
    _Button buttonGenerate;
    buttonGenerate._Shape.setSize(Vector2f(100.f, 35.f));
    buttonGenerate._Shape.setFillColor(Color(185, 185, 185));
    buttonGenerate._Shape.setPosition(Vector2f(575, 350));

    buttonGenerate._Text.setFont(font);
    buttonGenerate._Text.setString("Generate");
    buttonGenerate._Text.setCharacterSize(20);
    buttonGenerate._Text.setFillColor(Color::Black);
    buttonGenerate._Text.setPosition(Vector2f(583, 355));

    // Кнопка поиска пути из лабиринта
    _Button buttonStart;
    buttonStart._Shape.setSize(Vector2f(100.f, 35.f));
    buttonStart._Shape.setFillColor(Color(185, 185, 185));
    buttonStart._Shape.setPosition(Vector2f(575, 400));

    buttonStart._Text.setFont(font);
    buttonStart._Text.setString("Start");
    buttonStart._Text.setCharacterSize(20);
    buttonStart._Text.setFillColor(Color::Black);
    buttonStart._Text.setPosition(Vector2f(603, 405));

    // Вектор кнопок
    vector<_Button> vecButton = {buttonClear, buttonGenerate, buttonStart};

    // Текст для обозначения выпадающего списка VariableAlgorithms
    Text textAlgorithm;
    textAlgorithm.setFont(font);
    textAlgorithm.setCharacterSize(18);
    textAlgorithm.setFillColor(Color::Black);
    textAlgorithm.setString("Algorithm");
    textAlgorithm.setPosition(Vector2f(585, 10));

    // Выпадающий список алгоритмов
    ComboBox VariableAlgorithms;
    VariableAlgorithms.Elements.resize(7);
    VariableAlgorithms.selectedElement = 1;
    VariableAlgorithms.showElements = false;

    for (unsigned i = 0; i < 7; i++)
    {
        VariableAlgorithms.Elements[i]._Shape.setSize(Vector2f(100.f, 35.f));
        VariableAlgorithms.Elements[i]._Shape.setFillColor(Color(185, 185, 185));

        VariableAlgorithms.Elements[i]._Text.setFont(font);
        VariableAlgorithms.Elements[i]._Text.setCharacterSize(20);
        VariableAlgorithms.Elements[i]._Text.setFillColor(Color::Black);
    }
        
    VariableAlgorithms.Elements[0]._Text.setString("BFS");
    VariableAlgorithms.Elements[1]._Text.setString("BFS");
    VariableAlgorithms.Elements[2]._Text.setString("DFS iter");
    VariableAlgorithms.Elements[3]._Text.setString("DFS rec");
    VariableAlgorithms.Elements[4]._Text.setString("A star");
    VariableAlgorithms.Elements[5]._Text.setString("Dijkstra");
    VariableAlgorithms.Elements[6]._Text.setString("GBS");

    for (unsigned i = 0; i < 7; i++)
        VariableAlgorithms.Elements[i]._Shape.setPosition(Vector2f(575, HEIGHT_COMBOBOX_ALGORITHMS));

    VariableAlgorithms.Elements[0]._Text.setPosition(Vector2f(605, HEIGHT_COMBOBOX_ALGORITHMS + 5));
    VariableAlgorithms.Elements[1]._Text.setPosition(Vector2f(605, HEIGHT_COMBOBOX_ALGORITHMS + 40));
    VariableAlgorithms.Elements[2]._Text.setPosition(Vector2f(588, HEIGHT_COMBOBOX_ALGORITHMS + 75));
    VariableAlgorithms.Elements[3]._Text.setPosition(Vector2f(585, HEIGHT_COMBOBOX_ALGORITHMS + 110));
    VariableAlgorithms.Elements[4]._Text.setPosition(Vector2f(598, HEIGHT_COMBOBOX_ALGORITHMS + 145));
    VariableAlgorithms.Elements[5]._Text.setPosition(Vector2f(588, HEIGHT_COMBOBOX_ALGORITHMS + 180));
    VariableAlgorithms.Elements[6]._Text.setPosition(Vector2f(605, HEIGHT_COMBOBOX_ALGORITHMS + 215));

    // Текст для обозначения выпадающего списка VariableElMaze
    Text textElMaze;
    textElMaze.setFont(font);
    textElMaze.setCharacterSize(18);
    textElMaze.setFillColor(Color::Black);
    textElMaze.setString("Element");
    textElMaze.setPosition(Vector2f(590, 100));

    // Выпадающий список алгоритмов
    ComboBox VariableElMaze;
    VariableElMaze.Elements.resize(4);
    VariableElMaze.selectedElement = 1;
    VariableElMaze.showElements = false;

    for (unsigned i = 0; i < 4; i++)
    {
        VariableElMaze.Elements[i]._Shape.setSize(Vector2f(100.f, 35.f));
        VariableElMaze.Elements[i]._Shape.setFillColor(Color(185, 185, 185));

        VariableElMaze.Elements[i]._Text.setFont(font);
        VariableElMaze.Elements[i]._Text.setCharacterSize(20);
        VariableElMaze.Elements[i]._Text.setFillColor(Color::Black);
    }

    VariableElMaze.Elements[0]._Text.setString("Wall");
    VariableElMaze.Elements[1]._Text.setString("Wall");
    VariableElMaze.Elements[2]._Text.setString("Spawn");
    VariableElMaze.Elements[3]._Text.setString("Quit");

    for (unsigned i = 0; i < 4; i++)
        VariableElMaze.Elements[i]._Shape.setPosition(Vector2f(575, HEIGHT_COMBOBOX_EL_MAZE));

    VariableElMaze.Elements[0]._Text.setPosition(Vector2f(605, HEIGHT_COMBOBOX_EL_MAZE + 5));
    VariableElMaze.Elements[1]._Text.setPosition(Vector2f(605, HEIGHT_COMBOBOX_EL_MAZE + 40));
    VariableElMaze.Elements[2]._Text.setPosition(Vector2f(595, HEIGHT_COMBOBOX_EL_MAZE + 75));
    VariableElMaze.Elements[3]._Text.setPosition(Vector2f(605, HEIGHT_COMBOBOX_EL_MAZE + 110));

    // Вектор выпадающих списков
    vector<ComboBox> vecComboBox = {VariableElMaze, VariableAlgorithms};

    // Вектор текстов
    vector<Text> vecText = {textAlgorithm, textElMaze};

    // Главный цикл приложения: выполняется, пока открыто окно
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            bool flag = false;
            switch (event.type)
            {
                case Event::Closed: /* Закрытие окна */
                    window.close();
                    break;

                case Event::MouseButtonPressed: /* Нажата кнопка мыши */
                    // Получение координат мыши в поле
                    Vector2i pixelPos = Mouse::getPosition(window);
                    Vector2f pos = window.mapPixelToCoords(pixelPos);

                    switch (event.mouseButton.button)   /* Нажата ЛКМ или ПКМ */
                    {
                        case Mouse::Left:   /* Нажата ЛКМ */
                            if (pos.x <= WIDTH_MAZE && pos.y <= HEIGHT_MAZE)
                            {
                                cout << "Add cell maze" << endl;

                                int x = pos.x / 25;
                                int y = pos.y / 25;

                                if (elMaze == spawn || elMaze == quit)
                                {
                                    if (elMaze == spawn)
                                    {
                                        if (!CompasitionCellMaze(spawnPos, NONE_CELL_MAZE))
                                            maze[spawnPos.first][spawnPos.second] = road;

                                        spawnPos = {y, x};
                                    }

                                    if (elMaze == quit)
                                    {
                                        if (!CompasitionCellMaze(quitPos, NONE_CELL_MAZE))
                                            maze[quitPos.first][quitPos.second] = road;

                                        quitPos = {y, x};
                                    }
                                }

                                maze[y][x] = elMaze;
                            }

                            // Проверка нажатия ЛКМ на кнопку начала поиска пути выхода из лабиринта
                            else if (buttonStart._Shape.getGlobalBounds().contains(pos.x, pos.y))
                            {
                                cout << "Press to button Start" << endl;

                                if (CompasitionCellMaze(spawnPos, NONE_CELL_MAZE) || CompasitionCellMaze(quitPos, NONE_CELL_MAZE))
                                {
                                    cout << "Error: The start and end points of the maze are not set" << endl;
                                    break;
                                }

                                ClearWayMaze(maze, m, n);

                                clock_t start = clock();
                                t_mapCellMaze visitedCellMaze = searchAlgorithm(maze, m, n, spawnPos, quitPos);
                                clock_t end = clock();

                                BuildPathMaze(maze, m, n, visitedCellMaze, spawnPos, quitPos);
                            }

                            // Проверка нажатия ЛКМ на кнопку генерирования лабиринта
                            else if (buttonGenerate._Shape.getGlobalBounds().contains(pos.x, pos.y))
                            {
                                spawnPos = NONE_CELL_MAZE;
                                quitPos = NONE_CELL_MAZE;

                                cout << "Press to button generate" << endl;
                                maze = GenerateMaze(m, n);
                            }

                            // Проверка нажатия ЛКМ на кнопку очистки лабиринта
                            else if (buttonClear._Shape.getGlobalBounds().contains(pos.x, pos.y))
                            {
                                spawnPos = NONE_CELL_MAZE;
                                quitPos = NONE_CELL_MAZE;

                                cout << "Press to button clear" << endl;
                                ClearMaze(maze, m, n);
                            }

                            // Проверка нажатия ЛКМ на самый главный элемент списка алгоритмов
                            else if (VariableAlgorithms.Elements[0]._Shape.getGlobalBounds().contains(pos.x, pos.y))
                            {
                                VariableElMaze.showElements = false;
                                cout << "Press to Combo box to see variable algorithms" << endl;
                                VariableAlgorithms.showElements = !VariableAlgorithms.showElements;
                            }

                            // Проверка нажатия ЛКМ на список алгоритмов
                            else if (VariableAlgorithms.showElements)
                            {
                                VariableElMaze.showElements = false;

                                flag = false;
                                for (unsigned i = 1; !flag && i < VariableAlgorithms.Elements.size(); i++)
                                    if (VariableAlgorithms.Elements[i]._Shape.getGlobalBounds().contains(pos.x, pos.y))
                                    {
                                        cout << "Press to Combo box variable algorithms" << endl;
                                        flag = true;

                                        VariableAlgorithms.Elements[0]._Text.setString(VariableAlgorithms.Elements[i]._Text.getString());
                                        VariableAlgorithms.Elements[0]._Text.setPosition(VariableAlgorithms.Elements[i]._Text.getPosition().x, VariableAlgorithms.Elements[0]._Text.getPosition().y);
                                        VariableAlgorithms.selectedElement = i;

                                        searchAlgorithm = ChoosingSearchAlgorithm(i);
                                        VariableAlgorithms.showElements = false;
                                    }

                                if (!flag)
                                    VariableAlgorithms.showElements = false;
                            }

                            // Проверка нажатия ЛКМ на самый главный элемент списка блоков
                            else if (VariableElMaze.Elements[0]._Shape.getGlobalBounds().contains(pos.x, pos.y))
                            {
                                VariableAlgorithms.showElements = false;
                                cout << "Press to Combo box to see element size" << endl;
                                VariableElMaze.showElements = !VariableElMaze.showElements;
                            }

                            // Проверка нажатия ЛКМ на список блоков
                            else if (VariableElMaze.showElements)
                            {
                                VariableAlgorithms.showElements = false;
                                flag = false;
                                for (unsigned i = 1; !flag && i < VariableElMaze.Elements.size(); i++)
                                    if (VariableElMaze.Elements[i]._Shape.getGlobalBounds().contains(pos.x, pos.y))
                                    {
                                        cout << "Press to Combo box elements maze" << endl;
                                        flag = true;

                                        VariableElMaze.Elements[0]._Text.setString(VariableElMaze.Elements[i]._Text.getString());
                                        VariableElMaze.Elements[0]._Text.setPosition(VariableElMaze.Elements[i]._Text.getPosition().x, VariableElMaze.Elements[0]._Text.getPosition().y);
                                        VariableElMaze.selectedElement = i;

                                        elMaze = ChoosingElMaze(i);
                                        VariableElMaze.showElements = false;
                                    }

                                if (!flag)
                                    VariableElMaze.showElements = false;
                            }

                            break;

                        case Mouse::Right:  /* Нажата ПКМ */
                            // Очистка определённой клетки лабиринта
                            if (pos.x <= WIDTH_MAZE && pos.y <= HEIGHT_MAZE)
                            {
                                cout << "Clear cell maze" << endl;

                                int x = pos.x / 25;
                                int y = pos.y / 25;

                                if (maze[y][x] == spawn)
                                    spawnPos = NONE_CELL_MAZE;
                                else if (maze[y][x] == quit)
                                    quitPos = NONE_CELL_MAZE;

                                maze[y][x] = road;
                            }

                            if (VariableAlgorithms.showElements)
                                VariableAlgorithms.showElements = false;

                            if (VariableElMaze.showElements)
                                VariableElMaze.showElements = false;

                            break;
                    }
            }
        }

        if (VariableAlgorithms.showElements)
            for (unsigned i = 0; i < 7; i++)
                VariableAlgorithms.Elements[i]._Shape.setPosition(Vector2f(575, HEIGHT_COMBOBOX_ALGORITHMS + 35 * i));
        else
            for (unsigned i = 0; i < 7; i++)
                VariableAlgorithms.Elements[i]._Shape.setPosition(Vector2f(575, HEIGHT_COMBOBOX_ALGORITHMS));

        if (VariableElMaze.showElements)
            for (unsigned i = 0; i < 4; i++)
                VariableElMaze.Elements[i]._Shape.setPosition(Vector2f(575, HEIGHT_COMBOBOX_EL_MAZE  + 35 * i));
        else
            for (unsigned i = 0; i < 4; i++)
                VariableElMaze.Elements[i]._Shape.setPosition(Vector2f(575, HEIGHT_COMBOBOX_EL_MAZE));

        vecComboBox = {VariableElMaze, VariableAlgorithms};

        Draw(window, vecButton, vecComboBox, vecText, maze);
    }

    return 0;
}

// Выводит элементы графического окна
void Draw(RenderWindow &window, vector<_Button> vecButton, vector<ComboBox> vecComboBox, vector<Text> vecText, t_maze maze)
{
    // Создаем квадрат
    RectangleShape shape;
    shape.setSize(Vector2f(25.f, 25.f));

    // Вертикальные линии для вывода лабиринта
    RectangleShape lineWithThicknessVertical;
    lineWithThicknessVertical.setSize(Vector2f(500.f, 2.f));
    lineWithThicknessVertical.setFillColor(Color(202, 207, 210));

    // Горизонтальные линии для вывода лабиринта
    RectangleShape lineWithThicknessHorizontal;
    lineWithThicknessHorizontal.setSize(Vector2f(500.f, 2.f));
    lineWithThicknessHorizontal.setFillColor(Color(202, 207, 210));
    lineWithThicknessHorizontal.setRotation(90.f);

    // Установка цвета фона
    window.clear(Color(255, 255, 255, 0));

    for (unsigned i = 0; i < vecText.size(); i++)
        window.draw(vecText[i]);

    Color col;
    for (int y = 0; y < M; y++)
    {
        for (int x = 0; x < N; x++)
        {
            shape.setPosition(y * 25, x * 25);

            switch (maze[x][y])
            {
                case blank:
                    col = Color::White;
                    break;
                case road:
                    col = Color::White;
                    break;
                case wall:
                    col = Color(46, 64, 83);
                    break;
                case spawn:
                    col = Color(203, 67, 53);
                    break;
                case quit:
                    col = Color(0, 153, 255);
                    break;
                case way:
                    col = Color(26, 188, 156);
                    break;
                default:
                    col = Color(46, 64, 83);
                    break;
            }

            shape.setFillColor(col);
            window.draw(shape);
        }
    }

    for (int i = 0; i <= CNT_LINE; i++)
    {
        lineWithThicknessVertical.setPosition(0, i * 25);
        window.draw(lineWithThicknessVertical);

        lineWithThicknessHorizontal.setPosition(i * 25, 0);
        window.draw(lineWithThicknessHorizontal);
    }

    for (unsigned i = 0; i < vecButton.size(); i++)
    {
        window.draw(vecButton[i]._Shape);
        window.draw(vecButton[i]._Text);
    }

    for (unsigned i = 0; i < vecComboBox.size(); i++)
    {
        if (vecComboBox[i].showElements)
        {
            for (unsigned j = 0; j < vecComboBox[i].Elements.size(); j++)
            {
                window.draw(vecComboBox[i].Elements[j]._Shape);
                window.draw(vecComboBox[i].Elements[j]._Text);
                
                // Линия для разграничений элементов выпадающего списка
                RectangleShape lineCombobox;
                lineCombobox.setSize(Vector2f(100.f, 2.f));
                lineCombobox.setFillColor(Color(41, 41, 35, 100));
                
                if (j != 0)
                {
                    lineCombobox.setPosition(vecComboBox[i].Elements[j]._Shape.getPosition());
                    window.draw(lineCombobox);
                }
            }
        }
        else
        {
            window.draw(vecComboBox[i].Elements[0]._Shape);
            window.draw(vecComboBox[i].Elements[0]._Text);
        }
    }
    
    window.display();
}

// Выбор алгоритма поиска
t_searchAlgotithm ChoosingSearchAlgorithm(unsigned select) {
    switch (select)
    {
        case 1:
            return BFS;
        case 2:
            return DFS_iterative;
        case 3:
            return DFS_recursive;
        case 4:
            return AStar;
        case 5:
            return Dijkstra;
        case 6:
            return GBS;
        default:
            return nullptr;
    }
}

t_elMaze ChoosingElMaze(unsigned select)
{
    switch (select)
    {
        case 1:
            return wall;
        case 2:
            return spawn;
        case 3:
            return quit;
        default:
            return wall;
    }
}