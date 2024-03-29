﻿#include <iostream>
#include <fstream>

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
    struct List* next;
} ListObj;


// Указатели на объекты
ListObj* head = NULL, * tail = NULL;


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
        tail->next = ptr; // Предыдущий объект указывает на только что созданный. Т.к. мы добавляем его в хвост
        ptr->next = NULL;
        // Указываем что объект является хвостом
        tail = ptr;
    }
    return;
}


// Функция добавления элемента в позицию
void insert() {
    int pos = NULL, n = NULL;
    cout << "Введите позицию для добавляемого значения: ";
    cin >> pos;
    cout << "Введите значение: ";
    cin >> n;

    // Создаем объект данных
    DataList data = { n };

    ListObj* ptr = new ListObj;

    // Создаем указатели
    ListObj* obj = head, * temp = nullptr;

    for (int i = 1; obj != NULL; i++) {
        if (i == pos - 1) {
            if (obj->next == NULL) {
                cout << "Для вставки элемента в хвост используйте существующую для этого функцию.\n";
                return;
            }
            else {
                temp = obj->next; // Сохраняем указатель на следующий элемент
                obj->next = ptr; // Предыдущий объект указывает на только что созданный
                ptr->Data = data; // Записали данные в новый объект
                ptr->next = temp; // Созданный объект указывает на следующий
            }
        }

        if (obj == NULL) {
            cout << "Ошибка в значении позиции!\n";
            return;
        }
        if (pos == 1) {
            cout << "Для вставки элемента в голову используйте существующую для этого функцию.\n";
            return;
        }
        obj = obj->next;
    }
}


// Функция удаления элемента
void del() {
    int n;
    cout << "Введите номер элемента списка: ";
    cin >> n;


    // Создаем два объекта по образу ListObj
    ListObj* temp = head;
    ListObj* obj = nullptr;

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
    ListObj* obj = head;
    cout << "Элементы списка: ";

    // Пока объект не пуст
    while (obj != NULL) {
        // Выводим значение
        cout << obj->Data.Data << " ";
        // Перелистываем на следующий указатель
        obj = obj->next;
    }
    cout << "\nЭлементы списка выведены на экран.\n";
    // Очищаем память
    delete obj;
    return;
}


// Функция сохранения
void safe() {
    // Создаем объект для записи
    ofstream listSafe;
    string filename;
    cout << "Введите название файла, в который нужно сохранить список: ";
    cin >> filename;

    // Открываем файл
    listSafe.open(filename + ".txt");
    // Создаем объект списка
    ListObj* obj = head;

    // Проверяем открыт ли файл
    if (!listSafe.is_open()) {
        cout << "Произошла ошибка при создании файла. Проверьте правильность ввода названия файла.\n";
        return;
    }
    else {
        while (obj != NULL) {
            listSafe << obj->Data.Data << " ";
            obj = obj->next;
        }
    }

    cout << "Список успешно сохранен в файл: " << filename << ".txt\n";
    listSafe.close();
}


// Функция загрузки
void load() {
    // Создаем объект для чтения
    ifstream listLoad;
    string filename;
    cout << "Введите название файла, из которого нужно загрузить список: ";
    cin >> filename;

    // Создаем буферную переменную для хранения чисел
    int buffer = NULL;
    // Создаем новый объект структуры и записываем в него данные из буфера
    DataList data = { buffer };

    // Открываем файл для чтения
    listLoad.open(filename + ".txt");

    // Если в списке уже есть какие-то объекты
    if (head != NULL || tail != NULL) {
        cout << "Для загрузки списка он должен быть пустым! Очистите список и повторите попытку.\n";
        return;
    }

    // Если файл не смог открыться
    if (!listLoad.is_open()) {
        cout << "Произошла ошибка при открытии файла. Проверьте правильность ввода названия файла.\n";
        return;
    }
    else {
        // Считываем первое число из файла один раз, чтобы
        listLoad >> buffer;
        data = { buffer };
        // Запустить инициализацию списка
        initList(data);

        // Пока в файле есть данные для считывания
        while (listLoad >> buffer) {
            data = { buffer };
            // Создаем объект списка
            ListObj* ptr = new ListObj;
            // Присваиваем ему значения
            ptr->Data = data;
            tail->next = ptr; // Предыдущий объект указывает на только что созданный. Т.к. мы добавляем его в хвост
            ptr->next = NULL;
            // Указываем что объект является хвостом
            tail = ptr;
        }
    }

    cout << "Список успешно загружен из файла: " << filename << ".txt\n";
    // Закрываем файл
    listLoad.close();
}


