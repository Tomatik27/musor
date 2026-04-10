/* ---------------------------------------------------------------
	Практика по работе с бинарными деревьями.
	Метод нахождения в дереве элемента по его порядковому номеру,
	записанному в двоичной системе.

	ФКТиПМ. Группа 11/1. Брайко Глеб. 21.05.2018
	---------------------------------------------------------------*/

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string>

#include <iostream>
#include <ctime>
#include <iomanip>
#include <bitset>
#include <math.h>

#include <fstream>

using namespace std;

string Draw_File = "Draw_Tree_01.txt"; // Ввод дерева из файла

const int punkt_kol = 10;
string punkt_arr[punkt_kol] = {
" Создание дерева  = { 20, 10, 40, 6, 12, 28, 45, 3, 7, 11, 18, 25, 29, 43, 60 } ",
" Ввод дерева из файла ["+ Draw_File +"]                                        ",
" Ввод дерева вручную. Признак завершения ввода — 0                              ",
" Генерация дерева с заданным числом случайных элементов                         ",
" Вывод дерева - вершина вверху                                                  ",
" Вывод дерева - вершина слева                                                   ",
" Вывод дерева в строку прямым обходом                                           ",
" Вывод дерева в строку внутренним обходом                                       ",
" Вывод дерева в строку обратным обходом                                         ",
" Выход                                                                          "
};

const int Kol_Element = 15;
int a[Kol_Element] = { 20, 10, 40, 6, 12, 28, 45, 3, 7, 11, 18, 25, 29, 43, 60 };

int ColorText = 15;  // Белый
int ColorFon = 0;    // Чёрный

// Позиция Верхнего левого угла меню
int xx0 = 11;
int yy0 = 4;
int yy0_punkt_kol = yy0 + punkt_kol + 3;

int RNDlowLim = -50; // Нижний предел диапазона случайного числа.
int RNDhighLim = 100; // Верхний предел диапазона случайного числа.
int RND_Kol = 15; // Количество случайных чисел

bool cout_C = true;
bool Tree_Exist = false;

struct tree
{
	int info;
	tree* L, * R;
};


