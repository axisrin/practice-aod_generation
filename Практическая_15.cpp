#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <iomanip>
#include <Windows.h>
using namespace std;

//Жадный Алгоритм Хаффмана.
//Прошин Алексей Васильевич. Вариант 21.

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

struct elem
{
	char symbol = '*';
	int num = 0;
	float chance = 0;
};

struct mas
{
	elem* table;
	int control;
};

mas Table(string a)
{
	bool chk = false;
	int control = 0;

	elem* table2 = new elem[0];
	elem* table = new elem[a.size()];

	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (a[i] == table[j].symbol)
			{
				chk = true;
				table[j].num++;
			}
		}
		if (!chk)
		{
			table[i].symbol = a[i];
			table[i].num++;
		}
		chk = false;
	}
	for (int i = 0; i < a.size(); i++)
	{
		if (table[i].symbol != '*')
		{
			control++;
			elem* table1 = new elem[control];
			for (int j = 0; j < control; j++)
			{
				table1[j].symbol = table2[j].symbol;
				table1[j].num = table2[j].num;
			}

			table1[control - 1].symbol = table[i].symbol;
			table1[control - 1].num = table[i].num;
			table2 = table1;
		}
	}
	table = table2;

	int control1 = 0;
	for (int i = 0; i < control; i++)
	{
		control1 += table[i].num;
	}
	for (int i = 0; i < control; i++)
	{
		table[i].chance = (float)table[i].num / (float)control1;
	}
	mas tab;
	tab.table = table;
	tab.control = control;
	return tab;
}

mas TableSort(mas tab)
{
	for (int i = 1; i < tab.control; ++i)
	{
		for (int r = 0; r < tab.control - i; r++)
		{
			if (tab.table[r].chance < tab.table[r + 1].chance)
			{
				elem temp = tab.table[r];
				tab.table[r] = tab.table[r + 1];
				tab.table[r + 1] = temp;
			}
		}
	}

	return tab;
}
struct TreeNode
{
	elem node;
	TreeNode** children = new TreeNode * [2];
	int priority = 1;
	bool checker = 0;
	int code = -1;
};

void BuildTree(TreeNode**& element, int control);

TreeNode* BuildQueue(mas tab)
{
	int control = tab.control;
	TreeNode** queue = new TreeNode * [control];
	for (int i = 0; i < control; i++)
	{
		TreeNode* a = new TreeNode;
		a->node = tab.table[i];
		a->priority = tab.table[i].num;
		queue[i] = a;
	}
	while (control != 1)
	{
		BuildTree(queue, control);
		control--;
	}
	return queue[0];
}

void BuildTree(TreeNode**& element, int control)
{
	TreeNode* temp = new TreeNode;
	TreeNode* temp1 = new TreeNode;
	temp->priority = 0;
	temp1->priority = 0;
	int index;
	int index1;

	for (int i = 0; i < control; i++)
	{
		if (temp->priority != 0)
		{
			if (element[i]->priority < temp->priority)
			{
				temp1 = temp;
				index1 = index;
				temp = element[i];
				index = i;
			}
			else if (element[i]->priority < temp1->priority || temp1->priority == 0)
			{
				temp1 = element[i];
				index1 = i;
			}
		}
		else {
			temp = element[i];
			index = i;
		}
	}

	TreeNode* ret = new TreeNode;
	ret->checker = 1;
	ret->children = new TreeNode * [2];
	ret->children[0] = temp;
	ret->children[1] = temp1;
	ret->priority = temp->priority + temp1->priority;
	TreeNode** element1 = new TreeNode * [control - 1];
	element[index] = ret;

	for (int i = 0; i < control; i++)
	{
		if (i < index1)
		{
			element1[i] = element[i];
		}
		if (i > index1) {
			element1[i - 1] = element[i];
		}
	}
	element = element1;
}

void printTree(TreeNode* tree, int control)
{

	control++;
	if (tree->checker)
	{
		printTree(tree->children[0], control);
	}
	for (int i = 0; i < control - 1; i++)
		cout << "\t";

	cout << tree->node.symbol << "(" << tree->code << ")" << endl;
	if (tree->checker)
	{
		printTree(tree->children[1], control);
	}
}

void setIndex(TreeNode* tree)
{
	if (tree->checker) {
		tree->children[0]->code = 0;
		tree->children[1]->code = 1;
		setIndex(tree->children[0]);
		setIndex(tree->children[1]);
	}
}
bool endpoint = false;

string getSymbolCode(char symbol, string code, TreeNode* tree)
{
	if (tree->node.symbol == symbol)
	{
		endpoint = true;
		code += to_string(tree->code);
		return code;
	}
	else
	{
		if (tree->checker)
		{
			if (!endpoint)
			{
				code += getSymbolCode(symbol, "", tree->children[0]);
			}
			if (endpoint)
			{
				code += to_string(tree->code);
				return code;
			}
			if (!endpoint)
			{
				code += getSymbolCode(symbol, "", tree->children[1]);
			}
			if (endpoint)
			{
				code += to_string(tree->code);
				return code;
			}
		}
	}
	return "";
}

