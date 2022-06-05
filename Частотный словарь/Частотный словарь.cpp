#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Создаем список
typedef struct list {
    string word;
    int count = 1;
    float percent;
    struct list* next;
} dictionaryWord;

// Создаем указатели на голову и на хвост
dictionaryWord* head = NULL, *tail = NULL;
// Создаем объект для записи
ifstream loadFile;
// Инициализируем векторный массив
vector<string> wordArray;

// Говорим компилятору о существовании функций
void sort(int n);
void replace(dictionaryWord* temp_a, dictionaryWord* temp_b);
void percentCalc();

// Функция загрузки файла
void load_text() {
    string buffer;
    string file;

    // Массив символов для удаления знаков
    char symbols[] = "1234567890_=+/?!|.,@#$%^()«»<\":; ";
    // Массивы для перевода строк в нижний регистр
    char upper[] = "БАВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЫЭЮЯ";
    char lower[] = "абвгдеёжзийклмнопрстуфхцчшщыэюя";

    cout << "Введите названия файла с текстом который необходимо проанализировать: ";
    cin >> file;
    loadFile.open(file + ".txt");

    if (!loadFile.is_open()) {
        cout << "Файл невозможно открыть, либо файл не был открыт.\n";
        loadFile.close();
        return;
    }
    else {
        while (loadFile >> buffer) {
            // Проходим по всем символам из массива для удаления и ищем что нужно удалить
            for (int i = 0; i < sizeof(symbols); i++) {
                if (buffer.find(symbols[i]) != string::npos) {
                    // Удаляем символ из строки
                    buffer.erase(buffer.find(symbols[i]), 1);
                }
            }

            // Переводим символы в нижний регистр
            for (int i = 0; i < buffer.length(); i++) {
                for (int j = 0; j < sizeof(upper); j++) {
                    if (upper[j] == buffer[i]) buffer[i] = lower[j];
                }
            }
            // Добавляем слово в массив
            wordArray.push_back(buffer);
        }
    }
    // Закрываем файл
    loadFile.close();
}

// Функция создания словаря
void create_Dictionary() {
    for (int i = 0; i < wordArray.size(); i++) {
        // Создаем указатели
        dictionaryWord* ptr = new dictionaryWord;
        dictionaryWord* obj = head;
        
        // Если список пуст создаем первый объект
        if (head == NULL || tail == NULL) {
            ptr->word = wordArray[i];
            ptr->next = NULL;
            tail = ptr;
            head = ptr;
        }
        else {
            // Пока в списке есть элементы
            while (obj != NULL) {
                // Если слово из массива равняется слову из списка
                if (obj->word == wordArray[i]) {
                    // Прибавляем его кол-во
                    obj->count = obj->count + 1;
                    break;
                }
                // Если не нашил совпадений
                else if (obj == tail) {
                    // Добавляем слово в хвост
                    ptr->word = wordArray[i];
                    ptr->next = NULL;
                    tail->next = ptr;
                    tail = ptr;
                    break;
                }
                obj = obj->next;
            }
        }
    }
    // Сортируем список по алфавиту
    sort(1);
    // Находим процентаж
    percentCalc();
}

// Функция нахождения соотношений
void percentCalc() {
    float i;
    dictionaryWord* obj = head;

    // Считаем общее кол-во символов
    for (i = 0; obj != NULL; i++) {
        obj = obj->next;
    }

    cout << "Общее кол-во слов: " << i << endl;
    // Обнуляем Obj
    obj = head;

    // Проходим по всем объектам
    while (obj != NULL) {
        // Находим его процентное соотношение
        obj->percent = (obj->count / i) * 100;
        obj = obj->next;
    }
}

