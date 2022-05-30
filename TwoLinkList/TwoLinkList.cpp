#include <iostream>
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
    struct List* prev, *next;
} ListObj;

// Указатели на объекты
ListObj* head = NULL, * tail = NULL;

// Функция инициализации списка
void initList(DataList data) {
    // Создаем объект списка
    ListObj* ptr = new ListObj;

    // Присваиваем значение его параметрам (данным и указателем)
    ptr->Data = data;
    ptr->next = NULL;
    ptr->prev = NULL;

    // Присваиваем указатель на голову и на хвост
    head = ptr;
    tail = ptr;
    
    // Вывод отладочной информации
    //cout << "Инициализирован первый элемент списка. \nptr: " << ptr << " next: " << ptr->next << " prev: " << ptr->prev << " head: " << head << " tail:" << tail << endl;
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
        head->prev = ptr;
        ptr->prev = NULL;
        // Указываем что этот объект - новая голова
        head = ptr;

        // Вывод отладочной информации
        //cout << "Инициализирован элемент списка. ptr: " << ptr << " next: " << ptr->next << " prev: " << ptr->prev << " head: " << head << endl;
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
        ptr->prev = tail; 
        ptr->next = NULL;
        // Указываем что объект является хвостом
        tail = ptr;
        // Вывод отладочной информации
        //cout << "Инициализирован элемент списка. ptr: " << ptr << " next: " << ptr->next << " prev: " << ptr->prev << " tail:" << tail << endl;
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

    // Создаем указатели
    ListObj* ptr = new ListObj;
    ListObj* obj = head, *temp = nullptr;


    for (int i = 1; obj != NULL; i++) {
        if (i == pos) {
            if (obj->next == NULL) {
                cout << "Для вставки элемента в хвост используйте существующую для этого функцию.\n";
                return;
            }
            else {
                // Запоминаем указатель на элемент после которого происходит вставка
                temp = obj->prev;

                // Присваиваем указатели новому объекту
                ptr->next = obj;
                ptr->prev = temp;
                // Меняем указатели на новый объект
                obj->prev = ptr;
                temp->next = ptr;
                // Присваиваем значение
                ptr->Data = data;
                // Вывод отладочной информации
                //cout << "Инициализирован элемент списка. ptr: " << ptr << " next: " << ptr->next << " prev: " << ptr->prev << endl;
            }
        }

        // Обработка ошибок
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

    // Создаем указатели
    ListObj* obj = head, * temp_next = nullptr, * temp_prev = nullptr;

    // Ищем нужный элемент в списке
    for (int i = 1; obj != NULL; i++) {
        // Если нашли
        if (i == n) {
            // Вывод отладочной информации
            //cout << "Выбран объект с индексом " << i << " obj: " << obj << endl;
            // Выходим из цикла
            break;
        }
        obj = obj->next;
    }

    // Запоминаем указатели удаляемого объекта
    temp_next = obj->next;
    temp_prev = obj->prev;
    delete obj;
    
    // Если удаляемый объект не является головой
    if (temp_prev != NULL) temp_prev->next = temp_next;
    else head = temp_next;

    // Такая же проверка для хвоста
    if (temp_next != NULL) temp_next->prev = temp_prev;
    else tail = temp_prev;
    
    return;
}

// Функция вывода на экран
void show() {
    ListObj* obj = head;
    cout << "Элементы списка: ";

    //Пока объект не пуст
    while (obj != NULL) {
        // Выводим значение
        cout << obj->Data.Data << " ";
        // Перелистываем на следующий указатель
        obj = obj->next;
    }

    // Расширенный вывод с указателями
    //cout << "Элементы списка: \n";

    //while (obj != NULL) {
    //    // Выводим значение
    //    cout << "data: " << obj->Data.Data << endl;
    //    cout << "obj:" << obj << " prev: " << obj->prev << " next: " << obj->next << "\n\n";
    //    // Перелистываем на следующий указатель
    //    obj = obj->next;
    //}
    //cout << "head: " << head << " tail: " << tail << endl;
    
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
    // Записываем
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
        cout << "Для загрузки списка файл должен быть пустым! Очистите список и повторите попытку.\n";
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
            ptr->prev = tail; // Указатель на предыдущий объект, указывает на хвост
            ptr->next = NULL;
            // Указываем что объект является хвостом
            tail = ptr;
            // Вывод отладочной информации
            //cout << "Инициализирован элемент списка. \nptr: " << ptr << " next: " << ptr->next << " prev: " << ptr->prev << " tail:" << tail << endl;
        }
    }

    cout << "Список успешно загружен из файла: " << filename << ".txt\n";
    listLoad.close();
}

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
    ListObj* temp_a_prev = nullptr;
    ListObj* temp_b_prev = nullptr;

    // Ищем нужные объекты в списке
    for (int i = 1; obj != NULL; i++) {
        if (i == a) temp_a = obj;
        if (i == b) temp_b = obj;
        obj = obj->next;
    }

    // Запоминаем указатели объектов, которые нужно поменять местами
    temp_a_next = temp_a->next;
    temp_b_next = temp_b->next;
    temp_a_prev = temp_a->prev;
    temp_b_prev = temp_b->prev;

    // Если объекты стоят рядом
    if (temp_b == temp_a_next) {
        temp_b->next = temp_a;
        temp_b->prev = temp_a_prev;
        temp_a->next = temp_b_next;
        temp_a->prev = temp_b;
        if (temp_b_next != NULL) temp_b_next->prev = temp_a;
        if (temp_a != head) temp_a_prev->next = temp_b;
    }
    
    // Если объекты стоят рядом
    else if (temp_a == temp_b_next) {
        temp_a->next = temp_b;
        temp_a->prev = temp_b_prev;
        temp_b->next = temp_a_next;
        temp_b->prev = temp_a;
        if (temp_a_next != NULL) temp_a_next->prev = temp_b;
        if (temp_b != head) temp_b_prev->next = temp_a;
    }

    // Если объекты разделены
    else {
        // Меняем указатели на следующие объекты
        if (temp_a != head) temp_a_prev->next = temp_b;
        temp_b->next = temp_a_next;
        if (temp_b != head) temp_b_prev->next = temp_a;
        temp_a->next = temp_b_next;
        // Меняем указатели на предыдущие объекты
        temp_b->prev = temp_a_prev;
        if (temp_b_next != NULL) temp_b_next->prev = temp_a;
        temp_a->prev = temp_b_prev;
        if (temp_a_next != NULL) temp_a_next->prev = temp_b;
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

    // Вывод отладочной информации
    //cout << "temp_a: " << temp_a << " temp_b: " << temp_b << " head: " << head << " tail: " << tail << endl;

    return;
}

int main()
{
    setlocale(0, "");
    cout << "Двунаправленные списки\n";

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