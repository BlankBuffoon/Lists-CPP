#include <iostream>

using namespace std;


// Структура данных объекта (какие данные хранит объект списка)
typedef struct
{
    int Data;
} DataList;


// Объект списка хранящий в себе данные и указатель на следующий объект
typedef struct List
{
    // Объект данных созданный выше
    DataList Data;
    // Указатель на этот-же объект list (для того чтобы можно было ссылаться на другие желементы списка)
    struct List *next;
} ListObj;


// Указатели на объекты
ListObj* head = NULL, *tail = NULL;

// Функция инициализации списка
void initList(DataList data) {
    // Создаем объект структуры ListObj
    ListObj* ptr = new ListObj;
    
    // Присваиваем значение её параметрам (данным и указателем на следующий элемент)
    ptr->Data = data;
    ptr->next = NULL;

    // Присваиваем указатель на голову и на хвост
    head = ptr;
    tail = ptr;
    
    return;
}


// Функция добавления элемента в голову
void push_front() {
    int n;
    cout << "Введите элемент списка: ";
    cin >> n;

    // Создаем объект данных
    DataList data = { n };
    
    // Проверяем есть ли в списке голова и хвост. Если нет, то запускаем инициализацию
    if (head == NULL && tail == NULL) initList(data);
    // Если есть голова и хвост
    else {
        // Создаем объект списка
        ListObj* ptr = new ListObj;
        // Присваиваем ему значения
        ptr->Data = data;
        ptr->next = head;
        // Указываем что объект является головой
        head = ptr;
    }
    return;
}


// Функция добавления элемента в хвост
void push_back() {
    int n;
    cout << "Введите элемент списка: ";
    cin >> n;

    // Создаем объект данных
    DataList data = { n };

    // Проверяем есть ли в списке голова и хвост. Если нет, то запускаем инициализацию
    if (head == NULL && tail == NULL) initList(data);
    // Если есть голова и хвост
    else {
        // Создаем объект списка
        ListObj* ptr = new ListObj;
        // Присваиваем ему значения
        ptr->Data = data;
        tail->next = ptr; // Предыдущий объект указывает на только что созданны. Т.к. мы добавляем его в хвост
        ptr->next = NULL;
        // Указываем что объект является головой
        tail = ptr;
    }
    return;
}


// Функция добавления элемента в позицию
void push_pos() {

}


// Функция удаления элемента
void del() {
    int n;
    cout << "Введите номер элемента списка: ";
    cin >> n;


    // Создаем два объекта по образу ListObj
    ListObj* temp = head;
    ListObj* obj;

    // Если нужно удалить первый объект в списке
    if (n == 1 && temp != NULL) {
        head = temp->next;
        delete(temp);
        // Если объект был последним и первым одновременно (1 элемент в списке), указываем что он же является хвостом
        if (head == NULL) tail = NULL;
        
        return;
    }
    // Если удаляем не первый объект
    else {
        // Проходим по всем объектам
            for (int i = 1; i != n; i++) {
                // Если элемент существует
                if (temp != NULL) {
                // Находим предыдущий от удаляемого 
                if (n == i + 1) {
                    // Запоминаем удаляемый элемент для дальнейшей очистки памяти
                    obj = temp->next;
                    temp->next = temp->next->next;
                    // Очищаем память от удаленного элемента
                    delete obj;

                    // Если удаляемый элемент был последний, указываем новый хвост
                    if (temp->next == NULL) tail = temp;
                    return;
                }
                temp = temp->next;
            }
        }
    }
}


// Функция вывода на экран
void show() {
    cout << "Инициализирован вывод элементов списка.\n";
    ListObj* showObj = head;
    cout << "Элементы списка: ";

    // Пока объект не пуст
    while (showObj != NULL) {
        // Выводим значение
        cout << showObj->Data.Data << " ";
        // Перелистываем на следующий указатель
        showObj = showObj->next;
    }
    cout << "\nЭлементы списка выведены на экран.\n";
    // Очищаем память
    delete showObj;
    return;
}

void safe() {

}

void load() {

}

void replace() {

}

int main()
{
    setlocale(0, "");
    cout << "Однонаправленные списки\n";

    int menuChoice = NULL;


    // Меню
    do
    {
        cout << endl;
        cout << "1 - Добавить элемент в голову\n";
        cout << "2 - Добавить элемент в хвост\n";
        cout << "3 - Добавить элемент в позицию\n";
        cout << "4 - Вывести список на экран\n";
        cout << "5 - Удалить элемент списка\n";
        cout << "6 - Сохранить список в файл\n";
        cout << "7 - Загрузить список из файла\n";
        cout << "8 - Поменять элементы списка местами\n";
        cout << "0 - Выйти из программы\n";
        cout << "Выберите пункт меню: ";
        cin >> menuChoice;
        cout << endl;

        if (menuChoice < 0 || menuChoice > 8) {
            cout << "Неверный пункт! Повторите попытку.\n";
        }

        if (menuChoice == 1) push_front();
        if (menuChoice == 2) push_back();
        if (menuChoice == 3) push_pos();
        if (menuChoice == 4) show();
        if (menuChoice == 5) del();
        if (menuChoice == 6) safe();
        if (menuChoice == 7) load();
        if (menuChoice == 8) replace();

    } while (menuChoice != 0);
}