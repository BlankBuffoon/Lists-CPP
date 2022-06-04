#include <iostream>
#include <fstream>

using namespace std;

// Структура данных объекта (какие данные хранит объект списка)
typedef struct
{
    string Name; // Имя
    float Height; // Рост
    int Age; // Возраст
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
    string nameOfStudent;
    float heightOfStudent;
    int ageOfStudent;

    cout << "Введите имя: ";
    cin >> nameOfStudent;

    cout << "Введите рост: ";
    cin >> heightOfStudent;

    cout << "Введите возраст: ";
    cin >> ageOfStudent;

    // Создаем объект данных
    DataList data = { nameOfStudent, heightOfStudent, ageOfStudent };

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

    string nameOfStudent;
    float heightOfStudent;
    int ageOfStudent;

    cout << "Введите имя: ";
    cin >> nameOfStudent;

    cout << "Введите рост: ";
    cin >> heightOfStudent;

    cout << "Введите возраст: ";
    cin >> ageOfStudent;

    // Создаем объект данных
    DataList data = { nameOfStudent, heightOfStudent, ageOfStudent };

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

    int pos = NULL;
    string nameOfStudent;
    float heightOfStudent;
    int ageOfStudent;

    cout << "Введите позицию для добавляемого значения: ";
    cin >> pos;

    cout << "Введите имя: ";
    cin >> nameOfStudent;

    cout << "Введите рост: ";
    cin >> heightOfStudent;

    cout << "Введите возраст: ";
    cin >> ageOfStudent;

    // Создаем объект данных
    DataList data = { nameOfStudent, heightOfStudent, ageOfStudent };

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

// Функция вывода на экран
void show() {
    ListObj* obj = head;
    cout << "Студенты: ";

    // Пока объект не пуст
    while (obj != NULL) {
        // Выводим значение
        cout << endl;
        cout << "Имя: " << obj->Data.Name << " ";
        cout << "Рост: " << obj->Data.Height << " ";
        cout << "Возраст: " << obj->Data.Age << " ";
        // Перелистываем на следующий указатель
        obj = obj->next;
    }
    cout << "\nЭлементы базы данных <Студенты> выведены на экран.\n";
    // Очищаем память
    delete obj;
    return;
}

// Функция удаления элемента
void del() {
    int n;
    cout << "Введите номер элемента списка: ";
    cin >> n;


    // Создаем указатели
    ListObj* temp = head;
    ListObj* obj = nullptr;

    // Если нужно удалить первый объект в списке
    if (n == 1 && temp != NULL) {
        head = temp->next;
        delete(temp);
        // Если объект был последним и первым одновременно (1 элемент в списке)
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
            listSafe << "Имя: " << obj->Data.Name << " ";
            listSafe << "Рост: " << obj->Data.Height << " ";
            listSafe << "Возраст: " << obj->Data.Age << " ";
            listSafe << endl;
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

    // Создаем буферные переменные для хранения данных
    string nameOfStudent;
    float heightOfStudent = NULL;
    int ageOfStudent = NULL;
    string buffer;

    // Создаем новый объект структуры и записываем в него данные из буфера
    DataList data = { nameOfStudent, heightOfStudent, ageOfStudent };

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
        // Считываем один раз, чтобы
        listLoad >> buffer;
        listLoad >> nameOfStudent;
        listLoad >> buffer;
        listLoad >> heightOfStudent;
        listLoad >> buffer;
        listLoad >> ageOfStudent;

        data = { nameOfStudent, heightOfStudent, ageOfStudent };
        // Запустить инициализацию списка
        initList(data);

        // Пока в файле есть данные для считывания
        while (listLoad >> buffer) {
            listLoad >> nameOfStudent;
            listLoad >> buffer;
            listLoad >> heightOfStudent;
            listLoad >> buffer;
            listLoad >> ageOfStudent;
            data = { nameOfStudent, heightOfStudent, ageOfStudent };
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
}

// Функция поиска
void find()
{
    int n;
    string nameFind;
    float heightFind;
    int ageFind;
    bool finded = false;

    // Создаем указатели
    ListObj* obj = head;

    cout << "По какому параметру выполнять поиск?" << endl;
    cout << "1. Имя" << endl;
    cout << "2. Рост" << endl;
    cout << "3. Возраст" << endl;
    cin >> n;

    if (n < 1 || n > 3) {
        cout << "Неверный пункт! Повторите попытку.\n";
    }

    if (n == 1)
    {
        cout << "Введите имя: ";
        cin >> nameFind;
        while (obj != NULL) {
            if (obj->Data.Name == nameFind) {
                finded = true;
                cout << "Найдена запись.\n";
                cout << "Имя: " << obj->Data.Name << " ";
                cout << "Рост: " << obj->Data.Height << " ";
                cout << "Возраст: " << obj->Data.Age << " \n";
            }
            obj = obj->next;
        }

        if (!finded) cout << "В базе данных нет записей с именем " << nameFind << "!\n";
        finded = false;
    }

    if (n == 2)
    {
        cout << "Введите рост: ";
        cin >> heightFind;
        while (obj != NULL) {
            if (obj->Data.Height == heightFind) {
                finded = true;
                cout << "Найдена запись.\n";
                cout << "Имя: " << obj->Data.Name << " ";
                cout << "Рост: " << obj->Data.Height << " ";
                cout << "Возраст: " << obj->Data.Age << " \n";
            }
            obj = obj->next;
        }

        if (!finded) cout << "В базе данных нет записей с ростом " << heightFind << "!\n";
        finded = false;
    }

    if (n == 3)
    {
        cout << "Введите возраст: ";
        cin >> ageFind;
        while (obj != NULL) {
            if (obj->Data.Age == ageFind) {
                finded = true;
                cout << "Найдена запись.\n";
                cout << "Имя: " << obj->Data.Name << " ";
                cout << "Рост: " << obj->Data.Height << " ";
                cout << "Возраст: " << obj->Data.Age << " \n";
            }
            obj = obj->next;
        }

        if (!finded) cout << "В базе данных нет записей с возрастом " << ageFind << "!\n";
        finded = false;
    }
}

void replace(ListObj* temp_a, ListObj* temp_b);

// Функция сортировки (доделать)
void sorting()
{
    int n;

    cout << "По какому параметру сортировать?" << endl;
    cout << "1. Имя" << endl;
    cout << "2. Рост" << endl;
    cout << "3. Возраст" << endl;
    cin >> n;

    // Создаем указатели
    ListObj* obj = head;
    ListObj* objNext = head->next;
    ListObj* tempMin = head;
    ListObj* temp = head;

    if (n < 1 || n > 3) {
        cout << "Неверный пункт! Повторите попытку.\n";
    }

    if (n == 1)
    {
        while (obj != NULL) {
            while (temp != NULL) {
                // Сравниваем значения (для букв это первый символ) и находим минимальное
                if (tempMin->Data.Name[0] > temp->Data.Name[0]) {
                    tempMin = temp;
                    //cout << "min: " << tempMin->Data.Age << " с именем: " << tempMin->Data.Name << endl;
                }
                temp = temp->next;
            }
            if (obj != tempMin) replace(obj, tempMin); // Меняем местами
            //cout << "Заменен: " << obj->Data.Name << " | " << obj->Data.Age <<  " и " << tempMin->Data.Name << " | " << tempMin->Data.Age << endl;
            obj = objNext; // Присваиваем новые значения
            if (obj->next == NULL) return; // Если находимся в конце списка - выходим из функции
            objNext = obj->next;
            tempMin = obj;
            temp = obj;
        }
        cout << "База данных отсортирована.\n";
    }

    if (n == 2)
    {
        while (obj != NULL) {
            while (temp != NULL) {
                if (tempMin->Data.Height > temp->Data.Height) {
                    tempMin = temp;
                    //cout << "min: " << tempMin->Data.Age << " с именем: " << tempMin->Data.Name << endl;
                }
                temp = temp->next;
            }
            if (obj != tempMin) replace(obj, tempMin);
            //cout << "Заменен: " << obj->Data.Name << " | " << obj->Data.Age <<  " и " << tempMin->Data.Name << " | " << tempMin->Data.Age << endl;
            obj = objNext;
            if (obj->next == NULL) return;
            objNext = obj->next;
            tempMin = obj;
            temp = obj;
        }
        cout << "База данных отсортирована.\n";
    }

    if (n == 3)
    {
        while (obj != NULL) {
            while (temp != NULL) {
                if (tempMin->Data.Age > temp->Data.Age) {
                    tempMin = temp;
                    //cout << "min: " << tempMin->Data.Age << " с именем: " << tempMin->Data.Name << endl;
                }
                temp = temp->next;
            }
            if (obj != tempMin) replace(obj, tempMin);
            //cout << "Заменен: " << obj->Data.Name << " | " << obj->Data.Age <<  " и " << tempMin->Data.Name << " | " << tempMin->Data.Age << endl;
            obj = objNext;
            if (obj->next == NULL) return;
            objNext = obj->next;
            tempMin = obj;
            temp = obj;
        }
        cout << "База данных отсортирована.\n";
    }
}

void replace(ListObj* temp_a, ListObj* temp_b) {
    // Флаги отслеживающие менялись ли голова и хвост
    bool headChanged = false, tailChanged = false;

    // Создаем указатели на объекты списка
    ListObj* temp_a_next = nullptr;
    ListObj* temp_b_next = nullptr;
    ListObj* temp_a_prev = head;
    ListObj* temp_b_prev = head;

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
    }
    if (temp_b == head && headChanged == false) {
        head = temp_a;
        headChanged = true;
    }
    // То же самое для хвоста
    if (temp_a == tail && tailChanged == false) {
        tail = temp_b;
        tailChanged = true;
    }
    if (temp_b == tail && tailChanged == false) {
        tail = temp_a;
        tailChanged = true;
    }

    return;
}

// Функция редактирования
void edit()
{
    int n;
    int m;
    cout << "Введите номер элемента, который нужно отредактировать: ";
    cin >> n;
    cout << endl;

    // Создаем указатели
    ListObj* obj = head;

    // Проходим по всем объектам
    for (int i = 1; obj != NULL; i++)
    {
        if (n == i)
        {
            // Выводим значение
            cout << "Имя: " << obj->Data.Name << " ";
            cout << "Рост: " << obj->Data.Height << " ";
            cout << "Возраст: " << obj->Data.Age << " ";
            cout << endl;

            cout << n << " элемент базы данных <Студенты> выведен на экран.\n\n";

            cout << "Какой параметр нужно отредактировать?" << endl;
            cout << "1. Имя" << endl;
            cout << "2. Рост" << endl;
            cout << "3. Возраст" << endl;
            cin >> m;

            if (m < 1 || m > 3) {
                cout << "Неверный пункт! Повторите попытку.\n";
            }

            if (m == 1)
            {
                string nameBuff;
                cout << "На что надо заменить значение: ";
                cin >> nameBuff;
                obj->Data.Name = nameBuff;
                cout << "Значение отредактировано.\n";
                cout << endl;
                cout << "Имя: " << obj->Data.Name << " ";
                cout << "Рост: " << obj->Data.Height << " ";
                cout << "Возраст: " << obj->Data.Age << " ";
                cout << endl;
            }

            if (m == 2)
            {
                float heightBuff;
                cout << "На что надо заменить значение: ";
                cin >> heightBuff;
                obj->Data.Height = heightBuff;
                cout << "Значение отредактировано.\n";
                cout << endl;
                cout << "Имя: " << obj->Data.Name << " ";
                cout << "Рост: " << obj->Data.Height << " ";
                cout << "Возраст: " << obj->Data.Age << " ";
                cout << endl;
            }

            if (m == 3)
            {
                int ageBuff;
                cout << "На что надо заменить значение: ";
                cin >> ageBuff;
                obj->Data.Age = ageBuff;
                cout << "Значение отредактировано.\n";
                cout << endl;
                cout << "Имя: " << obj->Data.Name << " ";
                cout << "Рост: " << obj->Data.Height << " ";
                cout << "Возраст: " << obj->Data.Age << " ";
                cout << endl;
            }
        }
        obj = obj->next;
    }
    return;
}

int main()
{
    setlocale(0, "");
    system("chcp 1251");
    cout << "База данных <Студенты>\n";

    int menuChoice = NULL;
    int menuChoice2 = NULL;


    // Меню
    do
    {
        cout << endl;
        cout << "1 - Вывести на экран\n";
        cout << "2 - Добавить\n";
        cout << "3 - Удалить\n";
        cout << "4 - Сохранить в файл\n";
        cout << "5 - Вывести из файла\n";
        cout << "6 - Искать\n";
        cout << "7 - Сортировать\n";
        cout << "8 - Редактировать\n";
        cout << "0 - Выйти из программы\n";
        cout << "Выберите пункт меню: ";
        cin >> menuChoice;
        cout << endl;

        if (menuChoice < 0 || menuChoice > 8) {
            cout << "Неверный пункт! Повторите попытку.\n";
        }

        if (menuChoice == 1) show();

        if (menuChoice == 2) {
            {
                cout << "Куда вы хотите добавить элемент?\n";
                cout << "1. В начало\n";
                cout << "2. В конец\n";
                cout << "3. В позицию\n";
                cin >> menuChoice2;
                cout << endl;
            }
            if (menuChoice2 == 1) push_front();
            if (menuChoice2 == 2) push_back();
            if (menuChoice2 == 3) insert();
        }

        if (menuChoice == 3) del();
        if (menuChoice == 4) safe();
        if (menuChoice == 5) load();
        if (menuChoice == 6) find();
        if (menuChoice == 7) sorting();
        if (menuChoice == 8) edit();


    } while (menuChoice != 0);
}

