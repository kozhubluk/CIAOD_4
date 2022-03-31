#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct student
{
    int number; // Номер зачетной книжки
    string fio; // ФИО
    char group[11]; // Группа
    int mark[5]; // Оценки за 5 предметов
};

struct score
{
    float av_sc;
    int id;
};

float average_score(student st) // Вычисляет средний балл на основе 5-ти оценок
{
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += st.mark[i];
    }
    return ((float)sum) / 5;
}

vector <student> input1(int& n) // Заполнение таблицы с клавиатуры 
{
    cout << "Enter numbers of students: ";
    cin >> n;
    vector <student> v_s(n);
    for (int i = 0; i < n; i++)
    {
        cout << "student #" << i + 1 << endl;
        cout << "student's id: "; cin >> v_s[i].number;
        cin.ignore();
        cout << "student'f full name: "; getline(cin, v_s[i].fio);
        cout << "student's group: "; cin >> v_s[i].group;
        cout << "student's marks: ";
        for (int j = 0; j < 5; j++)
        {
            cin >> v_s[i].mark[j];
        }
    }
    return v_s;
}

vector <student> input2(int& n) // Считывание информации с данными о студентах
{
    ifstream in("task4.txt");
    if (!in.is_open())
    {
        cout << "Error of file reading :(\n";
        n = 0;
        in.close();
        vector <student> v(0);
        return v;
    }
    else
    {
        cout << "fdsf";
        in >> n;
        cout << n;
        vector <student> v_s(n);
        for (int i = 0; i < n; i++)
        {
            in >> v_s[i].number;
            in.ignore();
            getline(in, v_s[i].fio);
            in >> v_s[i].group;
            for (int j = 0; j < 5; j++)
            {
                in >> v_s[i].mark[j];
            }
        }
        in.close();
        return v_s;
    }
}

void output(vector <student> &v_s, int size) // Вывод таблицы с данным о всех студентах
{
    cout << "============================================================================================\n";
    cout << setw(16) << left << "| STUDENT'S ID" << "| " << setw(40) << left << "FULL NAME" << "| ";
    cout << setw(14) << left << "GROUP" << "| " << setw(15) << left << "MARKS" << "|\n";
    cout << "=============================================================================================\n";
    for (int i = 0; i < size; i++)
    {
        cout << "| " << setw(14) << v_s[i].number;
        cout << "| " << setw(40) << v_s[i].fio;
        cout << "| " << setw(14) << v_s[i].group << "| ";
        for (int j = 0; j < 5; j++)
        {
            cout << setw(3) << v_s[i].mark[j];
        }
        cout << "|\n";
        cout << "--------------------------------------------------------------------------------------------\n";
    }
}

void add(vector <student>& v_s, int& n) // Добавить новую запись о студенте
{
    student news;
    cout << "Please, enter following information about new student:\n";
    cout << "student's id: "; cin >> news.number;
    cin.ignore();
    cout << "student'f full name: "; getline(cin, news.fio);
    cout << "student's group: "; cin >> news.group;
    cout << "student's marks: ";
    for (int j = 0; j < 5; j++)
    {
        cin >> news.mark[j];
    }
    v_s.push_back(news);
    n++; // Увеличиваем количество студентов 
}


void creat_list(vector <student> v_s, int n)
{
    int list_size = 0;
    score temp;
    vector <score> a(0);
    for (int i = 0; i < n; i++) // Записываем в массив номера зачетных книжек студентов с ср. баллом больше 4.0
    {
        if (average_score(v_s[i]) > 4.0)
        {
            temp.av_sc = average_score(v_s[i]);
            temp.id = v_s[i].number;
            a.push_back(temp);
            list_size++;
        }
    }

    // Сортировка списка по убыванию с помощью сортировки выбором

    int max; // Для записи минимального значения
    for (int i = 0; i < list_size; i++)
    {
        max = i; // запомним номер текущей ячейки, как ячейки с минимальным значением
        for (int j = i + 1; j < list_size; j++)
        {
            if (a[j].av_sc > a[max].av_sc)
            {
                max = j;
            }
        }
        if (i != max)
        {
            temp = a[i];
            a[i] = a[max];
            a[max] = temp;
        }
    }

    // Выводим список 
    cout << "List of students with a score above 4.0 \n";
    for (int i = 0; i < list_size; i++)
    {
        cout << i + 1 << ") " << a[i].id << " average score: " << a[i].av_sc << endl;
    }
}

void delete_inf(vector <student> &v_s, int& n, float s) // Удаление записи о студентах, средний балл которых < s
{
    int dif = 0;
    for (int i = 0; i < n; i++)
    {
        if (average_score(v_s[i]) < s)
        {
            dif++;
        }
    }
    n = n - dif;
    int j = 0;
    while (j < n)
    {
        if (average_score(v_s[j]) < s)
        {
            v_s.erase(v_s.begin() + j);
        }
        else
        {
            j++;
        }
    }
}

int main()
{
    cout << "fd";
    int n, c, num;
    float b;
    vector <student> s;
    cout << "Type 1 to enter student data using the keyboard.\n";
    cout << "Type 2 to read student data from the file.\n";
    cin >> c;
    if (c == 2)
    {
        s = input2(n);
    }
    else
    {
        s = input1(n);
    }
    output(s, n);
    creat_list(s, n);
    cout << "Delete information about students with average score below ";
    cin >> b;
    delete_inf(s, n, b);
    output(s, n);
    cout << "How many students to add to the table: ";
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        add(s, n);
    }
    output(s, n);
    return 0;
}

