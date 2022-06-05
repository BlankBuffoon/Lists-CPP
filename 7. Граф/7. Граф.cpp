#include <iostream>
#include <vector>

using namespace std;

typedef struct Graph {
    int Data;
    struct Graph* next, * prev;
} GraphObj;

GraphObj* root = NULL;
vector<GraphObj*> verts;

void add_vert() {
    int value;
    cout << "Введите значение вершины: ";
    cin >> value;

    GraphObj* ptr = new GraphObj;
    
    ptr->Data = value;
    ptr->next = ptr->prev = NULL;
    verts.push_back(ptr);

    if (root == NULL) root = ptr;

    cout << "Вершина добавлена\n";
}

void add_edge() {
    int a, b;
    int valuevert = 0, findvert = 0, choicevert = NULL;

    GraphObj* temp;

    cout << "Список вершин графа:";
    show();

    cout << "К какой вершине нужно добавить ребро?: ";
    cin >> a;
    cout << "С какой вершиной небходимо связать?: ";
    cin >> b;

    if (a < 0 || b < 0) {
        cout << "Неверные входные данные. Попробуйте еще раз.\n";
        return;
    }

    if (a > verts.size() || b > verts.size()) {
        cout << "Неверные входные данные. Попробуйте еще раз.\n";
        return;
    }

    for (int i = 0; i < verts.size(); i++) {
        if (a == verts[i]->Data) findvert++;
    }

    if (findvert > 1 && findvert != 0) {
        cout << "Найдено несколько подходящих вершин. К какой нужно добавить связь?\n";
        cout << "Укажите номер по порядку: ";
        cin >> choicevert;
        for (int i = 0; i < verts.size(); i++) {
            if (a == verts[i]->Data) {
                valuevert++;
                if (valuevert == choicevert) {
                    temp = verts[i];
                }
            }
        }
    }
}

void del_vert() {

}

void del_edge() {

}

void show() {
    GraphObj* temp;

    cout << "Список вершин и их связей: \n";

    for (int i = 0; i < verts.size(); i++) {
        temp = verts[i];
        cout << temp->Data;
        while (temp->next != nullptr) {
            temp = temp->next;
            cout << "--";
            cout << temp->Data;
        }
        if (temp->next == nullptr) {
            cout << endl;
        }
    }
}

void safe() {

}

void load() {

}

void find_path() {

}

int main()
{
    setlocale(0, "");
    cout << "Графы\n";

    int menuChoice = NULL;

    // Меню
    do
    {
        cout << endl;
        cout << "1 - Добавить вершину\n";
        cout << "2 - Добавить ребро\n";
        cout << "3 - Удалить вершину\n";
        cout << "4 - Удалить ребро\n";
        cout << "5 - Вывод графа на экран\n";
        cout << "6 - Сохранить граф в файл\n";
        cout << "7 - Загрузить граф из файла\n";
        cout << "8 - Найти путь в графе\n";
        cout << "0 - Выйти из программы\n";
        cout << "Выберите пункт меню: ";
        cin >> menuChoice;
        cout << endl;

        if (menuChoice < 0 || menuChoice > 8) {
            cout << "Неверный пункт! Повторите попытку.\n";
        }

        if (menuChoice == 1) add_vert();
        if (menuChoice == 2) add_edge();
        if (menuChoice == 3) del_vert();
        if (menuChoice == 4) del_edge();
        if (menuChoice == 5) show();
        if (menuChoice == 6) safe();
        if (menuChoice == 7) load();
        if (menuChoice == 8) find_path();

    } while (menuChoice != 0);
}