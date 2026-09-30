#include <iostream>
#include <string>
#include <clocale>
#include <windows.h>
#include <fstream>
using namespace std;
struct Pipe {
    string kilometer_mark;
    double length;
    int diameter;
    bool inRepair;
};
struct CS {
    string CS_name;
    int workshops_numbers; 
    int work_workshop_numbers; 
    int stationClass; };
void loadPipe(Pipe& p);
void inputPipe(Pipe& p);
void printPipe(const Pipe& p);
void inputCS(CS& c);
void printCS(const CS& c);
void editPipe(Pipe& p);
void editCS(CS& c);
void savePipe(const Pipe& p);
void saveCS(const CS& c);
void loadCS(CS& c);
int get_int_Input(const string & prompt /*запрос*/, int min_val, int max_val);
double get_double_Input(const string & prompt, double min_val, double max_val);
string get_string_Input(const string& prompt);
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Pipe My_Pipe= { "", -1.0, -1, false };
    CS My_CS = { "", -1, -1, -1 };
    int choice;

    while (true)
    {
        cout << "\nГлавное меню" << endl;
        cout << "1. Добавить трубу" << endl;
        cout << "2. Добавить КС" << endl;
        cout << "3. Просмотр всех объектов" << endl;
        cout << "4. Редактировать трубу" << endl;
        cout << "5. Редактировать КС" << endl;
        cout << "6. Сохранить" << endl;
        cout << "7. Загрузить" << endl;
        cout << "0. Выход" << endl;

        choice = get_int_Input("Ваш выбор: ", 0, 7); 

        switch (choice)
        {
        case 1:
            if (My_Pipe.diameter > 0)  
            {
                cout << "Труба уже создана. Перезаписать? (1 - да, 0 - нет): ";
                if (get_int_Input("", 0, 1) == 0)
                    break;  
            }
            inputPipe(My_Pipe);
            break;

        case 2:
            if (My_CS.workshops_numbers > 0)
            {
                cout << "КС уже создана. Перезаписать? (1 - да, 0 - нет): ";
                if (get_int_Input("", 0, 1) == 0)
                    break;
            }
            inputCS(My_CS);
            break;

        case 3:
            printPipe(My_Pipe);
            printCS(My_CS);
            break;

        case 4:
            editPipe(My_Pipe);
            break;
        case 5:
            editCS(My_CS);
            break;

        case 6:
        {
            int saveChoice;
            while (true)
            {
                cout << "\nСохранение в файл" << endl;
                cout << "1. Сохранить трубу" << endl;
                cout << "2. Сохранить КС" << endl;
                cout << "3. Сохранить всё" << endl;
                cout << "0. Назад в главное меню" << endl;

                saveChoice = get_int_Input("Ваш выбор: ", 0, 3);

                if (saveChoice == 1) { savePipe(My_Pipe); }
                else if (saveChoice == 2) { saveCS(My_CS); }
                else if (saveChoice == 3) { savePipe(My_Pipe); saveCS(My_CS); }
                else break; 
            }
            break;
        }

        case 7:
        {
            int loadChoice;
            while (true)
            {
                cout << "\n--- Загрузка ---" << endl;
                cout << "1. Загрузить трубу" << endl;
                cout << "2. Загрузить КС" << endl;
                cout << "3. Загрузить всё" << endl;
                cout << "0. Назад в главное меню" << endl;

                loadChoice = get_int_Input("Ваш выбор: ", 0, 3);

                if (loadChoice == 1) { loadPipe(My_Pipe); }
                else if (loadChoice == 2) { loadCS(My_CS); }
                else if (loadChoice == 3) { loadPipe(My_Pipe); loadCS(My_CS); }
                else break; 
            }
            break;
        }

        case 0:
            cout << "Выход из программы." << endl;
            return 0;
        }
    }

    return 0;
}
int get_int_Input(const string& prompt /*запрос*/, int min_val, int max_val)
{
    cout << prompt << endl;
    int value;
    while (true)
    {
        
        if (!(std::cin>>value))
        { 
            cout << "Ошибка, значение должно быть числом от " << min_val << " до " << max_val << endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if ((value < min_val) || (value > max_val))
        {
            cout << "Ошибка, значение должно быть числом от " << min_val << " до " << max_val << endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (std::cin.peek() != '\n')
        {
            cout << "Ошибка, значение должно быть числом от " << min_val << " до " << max_val << endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        break;

    }
    return value;
}
double get_double_Input(const string& prompt /*запрос*/, double min_val, double max_val)
{
    cout << prompt << endl;
    double value;
    while (true)
    {

        if (!(std::cin >> value))
        {
            cout << "Ошибка, значение должно быть вещественным числом от " << min_val << " до " << max_val << endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if ((value < min_val) || (value > max_val))
        {
            cout << "Ошибка, значение должно быть вещественным числом от " << min_val << " до " << max_val << endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (std::cin.peek() != '\n')
        {
            cout << "Ошибка, значение должно быть вещественным числом от " << min_val << " до " << max_val << endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        break;

    }
    return value;
}
string get_string_Input(const string& prompt)
{
    cout << prompt << endl;
    string str;
    std::cin.ignore(10000, '\n');
    getline(std::cin, str);
    while (str.empty() /*строка пустая*/)
    {
        cout << "Ошибка, строка не может быть пустой. Повторите ввод: ";
        getline(std::cin, str);
    }
    return str;
}
void inputCS(CS& c)
{
    c.workshops_numbers = get_int_Input("Введите общее количество цехов(целое от 1 до 100): ", 1, 100);
    c.work_workshop_numbers = get_int_Input("Введите количество цехов в работе(целое число до количества цехов включительно): ", 0, c.workshops_numbers);
    c.stationClass = get_int_Input("Введите класс станции (1-3): ", 1, 3);
    c.CS_name = get_string_Input("Введите название КС: ");  // <-- было getStringInput
}

void printCS(const CS& c)
{
    if (c.workshops_numbers < 0)
    {
        cout << "\nКС не создана" << endl;
        return;
    }
    cout << "\nИнформация о КС" << endl;
    cout << "Название: " << c.CS_name << endl;
    cout << "Всего цехов: " << c.workshops_numbers << endl;
    cout << "Цехов в работе: " << c.work_workshop_numbers << endl;
    cout << "Класс станции: " << c.stationClass << endl;
}
void inputPipe(Pipe& p)
{
    p.length = get_double_Input("Введите длину трубы (км)(вещественное число от 0 до 100000): ", 1.0, 100000.0);
    p.diameter = get_int_Input("Введите диаметр трубы (мм)(целое число от 0 до 10000): ", 1, 10000);
    p.inRepair = (get_int_Input("В ремонте? (1 - да, 0 - нет): ", 0, 1) == 1);
    p.kilometer_mark = get_string_Input("Введите километровую отметку: ");
}
void printPipe(const Pipe& p)
{
    if (p.diameter < 0)
    {
        cout << "\nТруба не создана" << endl;
        return;
    }
    cout << "\nИнформация о трубе" << endl;
    cout << "Километровая отметка: " << p.kilometer_mark << endl;
    cout << "Длина (км): " << p.length << endl;
    cout << "Диаметр (мм): " << p.diameter << endl;
    cout << "В ремонте: " << (p.inRepair ? "Да" : "Нет") << endl;
}
void editPipe(Pipe& p)
{
    if (p.diameter < 0)
    {
        cout << "Труба не создана. Сначала добавьте её через главное меню." << endl;
        return; 
    }

    int choice;
    while (true)
    {
        cout << "\nРедактирование трубы" << endl;
        cout << "1. Показать текущие данные" << endl;
        cout << "2. Изменить флаг 'в ремонте'" << endl;
        cout << "3. Изменить длину" << endl;
        cout << "4. Изменить диаметр" << endl;
        cout << "5. Изменить километровую отметку" << endl;
        cout << "0. Выйти в главное меню" << endl;

        choice = get_int_Input("Ваш выбор: ", 0, 5);

        switch (choice)
        {
        case 1:
            printPipe(p);
            break;

        case 2:
            p.inRepair = !p.inRepair; 
            cout << "Флаг изменён. В ремонте: " << (p.inRepair ? "Да" : "Нет") << endl;
            break;

        case 3:
            p.length = get_double_Input("Новая длина (км): ", 1.0, 100000.0);
            break;

        case 4:
            p.diameter = get_int_Input("Новый диаметр (мм): ", 1, 10000);
            break;

        case 5:
            p.kilometer_mark = get_string_Input("Новая километровая отметка: ");
            break;

        case 0:
            return;
        }
    }
}
void editCS(CS& c)
{
    if (c.workshops_numbers < 0)
    {
        cout << "КС не создана. Сначала добавьте её через главное меню." << endl;
        return;
    }

    int choice;
    while (true)
    {
        cout << "\nРедактирование КС" << endl;
        cout << "1. Показать текущие данные" << endl;
        cout << "2. Изменить общее количество цехов" << endl;
        cout << "3. Изменить количество работающих цехов" << endl;
        cout << "4. Изменить название" << endl;
        cout << "5. Изменить класс станции" << endl;
        cout << "0. Выйти в главное меню" << endl;

        choice = get_int_Input("Ваш выбор: ", 0, 5);

        switch (choice)
        {
        case 1:
            printCS(c);
            break;

        case 2:
            c.workshops_numbers = get_int_Input(
                "Введите новое общее количество цехов (1-100): ", 1, 100);
            if (c.work_workshop_numbers > c.workshops_numbers)
            {
                cout << "Внимание! Количество работающих цехов ("
                    << c.work_workshop_numbers
                    << ") больше общего количества цехов ("
                    << c.workshops_numbers << ")." << endl;
                cout << "Необходимо ввести новое количество работающих цехов." << endl;

                c.work_workshop_numbers = get_int_Input(
                    "Введите количество цехов в работе(целое число до количества цехов включительно): ",
                    0, c.workshops_numbers);
            }
            break;

        case 3:
            c.work_workshop_numbers = get_int_Input(
                "Введите количество цехов в работе(целое число до количества цехов включительно): ",
                0, c.workshops_numbers);
            break;

        case 4:
            c.CS_name = get_string_Input("Введите новое название КС: ");
            break;

        case 5:
            c.stationClass = get_int_Input("Введите новый класс станции (1-3): ", 1, 3);
            break;

        case 0:
            return;
        }
    }
}
void savePipe(const Pipe& p)
{
    if (p.diameter < 0) {
        cout << "Труба не создана. Нечего сохранять." << endl;
        return;
    }
    ofstream fout("pipe.txt");
    if (!fout.is_open()) {
        cout << "Не удалось открыть pipe.txt для записи." << endl;
        return;
    }
    fout << p.kilometer_mark << endl;
    fout << p.length << endl;
    fout << p.diameter << endl;
    fout << (p.inRepair ? 1 : 0) << endl;
    fout.close();
    cout << "Труба сохранена в pipe.txt" << endl;
}
void loadPipe(Pipe& p)
{
    ifstream fin("pipe.txt");
    if (!fin.is_open()) {
        cout << "Файл pipe.txt не найден." << endl;
        return;
    }
    string tempMark;
    double tempLength;
    int tempDiameter;
    int tempRepair;
    if (!getline(fin, tempMark)) { cout << "Ошибка чтения отметки." << endl; return; }
    if (!(fin >> tempLength)) { cout << "Ошибка чтения длины." << endl; return; }
    if (!(fin >> tempDiameter)) { cout << "Ошибка чтения диаметра." << endl; return; }
    if (!(fin >> tempRepair)) { cout << "Ошибка чтения флага." << endl; return; }
    fin.close();
    if (tempMark.empty()) { cout << "Пустая отметка." << endl; return; }
    if (tempLength < 0 || tempLength > 100000) { cout << "Неверная длина." << endl; return; }
    if (tempDiameter < 1 || tempDiameter > 10000) { cout << "Неверный диаметр." << endl; return; }
    if (tempRepair != 0 && tempRepair != 1) { cout << "Флаг должен быть 0 или 1." << endl; return; }
    p.kilometer_mark = tempMark;
    p.length = tempLength;
    p.diameter = tempDiameter;
    p.inRepair = (tempRepair == 1);
    cout << "Труба загружена." << endl;
}
void saveCS(const CS& c)
{
    if (c.workshops_numbers < 0) {
        cout << "КС не создана. Нечего сохранять." << endl;
        return;
    }
    ofstream fout("cs.txt");
    if (!fout.is_open()) {
        cout << "Не удалось открыть cs.txt для записи." << endl;
        return;
    }
    fout << c.CS_name << endl;
    fout << c.workshops_numbers << endl;
    fout << c.work_workshop_numbers << endl;
    fout << c.stationClass << endl;
    fout.close();
    cout << "КС сохранена в cs.txt" << endl;
}
void loadCS(CS& c)
{
    ifstream fin("cs.txt");
    if (!fin.is_open()) {
        cout << "Файл cs.txt не найден." << endl;
        return;
    }
    string tempName;
    int tempTotal;
    int tempWorking;
    int tempClass;
    if (!getline(fin, tempName)) { cout << "Ошибка чтения названия." << endl; return; }
    if (!(fin >> tempTotal)) { cout << "Ошибка чтения общего количества." << endl; return; }
    if (!(fin >> tempWorking)) { cout << "Ошибка чтения работающих." << endl; return; }
    if (!(fin >> tempClass)) { cout << "Ошибка чтения класса." << endl; return; }
    fin.close();
    if (tempName.empty()) { cout << "Пустое название." << endl; return; }
    if (tempTotal < 1 || tempTotal > 100) { cout << "Неверное общее число цехов." << endl; return; }
    if (tempWorking < 0 || tempWorking > tempTotal) { cout << "Неверное количество рабочих цехов" << endl; return; }
    if (tempClass < 1 || tempClass > 3) { cout << "Неверный класс станции." << endl; return; }
    c.CS_name = tempName;
    c.workshops_numbers = tempTotal;
    c.work_workshop_numbers = tempWorking;
    c.stationClass = tempClass;
    cout << "КС загружена." << endl;
}