#pragma warning(disable : 4996)

// Метод Дейкстра 
// Граф 14.4.5



#include <iostream>
#include <iostream>
#include <string>
#include <windows.h>
#include <locale>

#pragma warning(suppress : 4996)


using namespace std;

void addFirstNode(); // Добавляет первый корень
void add(); // Добавить Элемент в связь
void print(); // Добавляет вывод
void fillingTable(); // Вывод кратчайшего пути


struct node {
    struct ConList;
    struct los;
    int countElement = 0;

    los* first = new los;

    struct Node {
        string name;
        ConList* firstPtrCon = NULL;
    };

    void addFirstNode() {
        cout << "Введите название начального  Корня: ";
        string nameNode;
        cin >> nameNode;
        first->Nodes = new Node;
        first->Nodes->name = nameNode;
        countElement = 1;
    }

    void add() {
        los* element = first;
        string nameNode1;
        string nameNode2;
        int con;

        while (true) {
            if (element->next == NULL) {
                element->next = new los;
                element = element->next;
                cout << "Напишите название Корня: ";;
                cin >> nameNode1;
                element->Nodes = new Node;
                element->Nodes->name = nameNode1;
                break;
            }
            else {
                element = element->next;
            }
        }

        while (true) {
            int workTheme = 0;
            cout << "0 - Добавить Корню связь с другим Корнем" << endl;
            cout << "1 - Добавить данный корень в граф" << endl;
            cout << "Введите команду: ";
            cin >> workTheme;
            if (workTheme == 0) {
                cout << "Введите имя соседствующего Корня: ";
                cin >> nameNode2;
                cout << "Введите длину связи: ";
                cin >> con;
                ConList* parent = element->Nodes->firstPtrCon;
                while (true) {
                    if (parent == NULL) {
                        element->Nodes->firstPtrCon = new ConList;
                        element->Nodes->firstPtrCon->name = nameNode2;
                        element->Nodes->firstPtrCon->lenght = con;
                        break;
                    }
                    else if (parent->next == NULL) {
                        parent->next = new ConList;
                        parent->next->name = nameNode2;
                        parent->next->lenght = con;
                        break;
                    }
                    parent = parent->next;
                }

                los* element = first;
                while (true) {
                    if (element == NULL) {
                        break;
                    }
                    else {
                        if (element->Nodes->name == nameNode2) {
                            ConList* parentEl = element->Nodes->firstPtrCon;
                            while (true) {
                                if (parentEl == NULL) {
                                    element->Nodes->firstPtrCon = new ConList;
                                    element->Nodes->firstPtrCon->name = nameNode1;
                                    element->Nodes->firstPtrCon->lenght = con;
                                    break;
                                }
                                else if (parentEl->next == NULL) {
                                    parentEl->next = new ConList;
                                    parentEl->next->name = nameNode1;
                                    parentEl->next->lenght = con;
                                    break;
                                }
                                parentEl = parentEl->next;
                            }
                        }
                    }
                    element = element->next;
                }

            }
            else if (workTheme == 1) {
                cout << "Корень добавлен" << endl;
                break;
            }
            else {
                cout << "ERROR : Comand Type" << endl;
            }
        }
        countElement++;
    }


    struct ConList {
        string name;
        ConList* next = NULL;
        int lenght;

    };

    struct los {
        los* next = NULL;
        Node* Nodes = new Node;
    };

    void print() {
        los* element = first;

        while (element != NULL) {
            ConList* bufCon = element->Nodes->firstPtrCon;
            while (bufCon != NULL) {
                cout << "  " << element->Nodes->name << "--" << bufCon->lenght << "->" << bufCon->name << endl;
                bufCon = bufCon->next;
            }

            element = element->next;
        }
    }

    void fillingTable() {
        los* element = first;
        int i = 0;
        while (element != 0) {
            i++;
            element = element->next;
        }

        const int SIZE = 9;
        int a[SIZE][SIZE];
        int d[SIZE];
        int v[SIZE];
        string names[SIZE];
        int temp, minindex, min;
        int begin_index = 0;
        element = first;
        for (int j = 0; j < SIZE; j++) {
            names[j] = element->Nodes->name;
            element = element->next;
        }

        element = first;
        for (int i = 0; i < SIZE; i++) {

            ConList* bufCon = element->Nodes->firstPtrCon;
            a[i][i] = 0;
            for (int j = 0; j < SIZE; j++) {
                ConList* bufCon = element->Nodes->firstPtrCon;
                int len = 0;
                while (bufCon != NULL) {
                    if (bufCon->name == names[j]) {
                        len = bufCon->lenght;
                    }
                    bufCon = bufCon->next;
                }
                a[i][j] = len;
                a[j][i] = len;

            }

            element = element->next;
        }
        for (int i = 0; i < SIZE; i++)
        {
            d[i] = 10000;
            v[i] = 1;
        }
        d[begin_index] = 0;
        do {
            minindex = 10000;
            min = 10000;
            for (int i = 0; i < SIZE; i++)
            {
                if ((v[i] == 1) && (d[i] < min))
                {
                    min = d[i];
                    minindex = i;
                }
            }
            if (minindex != 10000)
            {
                for (int i = 0; i < SIZE; i++)
                {
                    if (a[minindex][i] > 0)
                    {
                        temp = min + a[minindex][i];
                        if (temp < d[i])
                        {
                            d[i] = temp;
                        }
                    }
                }
                v[minindex] = 0;
            }
        } while (minindex < 10000);
        cout << "\nКратчайшие расстояния до вершин: \n";
        for (int i = 0; i < SIZE; i++) {
            cout << "  " << names[i] << " = " << d[i] << endl;
        }
        cout << endl;
    }

    void menu() {
        int choice;
        cout << "\n \tВАРИАНТ = 4\n \tМЕТОД = Дейкстра\n \tПРЕДЛОЖЕННЫЙ ГРАФ = 14.4.5\n\n";
        cout << "Выберети команду:\n";
        cout << "1. Добавление нового узла в граф\n";
        cout << "2. Вывод графа на экран\n";
        cout << "3. Вывод длинны кротчайшего пути\n";
        cout << "0. Выход\n";
        cout << "Введите команду: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1: {
            cout << "\n\n\n" << endl;
            add();
            menu();
            break;
        }
        case 2: {
            print();
            menu();
            break;
        }
        case 3: {
            fillingTable();
            menu();
            break;
        }
        case 0: {
            exit(0);
        }
        default: {
            cout << "Вы ввели неверную команду" << endl;
            menu();
        }
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    node* application = new node;
    application->addFirstNode();
    application->menu();
}