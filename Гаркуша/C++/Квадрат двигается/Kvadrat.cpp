// (с) Гаркуша О.В. март 2026
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;

const int kol_lines = 4;

string line_kvadrat;
string line_Ramka_Goriz;
string line_Ramka_Vert;

int Sleep_time = 100;
int Sleep_time_h = 10;

int ColorText = 15;  // Белый
int ColorFon = 0;    // Чёрный

// Позиция Верхнего левого угла квадрата
int xx0 = 3;
int yy0 = 4;
int Console_x = 66; int Console_y = 66;// ширина и высота окна консоли
// Позиция Верхнего левого угла Help
int x_h = 75;
int y_h = 4;
string Menu_Help_File;

int yy0_kol_lines = yy0 + kol_lines + 3;
int k_vert;
int k_goriz;
int xx01;
int yy01;

bool cout_C = true;

// Функция, которая устанавливает цвет текста и фона
static void SetColor(int textColor, int bgColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void hideCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void gotoxy(short x, short y) {
	COORD position = { x, y }; //позиция x и y
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
}

int rangeRand(int range_min, int range_max)  // Ф-я возвращает случайное число в заданном диапазоне.
{
	return rand() % (range_max - range_min + 1) + range_min;
}

// Очищаем место для вывода 
void Clear_Place_Tree(int xx, int yy) {
	int Kol_Str = 22;
	for (int i = 0; i < Kol_Str; i++) {
		gotoxy(xx, yy + i);
		cout << "                                                                                                                        ";
	}
	return;
}

// Выводим квадрат
void Out_Kvarat(int xx, int yy) {
	for (int i = 0; i < kol_lines; i++) {
		gotoxy(xx, yy + i);
		cout << line_kvadrat;
	}
	return;
}

// Выводим рамку
void Out_Ramka(int xx, int yy) {
	// Горизонтальная рамка
	// + + + + + + + + + +
	line_Ramka_Goriz = "+";
	for (int i = 0; i < Console_x / 2; i++) {
		line_Ramka_Goriz = line_Ramka_Goriz +" +";
	}

	// Вертикальная рамка
	// +                 +
	// +                 +
	line_Ramka_Vert = "+";
	for (int i = 0; i < Console_x - 1; i++) {
		line_Ramka_Vert = line_Ramka_Vert + " ";
	}
	line_Ramka_Vert = line_Ramka_Vert + "+";

	gotoxy(xx, yy);
	cout << line_Ramka_Goriz;

	for (int i = 0; i < Console_y/2; i++) {
		gotoxy(xx, yy + i+1);
		cout << line_Ramka_Vert;
	}
	gotoxy(xx, yy+ Console_y/2+1);
	cout << line_Ramka_Goriz;

	cout << endl;
	return;
}

// Очищаем место для Help
void Clear_Help() {
	SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
	int ii;
	for (ii = 1; ii <= 22; ii++) {
		gotoxy(x_h, y_h + ii - 1);
		cout << "                                           ";
	}
}

// Выводим  Help из файла
int Out_Help(string Menu_Help_File) {
	ifstream f_Help;

	f_Help.open(Menu_Help_File, ios::in);
	if (!f_Help) {
		gotoxy(x_h, y_h); 
		cout << "!!! Нет файла " << Menu_Help_File << endl;
		return -1;
	}

	int i_h = 0;
	int ColorText_h = 14;
	int ColorFon_h = 8;

	SetColor(ColorText_h, ColorFon_h);  // Возвращаем на стандартные цвета

	string str_h;
	while (!f_Help.eof()) {
		getline(f_Help, str_h);
		gotoxy(x_h, y_h + i_h); i_h = i_h + 1;
		cout << str_h << endl;
	}
	SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
}

// Движение квадрата
void Move_Kvadrat() {

	SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
	gotoxy(0, 0);
	cout << "Delete - ВЫХОД                                                                                     \n";
	cout << "Стрелки вверх-вниз СКОРОСТЬ                                                                        \n";
	cout << "Стрелки влево-вправо ЦВЕТ                                                                          \n";

	bool moving = true;
	int keyDel = 83;// выход - Delete
	int h_kx = 1;
	int h_ky = 1;
	bool color_change = false;

	while (moving) {
		if (_kbhit() != 0)
		{
			int cd = _getch();   // из файла conio.h
			switch (cd) {
			// Delete
			case 83: {
				moving = false;
				gotoxy(0, 0);
				SetColor(15, 0);  // Инверсия цвета
				cout << "                                                                                          \n";
				cout << "                                                                                          \n";
				cout << "                                                                                          \n";
				return;
			}
			// вверх    224 72 (a, H)
			case 72: {
				Sleep_time = Sleep_time - Sleep_time_h;
				if (Sleep_time < 0) { Sleep_time = 0; }
				break;
			}
			// вниз     224 80 (a, P)
			case 80: {
				Sleep_time = Sleep_time + Sleep_time_h;
				break;
			}
		    // влево    224 75 (a, K)
			case 75: {
				ColorText = ColorText + 1;
				if (ColorText > 15) { ColorText = 0; cout << char(7);
				}
				break;
			}
			// вправо   224 77 (a, M) 
			case 77: {
				ColorText = ColorText - 1;
				if (ColorText < 0) { ColorText = 15; cout << char(7);
				}
				break;
			}
			// F1
			case 59: {
				SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
				gotoxy(0, 0);
				if (cout_C) {
					cout << "(с) Гаркуша О.В. (Меню) ФКТиПМ. КИТ. Март 2026                      \n";
					cout << "                                                                    \n";
					cout << "                                                                    \n";
				}
				else {
					cout << "                                                                    \n";
					cout << "                                                                    \n";
					cout << "                                                                    \n";
				}
				cout_C = not cout_C;
				break;
			}
			// F2     60
			case 60: {
				// Очищаем место для Help
				Clear_Help();

				if (cout_C) {
					Menu_Help_File = "Help_Color.txt";
					// Выводим  Help из файла
					Out_Help(Menu_Help_File);
				}
				cout_C = not cout_C;
				break;
			}
			// F3     61
			case 61: {
				// Очищаем место для Help
				Clear_Help();

				if (cout_C) {
					Menu_Help_File = "Help_Key.txt";
					// Выводим  Help из файла
					Out_Help(Menu_Help_File);
				}
				cout_C = not cout_C;
				break;
			}
			}
		}
		
		SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
		Out_Kvarat(xx01 + k_goriz, yy01 + k_vert);			// Выводим квадрат

		k_vert = k_vert + h_ky;
		if (k_vert < 1)
		{
			h_ky =  -h_ky;
			color_change = true;
		}
		if (k_vert > Console_y / 2 - kol_lines - 1)
		{
			h_ky = -h_ky;
			color_change = true;
		}

		k_goriz = k_goriz + h_kx;
		if (k_goriz < 1) 
		{
			h_kx = -h_kx;
			color_change = true;
		}
		if (k_goriz > Console_x - kol_lines * 2 - 2)
		{
			h_kx = -h_kx;
			color_change = true;
		}

		if (color_change) {
			ColorText = ColorText - 1;
			if (ColorText < 0) { ColorText = 15; }
			if (ColorText > 15) { ColorText = 0; }
			color_change = false;
		}

		SetColor(ColorFon, ColorText);  // Инверсия цвета
		Out_Kvarat(xx01 + k_goriz, yy01 + k_vert);			// Выводим квадрат

		Sleep(Sleep_time);
	}
	return;
}

// Выбор пункта меню
void SelectMenu() {
	xx01 = xx0 + 1;
	yy01 = yy0 + 1;

	SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
	gotoxy(0, 0);
	cout << "Стрелки - управление. Enter - движение. Esc - выход                                       \n";
	cout << "                                                                                          \n";
	cout << "                                                                                          \n";

	k_vert = rangeRand(0, Console_y/2 - kol_lines);
	k_goriz = rangeRand(0, Console_x/2 - kol_lines);

	SetColor(ColorFon, ColorText);  // Инверсия цвета
	Out_Kvarat(xx01 + k_goriz, yy01 + k_vert);			// Выводим квадрат

	int c = _getch();   // из файла conio.h
	while (c != 27) {   // выход - ESC 
		switch (c) {
		// Enter 13 - Выбор
		case 13: {
			// Движение квадрата
			Move_Kvadrat();
			ColorText = 15; ColorFon = 0;
			SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
			gotoxy(0, 0);
			cout << "Стрелки - управление. Enter - движение. Esc - выход                                       \n";
		}
		// вверх    224 72 (a, H)
		case 72: {
			SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
			Out_Kvarat(xx01 + k_goriz, yy01 + k_vert);			// Выводим квадрат

			k_vert = k_vert - 1;
			if (k_vert < 0) { k_vert = Console_y / 2 - kol_lines; }
			SetColor(ColorFon, ColorText);  // Инверсия цвета
			Out_Kvarat(xx01 + k_goriz, yy01 + k_vert);			// Выводим квадрат
			break;
		}
		// вниз     224 80 (a, P)
		case 80: {
			SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
			Out_Kvarat(xx01 + k_goriz, yy01 + k_vert);			// Выводим квадрат

			k_vert = k_vert + 1;
			if (k_vert > Console_y / 2 - kol_lines) { k_vert = 0; }
			SetColor(ColorFon, ColorText);  // Инверсия цвета
			Out_Kvarat(xx01 + k_goriz, yy01 + k_vert);			// Выводим квадрат
			break;
		}
		// влево    224 75 (a, k_vert)
		case 75: {
			SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
			Out_Kvarat(xx01 + k_goriz, yy01 + k_vert);			// Выводим квадрат

			k_goriz = k_goriz - 1;
			if (k_goriz < 0) { k_goriz = Console_x - kol_lines * 2;	}
			SetColor(ColorFon, ColorText);  // Инверсия цвета
			Out_Kvarat(xx01 + k_goriz, yy01 + k_vert);			// Выводим квадрат
			break;
		}
		// вправо   224 77 (a, M)
		case 77: {
			SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
			Out_Kvarat(xx01 + k_goriz, yy01 + k_vert);			// Выводим квадрат

			k_goriz = k_goriz + 1;
			if (k_goriz > Console_x - kol_lines*2) { k_goriz = 0; }
			SetColor(ColorFon, ColorText);  // Инверсия цвета
			Out_Kvarat(xx01 + k_goriz, yy01 + k_vert);			// Выводим квадрат
			break;
		}
		// F1
		case 59: {
			SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
			gotoxy(0, 0);
			if (cout_C) {
				cout << "(с) Гаркуша О.В. (Меню) ФКТиПМ. КИТ. Март 2026                     \n";
				cout << "                                                                    \n";
				cout << "                                                                    \n";
			}
			else {
				cout << "                                                                    \n";
				cout << "                                                                    \n";
				cout << "                                                                    \n";
			}
			cout_C = not cout_C;
			break;
		}
			   // F2     60
		case 60: {
			// Очищаем место для Help
			Clear_Help();
			if (cout_C) {
				Menu_Help_File = "Help_Color.txt";
				// Выводим  Help из файла
				Out_Help(Menu_Help_File);
			}

			cout_C = not cout_C;
			break;
		}
			   // F3     61
		case 61: {
			// Очищаем место для Help
			Clear_Help();

			if (cout_C) {
				Menu_Help_File = "Help_Key.txt";
				// Выводим  Help из файла
				Out_Help(Menu_Help_File);
			}

			cout_C = not cout_C;
			break;
		}
		
	}
		c = _getch();
	}
	if (c == 27) {
		gotoxy(55, 55);
		SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
		return;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));

	system("mode 120");  // Full screen

	hideCursor();		// Скрыть курсор 

	// Выводим рамку
	Out_Ramka(xx0, yy0); 

	// Строка квадрата
	line_kvadrat = "";
	for (int i = 1; i < 2*kol_lines; i++) {
		line_kvadrat = line_kvadrat + " ";
	}

	SelectMenu();

	system("pause");
}
