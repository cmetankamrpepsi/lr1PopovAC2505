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
        if (!(std::cin >> value) || value < min_val || value > max_val || std::cin.peek() != '\n')
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
double get_double_Input(const string& prompt, double min_val, double max_val)
{
    cout << prompt << endl;
    double value;
    while (true)
    {
        if (!(std::cin >> value) || value < min_val || value > max_val || std::cin.peek() != '\n')
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
void savePipe(ofstream& fout, const Pipe& p, bool pipeExists)
{
    fout << pipeExists << "\n";
    if (pipeExists) {
        fout << p.kilometer_mark << "\n";
        fout << p.length << " " << p.diameter << " " << p.inRepair << "\n";
    }
}

void saveCS(ofstream& fout, const CS& c, bool csExists)
{
    fout << csExists << "\n";
    if (csExists) {
        fout << c.CS_name << "\n";
        fout << c.workshops_numbers << " " << c.work_workshop_numbers << " " << c.stationClass << "\n";
    }
}

void saveData(const Pipe& p, bool pipeExists, const CS& c, bool csExists)
{
    ofstream fout("data.txt");
    if (!fout.is_open()) {
        cout << "Не удалось открыть data.txt для записи." << endl;
        return;
    }

    savePipe(fout, p, pipeExists);
    saveCS(fout, c, csExists);

    fout.close();
    cout << "Данные сохранены в data.txt" << endl;
}
bool loadPipe(ifstream& fin, Pipe& p, bool& pipeExists)
{
    bool tempExists = false;
    if (!(fin >> tempExists)) return false;

    if (tempExists) {
        getline(fin >> ws, p.kilometer_mark);
        fin >> p.length >> p.diameter >> p.inRepair;
        pipeExists = true;
        return true;   
    }
    return false;     
}
bool loadCS(ifstream& fin, CS& c, bool& csExists)
{
    bool tempExists = false;
    if (!(fin >> tempExists)) return false;

    if (tempExists) {
        getline(fin >> ws, c.CS_name);
        fin >> c.workshops_numbers >> c.work_workshop_numbers >> c.stationClass;
        csExists = true;
        return true;   
    }
    return false;     
}
void loadData(Pipe& p, bool& pipeExists, CS& c, bool& csExists)
{
    ifstream fin("data.txt");
    if (!fin.is_open()) {
        cout << "Файл data.txt не найден." << endl;
        return;
    }

    bool pipeLoaded = loadPipe(fin, p, pipeExists);
    bool csLoaded = loadCS(fin, c, csExists);

    fin.close();

    if (pipeLoaded) {
        cout << "Труба загружена." << endl;
    }
    else {
        cout << "Труба не загружена, так как её не существует в файле." << endl;
    }

    if (csLoaded) {
        cout << "КС загружена." << endl;
    }
    else {
        cout << "КС не загружена, так как её не существует в файле." << endl;
    }
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Pipe My_Pipe;
    CS My_CS;
    bool pipeExists = false;  
    bool csExists = false;
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
        cout << "......." << endl;
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
            pipeExists = true;
            break;

        case 2:
            if (My_CS.workshops_numbers > 0)
            {
                cout << "КС уже создана. Перезаписать? (1 - да, 0 - нет): ";
                if (get_int_Input("", 0, 1) == 0)
                    break;
            }
            inputCS(My_CS);
            csExists = true;
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
            saveData(My_Pipe, pipeExists, My_CS, csExists);
            break;

        case 7:
            loadData(My_Pipe, pipeExists, My_CS, csExists);
            break;
        case 0:
            cout << "Выход из программы." << endl;
            return 0;
        }
    }

    return 0;
}

