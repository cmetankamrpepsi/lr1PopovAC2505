#include <iostream>
#include <string>
#include <clocale>
#include <windows.h>
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
void inputPipe(Pipe& p);
void printPipe(const Pipe& p);
void inputCS(CS& c);
void printCS(const CS& c);
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
            inputPipe(My_Pipe);
            break;

        case 2:
            inputCS(My_CS);
            break;

        case 3:
            printPipe(My_Pipe);
            printCS(My_CS);
            break;

        case 4:
            cout << ">>> Пункт 'Редактировать трубу' (в разработке)" << endl;
            break;

        case 5:
            cout << ">>> Пункт 'Редактировать КС' (в разработке)" << endl;
            break;

        case 6:
            cout << ">>> Пункт 'Сохранить' (в разработке)" << endl;
            break;

        case 7:
            cout << ">>> Пункт 'Загрузить' (в разработке)" << endl;
            break;

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
        
        if (!(cin>>value))
        { 
            cout << "Ошибка, значение должно быть числом от " << min_val << " до " << max_val << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if ((value < min_val) || (value > max_val))
        {
            cout << "Ошибка, значение должно быть числом от " << min_val << " до " << max_val << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (cin.peek() != '\n')
        {
            cout << "Ошибка, значение должно быть числом от " << min_val << " до " << max_val << endl;
            cin.clear();
            cin.ignore(10000, '\n');
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

        if (!(cin >> value))
        {
            cout << "Ошибка, значение должно быть вещественным числом от " << min_val << " до " << max_val << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if ((value < min_val) || (value > max_val))
        {
            cout << "Ошибка, значение должно быть вещественным числом от " << min_val << " до " << max_val << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (cin.peek() != '\n')
        {
            cout << "Ошибка, значение должно быть вещественным числом от " << min_val << " до " << max_val << endl;
            cin.clear();
            cin.ignore(10000, '\n');
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
    cin.ignore(10000, '\n');
    getline(cin, str);
    while (str.empty() /*строка пустая*/)
    {
        cout << "Ошибка, строка не может быть пустой. Повторите ввод: ";
        getline(cin, str);
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
    p.length = get_double_Input("Введите длину трубы (км)(вещественное число от 0 до 100000): ", 0.0, 100000.0);
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