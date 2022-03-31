#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int N = 50; // Максимальный размер таблицы 

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

void input1(student v_s[], int& n) // Заполнение таблицы с клавиатуры 
{
    do
    {
        cout << "Enter numbers of students: ";
        cin >> n;
    } while (n > 50); 
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
}

void input2(student v_s[], int& n) // Считывание информации с данными о студентах
{
    ifstream in("task4.txt");
    if (!in.is_open())
    {
        cout << "Error of file reading :(\n";
    }
    else
    {
        in >> n;
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
    }
    in.close();
}

    void output(student v_s[], int size) // Вывод таблицы с данным о всех студентах
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

void add(student v_s[], int& n) // Добавить новую запись о студенте
{
    cout << "Please, enter following information about new student:\n";
    cout << "student's id: "; cin >> v_s[n].number;
    cin.ignore();
    cout << "student'f full name: "; getline(cin, v_s[n].fio);
    cout << "student's group: "; cin >> v_s[n].group;
    cout << "student's marks: ";
    for (int j = 0; j < 5; j++)
    {
        cin >> v_s[n].mark[j];
    }
    n++; // Увеличиваем количество студентов 
}


void creat_list(student v_s[], int n)
{
    int list_size = 0;
    score a[N];
    for (int i = 0; i < n; i++) // Записываем в массив номера зачетных книжек студентов с ср. баллом больше 4.0
    {
        if (average_score(v_s[i]) > 4.0)
        {
            a[list_size].av_sc = average_score(v_s[i]);
            a[list_size].id = v_s[i].number;
            list_size++;
        }
    }

    // Сортировка списка по убыванию с помощью сортировки выбором

    int max; // Для записи минимального значения
    score temp;
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

void delete_inf(student v_s[], int& n, float s) // Удаление записи о студентах, средний балл которых < s
{
    int dif = 0;
    for (int i = 0; i < n; i++)
    {
        if (average_score(v_s[i]) < s)
        {
            dif++;
        }
    }
    for (int i = 0; i < (n - dif); i++)
    {
        int j = i;
        while (average_score(v_s[j]) < s && j < n) // Переставляем элементы, которые не удовлетворяют условия перемщаются в конец 
        {
            j++;
        }
        swap(v_s[i], v_s[j]);
    }
    n = n - dif; // изменяем размер таблицы
}

int main()
{
    student s[N];
    int n, c, num;
    float b;
    cout << "Type 1 to enter student data using the keyboard.\n";
    cout << "Type 2 to read student data from the file.\n";
    cin >> c;
    switch (c)
    {
    case 1:
        input1(s, n);
        break;
    case 2:
        input2(s, n);
        break;
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

