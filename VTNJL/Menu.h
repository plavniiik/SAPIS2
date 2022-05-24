#pragma once

#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

enum color
{
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

void SetColor(int text, int fon);

namespace Menu2
{
	int menu(const char menu[][200], int fieldsNumber);
};

const char mainMenu[][200] = { {" Аккаунт администратора "},{ " Аккаунт инвестора " },{" Аккаунт эксперта "},{" Выход "} };
const char adminMenu[][200] = { {" Раздел работы с экспертами "},{ " Раздел работы с инвесторами " },{" Изменить пароль и / или логин "},{" Информация о компании "}, {" Главное меню "} };

