#include <iostream>
#include <string>
#include <clocale>
#include <windows.h>
#include <fstream>
using namespace std;
struct Pipe {
    string kilometer_mark = "";
    double length = -1.0;
    int diameter = -1;
    bool inRepair = false ;
};
struct CS {
    string CS_name = "";
    int workshops_numbers = -1; 
    int work_workshop_numbers= -1; 
    int stationClass = -1; };
int get_int_Input(const string& prompt /*запрос*/, int min_val, int max_val)
{
    cout << prompt << endl;
    int value;
    while (true)
    {

        if (!(std::cin >> value))
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
    if (p.diameter < 0) {
        cout << "Труба не создана. Сначала добавьте её через главное меню." << endl;
        return;
    }

    cout << "\nТекущий статус: " << (p.inRepair ? "В ремонте" : "Не в ремонте") << endl;
    cout << "Переключить статус? (1 - да, 0 - нет): ";
    if (get_int_Input("", 0, 1) == 1) {
        p.inRepair = !p.inRepair;
        cout << "Новый статус: " << (p.inRepair ? "В ремонте" : "Не в ремонте") << endl;
    }
}
void editCS(CS& c)
{
    if (c.workshops_numbers < 0) {
        cout << "КС не создана. Сначала добавьте её через главное меню." << endl;
        return;
    }

    int choice;
    while (true)
    {
        cout << "\nУправление цехами КС" << endl;
        cout << "Цехов в работе: " << c.work_workshop_numbers
            << " из " << c.workshops_numbers << endl;
        cout << "1. Запустить цех" << endl;
        cout << "2. Остановить цех" << endl;
        cout << "0. Назад в главное меню" << endl;

        choice = get_int_Input("Ваш выбор: ", 0, 2);

        if (choice == 1)
        {
            if (c.work_workshop_numbers < c.workshops_numbers) {
                c.work_workshop_numbers++;
                cout << "Цех запущен. Теперь в работе: "
                    << c.work_workshop_numbers << " из " << c.workshops_numbers << endl;
            }
            else {
                cout << "Все цеха уже работают!" << endl;
            }
        }
        else if (choice == 2)
        {
            if (c.work_workshop_numbers > 0) {
                c.work_workshop_numbers--;
                cout << "Цех остановлен. Теперь в работе: "
                    << c.work_workshop_numbers << " из " << c.workshops_numbers << endl;
            }
            else {
                cout << "Нет работающих цехов!" << endl;
            }
        }
        else break; 
    }
}
void saveAll(const Pipe& p, const CS& c)
{
    ofstream fout("data.txt");
    if (!fout.is_open()) {
        cout << "Не удалось открыть data.txt для записи." << endl;
        return;
    }

    fout << p.kilometer_mark << endl;
    fout << p.length << endl;
    fout << p.diameter << endl;
    fout << (p.inRepair ? 1 : 0) << endl;
    fout << c.CS_name << endl;
    fout << c.workshops_numbers << endl;
    fout << c.work_workshop_numbers << endl;
    fout << c.stationClass << endl;

    fout.close();
    cout << "Данные сохранены в data.txt" << endl;
}
void loadAll(Pipe& p, CS& c)
{
    ifstream fin("data.txt");
    if (!fin.is_open()) {
        cout << "Файл data.txt не найден." << endl;
        return;
    }
    string tempMark;
    double tempLength;
    int tempDiameter, tempRepair;

    if (!getline(fin, tempMark)) { cout << "Ошибка чтения файла." << endl; fin.close(); return; }
    if (!(fin >> tempLength)) { cout << "Ошибка чтения файла." << endl; fin.close(); return; }
    if (!(fin >> tempDiameter)) { cout << "Ошибка чтения файла." << endl; fin.close(); return; }
    if (!(fin >> tempRepair)) { cout << "Ошибка чтения файла." << endl; fin.close(); return; }
    fin.ignore(10000, '\n'); 


    string tempName;
    int tempTotal, tempWorking, tempClass;

    if (!getline(fin, tempName)) { cout << "Ошибка чтения файла." << endl; fin.close(); return; }
    if (!(fin >> tempTotal)) { cout << "Ошибка чтения файла." << endl; fin.close(); return; }
    if (!(fin >> tempWorking)) { cout << "Ошибка чтения файла." << endl; fin.close(); return; }
    if (!(fin >> tempClass)) { cout << "Ошибка чтения файла." << endl; fin.close(); return; }
    fin.close();

  
    if (tempDiameter < 0)
    {
        cout << "Труба не загружена, так как её не существует." << endl;
    }
    else if (tempMark.empty())
    {
        cout << "Ошибка: пустая километровая отметка в файле." << endl;
    }
    else if (tempLength < 0 || tempLength > 100000)
    {
        cout << "Ошибка: неверная длина в файле." << endl;
    }
    else if (tempDiameter < 1 || tempDiameter > 10000)
    {
        cout << "Ошибка: неверный диаметр в файле." << endl;
    }
    else if (tempRepair != 0 && tempRepair != 1)
    {
        cout << "Ошибка: неверный флаг ремонта в файле." << endl;
    }
    else
    {
        p.kilometer_mark = tempMark;
        p.length = tempLength;
        p.diameter = tempDiameter;
        p.inRepair = (tempRepair == 1);
        cout << "Труба загружена." << endl;
    }

    if (tempTotal < 0)
    {
        cout << "КС не загружена, так как её не существует." << endl;
    }
    else if (tempName.empty())
    {
        cout << "Ошибка: пустое название КС в файле." << endl;
    }
    else if (tempTotal < 1 || tempTotal > 100)
    {
        cout << "Ошибка: неверное общее число цехов в файле." << endl;
    }
    else if (tempWorking < 0 || tempWorking > tempTotal)
    {
        cout << "Ошибка: неверное число работающих цехов в файле." << endl;
    }
    else if (tempClass < 1 || tempClass > 3)
    {
        cout << "Ошибка: неверный класс станции в файле." << endl;
    }
    else
    {
        c.CS_name = tempName;
        c.workshops_numbers = tempTotal;
        c.work_workshop_numbers = tempWorking;
        c.stationClass = tempClass;
        cout << "КС загружена." << endl;
    }
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Pipe My_Pipe;
    CS My_CS;
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
            saveAll(My_Pipe, My_CS);
            break;

        case 7:
            loadAll(My_Pipe, My_CS);
            break;

        case 0:
            cout << "Выход из программы." << endl;
            return 0;
        }
    }

    return 0;
}












