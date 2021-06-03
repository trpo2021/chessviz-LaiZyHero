#include <Windows.h>
#include <iostream>

using namespace std;
// Количество клеток на шахматной доске
const int n = 64;

void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
// Цвета
enum ConsoleColor 
{
	Black = 0,
	LightGray = 7,
	DarkGray = 8,
	White = 15
};
// Покраска шахматной доски и добавление нумерации по бокам 
void Chess(char item[n])
{
	system("cls");
    SetColor(White, Black);
	cout << "8 ";
	for (int i = 0; i < 8; i += 2) {
		SetColor(Black, White);
		cout << " " << item[i] << " ";
		SetColor(Black, DarkGray);
		cout << " " << item[i + 1] << " ";
	}
	SetColor(White, Black);
	cout << "\n7 ";
	for (int i = 8; i < 16; i += 2) {
		SetColor(Black, DarkGray);
		cout << " " << item[i] << " ";
		SetColor(Black, White);
		cout << " " << item[i + 1] << " ";
	}
	SetColor(White, Black);
	cout << "\n6 ";
	for (int i = 16; i < 24; i += 2) {
		SetColor(Black, White);
		cout << " " << item[i] << " ";
		SetColor(Black, DarkGray);
		cout << " " << item[i + 1] << " ";
	}
	SetColor(White, Black);
	cout << "\n5 ";
	for (int i = 24; i < 32; i += 2) 
	{
		SetColor(Black, DarkGray);
		cout << " " << item[i] << " ";
		SetColor(Black, White);
		cout << " " << item[i + 1] << " ";
	}
	SetColor(White, Black);
	cout << "\n4 ";
	for (int i = 32; i < 40; i += 2) 
	{
		SetColor(Black, White);
		cout << " " << item[i] << " ";
		SetColor(Black, DarkGray);
		cout << " " << item[i + 1] << " ";
	}
	SetColor(White, Black);
	cout << "\n3 ";
	for (int i = 40; i < 48; i += 2) 
	{
		SetColor(Black, DarkGray);
		cout << " " << item[i] << " ";
		SetColor(Black, White);
		cout << " " << item[i + 1] << " ";
	}
	SetColor(White, Black);
	cout << "\n2 ";
	for (int i = 48; i < 56; i += 2) 
	{
		SetColor(DarkGray, White);
		cout << " " << item[i] << " ";
		SetColor(LightGray, DarkGray);
		cout << " " << item[i + 1] << " ";
	}
	SetColor(White, Black);
	cout << "\n1 ";
	for (int i = 56; i < 63; i += 2) 
	{
		SetColor(LightGray, DarkGray);
		cout << " " << item[i] << " ";
		SetColor(DarkGray, White);
		cout << " " << item[i + 1] << " ";
	}
	SetColor(White, Black);
	cout << "\n  ";
	cout << " A  B  C  D  E  F  G  H ";
	SetColor(Black, Black);
}
// Шахматные фигуры
int main()
{
    	char item[n];
	for (int i = 0; i < 63; i++) 
	{
		item[i] = ' ';
	}
	for (int i = 8; i < 16; i++) 
	{
		item[i] = 'P';
	}
	for (int i = 55; i > 47; i--) 
	{
		item[i] = 'P';
	}
	item[0] = 'R';
	item[1] = 'N';
	item[2] = 'B';
	item[3] = 'Q';
	item[4] = 'K';
	item[5] = 'B';
	item[6] = 'N';
	item[7] = 'R';
	item[56] = 'R';
	item[57] = 'N';
	item[58] = 'B';
	item[59] = 'Q';
	item[60] = 'K';
	item[61] = 'B';
	item[62] = 'N';
	item[63] = 'R';
	Chess(item);
    return 0;
}
