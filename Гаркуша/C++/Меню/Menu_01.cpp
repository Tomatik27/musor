// (с) Гаркуша О.В. март 2026

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

const int punkt_kol = 4;
string punkt_arr[punkt_kol] = {
" Вывод кодов нажатых клавиш ",
" Пункт меню 2               ",
" Пункт меню 3               ",
" Выход                      "
};

int ColorText = 15; // Белый
int ColorFon = 0;    // Чёрный
// Позиция Верхнего левого угла меню
int xx0 = 11;
int yy0 = 5;

// Позиция Верхнего левого угла Help
int x_h = 66;
int y_h = 2;

string Menu_Help_File;
bool cout_C = true;

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

void Out_Ramka() { // Вывод рамки
    // Вывод рамки
    //cout << "╔";
    //for (int i = 0; i < max_len_punkt + 2; i++) {
    //    cout << "═";
    //}
    //cout << "═" << endl;

    // ╔════╗ ║ ╝  ╚ ╣ ═ ╠ 201 ╤
    // ║    ║
    // ╠════╣ 
    // ║    ║
    // ╚════╝
    // 
    //for (int cc = 180; cc < 223; cc++) {
    //    printf("%c - %d\t", char(cc), cc);
    //}

}
 /*Вывод кодов нажатых клавиш
     Стрелки:
     влево    224 75 (a, K)       
     вправо   224 77 (a, M)
     вверх    224 72 (a, H)
     вниз     224 80 (a, P)

     Пробел   32
     Home     224 71 (a, G)
     Delete   224 83 (a, S)
     Enter    13
     F1       59
     F2       60
     */
void Code_Keys() {
    int Kol_Key = 1;
    gotoxy(1, punkt_kol+12);
    cout << "Нажимаете любую клавишу, - получаете её код..." << endl;
    cout << "ESC - выход" << endl;
    int c = _getch();   // из файла conio.h
    while (c != 27) {   // выход - ESC 
        printf("%c - %d |\t", char(c), c);
        c = _getch();
        if (Kol_Key % 6 == 0) {
            cout << endl;
        }
        Kol_Key = Kol_Key + 1;
    }
    cout << endl;
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
        gotoxy(1, 0);
        cout << "!!! Нет файла "<< Menu_Help_File << endl;
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

// Выбор пункта меню
int SelectMenu() {
    // Выводим всё меню
    for (int i = 0; i < punkt_kol; i++) {
        gotoxy(xx0, yy0 + i);
        cout << punkt_arr[i];
    }
    
    short k = 0;    // Активная команда
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
                SetCursorPos(xx0, yy0 + 11);
                cout <<"k=" << k << " --> " << punkt_arr[k] << endl;
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
                break;
            }
            // F1     59
            case 59: {
                // Очищаем место для Help
                Clear_Help(); 

                Menu_Help_File = "Menu_Help_Key.txt";
                // Выводим  Help из файла
                Out_Help(Menu_Help_File);

                break;
            }
            // F2     60
            case 60: {
                // Очищаем место для Help
                Clear_Help(); 

                Menu_Help_File = "Menu_Help_Color.txt";
                // Выводим  Help из файла
                Out_Help(Menu_Help_File);

                break;
            }
            // F3     61
            case 61: {
                SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
                gotoxy(1, 0);
                if (cout_C) {
                    cout << "(с) Гаркуша О.В. март 2026";
                }
                else {
                    cout << "                          ";
                }
                cout_C = not cout_C;
                break;
            }
        }

        c = _getch();
    }
    if (c == 27) {
        k = punkt_kol-1;
        SetColor(ColorText, ColorFon);  // Возвращаем на стандартные цвета
        return k;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    int kk = 1;

    //clear_screen();  // очистка экрана
    
    cout << endl << " F1 - Коды нажатых клавиш" << endl;
    cout << " F2 - Номер цвета" << endl;

    while(kk != punkt_kol-1){
        // Выбор пункта меню
        kk = SelectMenu();

        switch (kk) {
        case 0: {
            // Выполняем пункт меню 1
            Code_Keys();        // Вывод кодов нажатых клавиш
            break;
        }
        case 1: {
            // Выполняем пункт меню 2
            gotoxy(xx0, yy0 + 22);
            cout << " kk=" << kk << "   " << punkt_arr[kk] << endl;
            break;
        }
        case 2: {
            // Выполняем пункт меню 3
            gotoxy(xx0, yy0 + 22);
            cout << " kk=" << kk << "   " << punkt_arr[kk] << endl;
            break;
        }
        case punkt_kol-1: {
            // Выход
            gotoxy(xx0, yy0 + 22);
            cout << " kk=" << kk << "   Выход ==============  " << punkt_arr[kk] << endl;
            break;
        }
    }
}
   
    gotoxy(xx0, yy0 + 23);
    cout << " !!!  END " << punkt_arr[kk] << endl;
    //system("pause");
}
