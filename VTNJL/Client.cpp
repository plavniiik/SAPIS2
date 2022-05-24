#define _AFXDLL
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include "Menu.h"


#define SIZE 40
#define length 17
using namespace std;

void pass(char* str)
{
	int j = 0;
	while (j != 16)
	{
		str[j] = _getch();
		if (str[j] == '\r')
			break;
		if (str[j] == '\b')
		{
			printf("\b \b");
			j--;
		}
		else if (str[j] != '\0')
		{
			printf("*");
			j++;
		}
	}
	str[j] = '\0';
}
void enter_logpass(char* login, char* password) {
	char str[length];

	while (true)
	{

		if (login[0] == '\0')
			cin.getline(str, length, '\n');
		else
			pass(str);
		if (strlen(str) >= 3)
		{
			for (unsigned int i = 0; i < strlen(str); i++)
			{
				if (str[i] >= 'A' && str[i] <= 'Z' || str[i] >= '0' && str[i] <= '9' || str[i] >= 'a' && str[i] <= 'z')
				{
					if (i == strlen(str) - 1)
					{
						if (login[0] == '\0')
							strcpy(login, str);
						else
							strcpy(password, str);

						return;
					}
					continue;
				}
				break;
			}
		}
		cin.clear();
		fflush(stdin);
		cout << "�����������, ���������� ��� ���!" << endl;
	}

}


void enter_login(char* login) {
	char str[length];

	while (true)
	{
		cin.getline(str, length, '\n');

		if (strlen(str) >= 3 && strlen(str) <= 16)
		{
			for (unsigned int i = 0; i < strlen(str); i++)
			{
				if (str[i] >= 'A' && str[i] <= 'Z' || str[i] >= '0' && str[i] <= '9' || str[i] >= 'a' && str[i] <= 'z')
				{
					if (i == strlen(str) - 1)
					{

						strcpy(login, str);
						return;
					}
					continue;
				}
				break;
			}
		}
		cin.clear();
		fflush(stdin);
		cout << "�����������, ���������� ��� ���!" << endl;
	}

}

double check_float() {
	float a;
	while (true)
	{
		cin >> a;
		if (cin.get() != '\n')
		{
			cout << "������ �����, ��������� �������." << endl;
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else return a;
	}
}
double check_i() {
	float a;
	while (true)
	{
		cin >> a;
		if (cin.get() != '\n')
		{
			cout << "������ �����, ��������� �������." << endl;
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else return a;
	}
}
bool check(char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] == '!' || str[i] == '@' || str[i] == '#' || str[i] == '$' || str[i] == '%' || str[i] == '^' || str[i] == '&' || str[i] == '*' || str[i] == '/' || str[i] == '.')
			return false;
	return true;
}
int ValueCheck_2(char* stroka)
{
	int k, flag = 0;
	k = strlen(stroka);
	while (flag != k)
	{
		for (int i = 0; i < k; i++)
		{
			int l = flag;
			if ((stroka[i] >= (-64)) && (stroka[i] <= (-1)))
			{
				flag++;
			}
			if ((stroka[i] == (-88)) || (stroka[i] == (-72)))
			{
				flag++;
			}
			if (flag == l)
			{
				i = k;
			}
		}
		if (flag != k)
		{
			return 1;
		}
		else return 2;
	}
}

bool check_numbers(char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] >= '0' && str[i] <= '9')
			return false;
	return true;
}

