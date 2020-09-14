#include <iostream>
#include <vector>

typedef std::vector<int> vec_line;

vec_line& sort(vec_line& dArr)
{
	int temp;
	int raz=1;
	bool flag_suc = 0;
	int le = dArr.size();
	int sum = 0;
	while (!flag_suc)
	{
		for (int i = 0; i < le; i++)
		{
			for (int j = 1; j < le; j++)
			{
				if (((dArr[j-1]) % (10 * raz)) / (1 * raz) > (((dArr[j]) % (10 * raz)) / (1 * raz)))
				{
					std::swap(dArr[j - 1], dArr[j]);
				}
			}
		}
		for (int i = 0; i < le; i++)
		{
			sum = sum + ((dArr[i]) % (100 * raz)) / (10 * raz);
		}
		if (sum == 0)
		{
			flag_suc = 1;
		}
		sum = 0;
		raz = raz * 10;
	}
	return dArr;
}

int main()
{
	setlocale(LC_ALL, "ru");
	std::vector <int> elem_;
	std::vector <std::vector<int>>  qu_;
	bool b = 0;
	int qu_total = 0;
	while (!b)
	{
		while (!b)
		{
			int a;
			std::cin >> a;
			elem_.push_back(a);
			std::cout << "Конец очереди ? : ";
			std::cin >> b;
		}
		qu_total++;
		qu_.push_back(elem_);
		elem_.clear();
		std::cout << "Больше нет очередей ? : ";
		std::cin >> b;
	}
	int qu_index = 0;
	std::cout << std::endl << std::endl;
	while (qu_index<qu_total)
	{
		std::cout << "Массив " << qu_index+1 << ":";
		qu_[qu_index].size();
		for (int i = 0; i < qu_[qu_index].size(); i++)
		{
			std::cout << " " << qu_[qu_index][i];
		}
		std::cout << std::endl;
		sort(qu_[qu_index]);
		std::cout << "Отсортированный Массив " << qu_index+1 << ":";
		qu_[qu_index].size();
		for (int i = 0; i < qu_[qu_index].size(); i++)
		{
			std::cout << " " << qu_[qu_index][i];
		}
		qu_index++;
		std::cout << std::endl;
	} 
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
