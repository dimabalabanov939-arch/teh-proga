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
int BinarySearchExact(books book[], int left, int right, const char* searchTitle)
{
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		int cmp = strcmp(book[mid].name, searchTitle);

		if (cmp == 0)
			return mid;  // Найдено точное совпадение
		else if (cmp < 0)
			left = mid + 1;  // Искомое название больше, ищем в правой половине
		else
			right = mid - 1;  // Искомое название меньше, ищем в левой половине
	}

	return -1;  // Элемент не найден
}
int FindFirstOccurrence(books book[], int N, const char* searchTitle)
{
	int left = 0, right = N - 1;
	int result = -1;

	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		int cmp = strcmp(book[mid].name, searchTitle);

		if (cmp >= 0)  // Название книги >= искомого
		{
			if (cmp == 0)
				result = mid;  // Запоминаем позицию
			right = mid - 1;  // Продолжаем искать в левой части
		}
		else  // cmp < 0
		{
			left = mid + 1;
		}
	}

	return result;
}
int FindLastOccurrence(books book[], int N, const char* searchTitle)
{
	int left = 0, right = N - 1;
	int result = -1;

	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		int cmp = strcmp(book[mid].name, searchTitle);

		if (cmp <= 0)  // Название книги <= искомого
		{
			if (cmp == 0)
				result = mid;  // Запоминаем позицию
			left = mid + 1;  // Продолжаем искать в правой части
		}
		else  // cmp > 0
		{
			right = mid - 1;
		}
	}

	return result;
}
void BinarySearchRange(books book[], int N, const char* searchTitle)
{
	// Находим первое и последнее вхождение искомого названия
	int first = FindFirstOccurrence(book, N, searchTitle);

	if (first == -1)
	{
		cout << "No books found with title containing '" << searchTitle << "'" << endl;
		return;
	}

	int last = FindLastOccurrence(book, N, searchTitle);

	cout << "\nFound " << (last - first + 1) << " book(s) with title containing '" << searchTitle << "':" << endl;
	for (int i = first; i <= last; i++)
	{
		cout << book[i].num << " | " << book[i].famavt << " | '" << book[i].name << "'" << endl;
	}
}
void randfam(char* fam)
{
	const char* famel[] =
	{
	"Ivanov", "Petrov", "Sidorov", "Smirnov", "Kuznetsov",
	"Popov", "Vasiliev", "Pavlov", "Semenov", "Golubev",
	"Vinogradov", "Bogdanov", "Vorobiev", "Fedorov", "Mikhailov",
	"Belyaev", "Tarasov", "Belov", "Komarov", "Orlov",
	"Kiselev", "Makarov", "Andreev", "Kovalev", "Ilyin",
	"Gusev", "Titov", "Kuzmin", "Krylov", "Baranov"
	};

	int f = rand() % 30;
	strcpy_s(fam, 100, famel[f]);
}
void randname(char* book)
{
	const char* books[] =
	{
		"War and Peace", "Crime and Punishment", "The Master and Margarita",
		"Anna Karenina", "The Idiot", "And Quiet Flows the Don", "A Hero of Our Time",
		"Dead Souls", "Fathers and Sons", "Oblomov", "Eugene Onegin",
		"Woe from Wit", "The Government Inspector", "The Cherry Orchard", "The Lower Depths",
		"Three Comrades", "One Hundred Years of Solitude", "The Golden Fish", "Ulysses",
		"The Great Gatsby", "The Catcher in the Rye", "The Picture of Dorian Gray",
		"The Hunchback of Notre-Dame", "Les Miserables", "Don Quixote",
		"The Decameron", "Gargantua and Pantagruel", "Faust", "The Divine Comedy",
		"One Thousand and One Nights"
	};

	int b = rand() % 30;
	strcpy_s(book, 100, books[b]);
}
void menu1(books* book, int n)
{
	cout << "\nBefore sorting:\n";
	for (int i = 0; i < n; i++)
	{
		cout << book[i].num << " | " << book[i].famavt << " | '" << book[i].name << "' " << endl;
	}
	TapeSort(book, n);

	cout << "\nAfter sorting by book title:\n";
	for (int i = 0; i < n; i++)
	{
		cout << book[i].num << " | " << book[i].famavt << " | '" << book[i].name << "'" << endl;
	}
}
void menu2(books book[], int n)
{
		cout << "\n=== SEARCH MENU ===" << endl;
		cout << "1. Single-aspect exact match search" << endl;
		cout << "2. Single-aspect range search" << endl;
		cout << "Enter action number: " << endl;
		int k;
		cin >> k;
		if (cin.fail())
		{
			cout << "Input error! Please enter a number." << endl;
			cin.clear();
			cin.ignore(10000000, '\n');
		}
		cin.ignore(10000000, '\n');

		char searchTitle[100];

		switch (k)
		{
		case 1:
		{
			cout << "Enter book title to search for: ";
			cin.getline(searchTitle, 100);

			int result = BinarySearchExact(book, 0, n - 1, searchTitle);

			if (result != -1)
			{
				cout << "\nBook found!" << endl;
				cout << book[result].num << " | " << book[result].famavt << " | '" << book[result].name << "'" << endl;
			}
			else
			{
				cout << "Book with title '" << searchTitle << "' not found." << endl;
			}
			break;
		}
		case 2:
		{
			cout << "Enter book title to search for (partial match): ";
			cin.getline(searchTitle, 100);
			BinarySearchRange(book, n, searchTitle);
			break;
		}
		default:
			cout << "Invalid choice! Please enter 1 or 2." << endl;
		}
}
void menu(books book[], int n)
{
	while (1)
	{
		cout << "======================================" << endl;
		cout << "                MENU                  " << endl;
		cout << "======================================" << endl;
		cout << "1. Sort" << endl;
		cout << "2. Search" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter action number: " << endl;
		int k;
		cin >> k;
		if (cin.fail())
		{
			cout << "Input error! Please enter a number." << endl;
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
			menu1(book, n);
			break;
		case 2:
			menu2(book, n);
			break;
		case 3:
			cout << "Exiting program..." << endl;
			exit(0);
		default:
			cout << "Invalid choice! Please enter 1, 2, or 3." << endl;
		}
	}
}
int main()
{
	srand(time(0));

	int n;
	cout << "Enter the number of array elements: ";
	cin >> n;
	books* book = new books[n];
	for (int i = 0; i < n; i++)
	{
		randfam(book[i].famavt);
		book[i].num = rand() % 10000;
		randname(book[i].name);
	}
	menu(book, n);
	return 0;
}