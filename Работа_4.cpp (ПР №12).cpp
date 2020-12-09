#include <fstream>
#include <string>

#include <iostream>

using namespace std;

struct Node

{
    string key = "";
    string name = "";
    string add = "";
};

void FileInfo()
{

    Node* node;
    ifstream test("File.txt");
    FILE* BinaryFile;
    fopen_s(&BinaryFile, "BinaryFile.txt", "wb");

    string stroka = "";
    int count = 0;
    int countSpace = 0;

    while (true)
    {

        node = new Node();
        getline(test, stroka);

        if (stroka == "")
        {

            break;

        }

        for (int i = 0; i <= stroka.size(); i++)
        {

            if (i < stroka.size())
            {

                if (stroka[i] == ' ')
                {

                    countSpace++;

                }

                if (countSpace == 0)
                {

                    node->key = node->key + stroka[i];

                }

                else if (countSpace == 1)
                {

                    node->name = node->name + stroka[i];

                }

                else if (countSpace == 2)
                {

                    node->add = node->add + stroka[i];

                }

            }

            else
            {

                fwrite(node, sizeof(Node), 1, BinaryFile);

            }

        }

        stroka = "";

        countSpace = 0;

    }

    cout << "Данные преобразованы в двоичный файл" << endl;
    test.close();
    fclose(BinaryFile);

}

void print()
{

    int count = 0;
    string s = "";
    ifstream BinaryFile("BinaryFile.txt");

    while (!BinaryFile.eof())
    {

        count++;
        BinaryFile.read((char*)&s, sizeof(s));

        if (!BinaryFile.eof())
        {

            cout << s;

            {

                cout << endl;

            }

        }

        else
        {

            break;

        }

    }

    cout << endl;
    BinaryFile.close();

}

void definition(int confirmation)
{

    string key;
    cout << "Введите номер читательского билета: ";

    cin >> key;
    cout << endl;
    int count = 0;
    string s = "";
    ifstream BinaryFile("BinaryFile.txt", ios::binary | ios::in);

    while (!BinaryFile.eof())
    {

        if (!BinaryFile.eof())
        {

            BinaryFile.read((char*)&s, sizeof(s));

            if (count == 1)
            {

                cout << "Искомый ключ: " << s << endl;

                count = 0;

            }

            if (count != 0)
            {

                count--;

            }

            if (s == key)
            {

                count = confirmation;

            }

        }

        else
        {

            break;

        }

    }

    BinaryFile.close();
    cout << endl;

}

void Replace(int confirmation)

{
    string par;
    if (confirmation == 1)

    {

        cout << "Введите ФИО: ";

    }

    else {

        cout << "Введите адресс: ";

    }

    cin >> par;
    cout << endl;
    string key;
    cout << "Введите номер читательского билета: ";
    cin >> key;
    cout << endl;
    ifstream BinaryFile("BinaryFile.txt", ios::binary | ios::in);
    ofstream pTextFile;
    pTextFile.open("File.txt");
    int count = 0;
    string stroka = "";
    string str1 = "";
    string str2 = "";
    string str3 = "";
    int countStr = 0;

    while (!BinaryFile.eof())
    {

        countStr++;

        if (!BinaryFile.eof())
        {

            BinaryFile.read((char*)&stroka, sizeof(stroka));

            if (countStr == 1)
            {

                str1 = stroka;

            }

            if (countStr == 2)
            {
                if (str1 == key && confirmation == 1)
                {

                    str2 = " " + par;

                }

                else
                {

                    str2 = stroka;

                }

            }

            if (countStr == 3)
            {

                if (str1 == key && confirmation == 2)
                {

                    str3 = " " + par;

                }

                else
                {

                    str3 = stroka;

                }

                pTextFile << str1 << str2 << str3 << endl;
                countStr = 0;

            }

        }

        else
        {

            break;

        }
    }

    FileInfo();

}

void menu()

{

    int choice;

    cout << "-----------------------------------------------------------------" << endl;
    cout << "1. Преобразование тестовых данных в двоичный файл" << endl;
    cout << "2. Отображение всех записей двоичного файла" << endl;
    cout << "3. Определение не ключевого параметра записи по ключу" << endl;
    cout << "4. Замена не ключевого параметра у нескольких записей по ключу" << endl;
    cout << "0. Выход" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "Введите команду: ";
    cin >> choice;
    cout << endl;

    switch (choice)
    {

    case 1:
    {
        FileInfo();
        menu();
        break;
    }

    case 2:
    {
        print();
        menu();
        break;
    }
    case 3:
    {
        int confirmation;
        cout << "Какой параметр вы хотите получить?" << endl;
        cout << "1. ФИО" << endl;
        cout << "2. Адрес" << endl;
        cout << "Введите команду: ";
        cin >> confirmation;
        if (confirmation != 1 && confirmation != 2)
        {
            cout << "Неверная команда" << endl;
            menu();
        }
        definition(confirmation);
        menu();
        break;
    }

    case 4: {
        int confirmation;
        cout << "Какой параметр вы хотите заменить?" << endl;
        cout << "1. ФИО" << endl;
        cout << "2. Адрес" << endl;
        cout << "Введите команду: ";
        cin >> confirmation;
        if (confirmation == 1 || confirmation == 2)
        {
            Replace(confirmation);
        }
        else
        {
            cout << "Неверная команда" << endl;
            menu();
        }
        menu();
        break;
    }
    case 0:
    {
        exit(0);
    }
    default:
    {
        cout << "Неверная команда" << endl;;
        menu();
    }
    }

}

int main(int argc, char const* argv[])

{
    menu();
}
