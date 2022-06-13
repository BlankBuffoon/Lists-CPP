#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct tree {
    string calculation;
    struct tree* child_left, * child_right;
    struct tree* parent;
} treeObj;

treeObj* root = NULL;
char symbol[] = "!&|>";
vector<string> calcTemp;

void input() {
    int inputPoint = NULL;
    string input;
    cout << "Введите пример: ";
    cin >> input;

    int openBracket = 0, closeBracket = 0;

    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '(') openBracket++;
        if (input[i] == ')') closeBracket++;
    }

    if (openBracket != closeBracket) {
        cout << "Ошибка в примере. Повторите попытку.\n";
        return;
    }

    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '(') {
            inputPoint == i;
        }
        if (input[i] == ')' && inputPoint != NULL) {
            string temp;
            for (int j = 0; j < i - inputPoint; j++) {
                temp += input[j];
            }
            calcTemp.push_back(temp);
        }
    }
}

void show() {
    for (int i = 0; i < calcTemp.size(); i++) {
        cout << calcTemp[i] << " ";
    }
    cout << "\n";
}

int main()
{
    setlocale(0, "");
    cout << "Вычисление методом аналитических таблиц\n";

    int menuChoice = NULL;

    // Меню
    do
    {
        cout << endl;
        cout << "1 - Ввести пример\n";
        cout << "2 - Показать решение\n";
        cout << "0 - Выйти из программы\n";
        cout << "Выберите пункт меню: ";
        cin >> menuChoice;
        cout << endl;

        if (menuChoice < 0 || menuChoice > 2) {
            cout << "Такого пункта меню не существует. Повторите попытку.\n";
        }

        if (menuChoice == 1) input();
        if (menuChoice == 2) show();
    } while (menuChoice != 0);
}