string getCorrectSymbolCode(char symbol, TreeNode* tree)
{
	string codepart = getSymbolCode(symbol, "", tree);
	reverse(codepart.begin(), codepart.end());
	string codepart1 = "";

	for (int j = 2; j < codepart.size(); j++)
	{
		codepart1 += codepart[j];
	}

	endpoint = false;
	return codepart1;
}

string stringCode(string name, TreeNode* tree, bool hm)
{
	string code = "";
	for (int i = 0; i < name.size(); i++)
	{
		string codepart = getSymbolCode(name[i], "", tree);
		reverse(codepart.begin(), codepart.end());
		string codepart1 = "";

		for (int j = 2; j < codepart.size(); j++)
		{
			codepart1 += codepart[j];
		}
		if (hm)
			code += codepart1;
		if (!hm) {
			code += codepart1;
			code += " ";
		}
		endpoint = false;
	}
	return code;
}

int main()
{

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	setlocale(LC_ALL, "rus");

	cout << "Введите любую цифру для начала работы (0 для завершения) : ";
	int numberUp;
	cin >> numberUp;
	if (numberUp == 0)
		return 0;
	cout << "\n\n\n";
	cout << " Практическая работа №15. Прошин Алексей ИКБО-01-19. Жадный алгоритм Хаффмана." << endl << endl;
	string a = "Прошин Алексей Васильевич";
	mas tab = Table(a);

	cout << " Данные, подвергаемые обработке: ";
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Green));
	cout << a << endl << endl;
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
	cout << " Таблица частот встречаемости символов" << endl << endl;
	cout << " zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz" << endl;
	cout << " [] №  [] Символ [] Количество вхождений [] Вероятность []" << endl;
	cout << " zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz" << endl;
	for (int i = 0; i < tab.control; i++)
	{
		cout << " [] ";
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Green));
		cout << setw(2) << i + 1;
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
		cout << " [] ";
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Cyan));
		cout << setw(6) << tab.table[i].symbol;
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
		cout << " [] ";
		cout << setw(20) << tab.table[i].num;
		cout << " [] ";
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Red));
		cout << setw(11) << tab.table[i].chance;
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
		cout << " []" << endl;
		cout << " zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz" << endl;
	}

	tab = TableSort(tab);
	cout << endl;
	cout << " Отсортированная таблица частот встречаемости символов:" << endl << endl;

	cout << " zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz" << endl;
	cout << " [] №  [] Символ [] Количество вхождений [] Вероятность []" << endl;
	cout << " zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz" << endl;
	for (int i = 0; i < tab.control; i++)
	{
		cout << " [] ";
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Green));
		cout << setw(2) << i + 1;
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
		cout << " [] ";
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Cyan));
		cout << setw(6) << tab.table[i].symbol;
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
		cout << " [] ";
		cout << setw(20) << tab.table[i].num;
		cout << " [] ";
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Red));
		cout << setw(11) << tab.table[i].chance;
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
		cout << " []" << endl;
		cout << " zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz" << endl;
	}

	TreeNode* tree = BuildQueue(tab);
	setIndex(tree);

	cout << endl;
	cout << " Дерево Хаффмана (табуляция демонстрирует глубину узла):" << endl << endl;

	printTree(tree->children[0], 1);
	cout << tree->node.symbol << "(" << tree->code << ")" << endl;
	printTree(tree->children[1], 1);
	string LHuff = stringCode(a, tree, 1);
	string LHuff1 = stringCode(a, tree, 0);
	cout << endl;

	cout << " Закодированная исходная строка:" << endl << endl;
	cout << " " << LHuff1 << endl << endl;
	int Lascii = 8 * a.size();
	int Lhuff = LHuff.size();
	float KSascii = (float)Lascii / (float)Lhuff;
	cout << " Коэффициент сжатия относительно кодировки ASCII: ";
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Green));
	cout << KSascii << endl << endl;
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));

	float tample = log(a.size()) / log(2);
	int tample1 = ceil(tample);
	float KSravnom = (float)(tample1 * a.size()) / (float)Lhuff;
	cout << " Коэффициент сжатия относительно равномерного кода: ";
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Green));
	cout << KSravnom << endl << endl;
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));

	float srdlcd = 0;
	string numm = "";

	for (int i = 0; i < tab.control; i++)
	{
		numm = getCorrectSymbolCode(tab.table[i].symbol, tree);
		srdlcd += tab.table[i].chance * float(numm.size());
	}
	cout << " Средняя длина полученного кода: ";
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Green));
	cout << srdlcd << endl << endl;
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));

	float disp = 0;

	for (int i = 0; i < tab.control; i++)
	{
		numm = getCorrectSymbolCode(tab.table[i].symbol, tree);
		disp += tab.table[i].chance * pow((float(numm.size()) - srdlcd), 2);
	}
	cout << " Дисперсия: ";
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Green));
	cout << disp << endl;
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
}
