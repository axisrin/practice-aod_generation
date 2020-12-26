#include <fstream>
#include <iostream>
#include <string>
#include "Function.h"

using namespace std;


#pragma warning(disable : 4996)

struct Node {
    string key = "";
    string name = "";
    string address = "";
};

void filling() {
    Node* node;
    ifstream test("File.txt");
    FILE* pBinaryFile;
    pBinaryFile = fopen("data.txt", "wb");
    char buffer;
    string stroka = "";
    int count = 0;
    int countSpace = 0;


    while (true) {
        node = new Node();
        getline(test, stroka);
        if (stroka == "") {
            break;
        }
        for (int i = 0; i <= stroka.size(); i++) {
            if (i < stroka.size()) {
                if (stroka[i] == ' ') {
                    countSpace++;
                }
                if (countSpace == 0) {
                    node->key = node->key + stroka[i];
                }
                else if (countSpace == 1) {
                    node->name = node->name + stroka[i];
                }
                else if (countSpace == 2) {
                    node->address = node->address + stroka[i];
                }
            }
            else {


                fwrite(node, sizeof(Node), 1, pBinaryFile);
            }
        }
        stroka = "";
        countSpace = 0;
    }
    cout << "Данные преобразованы в двоичный файл!" << endl;
    test.close();
    fclose(pBinaryFile);
}

void print() {
    int count = 0;
    string s = "";
    ifstream BinaryFile("data.txt");
    while (!BinaryFile.eof()) {
        count++;
        BinaryFile.read((char*)&s, sizeof(s));
        if (!BinaryFile.eof()) {
            cout << s;
            if (count % 3 == 0) {
                cout << endl;
            }
        }
        else {
            break;
        }
    }
    cout << endl;
    BinaryFile.close();

}

void definition(int confirmation) {
    string key;
    cout << "Введите номер читательского билета: ";
    cin >> key;
    cout << endl;
    int count = 0;
    string s = "";
    ifstream BinaryFile("data.txt", ios::binary | ios::in);
    while (!BinaryFile.eof()) {
        if (!BinaryFile.eof()) {
            BinaryFile.read((char*)&s, sizeof(s));
            if (count == 1) {
                cout << "Искомый параметр: " << s << endl;
                count = 0;
            }
            if (count != 0) {
                count--;
            }
            if (s == key) {
                count = confirmation;
            }
        }
        else {
            break;
        }
    }
    BinaryFile.close();
    cout << endl;
}


void replacement(int confirmation) {
    // Заменить не	ключевой параметр у нескольких записей по ключу
    string parameter;
    if (confirmation == 1) {
        cout << "Введите ФИО: ";
    }
    else {
        cout << "Введите адресс: ";
    }
    cin >> parameter;
    cout << endl;

    string key;
    cout << "Введите номер читательского билета: ";
    cin >> key;
    cout << endl;


    ifstream BinaryFile("data.txt", ios::binary | ios::in);
    ofstream pTextFile;
    pTextFile.open("File.txt");
    int count = 0;
    string stroka = "";
    string str1 = "";
    string str2 = "";
    string str3 = "";
    int countStr = 0;
    while (!BinaryFile.eof()) {
        countStr++;
        if (!BinaryFile.eof()) {
            BinaryFile.read((char*)&stroka, sizeof(stroka));
            if (countStr == 1)
            {
                str1 = stroka;
            }
            if (countStr == 2)
            {
                if (str1 == key && confirmation == 1) {
                    str2 = " " + parameter;
                }
                else {
                    str2 = stroka;
                }
            }
            if (countStr == 3)
            {
                if (str1 == key && confirmation == 2) {
                    str3 = " " + parameter;
                }
                else {
                    str3 = stroka;
                }
                pTextFile << str1 << str2 << str3 << endl;
                countStr = 0;
            }

        }
        else {
            break;
        }
    }

    filling();
}