// Функция сортировки
void sort(int n) {
    dictionaryWord* objNext = head->next;
    dictionaryWord* tempMin = head;
    dictionaryWord* temp = head;
    dictionaryWord* obj = head;

    // Если вызывали функцию самостоятельно из меню
    if (n == NULL) {
        cout << "Как будем сортировать?" << endl;
        cout << "1. По слову" << endl;
        cout << "2. Пол кол-ву" << endl;
        cin >> n;
    }

    if (n < 1 || n > 2) {
        cout << "Ошибка в выборе сортировки. Повторите попытку\n";
    }

    // Сортируем по алфавиту
    if (n == 1) {
        while (obj != NULL) {
            while (temp != NULL) {
                // Сравниваем значения (для букв это первый символ) и находим минимальное
                if (tempMin->word[0] > temp->word[0]) {
                    tempMin = temp;
                }
                temp = temp->next;
            }
            if (obj != tempMin) replace(obj, tempMin); // Меняем местами
            obj = objNext; // Присваиваем новые значения
            if (obj->next == NULL) return; // Если находимся в конце списка - выходим из функции
            objNext = obj->next;
            tempMin = obj;
            temp = obj;
        }
    }

    // Сортируем по кол-во
    if (n == 2) {
        while (obj != NULL) {
            while (temp != NULL) {
                // Сравниваем значения (для букв это первый символ) и находим минимальное
                if (tempMin->count < temp->count) {
                    tempMin = temp;
                }
                temp = temp->next;
            }
            if (obj != tempMin) replace(obj, tempMin); // Меняем местами
            obj = objNext; // Присваиваем новые значения
            if (obj->next == NULL) return; // Если находимся в конце списка - выходим из функции
            objNext = obj->next;
            tempMin = obj;
            temp = obj;
        }
    }
}

// Функция перестановки (нужна для сортировки)
void replace(dictionaryWord* temp_a, dictionaryWord* temp_b) {
    // Флаги отслеживающие менялись ли голова и хвост
    bool headChanged = false, tailChanged = false;

    // Создаем указатели на объекты списка
    dictionaryWord* temp_a_next = nullptr;
    dictionaryWord* temp_b_next = nullptr;
    dictionaryWord* temp_a_prev = head;
    dictionaryWord* temp_b_prev = head;

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

// Функция вывода
void show() {
    dictionaryWord* obj = head;

    cout << "Текущий словарь: \n";

    // Вывод
    // setw - указываем длину вывода
    // setprecision - округляем следующий вывод
    while (obj != NULL) {
        cout << setw(5) << "Слово: " << setw(25) << obj->word << setw(5) << " Кол-во: " << setw(5) << obj->count << setw(10) << setprecision(2) << " Соотношение: " << obj->percent << endl;
        obj = obj->next;
    }
}

// Функция сохранения словаря в файл
void save_Dictionary() {
    string file;
    ofstream saveDictionary;

    // Устанавливаем табуляцию слева
    saveDictionary << setiosflags(ios::left);

    dictionaryWord* obj = head;

    cout << "Введите названия файла с текстом который необходимо проанализировать: ";
    cin >> file;
    saveDictionary.open(file + ".txt");

    if (!saveDictionary.is_open()) {
        cout << "Файл невозможно открыть, либо файл не был открыт.\n";
        saveDictionary.close();
        return;
    }
    // Как в функции вывода на экран
    else {
        while (obj != NULL) {
            saveDictionary << setw(5) << "Слово: " << setw(25) << obj->word << setw(5) << " Кол-во: " << setw(5) << obj->count << setw(10) << setprecision(2) << " Соотношение: " << obj->percent << endl;
            obj = obj->next;
        }
    }

    saveDictionary.close();
    return;
}

// Функция очистки словаря
void erase() {
    dictionaryWord* obj = head;
    dictionaryWord* temp;

    // Пока есть объекты
    while (obj != NULL) {
        // Присваиваем указатели
        temp = obj;
        obj = obj->next;
        // Удаляем объект
        delete(temp);
    }

    // Обнуляем голову и хвост
    head = tail = NULL;
}

int main()
{
    // Устанавливаем табуляцию слева для вывода на экран
    cout << setiosflags(ios::left);
    setlocale(0, "");
    cout << "Частотный словарь\n";
    
    int menuChoice = NULL;


    // Меню
    do
    {
        cout << endl;
        cout << "1 - Загрузить текст для создания словаря\n";
        cout << "2 - Создать словарь\n";
        cout << "3 - Сохранить словарь в файл\n";
        cout << "4 - Вывести словарь\n";
        cout << "5 - Отсортировать словарь\n";
        cout << "6 - Очистить словарь\n";
        cout << "0 - Выйти из программы\n";
        cout << "Выберите пункт меню: ";
        cin >> menuChoice;
        cout << endl;

        if (menuChoice < 0 || menuChoice > 6) {
            cout << "Неверный пункт! Повторите попытку.\n";
        }

        if (menuChoice == 1) load_text();
        if (menuChoice == 2) create_Dictionary();
        if (menuChoice == 3) save_Dictionary();
        if (menuChoice == 4) show();
        if (menuChoice == 5) sort(NULL);
        if (menuChoice == 6) erase();

    } while (menuChoice != 0);
}