// Функция, которая устанавливает цвет текста и фона
static void SetColor(int textColor, int bgColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void clear_screen() { // очистка экрана
	cout << "\033[2J\033[1;1H";
}

void gotoxy(short x, short y) {
	COORD position = { x, y }; //позиция x и y
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
}

void hideCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

int rangeRand(int range_min, int range_max)  // Ф-я возвращает случайное число в заданном диапазоне.
{
	return rand() % (range_max - range_min + 1) + range_min;
}

void addDDP(tree* p, int x) // Добавление нового элемента в дерево.
{
	tree* g;
	if (x < p->info)
	{
		if (p->L == 0)
		{
			g = new(tree);
			g->info = x;
			g->L = 0; g->R = 0;
			p->L = g;

		}
		else addDDP(p->L, x);
	}
	else
	{
		if (p->R == 0)
		{
			g = new(tree);
			g->info = x;
			g->R = 0; g->L = 0;
			p->R = g;
		}
		else addDDP(p->R, x);
	}
}


tree* inTree() // Ввод дерева - Const 
{
	tree* t = new(tree);

	t = new(tree);
	t->info = a[0];
	t->L = 0;
	t->R = 0;
	for (int i = 1; i < Kol_Element; i++)
		addDDP(t, a[i]);
	cout << endl;
	return t;
}

tree* inTree_Hand() // Ввод дерева вручную. Прищнак завершения ввода — 0. 
{
	int x;
	tree* t = new(tree);
	cout << "Ввод дерева вручную. Прищнак завершения ввода — 0. " << endl;
	cin >> x;
	t = new(tree);
	t->info = x;

	t->L = 0; t->R = 0;

	while (x != 0)
	{
		cin >> x;
		if (x != 0) addDDP(t, x);
	}
	return t;
}

tree* genTree(int n) // Генерация дерева с заданным числом случайных элементов. 
{
	int x = rangeRand(RNDlowLim, RNDhighLim);
	tree* t = new(tree);
	t = new(tree);
	t->info = x;
	t->L = 0; t->R = 0;

	for (int i = 0; i < n; ++i)
	{
		x = rangeRand(RNDlowLim, RNDhighLim);
		addDDP(t, x);
	}
	return t;
}

void printPreorder(tree* t) // Вывод дерева в строку прямым обходом.
{
	cout << t->info << " ";
	if (t->L != 0) printPreorder(t->L);
	if (t->R != 0) printPreorder(t->R);
}

void printInorder(tree* t) //  Вывод дерева в строку внутренним обходом.
{
	if (t->L != 0) printInorder(t->L);
	cout << t->info << " ";
	if (t->R != 0) printInorder(t->R);
}

void printPostorder(tree* t) // Вывод дерева в строку обратным обходом. 
{
	if (t->L != 0) printPostorder(t->L);
	if (t->R != 0) printPostorder(t->R);
	cout << t->info << " ";
}


/*
	В основе этой реализации вывода Бинарного Дерева лежит эмперически выводимое свойство элементов БД.
	Путь до любого из них можно представить в виде последовательности переходов влево или вправо из корня БД :

					[1]
			[2]				[3]
		[4]		[5]		[6]		[7]
				.	.	.

		Для перехода в элемент 2 : Корень ? Лево
		Для перехода в элемент 3 : Корень ? Право
		Для перехода в элемент 4 : Корень ? Лево ? Лево
		Для перехода в элемент 5 : Корень ? Лево ? Право
		и т.д.

	Эти последовательности могут быть записаны : Л, П, ЛЛ, ЛП и т.д.
	Что подозрительно напоминает бинарный код. Заменив Л на 0, а П на 1, получим :
		Л, П, ЛЛ, ЛП ...
		0, 1, 00, 01 ...

	Чтобы избавится от незначащих нулей, обозначим корень за 1 и добавим его перед каждой записью :
		1, 10, 11, 100, 101 ... — Получили натуральных ряд в двоичной системе.

	Таким образом, в любом БД существует "невидимая" нумерация его элементов, представленная на схеме выше.
	И, что самое важное, каждый такой номер i, записанный в двоичной системе, можно использовать как
	код для восстановления пути от корня до i-го элемента, что и реализовано ниже.
*/

/* Визуализация (пример) ожидаемого вывода. Справа от дерева записаны : Кол-во элементов на этаже, Кол-во промежутков, Этаж


										10 									| 1 эл  / 2 пр  /  1 этаж

						6		 						21 					| 2 эл  / 4 пр  /  2 этаж

				3				8				15				25			| 4 эл  / 8 пр  /  3 этаж

			1		4		7		9		18		19		23		30		| 8 эл  / 16 пр /  4 этаж
*/


string tobinary(int i) // Перевод целого числа в двоичную систему (результат записывается в строку).
{
	string binary = bitset < 32 >(i).to_string(); // Мне было лень писать свою функцию перевода числа в двоичную систему.
	/*
	Но возникла проблема : В качестве параметра bitset<x> принимает только const int.
	Поэтому я взял размер с запасом (для систем х32 точно хватит, а число больше пользователь сам устанет вводить).

	Однако теперь строка binary при вводе, например, числа 5, выглядела так : "00000000000000000000000000000101".
	Поэтому в функцию был добавлен цикл, удаляющий лишние нули.
	*/

	string tmp;
	bool f = false;

	for (int j = 0; j < 32; ++j) // Итерация по числу (в виде строки), игнорирующая незначащие нули.
	{
		if (binary[j] == '1') f = true; // После первой встреченной единицы нули пойдут уже значащие.
		if (f) tmp += binary[j]; // После обнаружения начала числа, все последующие символы строки записываются.
	}
	return tmp;
}


tree* takeApple(tree* t, string branch) // Функция, возвращающая элемент дерева ("яблоко") по его номеру ("ветви").
{
	// branch — номер элемента-яблока в дереве, записанный в виде двочиной последовательности.
	// В то же время, branch — путь от корня до яблока.

	string observed = "1"; // Строка-счётчик. Используется для того, чтобы отследить, когда закончится рассматриваемая строка branch.
	int i = 1; // Переменная для итерации по branch.

	while (observed.length() < branch.length() && t != 0){
		// Если длина просмотренного становится равна длине строки branch, цикл завершается. 
		/*
		Цикл, использующий номер (в виде двоичной последовательности branch) элемента дерева, как код-карту,
		где 0 — переход влево, 1 — переход вправо.
		Первая единица в коде — это "Незначащая Единица Корня". Она не обозначает переходов,
		а потому не учитывается. Для этого обход строки начинается не с нулевого, а с первого
		элемента (i инициализируется 1-ей, а строка-счётчик observed — "1").
		*/
		if (branch[i] == '1') { t = t->R; }
		else { t = t->L; }
	observed += branch[i]; i++;
}
return t;
}

int Floor(int i) // Ф-я, определяющая "этаж", на котором находится i-й элемент. 
{
	return (int)(log2(i) + 1);
}

int floorSize(int i) // Ф-я, определяющая количество элементов на этаже, где находится i-й элемент. 
{
	return pow(2, Floor(i) - 1);
}

void DrawTree_HeadTop(tree* t) // Вывод дерева.
{
	string branch; tree* apple = new tree;

	int w = 100; // Максимальная ширина будущего дерева. 
	// Ширина выставлена наудачу и подойдёт для относительно скромных деревьев в тройку-другую этажей.

	int ww; // Промежуток между элементами (либо отступ от края в случае первого элемента на этаже).
	int floor; // Этаж.
	int leafs = 0; // Число листьев, чтобы отследить момент, когда нужно останавливать вывод.
	bool f = true; // Флажок, ответственный за остановку вывода. 

	cout << setw(w / 2) << t->info << " \n\n\n"; // Вывод корня.

	for (int i = 2; f; ++i) // Все остальные элементы выводятся в порядке их расположения на этажах дерева.
	{
		branch = tobinary(i); // Номер элемента переводится в код-путь branch от корня до i-го эл-та.
		floor = Floor(i);

		apple = takeApple(t, branch); // Получение элемента.

		if (log2(i) == floor - 1) { ww = w / pow(2, floor); }
		else { ww = 2 * w / pow(2, floor); }

		/*
			Условие выявляет, является ли элемент первым на этаже. Для него применяется одинарный отступ.
			Для остальных — двойной.
		*/

		if (apple != 0) { cout << setw(ww) << apple->info; } else { cout << setw(ww) << ""; leafs++; }

		// Вместо пустого элемента выводится "", т.е. ничего. Можно, конечно, "Х" или "*", но мне нравится так.
		// Такой элемент сразу записывается в листы. 

		if (i == floorSize(i + 1) - 1) { cout << "\n\n\n"; if (leafs >= floorSize(i)) f = false; }
		/*
			Условие проверяет, является ли элемент последним на этаже
			( Здесь буквально : является ли он предшествующим первому элементу следующего (i+1)-го этажа
			[т.к. номер первого элемента (i+1)-го этажа совпадает с размером этажа floorSize(i+1)] ).

			Если так, то происходит перевод строки и проверка, не являются ли число листьев больше
			либо равным числу элементов на этаже.

			Если все выведенные элементы — не существуют либо листья, флаг срабатывает, вывод останавливается.
		*/
	}
	cout << "\n\n";
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

//Овчарик Дарья, 11 группа 1 курс, 2019
void DrawTree_HeadLeft(tree* p, int tab)  //Вывод дерева
{
	//Печать по уровням: сначала самый крайний лист в правом поддереве,
	//затем двигаемся влево к корню,
	//затем печатаем левое поддерево от корня к крайнему листу

	if (p != 0)
	{
		if (p->R != 0)
			DrawTree_HeadLeft(p->R, tab + 1);

		for (int i = 0; i < tab; i++)
			cout << '\t';
		cout << p->info << endl;

		if (p->L != 0)
			DrawTree_HeadLeft(p->L, tab + 1);
	}
	else
		cout << endl;
}


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// Вводим дерево из файла
tree* inTree_File() {
	ifstream f_Draw;
	f_Draw.open(Draw_File, ios::in);
	if (!f_Draw) {
		gotoxy(xx0+44, yy0 + 22);
		cout << "!!! Нет файла " << Draw_File << endl;
		return 0;// t;
	}
	
	tree* t = new(tree);
	int x;
	f_Draw >> x;

	t->info = x;
	t->L = 0;
	t->R = 0;

	while (!f_Draw.eof()) {
		f_Draw >> x;
		addDDP(t, x);
	}
	Tree_Exist = true;
	return t;
}
// Очищаем место для вывода дерева
void Clear_Place_Tree(int xx, int yy) {
	int Kol_Str = 22;
	for (int i = 0; i < Kol_Str; i++) {
		gotoxy(xx, yy + i);
		cout << "                                                                                                                        " ;
	}
	return;
}

// Выбор пункта меню
int SelectMenu(int k) {
	// Выводим всё меню
	for (int i = 0; i < punkt_kol; i++) {
		gotoxy(xx0, yy0 + i);
		cout << punkt_arr[i];
	}

	// Функция, которая устанавливает цвет текста и фона
	SetColor(ColorFon, ColorText);

	// Вывод первой команды
	gotoxy(xx0, yy0 + k);
	cout << punkt_arr[k];

	int c = _getch();   // из файла conio.h
	while (c != 27) {   // выход - ESC 
		switch (c) {
			// Enter 13 - Выбор
		case 13: {
			SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
			return k;
		}
			   // вверх    224 72 (a, H)
		case 72: {
			SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
			gotoxy(xx0, yy0 + k);
			cout << punkt_arr[k];
			k = k - 1;
			if (k < 0) { k = punkt_kol - 1; }
			SetColor(ColorFon, ColorText);  // Инверсия цвета
			gotoxy(xx0, yy0 + k);
			cout << punkt_arr[k];
			gotoxy(xx0, yy0 + k);
			break;
		}
			   // вниз     224 80 (a, P)
		case 80: {
			SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
			gotoxy(xx0, yy0 + k);
			cout << punkt_arr[k];
			k = k + 1;
			if (k > punkt_kol - 1) { k = 0; }
			SetColor(ColorFon, ColorText);  // Инверсия цвета
			gotoxy(xx0, yy0 + k);
			cout << punkt_arr[k];
			gotoxy(xx0, yy0 + k);
			break;
		}
	   // F1
		case 59: {
			SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
			gotoxy(0, 0);
			if (cout_C) {
				cout << "(с) Брайко Глеб.   (Вершина вверху)   ФКТиПМ. Группа 11/1. 2018 \n";
				cout << "(с) Овчарик Дарья. (Вершина слева) ФКТиПМ.    Группа 11/1. 2019 \n";
				cout << "(с) Гаркуша О.В. (Меню) ФКТиПМ. КИТ. Март 2026                  \n";
			}
			else {
				cout << "                                                                    \n";
				cout << "                                                                    \n";
				cout << "                                                                    \n";
			}
			cout_C = not cout_C;
			break;
		}
		}

		c = _getch();
	}
	if (c == 27) {
		k = punkt_kol - 1;
		SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
		return k;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));
	system("mode 120");  // Full screen
	hideCursor();		// Скрыть курсор 

	gotoxy(0, 0);

	tree* t = new(tree);
	
	int kk = 0;

	/*
" Создание дерева  = { 20, 10, 40, 6, 12, 28, 45, 3, 7, 11, 18, 25, 29, 43, 60 } ",
" Ввод дерева из файла                                                           ",
" Ввод дерева вручную. Признак завершения ввода — 0                              ",
" Генерация дерева с заданным числом случайных элементов                         ",
" Вывод дерева - вершина вверху                                                  ",
" Вывод дерева - вершина слева                                                   ",
" Вывод дерева в строку прямым обходом                                           ",
" Вывод дерева в строку внутренним обходом                                       ",
" Вывод дерева в строку обратным обходом                                         ",
" Выход                                                                          "
	*/
	while (kk != punkt_kol - 1) {
		// Выбор пункта меню
		kk = SelectMenu(kk);

		switch (kk) {
		case 0: {
			// Создание дерева  = { 20, 10, 40, 6, 12, 28, 45, 3, 7, 11, 18, 25, 29, 43, 60 }
			t = inTree(); // Ввод дерева - Const 

			punkt_arr[0] = "+Создание дерева  = { 20, 10, 40, 6, 12, 28, 45, 3, 7, 11, 18, 25, 29, 43, 60 } ";
			Tree_Exist = true;			
			break;
		}
		case 1: {
			// Выводим дерево из файла
			t=inTree_File();

			punkt_arr[1] = "+Ввод дерева из файла                                                           ";
			Tree_Exist = true;
			break;
		}
		case 2: {
			// Ввод дерева вручную. Признак завершения ввода — 0
			t=inTree_Hand();

			gotoxy(0, yy0_punkt_kol);
			punkt_arr[2] = "+Ввод дерева вручную. Признак завершения ввода — 0                              ";
			Tree_Exist = true;
			break;
		}
		case 3: {
			// Генерация дерева с заданным числом случайных элементов
			t=genTree(RND_Kol); // Генерация дерева с заданным числом случайных элементов. 

			punkt_arr[3] = "+Генерация дерева с заданным числом случайных элементов                         ";
			Tree_Exist = true;
			break;
		}
		case 4: {
			// Очищаем место для вывода дерева
			Clear_Place_Tree(0, yy0_punkt_kol);

			// Вывод дерева - вершина вверху
			gotoxy(xx0, yy0_punkt_kol);
			if (Tree_Exist) {
				gotoxy(0, yy0 + yy0_punkt_kol);
				DrawTree_HeadTop(t); // Вывод дерева - вершина вверху
			}
			else {
				cout << "!!! Нет дерева !!!";
			};
			break;
		}
		case 5: {
			// Очищаем место для вывода дерева
			Clear_Place_Tree(0, yy0_punkt_kol);

			// Вывод дерева - вершина слева
			gotoxy(xx0, yy0_punkt_kol);
			if (Tree_Exist) {
				gotoxy(0, yy0_punkt_kol);
				DrawTree_HeadLeft(t, 0); // Вывод дерева - вершина слева
			}
			else {
				cout << "!!! Нет дерева !!!";
			};
			break;
		}
		case 6: {
			// Очищаем место для вывода дерева
			Clear_Place_Tree(0, yy0_punkt_kol);

			// Вывод дерева в строку прямым обходом
			gotoxy(xx0, yy0_punkt_kol);
			if (Tree_Exist) {
				cout << "Прямой обход            \n";
				printPreorder(t); // Вывод прямым обходом в строку.
			}
			else {
				cout << "!!! Нет дерева !!!";
			};
			break;
		}
		case 7: {
			// Очищаем место для вывода дерева
			Clear_Place_Tree(0, yy0_punkt_kol);

			// Вывод дерева в строку внутренним обходом
			gotoxy(xx0, yy0_punkt_kol);
			if (Tree_Exist) {
				cout << "Внутренний обход          \n";
				printInorder(t); // Вывод внутренним обходом в строку.
			}
			else {
				cout << "!!! Нет дерева !!!";
			};
			break;
		}
		case 8: {
			// Очищаем место для вывода дерева
			Clear_Place_Tree(0, yy0_punkt_kol);

			// Вывод дерева в строку обратным обходом
			gotoxy(xx0, yy0_punkt_kol);
			if (Tree_Exist) {
				cout << "Обратный обход            \n";
				printPostorder(t); // Вывод обратным обходом в строку.
			}
			else {
				cout << "!!! Нет дерева !!!";
			};
			break;
		}
		case punkt_kol - 1: {
			// Выход
			gotoxy(xx0, yy0_punkt_kol+10);
			break;
		}
		}
	}
	system("pause");
}

