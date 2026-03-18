#include<iostream>
#include<cmath>
#include<cstring>
#include<ctime>

using namespace std;

struct books {
	char famavt[100];
	char name[100];
	unsigned int num;
};

void SelectionSort(books book[], int N)
{
	for (int i = 0; i < N - 1; i++) 
	{
		int minIndex = i;

		for (int j = i + 1; j < N; j++) 
		{
			if (strcmp(book[j].name, book[minIndex].name) < 0) 
			{
				minIndex = j;
			}
		}

		if (minIndex != i) 
		{
			books temp = book[i];
			book[i] = book[minIndex];
			book[minIndex] = temp;
		}
	}
}
void TapeSort(books book[], int N)
{
	int TapesAmount = (int)sqrt((double)N);
	if (TapesAmount < 1) TapesAmount = 1;
	books** Tapes = new books * [TapesAmount];
	int* Sizes = new int[TapesAmount] {0};
	for (int i = 0; i < TapesAmount; i++) Tapes[i] = new books[N];
	for (int i = 0; i < N; i++) {
		int t = i % TapesAmount;
		Tapes[t][Sizes[t]++] = book[i];
	}
	for (int i = 0; i < TapesAmount; i++)
		SelectionSort(Tapes[i], Sizes[i]);

	int index = 0;
	while (index < N)
	{
		int minTape = -1;

		for (int i = 0; i < TapesAmount; i++) 
		{
			if (Sizes[i] > 0) 
			{
				if (minTape == -1 ||
					strcmp(Tapes[i][0].name, Tapes[minTape][0].name) < 0) 
				{
					minTape = i;
				}
			}
		}

		if (minTape != -1) 
		{

			book[index++] = Tapes[minTape][0];


			for (int j = 1; j < Sizes[minTape]; j++) 
			{
				Tapes[minTape][j - 1] = Tapes[minTape][j];
			}
			Sizes[minTape]--;
		}
	}


	for (int i = 0; i < TapesAmount; i++)
		delete[] Tapes[i];
	delete[] Tapes;
	delete[] Sizes;
}
void randfam(char *fam)
{
	const char* famel[] = 
	{
	"Иванов", "Петров", "Сидоров", "Смирнов", "Кузнецов",
	"Попов", "Васильев", "Павлов", "Семенов", "Голубев",
	"Виноградов", "Богданов", "Воробьев", "Федоров", "Михайлов",
	"Беляев", "Тарасов", "Белов", "Комаров", "Орлов",
	"Киселев", "Макаров", "Андреев", "Ковалев", "Ильин",
	"Гусев", "Титов", "Кузьмин", "Крылов", "Баранов"
	};

	int f = rand() % 30;
	strcpy_s(fam, 100, famel[f]);
}
void randname(char* book)
{
	const char* books[] = 
	{
		"Война и мир", "Преступление и наказание", "Мастер и Маргарита",
		"Анна Каренина", "Идиот", "Тихий Дон", "Герой нашего времени",
		"Мертвые души", "Отцы и дети", "Обломов", "Евгений Онегин",
		"Горе от ума", "Ревизор", "Вишневый сад", "На дне",
		"Три товарища", "Сто лет одиночества", "Золотая рыбка", "Улисс",
		"Великий Гэтсби", "Над пропастью во ржи", "Портрет Дориана Грея",
		"Собор Парижской Богоматери", "Отверженные", "Дон Кихот",
		"Декамерон", "Гаргантюа и Пантагрюэль", "Фауст", "Божественная комедия",
		"Тысяча и одна ночь"
	};

	int b = rand() % 30;
	strcpy_s(book, 100, books[b]);
}
void menu1(books *book, int n)
{
	cout << "\nДо сортировки:\n";
	for (int i = 0; i < n; i++)
	{
		cout << book[i].num << " | " << book[i].famavt << " | '" << book[i].name << "' " << endl;
	}
	TapeSort(book, n);

	cout << "\nПосле сортировки по названию книги:\n";
	for (int i = 0; i < n; i++)
	{
		cout << book[i].num << " | " << book[i].famavt << " | '" << book[i].name << "'" << endl;
	}
}
void menu2(books book, int n)
{

}
void menu(books book, int n)
{
	while (1)
	{
		cout << endl << "======================================" << endl;
		cout << "                МЕНЮ                  " << endl;
		cout << "1. Сортировка" << endl;
		cout << "2. Поиск" << endl;
		cout << "3. Выход" << endl;
		cout << "Введите номер действия: " << endl;
		int k;
		cin >> k;
		if (cin.fail()) 
		{
			cout << "Ошибка ввода! Необходимо ввести число." << endl;
			cin.clear(); 
			cin.ignore(10000000, '\n'); 
			
		}
		else 
		{
			cin.ignore(10000000, '\n'); 
		}
		switch (k)
		{
		case 1:
			menu1(&book, n);
			break;
		case 2:
			menu2(book, n);
			break;
		case 3:
			exit(0);
		}
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	int n;
	cout << "Введите количество элементов для массива";
	cin >> n;
	books *book = new books[n];
	for (int i = 0; i < n; i++)
	{
		randfam(book[i].famavt);
		book[i].num = rand();
		randname(book[i].name);
	}
	menu(*book, n);
	return 0;
}