// Функция перестановки
void replace() {
    // Флаги отслеживающие менялись ли голова и хвост
    bool headChanged = false, tailChanged = false;
    int a, b;
    cout << "Введите номера элемента списка: \n";
    cout << "A: ";
    cin >> a;
    cout << "B: ";
    cin >> b;

    // Создаем указатели на объекты списка
    ListObj* obj = head;
    ListObj* temp_a = nullptr;
    ListObj* temp_b = nullptr;
    ListObj* temp_a_next = nullptr;
    ListObj* temp_b_next = nullptr;
    ListObj* temp_a_prev = head;
    ListObj* temp_b_prev = head;

    // Ищем нужные объекты в списке
    for (int i = 1; obj != NULL; i++) {
        if (i == a) temp_a = obj;
        if (i == b) temp_b = obj;
        obj = obj->next;
    }

    // Проверяем указывает ли указатель на голову
    if (temp_a_prev == temp_a) temp_a_prev == NULL;
    else {
        // В противном случае перемещаем указатель пока не дойдем до предыдущего от А
        while (temp_a_prev->next != temp_a) {
            temp_a_prev = temp_a_prev->next;
        }
    }

    // То же самое повторяем для Б
    if (temp_b_prev == temp_b) temp_b_prev == NULL;
    else {
        while (temp_b_prev->next != temp_b) {
            temp_b_prev = temp_b_prev->next;
        }
    }

    // Указатель на следующие объекты
    temp_a_next = temp_a->next;
    temp_b_next = temp_b->next;


    // Исключение, если объекты для перестановки стоят рядом
    if (temp_b == temp_a_next) {
        temp_b->next = temp_a;
        temp_a->next = temp_b_next;
        // Если один из переставляемых не был головой, можем присвоить указатель
        if (temp_a != head) temp_a_prev->next = temp_b;
    }
    // Исключение, если объекты для перестановки стоят рядом
    else if (temp_a == temp_b_next) {
        temp_a->next = temp_b;
        temp_b->next = temp_a_next;
        // Если один из переставляемых не был головой, можем присвоить указатель
        if (temp_b != head) temp_b_prev->next = temp_b;
    }
    // Если объекты разделены
    else {
        // Проверка переставляем ли мы голову
        if (temp_a != head) {
            temp_a_prev->next = temp_b;
        }
        temp_b->next = temp_a_next;
        // Проверка переставляем ли мы голову
        if (temp_b != head) {
            temp_b_prev->next = temp_a;
        }
        temp_a->next = temp_b_next;
    }

    // Если голова была переставлена, но не менялся указатель, то присваеваем голове новый
    if (temp_a == head && headChanged == false) {
        head = temp_b;
        headChanged = true;
        cout << "head has been changed\n";
    }
    if (temp_b == head && headChanged == false) {
        head = temp_a;
        headChanged = true;
        cout << "head has been changed\n";
    }
    // То же самое для хвоста
    if (temp_a == tail && tailChanged == false) {
        tail = temp_b;
        tailChanged = true;
        cout << "tail has been changed\n";
    }
    if (temp_b == tail && tailChanged == false) {
        tail = temp_a;
        tailChanged = true;
        cout << "tail has been changed\n";
    }

    //Проверка
    //cout << "temp_a: " << temp_a << " temp_b: " << temp_b << " head: " << head << " tail: " << tail << endl;

    return;
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
        if (menuChoice == 3) insert();
        if (menuChoice == 4) show();
        if (menuChoice == 5) del();
        if (menuChoice == 6) safe();
        if (menuChoice == 7) load();
        if (menuChoice == 8) replace();

    } while (menuChoice != 0);
}