int CheckNumber() //���������� ������ ����� �����
{
	int number;
	while (1) {
		cin >> number;
		if (cin.get() != '\n') {
			cout << "��� �� �����. ��������� �������:" << endl;
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else return number;
	}
}

int CheckChoice(int a, int b) //������ ����� ����� �� ������������ ��������� (�� a �� b)
{
	int choice = 0;
	while (choice == 0) {
		choice = CheckNumber();
		if ((choice < a) || (choice > b)) {
			cout << "������ ����� ��� � ����! ����������, ��������� �������:" << endl;
			choice = 0;
		}
	}
	return choice;
}

int CheckChoicee(int a, int b) //������ ����� ����� �� ������������ ��������� (�� a �� b)
{
	int choice = 0;
	while (choice == 0) {
		choice = CheckNumber();
		if ((choice < a) || (choice > b)) {
			cout << "������ ����� ���� �� 0 �� 30! ��������� ���� ������, ����������!" << endl;
			choice = 0;
		}
	}
	return choice;
}

int CheckChoice2(int a, int b) //������ ����� ����� �� ������������ ��������� (�� a �� b)
{
	int choice = 0;
	while (choice == 0) {
		choice = CheckNumber();
		if ((choice < a) || (choice > b)) {
			cout << "� ��� ���� ������ ��������: �� � ���. �������� �����: 1/2!" << endl;
			choice = 0;
		}
	}
	return choice;
}


/*int Check_stazh(int a, int b) //������ ����� ����� �� ������������ ��������� (�� a �� b)
{
	int choice = 0;
	while (choice == 0) {
		choice = CheckNumber();
		if ((choice < a) || (choice > b)) {
			cout << "� ���������, ���������� �������� � ����� ������. " << endl;
			choice = 0;
		}
	}
	return choice;
}*/

template < typename T >
int Check_stazh(T a, T b) //������ ����� ����� �� ������������ ��������� (�� a �� b)
{
	int choice = 0;
	while (choice == 0) {
		choice = CheckNumber();
		if ((choice < a) || (choice > b)) {
			cout << "� ���������, ���������� �������� � ����� ������. " << endl;
			choice = 0;
		}
	}
	return choice;
}

float** Matrix(float**& matrix, int size) {

	matrix = new float* [size];

	for (int i = 0; i < size; i++) {

		matrix[i] = new float[4];

	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 0;
		}
	}

	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			if (j == i) {
				cout << endl;
			}
			else {
				if (matrix[j][i] == 0) {
					int ggg = 0;
					cout << "������� ������ ��� " << j + 1 << " ��������� ������������ " << i + 1 << endl;
					ggg = CheckChoicee(0, 30);
					matrix[j][i] = ggg;
					matrix[i][j] = 30 - matrix[j][i];
				}

			}

		}
	}

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {
			matrix[i][j] = matrix[i][j] / 30;
		}

	}


	return matrix;
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WORD wVersionRequested;
	WSADATA wsaData;
	int err, t, t1 = 0, t2 = 0, t3 = 0; int yyy;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		return -1;
	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(1280);
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	connect(s, (struct sockaddr*)&peer, sizeof(peer));
	char b[500], f[500], k[500], ex[35], buf[500], nuf[500];

	while (1) {
		f[0] = '\0';
		b[0] = '\0';
		recv(s, b, sizeof(b), 0);
		recv(s, f, sizeof(f), 0);
		cout << b;
		cout << f;
		t = Menu2::menu(mainMenu, 4);
		//t = CheckChoice(1, 4);//������� ����
		_itoa_s(t, b, 10);
		send(s, b, sizeof(b), 0);
		//recv(s, k, sizeof(k), 0);
		system("cls");
		//t = atoi(k);
		switch (t) {
		case 0: {
			char login2[20];
			char password2[20];
			int try_1 = 0;
			system("cls");
			f[0] = '\0';
			recv(s, f, sizeof(f), 0);

			if (strcmp(f, "0") == 0) {


				cout << "������������� ��� �� ���������������. ������� ������� �����������." << endl;
				cout << endl;

				cout << "������� �����:" << endl;
				enter_login(login2);
				f[0] = '\0';
				//��������� �����
				strcpy_s(f, login2);

				send(s, f, sizeof(f), 0);
				cout << endl;
				cout << "������� ������:" << endl;
				enter_logpass(login2, password2);
				f[0] = '\0';
				strcpy_s(f, password2);
				//��������� ������
				send(s, f, sizeof(f), 0);
				cout << endl;
			}
			else {
				cout << "���� � �������� ��������������." << endl;
				cout << endl;

				int yyy1 = 0;

				while (yyy1 == 0) {
					yyy1 = 0;
					ex[0] = '\0';
					cout << endl;
					cout << "������� �����:" << endl;
					enter_login(login2);
					f[0] = '\0';
					//��������� �����
					strcpy(f, login2);

					send(s, f, sizeof(f), 0);

					recv(s, ex, sizeof(ex), 0);//�������� ���������
					if (strcmp(ex, "0") == 0) {
						yyy1 = 1;
					}
					else {
						cout << "����� ��������!" << endl;
						cout << endl;
					}

				}

				int yyy2 = 0;

				while (yyy2 == 0) {
					yyy2 = 0;
					ex[0] = '\0';
					cout << endl;
					cout << "������� ������:" << endl;
					enter_logpass(login2, password2);
					f[0] = '\0';
					//��������� ������
					strcpy(f, password2);

					send(s, f, sizeof(f), 0);

					recv(s, ex, sizeof(ex), 0);//�������� ���������
					if (strcmp(ex, "0") == 0) {
						yyy2 = 1;
					}
					else {
						cout << endl;
						cout << "������ �� ���������!" << endl;
						cout << endl;

					}
				}
				cout << endl;
				cout << "���� �������� �������" << endl;
				cout << endl;
				system("pause");
				system("cls");
			}

			while (t1 != 5) {
				recv(s, k, sizeof(k), 0);
				cout << k << endl;
				t1 = CheckChoice(1, 5);
				_itoa_s(t1, b, 10);
				int check457 = 0;
				send(s, b, sizeof(b), 0);
				recv(s, k, sizeof(k), 0);
				t1 = atoi(k);
				switch (t1) {
				case 1: {
					//������ � ���������
					system("cls");
					while (t2 != 5) {
						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						t2 = CheckChoice(1, 5);
						_itoa_s(t2, b, 10);
						send(s, b, sizeof(b), 0);
						recv(s, k, sizeof(k), 0);
						t2 = atoi(k);
						switch (t2) {
						case 1: {
							system("cls");
							b[0] = '\0';
							f[0] = '\0';
							k[0] = '\0';
							strcpy_s(f, "*");
							strcpy_s(b, "f");
							recv(s, k, sizeof(k), 0);
							if (strcmp(k, "0") == 0) {
								cout << "��������� � ������ ���!" << endl;
							}

							else {
								while (strcmp(b, f) != 0) {
									b[0] = '\0';
									recv(s, b, sizeof(b), 0);
									if (strcmp(b, "*") != 0) { cout << b << endl; }
								}
							}
							f[0] = '\0';
							break;
						}
						case 2: {
							system("cls");

							k[0] = '\0';
							recv(s, k, sizeof(k), 0);

							if (strcmp(k, "0") == 0) {

								cout << "������� �������������� ��������." << endl;
								cout << endl;

								int check = 0;
								f[0] = '\0';
								while (check != 2)
								{
									cout << "������� �������" << endl;
									cin.getline(f, 20, '\n');
									check = ValueCheck_2(f);
									f[strlen(f)] = '\0';
									if (check == 1) {
										cout << "�������� ����, ���������� ��� ���!" << endl;
										cout << endl;
									}
								}
								send(s, f, sizeof(f), 0);

								check = 0;
								f[0] = '\0';
								while (check != 2)
								{
									cout << "������� ���:" << endl;
									cin.getline(f, 20, '\n');
									check = ValueCheck_2(f);
									if (check == 1) {
										cout << "�������� ����, ���������� ��� ���!" << endl;
										cout << endl;
									}
								}
								send(s, f, sizeof(f), 0);


								check = 0;
								f[0] = '\0';
								while (check != 2)
								{
									cout << "������� ���� ������:" << endl;

									check = Check_stazh(1, 55);
									break;
								}

								_itoa_s(check, f, 10);
								send(s, f, sizeof(f), 0);

								check = 0;
								f[0] = '\0';
								while (check != 2)
								{
									cout << "������� ���� ���������:" << endl;
									cin.getline(f, 50, '\n');
									check = ValueCheck_2(f);
									if (check == 1) {
										cout << "�������� ����, ���������� ��� ���!" << endl;
										cout << endl;
									}
								}
								send(s, f, sizeof(f), 0);

								check = 0;
								f[0] = '\0';
								while (check == 0) {
									cout << "������� ���� ����������� �����" << endl;
									cin.getline(f, 50, '\n');
									bool valid = true;
									int all_presents = 0;
									string suitable_symbols = "-_.@"; // ���������� ������� ������ ��������� ���� � ����

									for (int i = 0; f[i] != '\0'; i++)
									{
										if (!isalpha(f[i]) && !isdigit(f[i]) && suitable_symbols.find(f[i]) == std::string::npos) { // ������� ������������� �������
											valid = false; break;
										}
										if (i > 0 && f[i] == '.' && f[i - 1] == '.') { valid = false; break; } // ��� ����� ������
										else if (i > 0 && f[i] == '@' && !all_presents) { all_presents = 1; } // ������� @
										else if (f[i] == '@' && all_presents) { valid = false; break; } // ������� ���� @ � �������
										else if ((isalpha(f[i]) || isdigit(f[i])) && all_presents == 1) { all_presents = 2; } // ������� ����� ��� ����� ����� @
										else if (f[i] == '.' && all_presents == 2) { all_presents = 3; } // ������� ����� ����� �������( ������� ����� @ )
										else if (isalpha(f[i]) && all_presents == 3 && f[i + 2] == '\0') { all_presents = 4; } // ������� ����� � ����� �������
									}
									if (valid && all_presents == 4) { check = 1; }
									else { cout << "����� ������� �������!\n"; }
								}
								send(s, f, sizeof(f), 0);

								/*while (check != 2)
								{
									cout << "������� �����:" << endl;
									cin.getline(f, 50, '\n');
									check = ValueCheck_2(f);
									if (check == 1) {
										cout << "�������� ����, ���������� ��� ���!" << endl;
										cout << endl;
									}
								}*/

								char login[20];
								char password[20];
								f[0] = '\0';
								yyy = 0;
								while (yyy == 0) {
									yyy = 0;
									ex[0] = '\0';
									cout << "������� �����:" << endl;
									enter_login(login);
									f[0] = '\0';
									//��������� �����
									strcpy(f, login);

									send(s, f, sizeof(f), 0);

									recv(s, ex, sizeof(ex), 0);//�������� ���������
									if (strcmp(ex, "0") == 0) {
										yyy = 1;
									}
									else {
										cout << "����� ����� ��� ����������:" << endl;
									}
								}
								cout << "������� ������:" << endl;
								enter_logpass(login, password);
								f[0] = '\0';
								strcpy(f, password);
								//��������� ������
								send(s, f, sizeof(f), 0);
							}
							else {
								cout << "��� ���������� ��� ��������. � ��������� ������ ������!" << endl;
							}

							break;
						}
						case 3: {
							system("cls");
							//�������� ��������
							b[0] = '\0';
							f[0] = '\0';
							strcpy_s(f, "*");
							strcpy_s(b, "f");
							k[0] = '\0';
							recv(s, k, sizeof(k), 0);
							if (strcmp(k, "0") == 0) {
								cout << "��������� � ������ ���!" << endl;
							}

							else {
								while (strcmp(b, f) != 0) {
									b[0] = '\0';
									recv(s, b, sizeof(b), 0);
									if (strcmp(b, "*") != 0) { cout << b << endl; }
								}

								f[0] = '\0';
								cout << endl;

								cout << "������� ������� �������� �������� ������� �������." << endl;

								check457 = 0;
								while (check457 != 2)
								{
									cin.getline(f, 20, '\n');
									check457 = ValueCheck_2(f);
									f[strlen(f)] = '\0';
									if (check457 == 1) {
										cout << "�������� ����, ���������� ��� ���!" << endl;
										cout << endl;
									}
								}
								send(s, f, sizeof(f), 0);


								strcpy_s(f, "*");
								strcpy_s(b, "f");

								while (strcmp(b, f) != 0) {
									b[0] = '\0';
									recv(s, b, sizeof(b), 0);
									if (strcmp(b, "1") == 0) {
										cout << "������ �������� �� ����������!" << endl;
										strcpy_s(b, f);
									}
									if (strcmp(b, "*") != 0) { cout << b << endl; }
								}
								b[0] = '\0';
								cout << "������� ������� ������" << endl;
							}
							break;
						}
						case 4: {
							system("cls");
							//�������� ������ ���������
							k[0] = '\0';
							recv(s, k, sizeof(k), 0);

							if (strcmp(k, "0") == 0) {
								cout << "�������� ��� �� ������� ������� ���������!" << endl;
							}
							else {
								cout << "�������� ������� ����� ���������!" << endl;
								f[0] = '\0';
								b[0] = '\0';
								strcpy_s(f, "*");
								strcpy_s(b, "f");
								while (strcmp(b, f) != 0) {
									b[0] = '\0';
									recv(s, b, sizeof(b), 0);
									if (strcmp(b, "*") != 0) { cout << b << endl; }
								}
								cout << endl;
								cout << "�������� ��������� ��� ������ ��������� �������!" << endl;
								f[0] = '\0';
								b[0] = '\0';
								strcpy_s(f, "*");
								strcpy_s(b, "f");
								while (strcmp(b, f) != 0) {
									b[0] = '\0';
									recv(s, b, sizeof(b), 0);
									if (strcmp(b, "*") != 0) { cout << b << endl; }
								}
								system("pause");
							}
							break;
						}
						case 5: {
							system("cls");
							break;
						}
						}
					}
					t2 = 0;
					break;
				}
				case 2: {
					//������ ������ � �����������
					system("cls");
					while (t2 != 5) {
						recv(s, k, sizeof(k), 0);//�������� ����
						cout << k << endl;
						t2 = CheckChoice(1, 5);
						_itoa_s(t2, b, 10);
						send(s, b, sizeof(b), 0);
						recv(s, k, sizeof(k), 0);
						//cout << k << endl;
						int check456 = 0;
						t2 = atoi(k);
						switch (t2) {

						case 1: {
							system("cls");
							t3 = 0;
							k[0] = '\0';
							b[0] = '\0';
							while (t3 != 4) {
								recv(s, k, sizeof(k), 0);
								cout << k << endl;
								k[0] = '\0';
								t3 = 0;
								t3 = CheckChoice(1, 4);
								b[0] = '\0';
								_itoa_s(t3, b, 10);
								send(s, b, sizeof(b), 0);
								recv(s, k, sizeof(k), 0);
								int check = 0;
								t3 = atoi(k);
								int checu = 1;
								switch (t3) {

								case 1:
									system("cls");
									b[0] = '\0';
									f[0] = '\0';
									strcpy_s(f, "*");
									strcpy_s(b, "f");
									k[0] = '\0';
									recv(s, k, sizeof(k), 0);
									if (strcmp(k, "0") == 0) {
										cout << "���������� � ������ ���!" << endl;
									}

									else {
										cout << "�o��������" << endl;
										while (strcmp(b, f) != 0) {
											b[0] = '\0';
											recv(s, b, sizeof(b), 0);
											if (strcmp(b, "*") != 0) { cout << b << endl; }
										}


									}
									f[0] = '\0';

									break;
								case 2:
									system("cls");
									k[0] = '\0';
									recv(s, k, sizeof(k), 0);
									if (strcmp(k, "0") == 0) {
										cout << "���������� � ������ ���!" << endl;
									}

									else {
										cout << "����������" << endl;
										cout << "�� ������ ������������� ������ �� ����� ������ �� �����." << endl;
										check = 0;
										while (check != 2)
										{
											cout << "������� ����������� ��������" << endl;
											check = check_i();
											break;
										}
										_itoa_s(check, f, 10);
										send(s, f, sizeof(f), 0);


										check = 0;
										while (check != 2)
										{
											cout << "������� ������������ ��������" << endl;
											check = check_i();
											break;
										}
										_itoa_s(check, f, 10);
										send(s, f, sizeof(f), 0);


										strcpy_s(f, "*");
										strcpy_s(b, "f");

										while (strcmp(b, f) != 0) {
											b[0] = '\0';
											recv(s, b, sizeof(b), 0);
											if (strcmp(b, "1") == 0) {
												cout << "������ ��������� �� ����������!" << endl;
												strcpy_s(b, f);
											}
											if (strcmp(b, "*") != 0) { cout << b << endl; }
										}
									}
									b[0] = '\0';



									break;
								case 3:

									system("cls");
									k[0] = '\0';
									recv(s, k, sizeof(k), 0);
									if (strcmp(k, "0") == 0) {
										cout << "���������� � ������ ���!" << endl;
									}

									else {
										cout << "�����" << endl;

										check456 = 0;

										while (check456 != 2)
										{
											cout << "������� ������� ��� ������" << endl;
											cin.getline(f, 20, '\n');
											check456 = ValueCheck_2(f);
											f[strlen(f)] = '\0';
											if (check456 == 1) {
												cout << "�������� ����, ���������� ��� ���!" << endl;
												cout << endl;
											}
										}
										send(s, f, sizeof(f), 0);


										strcpy_s(f, "*");
										strcpy_s(b, "f");

										while (strcmp(b, f) != 0) {
											b[0] = '\0';
											recv(s, b, sizeof(b), 0);
											if (strcmp(b, "1") == 0) {
												cout << "������ ��������� �� ����������!" << endl;
												strcpy_s(b, f);
											}
											if (strcmp(b, "*") != 0) { cout << b << endl; }
										}
									}

									b[0] = '\0';

									break;
								case 4:
									system("cls");
									break;
								}
							}
							break;
						}
						case 2: {
							system("cls");
							//�������� ���������
							b[0] = '\0';
							f[0] = '\0';
							strcpy_s(f, "*");
							strcpy_s(b, "f");

							while (strcmp(b, f) != 0) {
								b[0] = '\0';
								recv(s, b, sizeof(b), 0);
								if (strcmp(b, "*") != 0) { cout << b << endl; }
							}

							f[0] = '\0';
							cout << endl;

							cout << "������� ������� ��������� �������� ������ �������." << endl;

							check457 = 0;
							while (check457 != 2)
							{
								cin.getline(f, 20, '\n');
								check457 = ValueCheck_2(f);
								f[strlen(f)] = '\0';
								if (check457 == 1) {
									cout << "�������� ����, ���������� ��� ���!" << endl;
									cout << endl;
								}
							}
							send(s, f, sizeof(f), 0);


							strcpy_s(f, "*");
							strcpy_s(b, "f");

							while (strcmp(b, f) != 0) {
								b[0] = '\0';
								recv(s, b, sizeof(b), 0);
								if (strcmp(b, "1") == 0) {
									cout << "������ ��������� �� ����������!" << endl;
									strcpy_s(b, f);
								}
								if (strcmp(b, "*") != 0) { cout << b << endl; }
							}
							b[0] = '\0';
							cout << "������� ������� ������" << endl;

							break;
						}
						case 3: {
							system("cls");
							//���������� ������� � ����������
							b[0] = '\0';
							f[0] = '\0';
							strcpy_s(f, "*");
							strcpy_s(b, "f");

							recv(s, k, sizeof(k), 0);

							if (strcmp(k, "0") == 0) {
								cout << "�������� �� ��������� ������ ����������. �� ������ ������� ������ �� ������!" << endl;
							}
							else {
								cout << "�������� ��������� ��� ������ ��������� ��������:" << endl;

								f[0] = '\0';
								b[0] = '\0';
								strcpy_s(f, "*");
								strcpy_s(b, "f");
								while (strcmp(b, f) != 0) {
									b[0] = '\0';
									recv(s, b, sizeof(b), 0);
									if (strcmp(b, "*") != 0) { cout << b << endl; }
								}
								cout << "\n*�������� �� ������� ��������, �� ������ ������� ������ ���������." << endl;
								cout << endl;
							}
							char y1[500];
							char y2[500];
							y1[0] = '\0';
							y2[0] = '\0';
							strcpy_s(y1, "*");
							strcpy_s(y2, "f");

							while (strcmp(y2, y1) != 0) {
								y2[0] = '\0';
								recv(s, y2, sizeof(y2), 0);
								if (strcmp(y2, "*") != 0) { cout << y2 << endl; }
							}
							y2[0] = '\0';
							cout << endl;
							cout << "������� �������, � ������� ������ ��������� �������." << endl;
							check457 = 0;
							while (check457 != 2)
							{
								cin.getline(f, 20, '\n');
								check457 = ValueCheck_2(f);
								f[strlen(f)] = '\0';
								if (check457 == 1) {
									cout << "�������� ����, ���������� ��� ���!" << endl;
									cout << endl;
								}
							}
							send(s, f, sizeof(f), 0);


							strcpy_s(f, "*");
							strcpy_s(b, "f");

							while (strcmp(b, f) != 0) {
								b[0] = '\0';
								recv(s, b, sizeof(b), 0);
								if (strcmp(b, "1") == 0) {
									cout << "������ ��������� �� ����������!" << endl;
									strcpy_s(b, f);
								}
								if (strcmp(b, "*") != 0) { cout << b << endl; }
							}
							b[0] = '\0';

							cout << endl;
							cout << "������ ���������� �� ���c�������� ���������!" << endl;

							break;
						}
						case 4: {
							system("cls");
							//����������� �������� � ����������
							b[0] = '\0';
							f[0] = '\0';
							strcpy_s(f, "*");
							strcpy_s(b, "f");

							while (strcmp(b, f) != 0) {
								b[0] = '\0';
								recv(s, b, sizeof(b), 0);
								if (strcmp(b, "*") != 0) { cout << b << endl; }
							}

							f[0] = '\0';
							//cout << endl;

							cout << "������� ������� ����������, � ������� ������ ����������� �������." << endl;

							check457 = 0;
							while (check457 != 2)
							{
								cin.getline(f, 20, '\n');
								check457 = ValueCheck_2(f);
								f[strlen(f)] = '\0';
								if (check457 == 1) {
									cout << "�������� ����, ���������� ��� ���!" << endl;
									cout << endl;
								}
							}
							send(s, f, sizeof(f), 0);


							strcpy_s(f, "*");
							strcpy_s(b, "f");

							while (strcmp(b, f) != 0) {
								b[0] = '\0';
								recv(s, b, sizeof(b), 0);
								if (strcmp(b, "1") == 0) {
									cout << "������ ��������� ���!" << endl;
									strcpy_s(b, f);
								}
								if (strcmp(b, "*") != 0) { cout << b << endl; }
							}
							b[0] = '\0';

							cout << endl;
							cout << "������ �� ������������!" << endl;

							break;
						}

						case 5: {
							system("cls");
							break;
						}

						}
					}
					t2 = 0;
					break;
				}
					  //���� ��������� ������ � ������
				case 3: {
					system("cls");
					int yyy1 = 0;
					cout << "����� �������� �����/������, �������� ��������� �����������." << endl;
					while (yyy1 == 0) {
						yyy1 = 0;
						ex[0] = '\0';
						cout << endl;
						cout << "������� �����:" << endl;
						enter_login(login2);
						f[0] = '\0';
						//��������� �����
						strcpy(f, login2);

						send(s, f, sizeof(f), 0);

						recv(s, ex, sizeof(ex), 0);//�������� ���������
						if (strcmp(ex, "0") == 0) {
							yyy1 = 1;
						}
						else {
							cout << "����� ��������!" << endl;
							cout << endl;
						}

					}

					int yyy2 = 0;

					while (yyy2 == 0) {
						yyy2 = 0;
						ex[0] = '\0';
						cout << endl;
						cout << "������� ������:" << endl;
						enter_logpass(login2, password2);
						f[0] = '\0';
						//��������� ������
						strcpy(f, password2);

						send(s, f, sizeof(f), 0);

						recv(s, ex, sizeof(ex), 0);//�������� ���������
						if (strcmp(ex, "0") == 0) {
							yyy2 = 1;
						}
						else {
							cout << endl;
							cout << "������ �� ���������!" << endl;
							cout << endl;

						}
					}
					cout << endl;
					cout << "������������� ������ �������!" << endl;
					system("pause");
					system("cls");
					while (t2 != 3) {
						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						t2 = CheckChoice(1, 3);;
						_itoa_s(t2, b, 10);
						send(s, b, sizeof(b), 0);
						recv(s, k, sizeof(k), 0);
						t2 = atoi(k);
						switch (t2) {
						case 1: {
							system("cls");
							//��������� ������
							cout << "������� �����:" << endl;
							enter_login(login2);
							f[0] = '\0';
							//��������� �����
							strcpy_s(f, login2);
							send(s, f, sizeof(f), 0);
							cout << endl;
							break;
						}
						case 2: {
							system("cls");
							//��������� ������

							cout << "������� ������:" << endl;
							enter_logpass(login2, password2);
							f[0] = '\0';
							strcpy_s(f, password2);
							//��������� ������
							send(s, f, sizeof(f), 0);
							cout << endl;

							break;
						}
						case 3: {
							system("cls");
							break;
						}

						}
					}
					t2 = 0;
					break;
				}
				case 4: {
					//���� ������ � ���������
					system("cls");
					while (t2 != 3) {
						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						t2 = CheckChoice(1, 3);;
						_itoa_s(t2, b, 10);
						send(s, b, sizeof(b), 0);
						recv(s, k, sizeof(k), 0);
						t2 = atoi(k);
						switch (t2) {
						case 1: {
							int check = 0;
							system("cls");
							k[0] = '\0';

							recv(s, k, sizeof(k), 0);

							if (strcmp(k, "0") == 0) {
								cout << "������� �������������� ��������!" << endl;
								cout << endl;
								cout << "������� �������� ��������." << endl;
								cout << endl;
								cin.getline(f, 20, '\n');
								f[strlen(f)] = '\0';
								send(s, f, sizeof(f), 0);

								cout << "������� �������� ������������ ��������." << endl;
								cout << endl;
								cin.getline(f, 20, '\n');
								f[strlen(f)] = '\0';

								send(s, f, sizeof(f), 0);

								check = 0;
								while (check != 2)
								{
									cout << "������� ������� �������������� �� ���������� �������� � �����������." << endl;
									cout << endl;
									cin.getline(f, 20, '\n');
									check = ValueCheck_2(f);
									f[strlen(f)] = '\0';
									if (check == 1) {
										cout << "�������� ����, ���������� ��� ���!" << endl;
										cout << endl;
									}
								}
								send(s, f, sizeof(f), 0);
								check = 0;
								float cap;
								while (true)
								{
									cout << "������� �������� ����� ��������, � ������� ��������� ��������" << endl;
									cap = check_float();
									break;
								}

								sprintf(f, "%.3f", cap);
								send(s, f, sizeof(f), 0);


							}

							else {
								cout << "������ � �������� ��� ����������. ������� ��, ������ ��� �������� ����� ������" << endl;
								cout << endl;
							}



							break;
						}
						case 2: {
							system("cls");
							k[0] = '\0';
							recv(s, k, sizeof(k), 0);

							if (strcmp(k, "0") == 0) {
								cout << "��� ������ ������� :(" << endl;
								cout << endl;
							}

							else {
								cout << "������ � �������� �������. �� �������� �������� ����� ������." << endl;
								cout << endl;
							}

							break;
						}
						case 3: {
							system("cls");
							break;
						}

						}
					}
					t2 = 0;
					break;
				}
				case 5: {
					system("cls");
					break;
				}
				}
			}
			t1 = 0;
			break;
		}
		case 1: {
			system("cls");
			int t444 = 0;
			k[0] = '\0';
			b[0] = '\0';
			while (t444 != 3) {
				recv(s, k, sizeof(k), 0);
				cout << k << endl;
				t444 = CheckChoice(1, 3);
				_itoa_s(t444, b, 10);
				send(s, b, sizeof(b), 0);
				recv(s, k, sizeof(k), 0);
				t444 = atoi(k);
				switch (t444) {
					f[0] = '\0';
				case 1: {
					//�����������

					system("cls");

					cout << "������� �������������� ��� � �������� ���������." << endl;
					cout << endl;

					int check = 0;

					while (check != 2)
					{
						cout << "������� ���� �������" << endl;
						cin.getline(f, 20, '\n');
						check = ValueCheck_2(f);
						f[strlen(f)] = '\0';
						if (check == 1) {
							cout << "�������� ����, ���������� ��� ���!" << endl;
							cout << endl;
						}
					}
					send(s, f, sizeof(f), 0);
					check = 0;
					while (check != 2)
					{
						cout << "������� ���� ���:" << endl;
						cin.getline(f, 20, '\n');
						check = ValueCheck_2(f);
						if (check == 1) {
							cout << "�������� ����, ���������� ��� ���!" << endl;
							cout << endl;
						}
					}
					send(s, f, sizeof(f), 0);


					check = 0;
					float cap;
					while (true)
					{
						cout << "������� ����� ��������, ������� ���������� ������� � ������������:(� ����������� ������):" << endl;
						cap = check_float();
						break;
					}

					sprintf(f, "%.3f", cap);
					//_itoa_s(check, f, 10);
					send(s, f, sizeof(f), 0);

					check = 0;
					while (check != 2)
					{
						cout << "������� ���������� ��������, � ������� �� ��� ������������:" << endl;

						check = check_i();
						break;
					}
					_itoa_s(check, f, 10);
					send(s, f, sizeof(f), 0);

					check = 0;
					while (check != 2)
					{
						cout << "������� ��� ���� ������ �� �����:" << endl;

						check = Check_stazh(1, 55);
						break;
					}

					_itoa_s(check, f, 10);
					send(s, f, sizeof(f), 0);


					char login[20];
					char password[20];

					yyy = 0;
					while (yyy == 0) {
						yyy = 0;
						ex[0] = '\0';
						cout << "������� �����:" << endl;
						enter_login(login);
						f[0] = '\0';
						//��������� �����
						strcpy(f, login);

						send(s, f, sizeof(f), 0);

						recv(s, ex, sizeof(ex), 0);//�������� ���������
						if (strcmp(ex, "0") == 0) {
							yyy = 1;
						}
						else {
							cout << "����� ����� ��� ����������:" << endl;
						}
					}
					cout << "������� ������:" << endl;
					enter_logpass(login, password);
					f[0] = '\0';
					strcpy(f, password);
					//��������� ������
					send(s, f, sizeof(f), 0);
					break;
				}
				case 2: {
					char login1[20];
					char password1[20];
					int yyy1 = 0;
					system("cls");
					while (yyy1 == 0) {
						yyy1 = 0;
						ex[0] = '\0';

						cout << "������� �����:" << endl;
						enter_login(login1);
						f[0] = '\0';
						//��������� �����
						strcpy(f, login1);

						send(s, f, sizeof(f), 0);

						recv(s, ex, sizeof(ex), 0);//�������� ���������
						if (strcmp(ex, "0") == 0) {
							yyy1 = 1;
						}
						else {
							cout << "������ ������������ ���!" << endl;
						}
					}

					int yyy2 = 0;
					while (yyy2 == 0) {
						yyy2 = 0;
						ex[0] = '\0';
						cout << "������� ������:" << endl;
						enter_logpass(login1, password1);
						f[0] = '\0';
						//��������� ������
						strcpy(f, password1);

						send(s, f, sizeof(f), 0);

						recv(s, ex, sizeof(ex), 0);//�������� ���������
						if (strcmp(ex, "0") == 0) {
							yyy2 = 1;
						}
						else {
							cout << "������ �� ���������!" << endl;
						}
					}

					cout << "���� �������� �������" << endl;
					while (t1 != 4) {

						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						t1 = CheckChoice(1, 4);
						_itoa_s(t1, b, 10);
						send(s, b, sizeof(b), 0);
						recv(s, k, sizeof(k), 0);
						yyy1 = 0;

						t1 = atoi(k);
						switch (t1) {

						case 1: {
							//�������������� ���������
							system("cls");
							while (t2 != 5) {

								//����� �������
								char F[500];
								F[0] = '\0';
								char I[500];
								I[0] = '\0';
								char cap[500];
								cap[0] = '\0';
								char pr[500];
								pr[0] = '\0';
								char exp[500];
								exp[0] = '\0';
								system("cls");
								for (int i = 0; i < 55; i++)
									cout << "-";
								cout << endl;
								cout << "|             �������|       ���|�������|�������| ����|" << endl;
								for (int i = 0; i < 55; i++)
									cout << "-";
								cout << endl;
								recv(s, F, sizeof(k), 0);
								recv(s, I, sizeof(k), 0);
								recv(s, cap, sizeof(k), 0);

								recv(s, pr, sizeof(k), 0);
								recv(s, exp, sizeof(k), 0);

								cout << "|" << setw(20) << F << "|" << setw(10) << I << "|" << setw(7) << cap << "|" << setw(7) << pr << "|" << setw(5) << exp << "|" << endl;
								for (int i = 0; i < 55; i++)
									cout << "-";
								cout << endl;

								//����� ������ �������

								recv(s, k, sizeof(k), 0);
								cout << k << endl;

								t2 = CheckChoice(1, 5);
								_itoa_s(t2, b, 10);
								send(s, b, sizeof(b), 0);
								recv(s, k, sizeof(k), 0);
								t2 = atoi(k);
								switch (t2) {
								case 1: {
									system("cls");
									int check = 0;
									while (check != 2)
									{
										cout << "������� ���� �������" << endl;
										cin.getline(f, 20, '\n');
										check = ValueCheck_2(f);
										f[strlen(f)] = '\0';
										if (check == 1) {
											cout << "�������� ����, ���������� ��� ���!" << endl;
											cout << endl;
										}
									}
									send(s, f, sizeof(f), 0);
									check = 0;
									while (check != 2)
									{
										cout << "������� ���� ���:" << endl;
										cin.getline(f, 20, '\n');
										check = ValueCheck_2(f);
										if (check == 1) {
											cout << "�������� ����, ���������� ��� ���!" << endl;
											cout << endl;
										}
									}
									send(s, f, sizeof(f), 0);

									break;
								}
								case 2: {
									system("cls");

									float cap;
									while (true)
									{
										cout << "������� ����� ��������, ������� ���������� ������� � ������������:(� ����������� ������):" << endl;
										cap = check_float();
										break;
									}

									sprintf(f, "%.3f", cap);
									//_itoa_s(check, f, 10);
									send(s, f, sizeof(f), 0);

									break;
								}
								case 3: {
									system("cls");

									int check = 0;
									while (check != 2)
									{
										cout << "������� ���������� ��������, � ������� �� ��� ������������:" << endl;

										check = check_i();
										break;
									}
									_itoa_s(check, f, 10);
									send(s, f, sizeof(f), 0);
									break;
								}
								case 4: {
									system("cls");

									int check = 0;
									while (check != 2)
									{
										cout << "������� ��� ���� ������ �� �����:" << endl;

										check = Check_stazh(1, 55);
										break;
									}

									_itoa_s(check, f, 10);
									send(s, f, sizeof(f), 0);

									break;
								}
								case 5: {
									system("cls");
									break;
								}
								}
							}
							t2 = 0;
							break;

						}
						case 2: {

							char F[500];
							F[0] = '\0';
							char I[500];
							I[0] = '\0';
							char cap[500];
							cap[0] = '\0';
							char pr[500];
							pr[0] = '\0';
							char exp[500];
							exp[0] = '\0';
							system("cls");
							for (int i = 0; i < 55; i++)
								cout << "-";
							cout << endl;
							cout << "|             �������|       ���|�������|�������| ����|" << endl;
							for (int i = 0; i < 55; i++)
								cout << "-";
							cout << endl;
							recv(s, F, sizeof(k), 0);
							recv(s, I, sizeof(k), 0);
							recv(s, cap, sizeof(k), 0);
							recv(s, pr, sizeof(k), 0);
							recv(s, exp, sizeof(k), 0);

							cout << "|" << setw(20) << F << "|" << setw(10) << I << "|" << setw(7) << cap << "|" << setw(7) << pr << "|" << setw(5) << exp << "|" << endl;
							for (int i = 0; i < 55; i++)
								cout << "-";
							cout << endl;

							system("pause");
							break;
						}
						case 3: {
							system("cls");
							char mes[500];
							char mes2[500];
							mes[0] = '\0';
							int t_4 = 0;
							k[0] = '\0';
							b[0] = '\0';
							while (t_4 != 4) {
								recv(s, k, sizeof(k), 0);
								cout << k << endl;
								t_4 = CheckChoice(1, 4);
								_itoa_s(t_4, b, 10);
								send(s, b, sizeof(b), 0);
								recv(s, k, sizeof(k), 0);
								t_4 = atoi(k);
								switch (t_4) {
									f[0] = '\0';
								case 1: {
									int choiceee;
									recv(s, mes, sizeof(k), 0);
									if (strcmp(mes, "0") == 0) {
										cout << "� ��� ���� ����� �� ���������� ��������!" << endl;
										//��� ����� ���������!!!!

										f[0] = '\0';
										b[0] = '\0';
										strcpy_s(f, "*");
										strcpy_s(b, "f");
										while (strcmp(b, f) != 0) {
											b[0] = '\0';
											recv(s, b, sizeof(b), 0);
											if (strcmp(b, "*") != 0) { cout << b << endl; }
										}


										cout << endl;
										cout << "�� ������ �������� ������?\n1 - ��\n2 - ���." << endl;
										choiceee = CheckChoice2(1, 2);
										if (choiceee == 1) {
											mes2[0] = '\0';
											strcpy(mes2, "1");
											send(s, mes2, sizeof(mes2), 0);
										}

										else {
											mes2[0] = '\0';
											strcpy(mes2, "2");
											send(s, mes2, sizeof(mes2), 0);
										}

									}

									else {
										cout << "� ���������, � ��� ��� ������ �� ���������� ��������!" << endl;
										cout << endl;
									}
									break;
								}
								case 2: {
									system("cls");
									int choiceee;
									recv(s, mes, sizeof(k), 0);
									if (strcmp(mes, "0") == 0) {
										cout << "� ��� ���� ����� �� ������������ ��������!" << endl;
										cout << endl;

										f[0] = '\0';
										b[0] = '\0';
										strcpy_s(f, "*");
										strcpy_s(b, "f");
										while (strcmp(b, f) != 0) {
											b[0] = '\0';
											recv(s, b, sizeof(b), 0);
											if (strcmp(b, "*") != 0) { cout << b << endl; }
										}

										cout << "�� ������ �������� ������?\n1 - ��\n2 - ���." << endl;
										choiceee = CheckChoice2(1, 2);
										if (choiceee == 1) {
											mes2[0] = '\0';
											strcpy(mes2, "1");
											send(s, mes2, sizeof(mes2), 0);
										}

										else {
											mes2[0] = '\0';
											strcpy(mes2, "2");
											send(s, mes2, sizeof(mes2), 0);
										}

									}

									else {
										cout << "� ��� ��� ������ �� ������������ ��������!" << endl;
										cout << endl;
									}
									break;
								}
								case 3: {
									system("cls");

									recv(s, mes, sizeof(k), 0);
									if (strcmp(mes, "0") == 0) {
										cout << "� ��� ���� ����������� ��������!" << endl;

										f[0] = '\0';
										b[0] = '\0';
										strcpy_s(f, "*");
										strcpy_s(b, "f");
										while (strcmp(b, f) != 0) {
											b[0] = '\0';
											recv(s, b, sizeof(b), 0);
											if (strcmp(b, "*") != 0) { cout << b << endl; }
										}
									}
									else {
										cout << "� ���������, � ��� ��� ����������� ���������!" << endl;
										cout << endl;
									}

									break;
								}
								case 4: {
									system("cls");
									break;
								}

								}
							}
							t_4 = 0;
							break;
						}
						case 4: {
							system("cls");
							break;
						}

						}
					}
					t1 = 0;
					break;
				}
				case 3: {
					system("cls");
					break;

				}
				}
			}

			t444 = 0;
			break;
		}
		case 2: {
			//system("cls");
			while (t1 != 4) {
				recv(s, k, sizeof(k), 0);
				cout << k << endl;
				t1 = CheckChoice(1, 4);
				_itoa_s(t1, b, 10);
				send(s, b, sizeof(b), 0);
				recv(s, k, sizeof(k), 0);
				t1 = atoi(k);
				switch (t1) {
				case 1: {
					system("cls");
					cout << "���������� �� ����������:" << endl;
					b[0] = '\0';
					f[0] = '\0';
					k[0] = '\0';
					strcpy_s(f, "*");
					strcpy_s(b, "f");

					recv(s, k, sizeof(k), 0);

					if (strcmp(k, "0") == 0) {
						cout << "���������� � ������ ���!" << endl;
					}

					else {
						while (strcmp(b, f) != 0) {
							b[0] = '\0';
							recv(s, b, sizeof(b), 0);
							if (strcmp(b, "*") != 0) { cout << b << endl; }
						}
					}
					system("pause");
					f[0] = '\0';
					break;
				}
				case 2: {
					//����������� ������ ����������
					system("cls");
					int size = 0;
					char message3[500];
					message3[0] = '\0';
					float** matrix3 = NULL;
					float** matrix4 = NULL;
					float** matrix5 = NULL;

					recv(s, message3, sizeof(message3), 0);

					if (strcmp(message3, "0") == 0) {
						cout << "�� ������ ��������� �� ���� ����������������!" << endl;
						system("pause");
					}

					else {
						k[0] = '\0';
						recv(s, k, sizeof(k), 0);

						if (strcmp(k, "0") == 0) {
							cout << "�� ������� ��������� ��� ����������� ������! �� ������ ���� 3." << endl;
							system("pause");
						}

						else {
							int choice89 = 0;
							string path4 = "E:\\4 ������\\����������������������\\SAPIS\\Server\\matrix1.txt";
							ifstream fff5(path4, ios::trunc | ios::out);
							if (fff5.peek() != EOF) {
								cout << "������������ ������ ��� ���������� � ����. ������ ������ ������ ������?\n1 - ��\n2 - ���.\n�����:" << endl;
								choice89 = CheckChoice2(1, 2);
								b[0] = '\0';

								fff5.close();
							}
							if (choice89 == 1 || choice89 == 0) {
								strcpy_s(b, "1");
								send(s, b, sizeof(b), 0);
								cout << "�� ������ ������������ ��� ������������� ���������." << endl;
								k[0] = '\0';
								size = atoi(message3);
								f[0] = '\0';
								b[0] = '\0';
								strcpy_s(f, "*");
								strcpy_s(b, "f");
								while (strcmp(b, f) != 0) {
									b[0] = '\0';
									recv(s, b, sizeof(b), 0);
									if (strcmp(b, "*") != 0) { cout << b << endl; }
								}
								cout << endl;


								cout << "������ �������� ����� ����. ����������, �������!" << endl;
								Matrix(matrix3, size);
								//Write(matrix3, size);
								string path = "E:\\4 ������\\����������������������\\SAPIS\\Server\\matrix1.txt";
								ofstream f(path, ios::trunc | ios::out);
								for (int i = 0; i < size; i++)
								{
									for (int j = 0; j < size; j++)
									{
										f << matrix3[i][j] << ";";
									}

								}
								f << "*";
								f.close();

								cout << endl;
								cout << "������ �������� ����� ���. ����������, �������!" << endl;
								Matrix(matrix4, size);
								//Write(matrix3, size);
								string path1 = "E:\\4 ������\\����������������������\\SAPIS\\Server\\matrix2.txt";

								ofstream fi(path1, ios::trunc | ios::out);
								for (int i = 0; i < size; i++)
								{
									for (int j = 0; j < size; j++)
									{
										fi << matrix4[i][j] << ";";
									}

								}
								fi << "*";
								fi.close();

								cout << endl;
								cout << "������ �������� ����� ���. ����������, �������!" << endl;
								Matrix(matrix5, size);
								//Write(matrix3, size);
								string path2 = "E:\\4 ������\\����������������������\\SAPIS\\Server\\matrix3.txt";

								ofstream fil(path2, ios::trunc | ios::out);
								for (int i = 0; i < size; i++)
								{
									for (int j = 0; j < size; j++)
									{
										fil << matrix5[i][j] << ";";
									}

								}
								fil << "*";
								fil.close();
								system("pause");
							}
							if (choice89 == 2) {
								strcpy_s(b, "2");
								send(s, b, sizeof(b), 0);
								cout << "������ �������� ��������!" << endl;
								system("pause");
							}
						}
					}
					break;
				}
				case 3: {
					system("cls");
					char message3[500];
					message3[0] = '\0';
					recv(s, message3, sizeof(message3), 0);
					if (strcmp(message3, "0") == 0) {
						cout << "������ ��� �� �����������! ��������� � ����� ���� ��� ������������ ������" << endl;
						system("pause");
					}

					else {
						cout << "����� ��������!" << endl;

						cout << "�������� ��������� ��� ������ ��������� �������!" << endl;
						f[0] = '\0';
						b[0] = '\0';
						strcpy_s(f, "*");
						strcpy_s(b, "f");
						while (strcmp(b, f) != 0) {
							b[0] = '\0';
							recv(s, b, sizeof(b), 0);
							if (strcmp(b, "*") != 0) { cout << b << endl; }
						}
						system("pause");
					}
					break;
				}
				case 4: {
					system("cls");
					break;
				}
				}
				system("cls");
			}
			t1 = 0;
			break;
		}
		case 3: {
			system("cls");
			WSACleanup();
			return 0;
		}
		}
	}
}
