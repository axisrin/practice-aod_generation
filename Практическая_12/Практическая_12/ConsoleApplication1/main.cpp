
#include <fstream>
#include <iostream>
#include "Function.h"

using namespace std;

void menu() {
	int choice;
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "Выберети команду:" << endl;
	cout << "1. Преобразовать тестовые данные в двоичный файл" << endl;
	cout << "2. Отобразить все записи двоичного файла" << endl;
	cout << "3. Определить не ключевой параметр записи по ключу" << endl;
	cout << "4. Заменить не	ключевой параметр у нескольких записей по ключу" << endl;
	cout << "0. Выход из программы" << endl;
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "Введите команду: ";
	cin >> choice;
	cout << endl;

	switch (choice) {
	case 1: {
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
		filling();
		menu();
		break;
	}
	case 2: {
		print();
		menu();
		break;
	}
	case 3: {
		int confirmation;

		cout << "Какой параметр вы хотите получить?" << endl;
		cout << "1. ФИО" << endl;
		cout << "2. Адрес" << endl;
		cout << "Введите команду: ";
		cin >> confirmation;
		if (confirmation != 1 && confirmation != 2) {
			cout << "Вы выбрали неверную команду и были возвращены в меню!" << endl;
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
		if (confirmation == 1 || confirmation == 2) {
			replacement(confirmation);
		}
		else {
			cout << "Вы выбрали неверную команду и были возвращены в меню!" << endl;
			menu();
		}

		menu();
		break;
	}
	case 0: {
		int confirmation;
		cout << "Вы действительно хотите выйти из программы?" << endl;
		cout << "0. Да" << endl;
		cout << "1. Нет" << endl << endl;
		cout << "Подтвердите: ";
		cin >> confirmation;
		if (confirmation == 0) {
			exit(0);
		}
		else if (confirmation == 1) {
			menu();
		}
		else {
			cout << "Вы выбрали неверную команду и были возвращены в меню!" << endl;
			menu();
		}
	}
	default: {
		cout << "Вы ввели неверную команду!" << endl;
		menu();
	}
	}
}

int main(int argc, char const* argv[])
{
	setlocale(LC_ALL, "ru");
	menu();
}