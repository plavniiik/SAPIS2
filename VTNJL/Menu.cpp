#include "Menu.h"

int Menu2::menu(const char menu[][200], int fieldsNumber)
{
	SetColor(LightGray, Black);
	int cursor, j = 0;
	while (true)
	{
		COORD position = { 0, 2 };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		for (int i = 0; i < fieldsNumber; i++)
		{
			if (i == j)
			{
				SetColor(Cyan, Black);
				cout << ">>>";
				cout << menu[i] << endl;
				SetColor(LightGray, Black);
			}
			else
				cout << "    " << menu[i] << endl;
		}
		cursor = _getch();
		switch (cursor)
		{
		case 72:
			j--;
			if (j == -1)
				j = fieldsNumber - 1;
			break;
		case 80:
			j++;
			if (j == fieldsNumber)
				j = 0;
			break;
		case 13:
			return j;
		}
	}
}

void SetColor(int text, int fon)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, (fon << 4) + text);
}
