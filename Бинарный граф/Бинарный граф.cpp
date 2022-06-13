#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


// Структура объекта графа
typedef struct graph {
    int data; // Данные
    struct graph* childLeft, *childRight, *parent; // Связи
} graphObj;


// Указатель на корень графа
graphObj* root = NULL;
// Массив для хранения найденых объектов
vector <graphObj*> findedObj;


// Типы данных отвечающие за правильную инициализацию функций
typedef enum NewNodeEdgeDirection { LEFT, RIGHT } edgedir;
typedef enum FindObjectType { FREE, NEED } findtype;
typedef enum saveType {ViewOnly, Load} saveType;


// Объекты для работы с файлами
ifstream loadFile;
ofstream saveFile;


// Функции
void find_node(findtype type, graphObj* obj, int findData);
void add_node(graphObj* parentObj, graphObj* childObj, edgedir dir);
void del_node(graphObj* delobj);
void show_nodes(const graphObj* node);
void save_nodes(const string& prefix, const graphObj* node, bool isLeft);


// Функция - обработчик добавления вершин
void add_node_handler() {
    graphObj* ptr = new graphObj; // Новый объект
    int inputData;

    cout << "Введите значение: ";
    cin >> inputData;

    ptr->data = inputData;

    // Если нет объектов в графе
    if (root == NULL) {
        ptr->childRight = NULL;
        ptr->childLeft = NULL;
        ptr->parent = NULL;
        root = ptr;
    }
    else {
        // Очищаем массив найденных объектов
        findedObj.clear();
        // Ищем свободные объекты
        find_node(FREE, root, NULL);

        if (findedObj.size() > 0) {    
            // Выводим дерево
            cout << endl;
            show_nodes(root);
            cout << endl;

            cout << "Найдено несколько вершин, с которыми можно установить связь: \n";

            // Выводим что нашли в графе из массива
            for (int i = 0; i < findedObj.size(); i++) {
                cout << i + 1 << ". " << findedObj[i]->data;
                if (findedObj[i]->parent != NULL) cout << " | Родитель: " << findedObj[i]->parent->data << endl;
                else cout << " | Родитель: NULL" << endl;
            }

            int cVert;
            int numChoiceEdgeDir;
            edgedir direction;
            cout << "Выберите с какой необходимо установить связь (укажите номер): ";
            cin >> cVert;
            cVert--;

            // Если у выбранного объекта есть и правая, и левая свободная связь
            if (findedObj[cVert]->childLeft == NULL && findedObj[cVert]->childRight == NULL) {
                cout << "Выбранная вершина может иметь несколько потомков. К какой стороне указать связь?\n";
                cout << "1 - К левой\n2 - К правой\n";
                cin >> numChoiceEdgeDir;
                if (numChoiceEdgeDir == 1) direction = LEFT;
                if (numChoiceEdgeDir == 2) direction = RIGHT;

                // Инициализируем добавление
                add_node(findedObj[cVert], ptr, direction);
                return;
            }
            // Если можем добавить только слева
            else if (findedObj[cVert]->childLeft == NULL && findedObj[cVert]->childRight != NULL) {
                add_node(findedObj[cVert], ptr, LEFT);
                return;
            }
            // Если можем добавить только справа
            else if (findedObj[cVert]->childLeft != NULL && findedObj[cVert]->childRight == NULL) {
                add_node(findedObj[cVert], ptr, RIGHT);
                return;
            }
        }
    }
    return;
}


// Функция добавления вершины
void add_node(graphObj* parentObj, graphObj* childObj, edgedir dir) {
    // Устанавливаем связи
    childObj->parent = parentObj;
    childObj->childLeft = childObj->childRight = NULL;

    // Связываем объект с родителем. Либо слева, либо справа
    switch (dir) {
    case LEFT: parentObj->childLeft = childObj; break;
    case RIGHT: parentObj->childRight = childObj; break;
    }
    cout << "Новая вершина создана!\n";
}


// Функция - обработчик удаления вершин
void del_node_handler() {
    int findData;
    cout << "Текущее дерево:\n";

    // Выводим граф
    cout << endl;
    show_nodes(root);
    cout << endl;

    cout << "Какую вершину необходимо удалить? ";
    cin >> findData;

    // Очищаем массив найденых объектов
    findedObj.clear();
    // Ищем объекты совпадающие с искомым
    find_node(NEED, root, findData);
    
    // Если было найдено несколько подходящих объектов
    if (findedObj.size() > 1) {
        cout << "Найдено несколько вершин c такими данными: \n";
        
        // Выводим что нашли в графе из массива
        for (int i = 0; i < findedObj.size(); i++) {
            cout << i + 1 << ". " << findedObj[i]->data;
            if (findedObj[i]->parent != NULL) cout << " | Родитель: " << findedObj[i]->parent->data << endl;
            else cout << " | Родитель: NULL" << endl;
        }

        int cVert;
        cout << "Выберите какую из вершин удалить (укажите номер): ";
        cin >> cVert;
        cVert--;

        // Если удаляемый не был корнем, убираем дочерние связи его родителя
        if (findedObj[cVert] != root) {
            if (findedObj[cVert]->parent->childLeft == findedObj[cVert]) {
                findedObj[cVert]->parent->childLeft = NULL;
            }
            if (findedObj[cVert]->parent->childRight == findedObj[cVert]) {
                findedObj[cVert]->parent->childRight = NULL;
            }
        }
        // Если был корнем, обнуляем связи до NULL
        else if (findedObj[cVert] == root) root = nullptr;

        cout << "Будут удалены следующие объекты: \n";
        // Выводим то что удалим
        cout << endl;
        show_nodes(findedObj[cVert]);
        cout << endl;
        // Удаляем все начиная с удаляемого
        del_node(findedObj[cVert]);
    }
    // Если найден один
    else if (findedObj.size() == 1) {
        if (findedObj[0] != root) {
            if (findedObj[0]->parent->childLeft == findedObj[0]) {
                findedObj[0]->parent->childLeft = NULL;
            }
            if (findedObj[0]->parent->childRight == findedObj[0]) {
                findedObj[0]->parent->childRight = NULL;
            }
        }
        else if (findedObj[0] == root) root = nullptr;
        
        cout << "Будут удалены следующие объекты: \n";
        cout << endl;
        show_nodes(findedObj[0]);
        cout << endl;
        del_node(findedObj[0]);
    }
}


// Функция удаления
void del_node(graphObj* delobj) {
    if (delobj == NULL) return;

    // Рекурсивно двигаемся по детям объекта
    del_node(delobj->childLeft);
    del_node(delobj->childRight);
    // Удаляем объект
    delete delobj;
}


// Функция поиска объекта
void find_node(findtype type = FREE, graphObj* obj = root, int findData = NULL) {
    if (obj == NULL) return;
    
    // Если ищем конкретный объект
    if (type == NEED) {
        // Сравниваем по data
        if (obj->data == findData) findedObj.push_back(obj);

        // Рекурсивно двигаемся по графу
        find_node(NEED, obj->childLeft, findData);
        find_node(NEED, obj->childRight, findData);
    }

    // Если ищем свободный объект
    if (type == FREE) {
        // Находим по NULL на указателях свободных объектов
        if (obj->childLeft == NULL || obj->childRight == NULL) findedObj.push_back(obj);

        // Рекурсивно двигаемся по графу
        find_node(FREE, obj->childLeft);
        find_node(FREE, obj->childRight);
    }
}


// Функция вывода на экран
void show_nodes(const string& prefix, const graphObj* node, bool isLeft)
{
    if (node != nullptr) {
        // Выводим префикс (символ(ы) которые должны быть перед выводимым)
        cout << prefix;
        // Выводим нужный символ обозначающий связь
        cout << (isLeft ? "|> " : "-> ");
        // Выводим данные
        cout << node->data << std::endl;

        // Рекусрисно двигаемся по объектам
        show_nodes(prefix + (isLeft ? "|  " : "   "), node->childLeft, true);
        show_nodes(prefix + (isLeft ? "|  " : "   "), node->childRight, false);
    }
}


// Функция - обработчик (для более легкого вызова функции)
void show_nodes(const graphObj* node) {
    show_nodes("", node, false);
}


// Функция сохранения
void save() {
    string filename;
    int choice = NULL;
    
    cout << "Введите название файла для открытия: ";
    cin >> filename;

    saveFile.open(filename + ".txt");
    // Проверка
    if (!saveFile.is_open()) {
        cout << "Ошибка открытия файла.\n";
        return;
    }
    else {
        // Вызываем функция сохранения
        save_nodes("", root, false);
    }
    saveFile.close();
    return;
}


// То-же самое что и в функции вывода, только в файл
void save_nodes(const string& prefix, const graphObj* node, bool isLeft)
{
    if (node != nullptr) {
        saveFile << prefix;

        saveFile << (isLeft ? "|> " : "-> ");

        saveFile << node->data << std::endl;

        save_nodes(prefix + (isLeft ? "|  " : "   "), node->childLeft, true);
        save_nodes(prefix + (isLeft ? "|  " : "   "), node->childRight, false);
    }
}



/*
void load() {
    /// ?????
}
*/



// Главная функция
int main()
{
    // Кодировка для русских символов
    SetConsoleOutputCP(1251);
    cout << "Двунаправленные списки (сортировка слиянием)\n";

    int menuChoice = NULL;

    // Меню
    do
    {
        cout << endl;
        cout << "1 - Добавить вершину\n";
        cout << "2 - Удалить вершину\n";
        cout << "3 - Добавить ребро\n";
        cout << "4 - Удалить ребро\n";
        cout << "5 - Вывести граф на экран\n";
        cout << "6 - Сохранить граф в файл\n";
        cout << "0 - Выйти из программы\n";
        cout << "Выберите пункт меню: ";
        cin >> menuChoice;
        cout << endl;

        if (menuChoice < 0 || menuChoice > 6) {
            cout << "Неверный пункт! Повторите попытку.\n";
        }

        if (menuChoice == 1) add_node_handler();
        if (menuChoice == 2) del_node_handler();
        if (menuChoice == 3) {
            cout << "Добавление ребра происходит так-же как и добавление вершины!\n";
            cout << "Для добавления ребра, укажите новую вершину с которой оно будет связано.\n\n";
            add_node_handler();
        }
        if (menuChoice == 4) {
            cout << "Удаление ребра происходит так-же как и удаление вершины!\n";
            cout << "Для удаление ребра, удалите вершину с которой оно связано.\n\n";
            del_node_handler();
        }
        if (menuChoice == 5) show_nodes(root);
        if (menuChoice == 6) save();
        //if (menuChoice == 7) load();

    } while (menuChoice != 0);
}