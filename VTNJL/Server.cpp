#define _AFXDLL 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <afx.h>  
#include <winsock2.h>
#include <process.h> 
#include <string>
#include <fstream>
#include <list>
#include <iomanip>
#include <ctime>
#include <exception>




#define SIZE 40
#define length 17


//#include "Windows.h"

using namespace std;

CFile f;
CFileException ex;

class IntentionalException : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Вызвано исключение преднамеренной проверки";
	}

} intentional_exception;

int check_int() {
	int a;
	while (true)
	{
		cin >> a;
		if (cin.get() != '\n')
		{
			cout << "Ошибка ввода, повторите попытку." << endl;
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else return a;
	}
}


class Account {

protected:
	char login[length];               //логин учетной записи
	char password[length];            //пароль учетонй записи
public:
	Account() { login[0] = '\0'; password[0] = '\0'; }
	void enter_logpass() {};             //ввод логина и пароля
	void encrypt_pass() {};              //шифровка пароля
	void create_account();
	char* get_login() { return login; }  //получение логина
	void pass(char* str) {};   //ввод пароля звездочками
	char* Get_pass()
	{
		return password;
	}

	char* Get_log()
	{
		return login;
	}
	void Set_login(const char* log) {
		strcpy_s(login, log);

	}

	void Set_pass(const char* pas) {
		strcpy_s(password, pas);
	}

	/*Account(const Account& obj) {

		strcpy_s(this->login, obj.login);
		strcpy_s(this->password, obj.password);

	}*/
};

class Admin : public Account {
public:
	bool autorization() {};                       //авторизация администратора
	void create_account() {};                     //создание администратора
	bool enter() {};                              //вход администратора
	bool account_exist() {};                      //проверка на существование аккаунта

	Admin() {  };  //конструктор
	~Admin() {};

	friend bool operator<(const Admin& o1, const Admin& o2);
	friend bool operator>(const Admin& o1, const Admin& o2);
	friend bool operator==(const Admin& o1, const Admin& o2);
	friend bool operator!=(const Admin& o1, const Admin& o2);
	friend void write_in_file_password_admin(list<Admin> lst);

};

bool operator<(const Admin& o1, const Admin& o2) {
	return strcmp(o1.login, o2.login) < 0;
}
bool operator>(const Admin& o1, const Admin& o2) {
	return strcmp(o1.login, o2.login) > 0;
}
bool operator==(const Admin& o1, const Admin& o2) {
	return strcmp(o1.login, o2.login) == 0;
}
bool operator!=(const Admin& o1, const Admin& o2) {
	return strcmp(o1.login, o2.login) != 0;
}

void write_in_file_password_admin(list<Admin> lst)
{
	list<Admin>::iterator ite;
	ofstream file("Admin_log.txt", ios_base::out & ios_base::trunc);

	for (ite = lst.begin(); ite != lst.end(); ite++) {
		for (int i = 0; i < strlen(ite->login); i++) {
			ite->login[i] = (char)((int)ite->login[i] + 3);
		}
		for (int i = 0; i < strlen(ite->password); i++) {
			ite->password[i] = (char)((int)ite->password[i] + 3);
		}
		file << ite->Get_log() << ";" << ite->Get_pass() << ";";
	}
	file << "*;";
	file.close();
}

void read_admin_fromfile(list<Admin>& investors)
{

	Admin admin;
	char stro[100];
	float ff12;
	int k12;
	ifstream fout("Admin_log.txt", ios_base::in);


	try
	{
		if (!fout.is_open() || fout.peek() == EOF)
			throw intentional_exception;
	}
	catch (IntentionalException ex)
	{
		std::cerr << "Исключение! Файл не открыт!" << std::endl;

		return;

	}

	while (1) {
		fout.getline(stro, 100, ';');
		if (strcmp(stro, "*") == 0) {
			break;
		}
		for (int i = 0; i < strlen(stro); i++) {
			stro[i] = (char)((int)stro[i] - 3);
		}
		admin.Set_login(stro);
		fout.getline(stro, 100, ';');
		for (int i = 0; i < strlen(stro); i++) {
			stro[i] = (char)((int)stro[i] - 3);
		}
		admin.Set_pass(stro);
		investors.push_back(admin);
	}
	fout.close();
}

class Expert : public Account {
protected:
	char F[20];
	char I[10];
	int exp;
	char position[50];
	char email[50];

public:
	Expert() { F[0] = '\0'; I[0] = '\0', exp = 0; login[0] = '\0'; password[0] = '\0'; position[0] = '\0'; email[0] = '\0'; }; //конструктор без параметров

	//Expert(char*, char*) {};                              //конструктор с параметрами
	bool autorization() {};                            //авторизация клиента
	void create_account(list<Expert>&) {};               //регистрация клиента
	bool enter(list<Expert>) {};                         //метод входа клиента
	bool account_exist(list<Expert>) {};                 //проверка на существование аккаунта
	~Expert() {};                                      //пустой деструктор

	char* Get_F()
	{
		return F;
	}
	char* Get_I()
	{
		return I;
	}

	char* Get_email()
	{
		return email;
	}

	char* Get_position()
	{
		return position;

	}

	int Get_exp() {
		return exp;
	}

	void Set_F(const char* lastname)
	{
		strcpy_s(F, lastname);
	}


	void Set_I(const char* name)
	{
		strcpy_s(I, name);
	}

	void Set_position(const char* name)
	{
		strcpy_s(position, name);
	}

	void Set_email(const char* em)
	{
		strcpy_s(email, em);
	}

	void Set_exp(int ex) {
		this->exp = ex;
	}
	friend void write_in_file_password_experts(list<Expert> lst);


	void write_expert_sort(list<Expert> lst)
	{

		list<Expert>::iterator p;
		ofstream file("Experts_sort.txt", ios_base::out & ios_base::trunc);
		for (int i = 0; i < 85; i++)
			file << "-";
		file << endl;
		file << "|             Фамилия|       Имя| Стаж|        Должность|                     e-mail|" << endl;
		for (int i = 0; i < 85; i++)
			file << "-";
		file << endl;
		for (p = lst.begin(); p != lst.end(); p++) {
			file << "|" << setw(20) << p->Get_F() << "|" << setw(10) << p->Get_I() << "|" << setw(5) << p->Get_exp() << "|" << setw(17) << p->Get_position() << "|" << setw(27) << p->Get_email() << "|" << endl;
		}
		for (int i = 0; i < 85; i++) {
			file << "-";
		}

		file << endl;
		file << "*;";
		file.close();
	}


	int write_expert_search(list<Expert> lst, char* str)
	{
		int i = 0;
		list<Expert>::iterator p;
		ofstream file("Experts_search.txt", ios_base::out & ios_base::trunc);
		for (int i = 0; i < 85; i++)
			file << "-";
		file << endl;
		file << "|             Фамилия|       Имя| Стаж|        Должность|                     e-mail|" << endl;
		for (int i = 0; i < 85; i++)
			file << "-";
		file << endl;
		for (p = lst.begin(); p != lst.end(); p++) {
			if (strcmp(p->Get_F(), str) == 0) {
				file << "|" << setw(20) << p->Get_F() << "|" << setw(10) << p->Get_I() << "|" << setw(5) << p->Get_exp() << "|" << setw(17) << p->Get_position() << "|" << setw(27) << p->Get_email() << "|" << endl;
				i++;
			}
		}
		for (int i = 0; i < 85; i++) {
			file << "-";
		}

		file << endl;
		file << "*;";
		file.close();
		return i;
	}


};


void write_expert_infile(list<Expert> lst)
{
	list<Expert>::iterator p;
	ofstream file("Experts.txt", ios_base::out & ios_base::trunc);
	for (p = lst.begin(); p != lst.end(); p++) {
		file << p->Get_F() << ";" << p->Get_I() << ";" << p->Get_exp() << ";" << p->Get_position() << ";" << p->Get_email() << ";";
	}
	file << "*;";
	file.close();
}

void write_in_file_password_experts(list<Expert> lst)
{
	list<Expert>::iterator p;
	ofstream file("Experts_log.txt", ios_base::out & ios_base::trunc);

	for (p = lst.begin(); p != lst.end(); p++) {
		for (int i = 0; i < strlen(p->login); i++) {
			p->login[i] = (char)((int)p->login[i] + 3);
		}
		for (int i = 0; i < strlen(p->password); i++) {
			p->password[i] = (char)((int)p->password[i] + 3);
		}
		file << p->Get_log() << ";" << p->Get_pass() << ";";
	}
	file << "*;";
	file.close();
}

void read_experts_fromfile(list<Expert>& experts)
{

	Expert expert;
	char str[100];
	float ff;
	int k;
	ifstream f("Experts.txt", ios_base::in);
	if (!f.is_open() || f.peek() == EOF) {
		//cout << "Файл не удалось открыть или он пуст(эксперты)." << endl;
		return;
	}

	ifstream file("Experts_log.txt", ios_base::in);
	if (!file.is_open() || file.peek() == EOF) {
		//cout << "Файл не удалось открыть или он пуст (эксперты)." << endl;
		return;
	}
	while (1) {
		f.getline(str, 100, ';');
		if (strcmp(str, "*") == 0) {
			break;
		}
		expert.Set_F(str);
		f.getline(str, 100, ';');
		expert.Set_I(str);

		f.getline(str, 100, ';');
		k = 0;
		k = atoi(str);
		expert.Set_exp(k);

		f.getline(str, 100, ';');
		expert.Set_position(str);
		f.getline(str, 100, ';');

		expert.Set_email(str);

		file.getline(str, 100, ';');
		if (strcmp(str, "*") == 0) {
			break;
		}
		for (int i = 0; i < strlen(str); i++) {
			str[i] = (char)((int)str[i] - 3);
		}
		expert.Set_login(str);
		file.getline(str, 100, ';');

		for (int i = 0; i < strlen(str); i++) {
			str[i] = (char)((int)str[i] - 3);
		}
		expert.Set_pass(str);
		experts.push_back(expert);
	}
	f.close();
	file.close();
}
class Investor : public Account {
protected:
	char F[20];
	char I[10];
	int practice;
	float capital;
	int projects;

public:
	Investor() { F[0] = '\0'; I[0] = '\0', practice = 0; capital = 0; projects = 0; } //конструктор без параметров
	//Investor(char*, char*) {}                            //конструктор с параметрами
	void action() {}
	bool autorization() {}                            //авторизация клиента
	void create_account(list<Investor>&) {}             //регистрация клиента
	bool enter(list<Investor>) {}                      //метод входа клиента
	bool account_exist(list<Investor>) {}          //проверка на существование аккаунта
	~Investor() {};      //пустой деструктор

	char* Get_F()
	{
		return F;
	}
	char* Get_I()
	{
		return I;
	}

	void Set_F(const char* lastname)
	{
		strcpy_s(F, lastname);
	}

	void Set_I(const char* name)
	{
		strcpy_s(I, name);
	}

	int Get_practice() {
		return practice;
	}

	int Get_projects() {
		return projects;
	}

	float Get_capital() {
		return capital;
	}

	void Set_practice(int pr) {
		this->practice = pr;
	}

	void Set_projects(int project) {
		this->projects = project;
	}

	void Set_capital(float cap) {
		this->capital = cap;

	}

	void write_investor_best2(list<Investor> lst)
	{
		//lst.sort();
		list<Investor>::iterator p;
		ofstream file("Investors_best2.txt", ios_base::out & ios_base::trunc);
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		file << "|             Фамилия|       Имя|Капитал|Проекты| Стаж|" << endl;
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		for (p = lst.begin(); p != lst.end(); p++) {
			file << "|" << setw(20) << p->Get_F() << "|" << setw(10) << p->Get_I() << "|" << setw(7) << p->Get_capital() << "|" << setw(7) << p->Get_projects() << "|" << setw(5) << p->Get_practice() << "|" << endl;
		}
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		file << "*;";
		file.close();
	}
	void write_investor_best(list<Investor> lst)
	{
		//lst.sort();
		list<Investor>::iterator p;
		ofstream file("Investors_best.txt", ios_base::out & ios_base::trunc);
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		file << "|             Фамилия|       Имя|Капитал|Проекты| Стаж|" << endl;
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		for (p = lst.begin(); p != lst.end(); p++) {
			file << "|" << setw(20) << p->Get_F() << "|" << setw(10) << p->Get_I() << "|" << setw(7) << p->Get_capital() << "|" << setw(7) << p->Get_projects() << "|" << setw(5) << p->Get_practice() << "|" << endl;
		}
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		file << "*;";
		file.close();
	}

	void write_investor_sort(list<Investor> lst)
	{
		lst.sort();
		list<Investor>::iterator p;
		ofstream file("Investors_sort.txt", ios_base::out & ios_base::trunc);
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		file << "|             Фамилия|       Имя|Капитал|Проекты| Стаж|" << endl;
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		for (p = lst.begin(); p != lst.end(); p++) {
			file << "|" << setw(20) << p->Get_F() << "|" << setw(10) << p->Get_I() << "|" << setw(7) << p->Get_capital() << "|" << setw(7) << p->Get_projects() << "|" << setw(5) << p->Get_practice() << "|" << endl;
		}
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		file << "*;";
		file.close();
	}


	void write_investor_sort2(list<Investor> lst)
	{
		lst.sort();
		list<Investor>::iterator p;
		ofstream file("Investors_done2.txt", ios_base::out & ios_base::trunc);
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		file << "|             Фамилия|       Имя|Капитал|Проекты| Стаж|" << endl;
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		for (p = lst.begin(); p != lst.end(); p++) {
			file << "|" << setw(20) << p->Get_F() << "|" << setw(10) << p->Get_I() << "|" << setw(7) << p->Get_capital() << "|" << setw(7) << p->Get_projects() << "|" << setw(5) << p->Get_practice() << "|" << endl;
		}
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		file << "*;";
		file.close();
	}

	int write_investor_filtration(list<Investor> lst, int min, int max)
	{
		int i = 0;
		//lst.sort();
		list<Investor>::iterator p;
		ofstream file("Investors_filtr.txt", ios_base::out & ios_base::trunc);
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		file << "|             Фамилия|       Имя|Капитал|Проекты| Стаж|" << endl;
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		for (p = lst.begin(); p != lst.end(); p++) {
			if ((p->Get_practice() >= min) && (p->Get_practice() <= max)) {
				file << "|" << setw(20) << p->Get_F() << "|" << setw(10) << p->Get_I() << "|" << setw(7) << p->Get_capital() << "|" << setw(7) << p->Get_projects() << "|" << setw(5) << p->Get_practice() << "|" << endl;
				i++;
			}
		}
		for (int i = 0; i < 55; i++) {
			file << "-";
		}
		file << endl;
		file << "*;";
		file.close();
		return i;
	}


	int write_investor_search(list<Investor> lst, char* str)
	{
		int i = 0;
		//lst.sort();
		list<Investor>::iterator p;
		ofstream file("Investors_search.txt", ios_base::out & ios_base::trunc);
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		file << "|             Фамилия|       Имя|Капитал|Проекты| Стаж|" << endl;
		for (int i = 0; i < 55; i++)
			file << "-";
		file << endl;
		for (p = lst.begin(); p != lst.end(); p++) {
			if (strcmp(p->Get_F(), str) == 0) {
				file << "|" << setw(20) << p->Get_F() << "|" << setw(10) << p->Get_I() << "|" << setw(7) << p->Get_capital() << "|" << setw(7) << p->Get_projects() << "|" << setw(5) << p->Get_practice() << "|" << endl;
				i++;
			}
		}
		for (int i = 0; i < 55; i++) {
			file << "-";
		}
		file << endl;
		file << "*;";
		file.close();
		return i;
	}


	friend void write_in_file_password(list<Investor> lst);
	friend bool operator<(const Investor& o1, const Investor& o2);
	friend bool operator>(const Investor& o1, const Investor& o2);
	friend bool operator==(const Investor& o1, const Investor& o2);
	friend bool operator!=(const Investor& o1, const Investor& o2);
};


bool operator<(const Investor& o1, const Investor& o2) {
	return strcmp(o1.F, o2.F) < 0;
}
bool operator>(const Investor& o1, const Investor& o2) {
	return strcmp(o1.F, o2.F) > 0;
}
bool operator==(const Investor& o1, const Investor& o2) {
	return strcmp(o1.F, o2.F) == 0;
}
bool operator!=(const Investor& o1, const Investor& o2) {
	return strcmp(o1.F, o2.F) != 0;
}

void write_investor_poss(list<Investor> lst)
{

	list<Investor>::iterator p;
	ofstream file("Investors_poss.txt", ios_base::out & ios_base::trunc);
	for (int i = 0; i < 55; i++)
		file << "-";
	file << endl;
	file << "|             Фамилия|       Имя|Капитал|Проекты| Стаж|" << endl;
	for (int i = 0; i < 55; i++)
		file << "-";
	file << endl;
	for (p = lst.begin(); p != lst.end(); p++) {
		file << "|" << setw(20) << p->Get_F() << "|" << setw(10) << p->Get_I() << "|" << setw(7) << p->Get_capital() << "|" << setw(7) << p->Get_projects() << "|" << setw(5) << p->Get_practice() << "|" << endl;
	}
	for (int i = 0; i < 55; i++)
		file << "-";
	file << endl;
	file << "*;";
	file.close();
}

//добавление инвестора в файл
void write_investor_infile(list<Investor> lst)
{
	list<Investor>::iterator p;
	ofstream file("Investors.txt", ios_base::out & ios_base::trunc);
	for (p = lst.begin(); p != lst.end(); p++) {
		file << p->Get_F() << ";" << p->Get_I() << ";" << p->Get_capital() << ";" << p->Get_projects() << ";" << p->Get_practice() << ";";
	}
	file << "*;";
	file.close();
}

void write_investor_infile_thebest(list<Investor> lst)
{
	list<Investor>::iterator p;
	ofstream file("Investors_thebest.txt", ios_base::out & ios_base::trunc);
	for (p = lst.begin(); p != lst.end(); p++) {
		file << p->Get_F() << ";" << p->Get_I() << ";" << p->Get_capital() << ";" << p->Get_projects() << ";" << p->Get_practice() << ";";
	}
	file << "*;";
	file.close();
}

void read_investors_fromfile_thebest(list<Investor>& investors)
{

	Investor investor;
	char str[100];
	float ff;
	int k;
	ifstream f("Investors_thebest.txt", ios_base::in);
	if (!f.is_open() || f.peek() == EOF) {
		//cout << "Файл не удалось открыть или он пуст(инвесторы)." << endl;
		return;
	}


	while (1) {
		f.getline(str, 100, ';');
		if (strcmp(str, "*") == 0) {
			break;
		}
		investor.Set_F(str);
		f.getline(str, 100, ';');
		investor.Set_I(str);
		f.getline(str, 100, ';');
		ff = stof(str);
		investor.Set_capital(ff);
		f.getline(str, 100, ';');
		k = atoi(str);
		investor.Set_projects(k);
		f.getline(str, 100, ';');
		k = 0;
		k = atoi(str);
		investor.Set_practice(k);
		investors.push_back(investor);
	}
	f.close();
}

//добавление инвестора в файла - логин и пароль
void write_in_file_password(list<Investor> lst)
{
	list<Investor>::iterator p;
	ofstream file("Investors_log.txt", ios_base::out & ios_base::trunc);

	for (p = lst.begin(); p != lst.end(); p++) {
		for (int i = 0; i < strlen(p->login); i++) {
			p->login[i] = (char)((int)p->login[i] + 3);
		}
		for (int i = 0; i < strlen(p->password); i++) {
			p->password[i] = (char)((int)p->password[i] + 3);
		}
		file << p->Get_log() << ";" << p->Get_pass() << ";";
	}
	file << "*;";
	file.close();
}

//чтение инвестора из файла, добавление в список
void read_investors_fromfile(list<Investor>& investors)
{

	Investor investor;
	char str[100];
	float ff;
	int k;
	ifstream f("Investors.txt", ios_base::in);
	if (!f.is_open() || f.peek() == EOF) {
		//cout << "Файл не удалось открыть или он пуст(инвесторы)." << endl;
		return;
	}

	ifstream file("Investors_log.txt", ios_base::in);
	if (!file.is_open() || file.peek() == EOF) {
		//cout << "Файл не удалось открыть или он пуст (инвесторы)." << endl;
		return;
	}
	while (1) {
		f.getline(str, 100, ';');
		if (strcmp(str, "*") == 0) {
			break;
		}
		investor.Set_F(str);
		f.getline(str, 100, ';');
		investor.Set_I(str);
		f.getline(str, 100, ';');
		ff = stof(str);
		investor.Set_capital(ff);
		f.getline(str, 100, ';');
		k = atoi(str);
		investor.Set_projects(k);
		f.getline(str, 100, ';');
		k = 0;
		k = atoi(str);
		investor.Set_practice(k);
		file.getline(str, 100, ';');
		if (strcmp(str, "*") == 0) {
			break;
		}
		for (int i = 0; i < strlen(str); i++) {
			str[i] = (char)((int)str[i] - 3);
		}
		investor.Set_login(str);
		file.getline(str, 100, ';');
		for (int i = 0; i < strlen(str); i++) {
			str[i] = (char)((int)str[i] - 3);
		}
		investor.Set_pass(str);
		investors.push_back(investor);
	}
	f.close();
	file.close();
}


void read_matrix(int size, float**& matrix, string name)
{
	//float** matrix = NULL;
	matrix = new float* [size];
	for (int j = 0; j < size; j++) {
		matrix[j] = new float[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 0;
		}
	}
	float a = 0;
	int b = 0;
	char str[100];
	ifstream f(name, ios_base::in);
	if (!f.is_open() || f.peek() == EOF) {
		cout << "матрица." << endl;
		return;
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			f.getline(str, 100, ';');
			a = stof(str);
			matrix[i][j] = a;
		}
	}
	f.close();
}

void read_matrix2(int size, float*& matrix, string name)
{
	matrix = new float[size];
	for (int i = 0; i < size; i++) {
		matrix[i] = 0;
	};

	float a = 0;
	int b = 0;
	char str[100];
	ifstream f(name, ios_base::in);
	if (!f.is_open() || f.peek() == EOF) {
		cout << "матрица - веса." << endl;
		return;
	}
	for (int i = 0; i < size; i++) {

		f.getline(str, 100, ';');
		a = stof(str);
		matrix[i] = a;
	}
	cout << endl;
	cout << "Веса каждого инвестора:" << endl;
	for (int i = 0; i < size * 5; i++) {
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < size; i++) {

		cout << setprecision(2) << setw(4) << matrix[i] << "|";
	}
	cout << endl;
	for (int i = 0; i < size * 5; i++) {
		cout << "-";
	}
	f.close();
}

void read_matrix_table(int size, float*& matrix, string name)
{
	matrix = new float[size];
	for (int i = 0; i < size; i++) {
		matrix[i] = 0;
	};

	float a = 0;
	int b = 0;
	char str[100];
	ifstream f(name, ios_base::in);
	if (!f.is_open() || f.peek() == EOF) {
		cout << "матрица - веса." << endl;
		return;
	}
	for (int i = 0; i < size; i++) {

		f.getline(str, 100, ';');
		a = stof(str);
		matrix[i] = a;
	}

	f.close();


	ofstream f2("Wesa.txt", ios_base::out & ios_base::trunc);
	if (!f2.is_open()) {
		cout << "матрица - веса." << endl;
		return;
	}
	for (int i = 0; i < size * 5; i++) {
		f2 << "-";
	}
	f2 << endl;
	for (int i = 0; i < size; i++) {

		f2 << setprecision(2) << setw(4) << matrix[i] << "|";
	}
	f2 << endl;
	for (int i = 0; i < size * 5; i++) {
		f2 << "-";
	}
	f2 << endl;
	f2 << "*;";
	f2.close();
}


//заявки инвесторов

void write_investor_app_infile(list<Investor> lst)
{
	list<Investor>::iterator p;
	ofstream file("Investors_app.txt", ios_base::out & ios_base::trunc);
	for (p = lst.begin(); p != lst.end(); p++) {
		file << p->Get_F() << ";" << p->Get_I() << ";" << p->Get_capital() << ";" << p->Get_projects() << ";" << p->Get_practice() << ";";
	}
	file << "*;";
	file.close();
}
//заявки на рассторжение
void write_investor_del_infile(list<Investor> lst)
{
	list<Investor>::iterator p;
	ofstream file("Investors_del.txt", ios_base::out & ios_base::trunc);
	for (p = lst.begin(); p != lst.end(); p++) {
		file << p->Get_F() << ";" << p->Get_I() << ";" << p->Get_capital() << ";" << p->Get_projects() << ";" << p->Get_practice() << ";";
	}
	file << "*;";
	file.close();
}

void read_investors_fromfile_del(list<Investor>& investors)
{

	Investor investor;
	char str[100];
	float ff;
	int k;
	ifstream f("Investors_del.txt", ios_base::in);
	if (!f.is_open() || f.peek() == EOF) {
		//cout << "Файл не удалось открыть или он пуст(инвесторы заявки)." << endl;
		return;
	}


	while (1) {
		f.getline(str, 100, ';');
		if (strcmp(str, "*") == 0) {
			break;
		}
		investor.Set_F(str);
		f.getline(str, 100, ';');
		investor.Set_I(str);
		f.getline(str, 100, ';');
		ff = stof(str);
		investor.Set_capital(ff);
		f.getline(str, 100, ';');
		k = atoi(str);
		investor.Set_projects(k);
		f.getline(str, 100, ';');
		k = 0;
		k = atoi(str);
		investor.Set_practice(k);


		investors.push_back(investor);
	}
	f.close();

}

void read_investors_fromfile_app(list<Investor>& investors)
{

	Investor investor;
	char str[100];
	float ff;
	int k;
	ifstream f("Investors_app.txt", ios_base::in);
	if (!f.is_open() || f.peek() == EOF) {
		//cout << "Файл не удалось открыть или он пуст(инвесторы заявки)." << endl;
		return;
	}


	while (1) {
		f.getline(str, 100, ';');
		if (strcmp(str, "*") == 0) {
			break;
		}
		investor.Set_F(str);
		f.getline(str, 100, ';');
		investor.Set_I(str);
		f.getline(str, 100, ';');
		ff = stof(str);
		investor.Set_capital(ff);
		f.getline(str, 100, ';');
		k = atoi(str);
		investor.Set_projects(k);
		f.getline(str, 100, ';');
		k = 0;
		k = atoi(str);
		investor.Set_practice(k);


		investors.push_back(investor);
	}
	f.close();

}

void read_investors_fromfile_pos(list<Investor>& investors)
{

	Investor investor;
	char str[100];
	float ff;
	int k;
	ifstream f("Investors_pos.txt", ios_base::in);
	if (!f.is_open() || f.peek() == EOF) {
		//cout << "Файл не удалось открыть или он пуст(инвесторы - потенциальные)." << endl;
		return;
	}


	while (1) {
		f.getline(str, 100, ';');
		if (strcmp(str, "*") == 0) {
			break;
		}
		investor.Set_F(str);
		f.getline(str, 100, ';');
		investor.Set_I(str);
		f.getline(str, 100, ';');
		ff = stof(str);
		investor.Set_capital(ff);
		f.getline(str, 100, ';');
		k = atoi(str);
		investor.Set_projects(k);
		f.getline(str, 100, ';');
		k = 0;
		k = atoi(str);
		investor.Set_practice(k);


		investors.push_back(investor);
	}
	f.close();

}


void write_investor_done_infile(list<Investor> lst)
{
	list<Investor>::iterator p;
	ofstream file("Investors_done.txt", ios_base::out & ios_base::trunc);
	for (p = lst.begin(); p != lst.end(); p++) {
		file << p->Get_F() << ";" << p->Get_I() << ";" << p->Get_capital() << ";" << p->Get_projects() << ";" << p->Get_practice() << ";";
	}
	file << "*;";
	file.close();
}

void write_investor_done_pos(list<Investor> lst)
{
	list<Investor>::iterator p;
	ofstream file("Investors_pos.txt", ios_base::out & ios_base::trunc);
	for (p = lst.begin(); p != lst.end(); p++) {
		file << p->Get_F() << ";" << p->Get_I() << ";" << p->Get_capital() << ";" << p->Get_projects() << ";" << p->Get_practice() << ";";
	}
	file << "*;";
	file.close();
}

void read_investors_fromfile_done(list<Investor>& investors)
{

	Investor investor;
	char str[100];
	float ff;
	int k;
	ifstream f("Investors_done.txt", ios_base::in);
	if (!f.is_open() || f.peek() == EOF) {
		//cout << "Файл не удалось открыть или он пуст(инвесторы заявки)." << endl;
		return;
	}


	while (1) {
		f.getline(str, 100, ';');
		if (strcmp(str, "*") == 0) {
			break;
		}
		investor.Set_F(str);
		f.getline(str, 100, ';');
		investor.Set_I(str);
		f.getline(str, 100, ';');
		ff = stof(str);
		investor.Set_capital(ff);
		f.getline(str, 100, ';');
		k = atoi(str);
		investor.Set_projects(k);
		f.getline(str, 100, ';');
		k = 0;
		k = atoi(str);
		investor.Set_practice(k);


		investors.push_back(investor);
	}
	f.close();

}


class Company : public Admin {
	char name[50];
	char product[20];
	char director[20];
	float money;
public:
	Company() {
		name[0] = '\0'; product[0] = '\0', money = 0; director[0] = '\0';
	} //конструктор без параметров
	~Company() {};      //пустой деструктор
	char* Get_name()
	{
		return name;
	}
	char* Get_product()
	{
		return product;
	}
	char* Get_director()
	{
		return director;
	}
	void Set_name(const char* lastname)
	{
		strcpy_s(name, lastname);
	}

	void Set_product(const char* name)
	{
		strcpy_s(product, name);
	}

	float Get_money() {
		return money;
	}

	void Set_money(float pr) {
		this->money = pr;
	}

	void Set_director(const char* name)
	{
		strcpy_s(director, name);
	}

	void write_company_infile(list<Company> lst)
	{
		list<Company>::iterator p;
		ofstream file("Company.txt", ios_base::out & ios_base::trunc);
		for (p = lst.begin(); p != lst.end(); p++) {
			file << p->Get_name() << ";" << p->Get_product() << ";" << p->Get_director() << ";" << p->Get_money() << ";";
		}
		file << "*;";
		file.close();
	}

};


void write_company_table(list<Company> lst)

{
	list<Company>::iterator p;
	ofstream file("Company_table1.txt", ios_base::out & ios_base::trunc);
	for (int i = 0; i < 73; i++)
		file << "-";
	file << endl;
	file << "|   Название компании|             Продукт|             Фамилия|Капитал|" << endl;
	for (int i = 0; i < 73; i++)
		file << "-";
	file << endl;
	for (p = lst.begin(); p != lst.end(); p++) {
		file << "|" << setw(20) << p->Get_name() << "|" << setw(20) << p->Get_product() << "|" << setw(20) << p->Get_director() << "|" << setw(7) << p->Get_money() << "|" << endl;
	}
	for (int i = 0; i < 73; i++)
		file << "-";
	file << endl;
	file << "*;";
	file.close();
}


void read_company_from_file(list<Company>& companyy)
{
	Company company;
	char str[100];
	float ff;
	int k;
	ifstream f("Company.txt", ios_base::in);
	if (!f.is_open() || f.peek() == EOF) {
		//cout << "Файл не удалось открыть или он пуст(компания)." << endl;
		return;
	}
	while (1) {
		f.getline(str, 100, ';');
		if (strcmp(str, "*") == 0) {
			break;
		}
		company.Set_name(str);

		f.getline(str, 100, ';');
		company.Set_product(str);

		f.getline(str, 100, ';');
		company.Set_director(str);

		f.getline(str, 100, ';');
		ff = stof(str);
		company.Set_money(ff);
		companyy.push_back(company);
	}
	f.close();
}

void write_contract(list<Company> lst, string name)

{
	list<Company>::iterator p;
	ofstream file("Company_table.txt", ios_base::out & ios_base::trunc);
	time_t t = time(NULL);
	tm tm = *localtime(&t);

	char F[20];
	char namee[20];
	char pr[20];
	float mo;
	for (int i = 0; i < 100; i++)
		file << "_";
	file << endl;
	file << endl;

	file << setw(18) << "ДОГОВОР НА ФИНАНСИРОВАНИЕ" << endl;
	file << endl;
	file << endl;
	file << endl;
	file.setf(ios::right);
	file.width(40);
	file << setfill('0') << setw(2) << tm.tm_mday << '.' << setw(2) << tm.tm_mon + 1 << '.' << setw(4) << tm.tm_year + 1900 << '\n';
	for (p = lst.begin(); p != lst.end(); p++) {
		strcpy_s(namee, p->Get_name());
		strcpy_s(pr, p->Get_product());
		strcpy_s(F, p->Get_director());
		mo = p->Get_money();
	}
	file << endl;
	file << endl;
	file << " Текстильная компания «" << namee << "», \n именуемое в дальнейшем «Финансовый агент», в лице \n " << F << "\n на основании Гомельского положения №9\n с одной стороны, и\n инвестора " << name << "\n именуемое в дальнейшем «Клиент» («Кредитор»)\n действующего на основании Гомельского договора №2\n с другой стороны, заключили настоящий договор об инвестировании компании, выпускающей " << pr << "\n суммы не менее, чем " << mo << " белорусских рублей.";
	file << "\n\nПри штатных обстоятельствах договор длится до 2025 года" << endl;
	for (int i = 0; i < 100; i++)
		file << "_";
	file << endl;
	file << "*;";
	file.close();
}

class Contract :public Company, public Investor {

public:
	char* data;
	Contract() {
		data = NULL;
	}
	~Contract() {};






};


class Exception {

};


class Method
{
public:
	float** f;
	float** Q;
	float* W;
	int result;

	Method() {
		f = NULL; Q = NULL; W = NULL; result = 0;
	}

	void Set_result(int res) {
		this->result = res;
	}

	int Get_result() {
		return result;
	}


	int methodd(float**& matrix1, float**& matrix2, float**& matrix3, int size, int size2);

};

template < typename T >
int find_max(T& max, T*& matrix, int size)
{
	int flag = 0;
	max = matrix[0];
	for (int i = 0; i < size; i++)
	{
		if (matrix[i] > max) {
			max = matrix[i];
			flag = i;
		}
	}
	flag++;
	return flag;
}

int Method::methodd(float**& matrix1, float**& matrix2, float**& matrix3, int size, int size2) {

	f = new float* [size2];
	for (int i = 0; i < size2; i++)
		f[i] = new float[size];

	for (int i = 0; i < size2; i++) {
		for (int j = 0; j < size; j++) {
			f[i][j] = 0;
		}
	}

	for (int i = 0; i < size2; i++)
	{
		for (int j = 0; j < size; j++)
		{
			f[0][i] += matrix1[i][j];
			f[1][i] += matrix2[i][j];
			f[2][i] += matrix3[i][j];

		}
	}
	cout << endl;
	cout << " Таблица f: " << endl;
	cout << endl;
	for (int i = 0; i < size2; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << setprecision(2) << setw(4) << f[i][j] << "| ";

		}
		cout << endl;
	}



	Q = new float* [size2];
	for (int i = 0; i < size2; i++)
		Q[i] = new float[size];

	for (int i = 0; i < size2; i++) {
		for (int j = 0; j < size; j++) {
			Q[i][j] = 0;
		}
	}


	for (int i = 0; i < size2; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Q[0][j] = f[0][j] / 30;
			Q[1][j] = f[1][j] / 30;
			Q[2][j] = f[2][j] / 30;
		}
	}
	cout << endl;
	cout << " Таблица Q:" << endl;
	cout << endl;
	for (int i = 0; i < size2; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << setprecision(2) << setw(4) << Q[i][j] << "| ";

		}
		cout << endl;
	}


	W = new float[size];
	for (int i = 0; i < size; i++) {
		W[i] = 0;
	};

	for (int j = 0; j < size; j++)
	{
		W[j] = Q[0][j] + Q[1][j] + Q[2][j];
	}

	ofstream fily("Веса.txt", ios::trunc | ios::out);

	for (int i = 0; i < size; i++)
	{
		fily << W[i] << ";";
	}
	fily << "*";
	fily.close();

	int flag = 0;
	float max;
	flag = find_max(max, W, size);

	/*float max = W[0];

	for (int i = 0; i < size; i++)
	{
		if (W[i] > max) {
			max = W[i];
			flag = i;
		}
	}
	flag++;*/

	ofstream fil("result.txt", ios::trunc | ios::out);
	fil << flag;
	fil << "*";
	fil.close();


	return flag;
}



class Matrix : public Method {

};



void mailWorking(void* newS) {
	int c, c1 = 0, c2 = 0, c11 = 0, c3 = 0; int e = 0;
	int flag = 0;
	char p[500], com[200], k[500], m[500], q[500], buf[500];
	com[0] = '\0'; p[0] = '\0'; k[0] = '\0'; m[0] = '\0'; q[0] = '\0'; buf[0] = '\0';


	cout << "Сервер работает.\n";
	Investor invest;
	Admin adm;
	Expert expe;
	Company comp;
	Contract cont;
	Method method;

	list<Investor> investor;
	list<Investor> investor_best;
	list<Investor> investor_app;
	list<Investor> investor_done;
	list<Investor> investor_del;
	list<Admin> admin;
	list<Expert> expert;
	list<Company> company;
	list<Investor> investor_pos;

	list<Investor>::iterator it;
	list<Investor>::iterator it_best;
	list<Investor>::iterator it_app;
	list<Investor>::iterator it_done;
	list<Investor>::iterator it_del;
	list<Investor>::iterator it_pos;
	list<Admin>::iterator it_2;
	list<Expert>::iterator it3;
	list<Company>::iterator it4;

	char* login_admin;
	char password_admin[20];

	read_investors_fromfile(investor);
	read_investors_fromfile_app(investor_app);
	read_admin_fromfile(admin);
	read_experts_fromfile(expert);
	read_company_from_file(company);
	read_investors_fromfile_done(investor_done);
	read_investors_fromfile_pos(investor_pos);
	read_investors_fromfile_thebest(investor_best);
	read_investors_fromfile_del(investor_del);

	cout << "размер" << expert.size();

	/*for (it = investor.begin(); it != investor.end(); it++) {
		cout << (*it).Get_F() << (*it).Get_I() << (*it).Get_capital() << (*it).Get_projects() << (*it).Get_practice()<< "   " << (*it).Get_log()<<"    " << (*it).Get_pass() << "    "<< endl;
	}

	for (it_2 = admin.begin(); it_2 != admin.end(); it_2++) {
		cout << (*it_2).Get_log() << (*it_2).Get_pass() << endl;
	}

	for (it3 = expert.begin(); it3 != expert.end(); it3++) {
		cout << (*it3).Get_F() << (*it3).Get_I() << (*it3).Get_exp() << (*it3).Get_position()<<(*it3).Get_email() <<(*it3).Get_log() << (*it3).Get_pass() << endl;
	}*/
	//strcpy_s(adm.Get_log(), login_admin);
	//strcpy_s(adm.Get_pass(), password_admin);

	cout << endl;
	while (1) {
		strcpy_s(p, "Добро пожаловать!\n");
		send((SOCKET)newS, p, sizeof(p), 0);
		strcpy_s(k, "Выберите действие:\n 1 - Аккаунт администратора\n 2 - Аккаунт инвестора\n 3 - Аккаунт эксперта\n 4 - Выход.\n ");
		send((SOCKET)newS, k, sizeof(k), 0);
		p[0] = '\0'; k[0] = '\0';
		recv((SOCKET)newS, m, sizeof(m), 0);
		c = atoi(m);
		switch (c) {
		case 0: {
			//strcpy_s(p, "1");
			//send((SOCKET)newS, p, sizeof(p), 0);

			if (admin.size() == 0) {
				//cout << "Регистрация." << endl;
				m[0] = '\0';
				strcpy_s(m, "0");
				send((SOCKET)newS, m, sizeof(m), 0);
				//получили логин
				recv((SOCKET)newS, m, sizeof(m), 0);
				//cout << m << endl;

				adm.Set_login(m);

				m[0] = '\0';
				//получили пароль
				recv((SOCKET)newS, m, sizeof(m), 0);
				//cout << m << endl;
				adm.Set_pass(m);

				admin.push_back(adm);

				//cout << adm.Get_log() << adm.Get_pass() << endl;
				write_in_file_password_admin(admin);

			}

			else {
				//cout << "Вход." << endl;
				m[0] = '\0';
				strcpy_s(m, "1");
				send((SOCKET)newS, m, sizeof(m), 0);
				int try_1 = 0;
				char ex1[30];
				char ex21[5];
				int flag = 0;
				e = 1;
				int iteratorr = 0;

				while (e == 1) {
					flag = 0;
					recv((SOCKET)newS, m, sizeof(m), 0);
					//cout << m << endl;
					e = 1;
					strcpy_s(ex1, "Такого пользователя нет!");
					strcpy_s(ex21, "0");

					if (admin.size() != 0) {
						for (it_2 = admin.begin(); it_2 != admin.end(); it_2++) {
							if (strcmp(m, it_2->Get_log()) == 0) {
								send((SOCKET)newS, ex21, sizeof(ex21), 0);
								flag = 1;
								e = 2;
								//cout << "Логин существует!" << endl;	
							}
						}

						if (flag == 0) {
							send((SOCKET)newS, ex1, sizeof(ex1), 0);

						}
					}
				}

				//cout << "Это итth " << iteratorr << endl;
				e = 0;
				try_1 = 0;


				while (e == 0) {
					flag = 0;
					//cout << "33333" << m << endl;
					recv((SOCKET)newS, m, sizeof(m), 0);
					e = 0;
					strcpy_s(ex1, "Такого пользователя нет!");
					strcpy_s(ex21, "0");
					int it1 = 0;

					if (admin.size() != 0) {

						for (it_2 = admin.begin(); it_2 != admin.end(); it_2++) {
							cout << endl;
							//cout << it_2->Get_pass() << endl;
							if (strcmp(m, it_2->Get_pass()) == 0) {
								send((SOCKET)newS, ex21, sizeof(ex21), 0);
								flag = 1;
								e++;
								//cout << "Пароль совпадает!" << endl;
							}
						}

					}
					if (flag == 0) {
						send((SOCKET)newS, ex1, sizeof(ex1), 0);

					}
				}


			}
			while (c1 != 5) {
				strcpy_s(k, "Меню администратора:\n 1 - Раздел работы с экспертами \n 2 - Раздел работы с инвесторами \n 3 - Изменить пароль и/или логин;\n 4 - Информация о компании; \n 5 - Главное меню.\n ");
				send((SOCKET)newS, k, sizeof(k), 0);
				recv((SOCKET)newS, m, sizeof(m), 0);

				c1 = atoi(m);
				switch (c1) {
				case 1: {
					strcpy_s(p, "1");
					send((SOCKET)newS, p, sizeof(p), 0);
					while (c2 != 5) {
						strcpy_s(p, "Работа с экспертами:\n1 - Просмотр экспертов \n2 - Добавить эксперта \n3 - Удалить эксперта \n4 - Просмотреть оценки экспертов\n5 - Выход.\n");


						send((SOCKET)newS, p, sizeof(p), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);
						c2 = atoi(m);
						ifstream file5("Experts_sort.txt");
						switch (c2) {
						case 1: {
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							if (expert.size() == 0) {
								p[0] = '\0';
								strcpy_s(p, "0");
								send((SOCKET)newS, p, sizeof(p), 0);
							}

							else {
								p[0] = '\0';
								strcpy_s(p, "1");

								expe.write_expert_sort(expert);
								while (!file5.eof()) {
									k[0] = '\0';
									file5.getline(k, 256, '\n');
									m[0] = '\0';
									strcpy_s(m, "*");
									if (file5.eof()) {
										send((SOCKET)newS, m, sizeof(m), 0);
									}

									else {
										send((SOCKET)newS, k, sizeof(k), 0);
										//cout << k << endl;
									}
								}
								file5.close();
							}

							m[0] = '\0';
							k[0] = '\0';
							break;
						}
						case 2: {
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);

							p[0] = '\0';
							strcpy_s(p, "0");
							if (expert.size() < 3) {
								send((SOCKET)newS, p, sizeof(p), 0);

								//получение фамилии
								recv((SOCKET)newS, m, sizeof(m), 0);
								//cout << m << endl;
								expe.Set_F(m);

								//получение имени
								recv((SOCKET)newS, m, sizeof(m), 0);
								//cout << m << endl;

								expe.Set_I(m);

								int temp = 0;

								//получение стажа работы
								recv((SOCKET)newS, m, sizeof(m), 0);
								//cout << m << endl;
								temp = atoi(m);
								expe.Set_exp(temp);


								//получение должности
								recv((SOCKET)newS, m, sizeof(m), 0);
								//cout << m << endl;
								expe.Set_position(m);

								//получение почты
								recv((SOCKET)newS, m, sizeof(m), 0);
								//cout << m << endl;
								expe.Set_email(m);


								char ex[30];
								char ex2[5];
								int flag = 0;
								e = 0;
								while (e == 0) {
									flag = 0;
									recv((SOCKET)newS, m, sizeof(m), 0);
									//cout << m << endl;
									e = 0;
									strcpy_s(ex, "Такой логин уже существует!");
									strcpy_s(ex2, "0");
									if (expert.size() != 0) {
										for (it3 = expert.begin(); it3 != expert.end(); it3++) {
											if (strcmp(m, it3->Get_log()) == 0) {
												send((SOCKET)newS, ex, sizeof(ex), 0);
												flag = 1;
												//cout << "Логин существует!" << endl;
											}
										}
									}
									if (flag == 0) {
										send((SOCKET)newS, ex2, sizeof(ex2), 0);
										e++;
									}
								}
								expe.Set_login(m);
								//cout << expe.Get_log() << endl;
								//получили пароль
								recv((SOCKET)newS, m, sizeof(m), 0);
								//cout << m << endl;
								expe.Set_pass(m);


								expert.push_back(expe);
								write_expert_infile(expert);
								write_in_file_password_experts(expert);

								/*for (it3 =expert.begin(); it3 != expert.end(); it3++) {
									cout << (*it3).Get_F() << (*it3).Get_I() << (*it3).Get_exp() << (*it3).Get_position() << (*it3).Get_email() << (*it3).Get_log() << (*it3).Get_pass() << endl;
								}*/

							}

							else {
								p[0] = '\0';
								strcpy_s(p, "1");
								send((SOCKET)newS, p, sizeof(p), 0);
							}

							break;
						}
						case 3: {
							ifstream file6("Experts_search.txt");
							ifstream file7("Experts_sort.txt");
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);

							if (expert.size() == 0) {
								p[0] = '\0';
								strcpy_s(p, "0");
								send((SOCKET)newS, p, sizeof(p), 0);
							}

							else {
								p[0] = '\0';
								strcpy_s(p, "1");

								expe.write_expert_sort(expert);
								while (!file7.eof()) {
									k[0] = '\0';
									file7.getline(k, 256, '\n');
									m[0] = '\0';
									strcpy_s(m, "*");
									if (file7.eof()) {
										send((SOCKET)newS, m, sizeof(m), 0);
									}

									else {
										send((SOCKET)newS, k, sizeof(k), 0);
										//cout << k << endl;
									}
								}

								file7.close();
								m[0] = '\0';
								k[0] = '\0';



								//получение фамилии
								recv((SOCKET)newS, buf, sizeof(buf), 0);
								//cout << buf << endl;
								int temp4 = 0;

								temp4 = expe.write_expert_search(expert, buf);

								if (temp4 == 0) {
									m[0] = '\0';
									strcpy_s(m, "1");
									send((SOCKET)newS, m, sizeof(m), 0);
								}
								else {
									while (!file6.eof()) {
										k[0] = '\0';
										file6.getline(k, 256, '\n');
										m[0] = '\0';
										strcpy_s(m, "*");
										if (file6.eof()) {
											send((SOCKET)newS, m, sizeof(m), 0);
										}

										else {
											send((SOCKET)newS, k, sizeof(k), 0);
											//cout << k << endl;
										}
									}
									file6.close();
									m[0] = '\0';
									k[0] = '\0';
									for (it3 = expert.begin(); it3 != expert.end(); it3++) {

										cout << it3->Get_F() << endl;


									}
									for (it3 = expert.begin(); it3 != expert.end(); it3++) {

										if (strcmp(buf, it3->Get_F()) == 0) {
											expert.erase(it3);
											break;
										}
									}
									write_expert_infile(expert);
									write_in_file_password_experts(expert);
								}


							}
							break;
						}
						case 4: {
							strcpy_s(p, "4");
							send((SOCKET)newS, p, sizeof(p), 0);

							ifstream ff("Investors_best2.txt", ios_base::in);
							if (!ff.is_open() || ff.peek() == EOF) {
								//cout << "С файлом проблемы" << endl;
								//return;
							}

							if (investor_best.size() == 0) {
								p[0] = '\0';
								strcpy_s(p, "0");
								send((SOCKET)newS, p, sizeof(p), 0);
							}
							else
							{
								strcpy_s(p, "1");
								send((SOCKET)newS, p, sizeof(p), 0);

								ifstream ff7("Wesa.txt", ios_base::in);
								if (!ff7.is_open() || ff7.peek() == EOF) {
									//cout << "С файлом проблемы" << endl;
									//return;
								}

								while (!ff7.eof()) {
									k[0] = '\0';
									ff7.getline(k, 256, '\n');
									m[0] = '\0';
									strcpy_s(m, "*");

									if (ff7.eof()) {
										send((SOCKET)newS, m, sizeof(m), 0);
									}
									else {
										send((SOCKET)newS, k, sizeof(k), 0);
									}
								}

								while (!ff.eof()) {
									k[0] = '\0';
									ff.getline(k, 256, '\n');
									m[0] = '\0';
									strcpy_s(m, "*");

									if (ff.eof()) {
										send((SOCKET)newS, m, sizeof(m), 0);
									}
									else {
										send((SOCKET)newS, k, sizeof(k), 0);
									}
								}
							}
							break;

						}
						case 5: {
							strcpy_s(p, "5");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}

						}
					}
					c2 = 0;
					break;
				}
				case 2: {
					strcpy_s(p, "2");
					send((SOCKET)newS, p, sizeof(p), 0);
					while (c2 != 5) {
						strcpy_s(p, "Работа с инвесторами:\n 1 - Просмотреть данные об инвесторах \n 2 - Удалить инвестора \n 3 - Заключить договор \n 4 - Расторгнуть договор \n 5 - Выход.");
						send((SOCKET)newS, p, sizeof(p), 0);//отправили меню
						recv((SOCKET)newS, m, sizeof(m), 0);
						c2 = atoi(m);
						switch (c2) {
						case 1: {
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							//просмотр информации

							char menu[500];
							menu[0] = '\n';

							while (c3 != 4) {
								m[0] = '\0';
								strcpy_s(menu, "Просмотр информации:\n1 - Сортировка \n2 - Фильтрация \n3 - Поиск \n4 - Выход.\n");
								send((SOCKET)newS, menu, sizeof(menu), 0);
								recv((SOCKET)newS, m, sizeof(m), 0);
								c3 = atoi(m);
								ifstream file("Investors_sort.txt");
								ifstream file2("Investors_filtr.txt");
								ifstream file3("Investors_search.txt");
								int temp = 0;
								int tem2 = 0;
								int temp3 = 0;
								int temp4 = 0;
								switch (c3) {
								case 1: {
									p[0] = '\0';
									strcpy_s(p, "1");
									send((SOCKET)newS, p, sizeof(p), 0);

									if (investor.size() == 0) {
										p[0] = '\0';
										strcpy_s(p, "0");
										send((SOCKET)newS, p, sizeof(p), 0);
									}

									else {
										p[0] = '\0';
										strcpy_s(p, "1");
										send((SOCKET)newS, p, sizeof(p), 0);
										invest.write_investor_sort(investor);

										while (!file.eof()) {
											k[0] = '\0';
											file.getline(k, 256, '\n');
											m[0] = '\0';
											strcpy_s(m, "*");
											if (file.eof()) {
												send((SOCKET)newS, m, sizeof(m), 0);
											}

											else {
												send((SOCKET)newS, k, sizeof(k), 0);
												//cout << k << endl;
											}
										}

										file.close();

									}

									break;
									m[0] = '\0';
									k[0] = '\0';
								}


								case 2: {


									strcpy_s(p, "2");
									send((SOCKET)newS, p, sizeof(p), 0);

									if (investor.size() == 0) {
										p[0] = '\0';
										strcpy_s(p, "0");
										send((SOCKET)newS, p, sizeof(p), 0);
									}

									else {
										p[0] = '\0';
										strcpy_s(p, "1");
										send((SOCKET)newS, p, sizeof(p), 0);

										//получение минимального значения
										recv((SOCKET)newS, m, sizeof(m), 0);
										//cout << m << endl;
										temp = atoi(m);

										//получение максимального значения
										recv((SOCKET)newS, m, sizeof(m), 0);
										//cout << m << endl;
										tem2 = atoi(m);

										temp3 = invest.write_investor_filtration(investor, temp, tem2);

										if (temp3 == 0) {
											m[0] = '\0';
											strcpy_s(m, "1");
											send((SOCKET)newS, m, sizeof(m), 0);
										}
										else {
											while (!file2.eof()) {
												k[0] = '\0';
												file2.getline(k, 256, '\n');
												m[0] = '\0';
												strcpy_s(m, "*");
												if (file2.eof()) {
													send((SOCKET)newS, m, sizeof(m), 0);
												}

												else {
													send((SOCKET)newS, k, sizeof(k), 0);
													//cout << k << endl;
												}
											}

											file2.close();


										}

									}

									m[0] = '\0';
									k[0] = '\0';

									break;
								}

								case 3:
									strcpy_s(p, "3");
									send((SOCKET)newS, p, sizeof(p), 0);

									if (investor.size() == 0) {
										p[0] = '\0';
										strcpy_s(p, "0");

									}

									else {
										p[0] = '\0';
										strcpy_s(p, "1");
										send((SOCKET)newS, p, sizeof(p), 0);
										//получение фамилии
										recv((SOCKET)newS, m, sizeof(m), 0);
										cout << m << endl;


										temp4 = invest.write_investor_search(investor, m);

										if (temp4 == 0) {
											m[0] = '\0';
											strcpy_s(m, "1");
											send((SOCKET)newS, m, sizeof(m), 0);
										}
										else {
											while (!file3.eof()) {
												k[0] = '\0';
												file3.getline(k, 256, '\n');
												m[0] = '\0';
												strcpy_s(m, "*");
												if (file3.eof()) {
													send((SOCKET)newS, m, sizeof(m), 0);
												}

												else {
													send((SOCKET)newS, k, sizeof(k), 0);
													//cout << k << endl;
												}
											}
											file3.close();

										}
										m[0] = '\0';
										k[0] = '\0';
									}
									break;

								case 4:
									strcpy_s(p, "4");
									send((SOCKET)newS, p, sizeof(p), 0);
									break;
								}

							}
							c3 = 0;
							break;
						}
						case 2: {
							ifstream file9("Investors_sort.txt");
							ifstream file10("Investors_search.txt");
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);

							invest.write_investor_sort(investor);
							while (!file9.eof()) {
								k[0] = '\0';
								file9.getline(k, 256, '\n');
								m[0] = '\0';
								strcpy_s(m, "*");
								if (file9.eof()) {
									send((SOCKET)newS, m, sizeof(m), 0);
								}

								else {
									send((SOCKET)newS, k, sizeof(k), 0);
									//cout << k << endl;
								}
							}

							file9.close();
							m[0] = '\0';
							k[0] = '\0';

							//получение фамилии
							recv((SOCKET)newS, buf, sizeof(buf), 0);
							//cout << buf << endl;
							int temp4 = 0;

							temp4 = invest.write_investor_search(investor, buf);

							if (temp4 == 0) {
								m[0] = '\0';
								strcpy_s(m, "1");
								send((SOCKET)newS, m, sizeof(m), 0);
							}
							else {
								while (!file10.eof()) {
									k[0] = '\0';
									file10.getline(k, 256, '\n');
									m[0] = '\0';
									strcpy_s(m, "*");
									if (file10.eof()) {
										send((SOCKET)newS, m, sizeof(m), 0);
									}

									else {
										send((SOCKET)newS, k, sizeof(k), 0);
										//cout << k << endl;
									}
								}
								file10.close();
								m[0] = '\0';
								k[0] = '\0';
							}

							for (it = investor.begin(); it != investor.end(); it++) {

								if (strcmp(buf, it->Get_F()) == 0) {
									investor.erase(it);
									break;
								}
							}
							for (it_pos = investor_pos.begin(); it_pos != investor_pos.end(); it_pos++) {

								if (strcmp(buf, it_pos->Get_F()) == 0) {
									investor_pos.erase(it_pos);
									break;
								}
							}
							write_investor_infile(investor);
							write_in_file_password(investor);
							write_investor_done_pos(investor_pos);

							break;
						}
						case 3: {
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);
							//заключение договора с инвестором

							ifstream ff("Investors_best2.txt", ios_base::in);
							if (!ff.is_open() || ff.peek() == EOF) {
								//cout << "С файлом проблемы" << endl;
								//return;
							}
							if (investor_best.size() == 0) {
								p[0] = '\0';
								strcpy_s(p, "0");
								send((SOCKET)newS, p, sizeof(p), 0);
							}
							else
							{
								strcpy_s(p, "1");
								send((SOCKET)newS, p, sizeof(p), 0);
								while (!ff.eof()) {
									k[0] = '\0';
									ff.getline(k, 256, '\n');
									m[0] = '\0';
									strcpy_s(m, "*");

									if (ff.eof()) {
										send((SOCKET)newS, m, sizeof(m), 0);
									}
									else {
										send((SOCKET)newS, k, sizeof(k), 0);
									}
								}
							}

							ifstream file9("Investors_sort.txt");
							ifstream file10("Investors_search.txt");
							//strcpy_s(p, "2");
							//send((SOCKET)newS, p, sizeof(p), 0);

							invest.write_investor_sort(investor_pos);

							while (!file9.eof()) {
								k[0] = '\0';
								file9.getline(k, 256, '\n');
								m[0] = '\0';
								strcpy_s(m, "*");
								if (file9.eof()) {
									send((SOCKET)newS, m, sizeof(m), 0);
								}

								else {
									send((SOCKET)newS, k, sizeof(k), 0);
									//cout << k << endl;
								}
							}

							file9.close();
							m[0] = '\0';
							k[0] = '\0';

							//получение фамилии
							recv((SOCKET)newS, buf, sizeof(buf), 0);
							//cout << buf << endl;
							int temp4 = 0;

							temp4 = invest.write_investor_search(investor_pos, buf);

							if (temp4 == 0) {
								m[0] = '\0';
								strcpy_s(m, "1");
								send((SOCKET)newS, m, sizeof(m), 0);
							}
							else {
								while (!file10.eof()) {
									k[0] = '\0';
									file10.getline(k, 256, '\n');
									m[0] = '\0';
									strcpy_s(m, "*");
									if (file10.eof()) {
										send((SOCKET)newS, m, sizeof(m), 0);
									}

									else {
										send((SOCKET)newS, k, sizeof(k), 0);
										//cout << k << endl;
									}
								}
								file10.close();
								m[0] = '\0';
								k[0] = '\0';

								for (it_pos = investor_pos.begin(); it_pos != investor_pos.end(); it_pos++) {
									if (strcmp(it_pos->Get_F(), buf) == 0) {
										investor_app.push_back(*it_pos);
									}
								}
								write_investor_app_infile(investor_app);

							}
							break;
						}
						case 4: {
							//расторжение договора с инвестором
							ifstream file9("Investors_done2.txt");
							ifstream file10("Investors_search.txt");

							strcpy_s(p, "4");
							send((SOCKET)newS, p, sizeof(p), 0);
							invest.write_investor_sort2(investor_done);

							while (!file9.eof()) {
								k[0] = '\0';
								file9.getline(k, 256, '\n');
								m[0] = '\0';
								strcpy_s(m, "*");
								if (file9.eof()) {
									send((SOCKET)newS, m, sizeof(m), 0);
								}

								else {
									send((SOCKET)newS, k, sizeof(k), 0);
									//cout << k << endl;
								}
							}

							file9.close();
							m[0] = '\0';
							k[0] = '\0';

							//получение фамилии
							recv((SOCKET)newS, buf, sizeof(buf), 0);
							//cout << buf << endl;
							int temp4 = 0;

							temp4 = invest.write_investor_search(investor_done, buf);

							if (temp4 == 0) {
								m[0] = '\0';
								strcpy_s(m, "1");
								send((SOCKET)newS, m, sizeof(m), 0);
							}
							else {
								while (!file10.eof()) {
									k[0] = '\0';
									file10.getline(k, 256, '\n');
									m[0] = '\0';
									strcpy_s(m, "*");
									if (file10.eof()) {
										send((SOCKET)newS, m, sizeof(m), 0);
									}

									else {
										send((SOCKET)newS, k, sizeof(k), 0);
										//cout << k << endl;
									}
								}
								file10.close();
								m[0] = '\0';
								k[0] = '\0';
							}

							for (it_done = investor_done.begin(); it_done != investor_done.end(); it_done++) {
								if (strcmp(it_done->Get_F(), buf) == 0) {
									investor_del.push_back(*it_done);
									investor_done.erase(it_done);
									break;
								}
							}
							write_investor_app_infile(investor_app);
							write_investor_del_infile(investor_del);
							write_investor_done_infile(investor_done);

							break;
						}
						case 5: {
							strcpy_s(p, "5");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						}
					}
					c2 = 0;
					break;
				}
				case 3: {
					strcpy_s(p, "3");
					send((SOCKET)newS, p, sizeof(p), 0);

					m[0] = '\0';

					int try_1 = 0;
					char ex1[30];
					char ex21[5];
					int flag = 0;
					e = 1;
					int iteratorr = 0;

					while (e == 1) {
						flag = 0;
						recv((SOCKET)newS, m, sizeof(m), 0);
						cout << m << endl;
						e = 1;
						strcpy_s(ex1, "Такого пользователя нет!");
						strcpy_s(ex21, "0");

						if (admin.size() != 0) {
							for (it_2 = admin.begin(); it_2 != admin.end(); it_2++) {
								if (strcmp(m, it_2->Get_log()) == 0) {
									send((SOCKET)newS, ex21, sizeof(ex21), 0);
									flag = 1;
									e = 2;
									//cout << "Логин существует!" << endl;	
								}
							}

							if (flag == 0) {
								send((SOCKET)newS, ex1, sizeof(ex1), 0);

							}
						}
					}

					//cout << "Это итth " << iteratorr << endl;
					e = 0;
					try_1 = 0;


					while (e == 0) {
						flag = 0;
						//cout << "33333" << m << endl;
						recv((SOCKET)newS, m, sizeof(m), 0);
						e = 0;
						strcpy_s(ex1, "Такого пользователя нет!");
						strcpy_s(ex21, "0");
						int it1 = 0;

						if (admin.size() != 0) {

							for (it_2 = admin.begin(); it_2 != admin.end(); it_2++) {
								//cout << endl;
								//cout << it_2->Get_pass() << endl;
								if (strcmp(m, it_2->Get_pass()) == 0) {
									send((SOCKET)newS, ex21, sizeof(ex21), 0);
									flag = 1;
									e++;
									//cout << "Пароль совпадает!" << endl;
								}
							}

						}
						if (flag == 0) {
							send((SOCKET)newS, ex1, sizeof(ex1), 0);

						}

					}



					while (c2 != 3) {
						strcpy_s(p, "Меню изменения пароля и/или логина:\n 1 - Изменить логин \n 2 - Изменить пароль;\n 3 - Выход.\n");
						send((SOCKET)newS, p, sizeof(p), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);
						c2 = atoi(m);
						switch (c2) {
						case 1: {
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);

							m[0] = '\0';

							//получили логин
							recv((SOCKET)newS, m, sizeof(m), 0);
							//cout << m << endl;


							for (it_2 = admin.begin(); it_2 != admin.end(); it_2++) {

								it_2->Set_login(m);

							}


							write_in_file_password_admin(admin);
							break;
						}
						case 2: {
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);
							m[0] = '\0';
							//получили пароль
							recv((SOCKET)newS, m, sizeof(m), 0);
							//cout << m << endl;
							for (it_2 = admin.begin(); it_2 != admin.end(); it_2++) {

								it_2->Set_pass(m);

							}

							write_in_file_password_admin(admin);
							break;
						}
						case 3: {
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						}
					}
					c2 = 0;
					break;
				}
				case 4: {
					strcpy_s(p, "4");
					send((SOCKET)newS, p, sizeof(p), 0);
					while (c2 != 3) {
						strcpy_s(p, "Меню работы с информацией:\n 1 - Добавить информацию о компании \n 2 - Удалить информацию о компании;\n 3 - Выход.\n");
						send((SOCKET)newS, p, sizeof(p), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);
						c2 = atoi(m);
						switch (c2) {
						case 1: {
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);

							if (company.size() == 0) {
								p[0] = '\0';
								strcpy_s(p, "0");
								send((SOCKET)newS, p, sizeof(p), 0);

								//получение названия компании
								recv((SOCKET)newS, m, sizeof(m), 0);
								//cout << m << endl;
								comp.Set_name(m);

								//получение продукта
								recv((SOCKET)newS, m, sizeof(m), 0);
								//cout << m << endl;

								comp.Set_product(m);

								//получение руководителя
								recv((SOCKET)newS, m, sizeof(m), 0);
								//cout << m << endl;

								comp.Set_director(m);

								//получение капитала
								recv((SOCKET)newS, m, sizeof(m), 0);
								//cout << m << endl;

								float temp;
								temp = stof(m);
								comp.Set_money(temp);

								company.push_back(comp);
								comp.write_company_infile(company);

							}

							else {
								p[0] = '\0';
								strcpy_s(p, "1");
								send((SOCKET)newS, p, sizeof(p), 0);

							}
							break;
						}
						case 2: {
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);

							if (company.size() == 0) {
								p[0] = '\0';
								strcpy_s(p, "0");
								send((SOCKET)newS, p, sizeof(p), 0);
							}
							else {
								p[0] = '\0';
								strcpy_s(p, "1");
								send((SOCKET)newS, p, sizeof(p), 0);
								for (it4 = company.begin(); it4 != company.end(); it4++) {
									company.erase(it4);
									break;
								}
								comp.write_company_infile(company);
							}
							break;
						}
						case 3: {
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						}
					}
					c2 = 0;
					break;
				}
				case 5: {
					strcpy_s(p, "5");
					send((SOCKET)newS, p, sizeof(p), 0);
					break;
				}
				}
			}
			c1 = 0;
			break;
		}
		case 1: {
			cout << endl;
			//strcpy_s(p, "2");
			//send((SOCKET)newS, p, sizeof(p), 0);
			int c444 = 0;
			while (c444 != 3) {
				strcpy_s(k, "Аккаунт инвестора: \n1 - Зарегистрироваться  \n2 - Войти\n3 - Выход\n ");
				send((SOCKET)newS, k, sizeof(k), 0);
				recv((SOCKET)newS, m, sizeof(m), 0);
				c444 = atoi(m);
				switch (c444) {
				case 1: {
					strcpy_s(p, "1");
					send((SOCKET)newS, p, sizeof(p), 0);

					//получение фамилии
					recv((SOCKET)newS, m, sizeof(m), 0);
					//cout << m << endl;
					invest.Set_F(m);

					//получение имени
					recv((SOCKET)newS, m, sizeof(m), 0);
					//cout << m << endl;

					invest.Set_I(m);

					//получение капитала
					recv((SOCKET)newS, m, sizeof(m), 0);
					//cout << m << endl;

					float temp;
					temp = stof(m);
					invest.Set_capital(temp);


					//получение проектов
					recv((SOCKET)newS, m, sizeof(m), 0);
					//cout << m << endl;
					temp = atoi(m);
					invest.Set_projects(temp);

					//получение опыта
					recv((SOCKET)newS, m, sizeof(m), 0);
					//cout << m << endl;
					temp = atoi(m);
					invest.Set_practice(temp);

					//получили логин

					char ex[30];
					char ex2[5];
					int flag = 0;
					e = 0;
					while (e == 0) {
						flag = 0;
						recv((SOCKET)newS, m, sizeof(m), 0);
						//cout << m << endl;
						e = 0;
						strcpy_s(ex, "Такой логин уже существует!");
						strcpy_s(ex2, "0");
						if (investor.size() != 0) {
							for (it = investor.begin(); it != investor.end(); it++) {
								if (strcmp(m, it->Get_log()) == 0) {
									send((SOCKET)newS, ex, sizeof(ex), 0);
									flag = 1;
									//cout << "Логин существует!" << endl;
								}
							}
						}
						if (flag == 0) {
							send((SOCKET)newS, ex2, sizeof(ex2), 0);
							e++;
						}
					}
					invest.Set_login(m);
					//cout << invest.Get_log() << endl;
					//получили пароль
					recv((SOCKET)newS, m, sizeof(m), 0);
					//cout << m << endl;
					invest.Set_pass(m);
					//cout << invest.Get_pass()<<endl;
					investor.push_back(invest);
					investor_pos.push_back(invest);
					it = investor.begin();

					//cout << (*it).Get_log();
					//cout << it->Get_pass();

					write_investor_infile(investor);

					write_in_file_password(investor);

					write_investor_done_pos(investor_pos);

					/*for (it = investor.begin(); it != investor.end(); it++) {
						cout << (*it).Get_F() << (*it).Get_I() << (*it).Get_capital() << (*it).Get_projects() << (*it).Get_practice() << (*it).Get_log() << (*it).Get_pass() << endl;
					}*/
					break;
				}
				case 2: {
					strcpy_s(p, "2");
					send((SOCKET)newS, p, sizeof(p), 0);
					p[0] = '\0';

					char ex1[30];
					char ex21[5];
					int flag = 0;
					e = 1;
					int iteratorr = 0;

					while (e == 1) {
						flag = 0;
						recv((SOCKET)newS, m, sizeof(m), 0);
						//cout << m << endl;
						e = 1;
						strcpy_s(ex1, "Такого пользователя нет!");
						strcpy_s(ex21, "0");

						if (investor.size() != 0) {
							iteratorr = 0;
							for (it = investor.begin(); it != investor.end(); it++) {
								if (strcmp(m, it->Get_log()) == 0) {
									send((SOCKET)newS, ex21, sizeof(ex21), 0);
									flag = 1;
									e = 2;
									it = investor.end();
									it--;
									//cout << "Логин существует!" << endl;	
								}

								iteratorr++;
							}

							if (flag == 0) {
								send((SOCKET)newS, ex1, sizeof(ex1), 0);

							}
						}
					}


					//cout << "Это итth " << iteratorr << endl;


					e = 0;

					while (e == 0) {
						flag = 0;
						//cout << "33333" << m << endl;
						recv((SOCKET)newS, m, sizeof(m), 0);
						e = 0;
						strcpy_s(ex1, "Такого пользователя нет!");
						strcpy_s(ex21, "0");
						int it1 = 0;

						if (investor.size() != 0) {

							for (it = investor.begin(); it != investor.end(); it++) {
								it1++;
								if (it1 == iteratorr) {
									//cout << endl;
									//cout << it->Get_pass() << endl;
									if (strcmp(m, it->Get_pass()) == 0) {
										send((SOCKET)newS, ex21, sizeof(ex21), 0);
										flag = 1;
										e++;
										//cout << "Пароль совпадает!" << endl;
									}
								}

							}
						}
						if (flag == 0) {
							send((SOCKET)newS, ex1, sizeof(ex1), 0);

						}
					}

					while (c11 != 4) {
						strcpy_s(k, "Меню инвестора: \n1 - Редактировать свои данные \n2 - Просмотреть свои данные \n3 - Просмотреть договоры \n4 - Выход. ");
						send((SOCKET)newS, k, sizeof(k), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);

						c11 = atoi(m);
						switch (c11) {
							//ввод инвестиционных данных
						case 1: {
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							while (c2 != 5) {
								char stroka[500];
								stroka[0] = '\0';
								int it2 = 0;
								int strooka;
								for (it = investor.begin(); it != investor.end(); it++) {
									it2++;
									if (it2 == iteratorr) {

										stroka[0] = '\0';
										strcpy_s(stroka, it->Get_F());
										send((SOCKET)newS, stroka, sizeof(stroka), 0);

										stroka[0] = '\0';
										strcpy_s(stroka, it->Get_I());
										send((SOCKET)newS, stroka, sizeof(stroka), 0);

										stroka[0] = '\0';
										strooka = it->Get_capital();
										_itoa_s(strooka, stroka, 10);//здесь плохо с флоооот
										send((SOCKET)newS, stroka, sizeof(stroka), 0);

										stroka[0] = '\0';
										strooka = it->Get_projects();
										_itoa_s(strooka, stroka, 10);
										send((SOCKET)newS, stroka, sizeof(stroka), 0);

										stroka[0] = '\0';
										strooka = it->Get_practice();
										_itoa_s(strooka, stroka, 10);
										send((SOCKET)newS, stroka, sizeof(stroka), 0);
									}
								}



								strcpy_s(k, "Выберите что хотите отредактировать:\n 1 - Фамилию и имя\n 2 - Капиталовложения\n 3 - Опыт работы\n 4 - Количество проектов\n 5 - Выход\n ");
								send((SOCKET)newS, k, sizeof(k), 0);
								recv((SOCKET)newS, m, sizeof(m), 0);
								c2 = atoi(m);
								switch (c2) {
								case 1: {
									strcpy_s(p, "1");
									send((SOCKET)newS, p, sizeof(p), 0);

									//получение фамилии
									recv((SOCKET)newS, m, sizeof(m), 0);
									//cout << m << endl;

									int it1 = 0;
									for (it = investor.begin(); it != investor.end(); it++) {
										it1++;
										if (it1 == iteratorr) {
											it->Set_F(m);

										}

									}
									it1 = 0;
									for (it_pos = investor_pos.begin(); it_pos != investor_pos.end(); it_pos++) {
										it1++;
										if (it1 == iteratorr) {
											it_pos->Set_F(m);

										}

									}



									//получение имени
									recv((SOCKET)newS, m, sizeof(m), 0);
									//cout << m << endl;
									it1 = 0;
									for (it = investor.begin(); it != investor.end(); it++) {
										it1++;
										if (it1 == iteratorr) {
											it->Set_I(m);

										}

									}

									it1 = 0;
									for (it_pos = investor_pos.begin(); it_pos != investor_pos.end(); it_pos++) {
										it1++;
										if (it1 == iteratorr) {
											it_pos->Set_I(m);

										}

									}

									write_investor_infile(investor);
									write_investor_done_pos(investor_pos);
									break;
								}
								case 2: {
									strcpy_s(p, "2");
									send((SOCKET)newS, p, sizeof(p), 0);
									//получение капитала
									recv((SOCKET)newS, m, sizeof(m), 0);
									//cout << m << endl;

									float temp;
									temp = stof(m);
									int it1 = 0;
									for (it = investor.begin(); it != investor.end(); it++) {
										it1++;
										if (it1 == iteratorr) {
											it->Set_capital(temp);

										}

									}

									it1 = 0;
									for (it_pos = investor_pos.begin(); it_pos != investor_pos.end(); it_pos++) {
										it1++;
										if (it1 == iteratorr) {
											it_pos->Set_capital(temp);

										}

									}

									write_investor_infile(investor);
									write_investor_done_pos(investor_pos);

									break;
								}
								case 3: {
									strcpy_s(p, "3");
									send((SOCKET)newS, p, sizeof(p), 0);
									float temp;
									//получение проектов
									recv((SOCKET)newS, m, sizeof(m), 0);
									//cout << m << endl;
									temp = atoi(m);

									int it1 = 0;
									for (it = investor.begin(); it != investor.end(); it++) {
										it1++;
										if (it1 == iteratorr) {
											it->Set_projects(temp);

										}

									}


									it1 = 0;
									for (it_pos = investor_pos.begin(); it_pos != investor_pos.end(); it_pos++) {
										it1++;
										if (it1 == iteratorr) {
											it_pos->Set_projects(temp);

										}

									}


									write_investor_done_pos(investor_pos);
									write_investor_infile(investor);
									break;
								}
								case 4: {
									strcpy_s(p, "4");
									send((SOCKET)newS, p, sizeof(p), 0);

									//получение опыта
									recv((SOCKET)newS, m, sizeof(m), 0);
									//cout << m << endl;
									int it1 = 0;
									int temp = 0;
									temp = atoi(m);

									for (it = investor.begin(); it != investor.end(); it++) {
										it1++;
										if (it1 == iteratorr) {
											it->Set_practice(temp);

										}
									}
									it1 = 0;
									for (it_pos = investor_pos.begin(); it_pos != investor_pos.end(); it_pos++) {
										it1++;
										if (it1 == iteratorr) {
											it_pos->Set_projects(temp);

										}

									}

									write_investor_done_pos(investor_pos);
									write_investor_infile(investor);

									break;
								}
								case 5: {
									strcpy_s(p, "5");
									send((SOCKET)newS, p, sizeof(p), 0);
									break;
								}

								}
							}
							c2 = 0;
							break;


						}
						case 2: {
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);
							char stroka[500];
							stroka[0] = '\0';
							int it2 = 0;
							int strooka;
							for (it = investor.begin(); it != investor.end(); it++) {
								it2++;
								if (it2 == iteratorr) {

									stroka[0] = '\0';
									strcpy_s(stroka, it->Get_F());
									send((SOCKET)newS, stroka, sizeof(stroka), 0);

									stroka[0] = '\0';
									strcpy_s(stroka, it->Get_I());
									send((SOCKET)newS, stroka, sizeof(stroka), 0);

									stroka[0] = '\0';
									strooka = it->Get_capital();
									_itoa_s(strooka, stroka, 10);
									send((SOCKET)newS, stroka, sizeof(stroka), 0);

									stroka[0] = '\0';
									strooka = it->Get_projects();
									_itoa_s(strooka, stroka, 10);
									send((SOCKET)newS, stroka, sizeof(stroka), 0);

									stroka[0] = '\0';
									strooka = it->Get_practice();
									_itoa_s(strooka, stroka, 10);
									send((SOCKET)newS, stroka, sizeof(stroka), 0);
								}
							}

							break;
						}
						case 3: {
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);
							int choice_i = 0;
							char message[500];
							char message2[500];
							char p2[500];
							int flag2 = 0;
							int it1 = 0;
							while (choice_i != 4) {
								strcpy_s(k, "Выберите пункт, который хотите просмотреть:\n1 - Просмотреть заявки на договор\n2 - Просмотреть заявки на рассторжение договора\n3 - Просмотреть активные договоры\n4 - Выход\nВвведите пункт: ");
								send((SOCKET)newS, k, sizeof(k), 0);
								recv((SOCKET)newS, m, sizeof(m), 0);
								choice_i = atoi(m);
								switch (choice_i) {
								case 1: {
									strcpy_s(p, "1");
									send((SOCKET)newS, p, sizeof(p), 0);
									int flag2 = 0;
									p[0] = '\0';
									p2[0] = '\0';

									for (it = investor.begin(); it != investor.end(); it++) {
										it1++;
										if (it1 == iteratorr) {
											strcpy_s(p, it->Get_F());
										}

									}


									it1 = 0;
									message[0] = '\0';
									message2[0] = '\0';

									strcpy_s(message, "0");
									strcpy_s(message2, "1");

									if (investor_app.size() != 0) {
										for (it_app = investor_app.begin(); it_app != investor_app.end(); it_app++) {

											if (strcmp(p, it_app->Get_F()) == 0) {
												send((SOCKET)newS, message, sizeof(message), 0);
												flag2++;

											}
										}
									}

									if (flag2 == 0) {
										//у вас нет договоров
										send((SOCKET)newS, message2, sizeof(message2), 0);
									}

									else {
										//есть договор

										write_company_table(company);
										ifstream ff("Company_table1.txt", ios_base::in);

										if (!ff.is_open() || ff.peek() == EOF) {
											cout << "Файл не удалось открыть или он пуст (  )." << endl;
											return;
										}


										while (!ff.eof()) {
											k[0] = '\0';
											ff.getline(k, 256, '\n');
											m[0] = '\0';
											strcpy_s(m, "*");
											if (ff.eof()) {
												send((SOCKET)newS, m, sizeof(m), 0);
											}

											else {
												send((SOCKET)newS, k, sizeof(k), 0);
											}
										}
										ff.close();

										p2[0] = '\0';
										recv((SOCKET)newS, p2, sizeof(p2), 0);


										if (strcmp(p2, "1") == 0) {

											//cout << "Заявка подтверждена" << endl;

											for (it_app = investor_app.begin(); it_app != investor_app.end(); it_app++) {

												if (strcmp(p, it_app->Get_F()) == 0) {

													investor_done.push_back(*it_app);
													investor_app.erase(it_app);

													break;
												}
											}

											for (it_pos = investor_pos.begin(); it_pos != investor_pos.end(); it_pos++) {

												if (strcmp(p, it_pos->Get_F()) == 0) {

													investor_pos.erase(it_pos);

													break;
												}
											}


											write_investor_app_infile(investor_app);
											write_investor_done_infile(investor_done);
											write_investor_done_pos(investor_pos);
										}

										else {
											//cout << "Заявка НЕ подтверждена" << endl;

											for (it_app = investor_app.begin(); it_app != investor_app.end(); it_app++) {

												if (strcmp(p, it_app->Get_F()) == 0) {
													investor_app.erase(it_app);
													break;
												}
											}
											write_investor_app_infile(investor_app);

										}


									}
									break;
								}

								case 2: {
									strcpy_s(p, "2");
									send((SOCKET)newS, p, sizeof(p), 0);
									flag2 = 0;
									p[0] = '\0';
									p2[0] = '\0';

									for (it = investor.begin(); it != investor.end(); it++) {
										it1++;
										if (it1 == iteratorr) {
											strcpy_s(p, it->Get_F());
										}

									}

									it1 = 0;
									message[0] = '\0';
									message2[0] = '\0';

									strcpy_s(message, "0");
									strcpy_s(message2, "1");

									for (it_del = investor_del.begin(); it_del != investor_del.end(); it_del++) {

										if (strcmp(p, it_del->Get_F()) == 0) {
											send((SOCKET)newS, message, sizeof(message), 0);
											flag2++;

										}
									}

									if (flag2 == 0) {
										//у вас нет договоров
										send((SOCKET)newS, message2, sizeof(message2), 0);
									}

									else {
										//есть договор

										write_contract(company, p);

										ifstream ff("Company_table.txt", ios_base::in);

										if (!ff.is_open() || ff.peek() == EOF) {
											cout << "Файл не удалось открыть или он пуст (  )." << endl;
											return;
										}


										while (!ff.eof()) {
											k[0] = '\0';
											ff.getline(k, 256, '\n');
											m[0] = '\0';
											strcpy_s(m, "*");
											if (ff.eof()) {
												send((SOCKET)newS, m, sizeof(m), 0);
											}

											else {
												send((SOCKET)newS, k, sizeof(k), 0);
											}
										}
										ff.close();


										p2[0] = '\0';
										recv((SOCKET)newS, p2, sizeof(p2), 0);

										if (strcmp(p2, "1") == 0) {

											//cout << "Заявка на удаление подтверждена" << endl;

											for (it_del = investor_del.begin(); it_del != investor_del.end(); it_del++) {

												if (strcmp(p, it_del->Get_F()) == 0) {

													investor_pos.push_back(*it_del);
													investor_del.erase(it_del);


													break;
												}
											}
											write_investor_del_infile(investor_del);
											//write_investor_done_infile(investor_done);
											write_investor_done_pos(investor_pos);
										}

										else {
											//cout << "Заявка на удаление НЕ подтверждена" << endl;

											for (it_del = investor_del.begin(); it_del != investor_del.end(); it_del++) {

												if (strcmp(p, it_del->Get_F()) == 0) {

													investor_done.push_back(*it_del);
													investor_del.erase(it_del);
													break;
												}
											}
											write_investor_del_infile(investor_del);
											write_investor_done_infile(investor_done);

										}

									}
									break;

								}

								case 3: {
									strcpy_s(p, "3");


									send((SOCKET)newS, p, sizeof(p), 0);

									for (it = investor.begin(); it != investor.end(); it++) {
										it1++;
										if (it1 == iteratorr) {
											strcpy_s(p, it->Get_F());
										}

									}

									it1 = 0;
									message[0] = '\0';
									message2[0] = '\0';

									strcpy_s(message, "0");
									strcpy_s(message2, "1");

									for (it_done = investor_done.begin(); it_done != investor_done.end(); it_done++) {

										if (strcmp(p, it_done->Get_F()) == 0) {
											send((SOCKET)newS, message, sizeof(message), 0);
											flag2++;

											write_contract(company, p);

											ifstream ff("Company_table.txt", ios_base::in);

											if (!ff.is_open() || ff.peek() == EOF) {
												//cout << "Файл не удалось открыть или он пуст (  )." << endl;
												return;
											}


											while (!ff.eof()) {
												k[0] = '\0';
												ff.getline(k, 256, '\n');
												m[0] = '\0';
												strcpy_s(m, "*");
												if (ff.eof()) {
													send((SOCKET)newS, m, sizeof(m), 0);
												}

												else {
													send((SOCKET)newS, k, sizeof(k), 0);
												}
											}
											ff.close();

										}
									}

									if (flag2 == 0) {
										//у вас нет договоров
										send((SOCKET)newS, message2, sizeof(message2), 0);
									}
									break;
								}
								case 4: {
									strcpy_s(p, "4");
									send((SOCKET)newS, p, sizeof(p), 0);
									break;
								}
								}
							}
							choice_i = 0;
							break;
						}
						case 4: {
							strcpy_s(p, "4");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						}
					}
					c11 = 0;
					break;
				}
				case 3: {
					strcpy_s(p, "3");
					send((SOCKET)newS, p, sizeof(p), 0);
					break;
				}
				}
			}
			c444 = 0;
			break;
		}
		case 2: {
			p[0] = '\0';
			//strcpy_s(p, "3");
			//send((SOCKET)newS, p, sizeof(p), 0);
			while (c1 != 4) {
				strcpy_s(k, "Меню эксперта:\n 1 - Информация об инвесторах \n 2 - Выставить оценки для инвесторов \n 3 - Выбрать наилучший вариант\n 4 - Выход. ");
				send((SOCKET)newS, k, sizeof(k), 0);
				recv((SOCKET)newS, m, sizeof(m), 0);
				c1 = atoi(m);
				switch (c1) {
				case 1: {
					ifstream file5("Investors_best.txt");
					strcpy_s(p, "1");
					send((SOCKET)newS, p, sizeof(p), 0);

					//просмотр информации об инвесторах
					if (investor.size() == 0) {
						p[0] = '\0';
						strcpy_s(p, "0");
						send((SOCKET)newS, p, sizeof(p), 0);
					}

					else {
						p[0] = '\0';
						strcpy_s(p, "1");
						send((SOCKET)newS, p, sizeof(p), 0);

						invest.write_investor_best(investor);
						while (!file5.eof()) {
							k[0] = '\0';
							file5.getline(k, 256, '\n');
							m[0] = '\0';
							strcpy_s(m, "*");
							if (file5.eof()) {
								send((SOCKET)newS, m, sizeof(m), 0);
							}

							else {
								send((SOCKET)newS, k, sizeof(k), 0);
								//cout << k << endl;
							}
						}
						file5.close();
					}

					m[0] = '\0';
					k[0] = '\0';
					break;
				}
				case 2: {
					strcpy_s(p, "2");
					send((SOCKET)newS, p, sizeof(p), 0);

					p[0] = '\0';

					if (investor_pos.size() == 0) {
						strcpy_s(p, "0");
						send((SOCKET)newS, p, sizeof(p), 0);

					}
					else {
						_itoa_s(investor_pos.size(), p, 10);
						send((SOCKET)newS, p, sizeof(p), 0);

						if (expert.size() != 3) {//сделать здесь другой список
							strcpy_s(p, "0");
							send((SOCKET)newS, p, sizeof(p), 0);

						}
						else {
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							m[0] = '\0';
							recv((SOCKET)newS, m, sizeof(m), 0);

							if (strcmp(m, "1") == 0)
							{
								write_investor_poss(investor_pos);
								ifstream ff2("Investors_poss.txt", ios_base::in);

								if (!ff2.is_open() || ff2.peek() == EOF) {
									cout << "Файл не удалось открыть или он пуст (  )." << endl;
									return;
								}
								while (!ff2.eof()) {
									k[0] = '\0';
									ff2.getline(k, 256, '\n');
									m[0] = '\0';
									strcpy_s(m, "*");
									if (ff2.eof()) {
										send((SOCKET)newS, m, sizeof(m), 0);
									}

									else {
										send((SOCKET)newS, k, sizeof(k), 0);
									}
								}

								p[0] = '\0';
							}

						}
					}

					break;
				}
				case 3: {
					p[0] = '\0';
					strcpy_s(p, "3");
					send((SOCKET)newS, p, sizeof(p), 0);

					string name1 = "E:\\4 сеееем\\курсачкакойтоидиотский\\SAPIS\\Server\\matrix1.txt";
					string name2 = "E:\\4 сеееем\\курсачкакойтоидиотский\\SAPIS\\Server\\matrix2.txt";
					string name3 = "E:\\4 сеееем\\курсачкакойтоидиотский\\SAPIS\\Server\\matrix3.txt";
					string name4 = "Веса.txt";


					ifstream fff5("E:\\4 сеееем\\курсачкакойтоидиотский\\SAPIS\\Server\\matrix1.txt", ios_base::in);

					if (!fff5.is_open() || fff5.peek() == EOF) {
						p[0] = '\0';
						strcpy_s(p, "0");
						send((SOCKET)newS, p, sizeof(p), 0);
						cout << "Оценки еще не выставлены!." << endl;
						//return;
						fff5.close();
					}

					else {
						int sizee = investor_pos.size();
						p[0] = '\0';
						strcpy_s(p, "1");
						send((SOCKET)newS, p, sizeof(p), 0);
						p[0] = '\0';
						float** matrix;
						float** matrix2;
						float** matrix3;
						float* wesa;

						read_matrix(sizee, matrix, name1);

						cout << endl;
						cout << "Матрица оценок первого эксперта" << endl;
						cout << endl;
						for (int i = 0; i < sizee; i++) {
							for (int j = 0; j < sizee; j++) {
								cout << setprecision(2) << setw(4) << matrix[i][j] << "|";
							}
							cout << endl;
						}

						cout << endl;

						read_matrix(sizee, matrix2, name2);
						cout << endl;
						cout << "Матрица оценок второго эксперта" << endl;
						cout << endl;
						for (int i = 0; i < sizee; i++) {
							for (int j = 0; j < sizee; j++) {
								cout << setprecision(2) << setw(4) << matrix2[i][j] << "|";
							}

							cout << endl;
						}
						cout << endl;
						read_matrix(sizee, matrix3, name3);
						cout << endl;
						cout << "Матрица оценок третьего эксперта" << endl;
						cout << endl;
						for (int i = 0; i < sizee; i++) {
							for (int j = 0; j < sizee; j++) {
								cout << setprecision(2) << setw(4) << matrix3[i][j] << "|";
							}

							cout << endl;
						}
						int three = 3;

						method.methodd(matrix, matrix2, matrix3, sizee, sizee);
						read_matrix2(sizee, wesa, name4);
						read_matrix_table(sizee, wesa, name4);

						ifstream fout("result.txt", ios_base::in);

						if (!fout.is_open() || fout.peek() == EOF) {
							cout << "Файл не удалось открыть или он пуст (результат)." << endl;
							return;
						}
						char stro[3];
						int ress = 0;

						fout.getline(stro, 3, '*');
						if (strcmp(stro, "*") == 0) {
							break;
						}
						ress = atoi(stro);
						method.Set_result(ress);
						cout << endl;
						cout << "Номер инвестора в списке с наилучшими результатами: ";
						cout << ress << endl;
						cout << endl;
						fout.close();
						int it1 = 0;
						p[0] = '\0';

						investor_best.clear();


						for (it_pos = investor_pos.begin(); it_pos != investor_pos.end(); it_pos++) {
							it1++;
							if (it1 == ress) {
								strcpy_s(p, it_pos->Get_F());
								investor_best.push_back(*it_pos);
							}

						}
						write_investor_infile_thebest(investor_best);

						invest.write_investor_best2(investor_best);


						ifstream ff("Investors_best2.txt", ios_base::in);

						if (!ff.is_open() || ff.peek() == EOF) {
							//cout << "Файл не удалось открыть или он пуст (  )." << endl;
							return;
						}


						while (!ff.eof()) {
							k[0] = '\0';
							ff.getline(k, 256, '\n');
							m[0] = '\0';
							strcpy_s(m, "*");
							if (ff.eof()) {
								send((SOCKET)newS, m, sizeof(m), 0);
							}

							else {
								send((SOCKET)newS, k, sizeof(k), 0);
							}
						}
						fout.close();
					}
					break;
				}
				case 4: {
					strcpy_s(p, "4");
					send((SOCKET)newS, p, sizeof(p), 0);
				}
				}
			}
			c1 = 0;
			break;
		}
		case 3: {
			//strcpy_s(p, "4");
			//send((SOCKET)newS, p, sizeof(p), 0);
			closesocket((SOCKET)newS);
			exit(EXIT_SUCCESS);
			break;
		}
		}
	}
}
int numcl = 0;
void print()
{
	if (numcl) printf("%d клиент подключен\n", numcl);
	else printf("Нет подключений\n");
	cout << endl;
}



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		return -1;
	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(1280);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr_in cs_addr; //или SOCKADDR_IN cs_addr;
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	int c = bind(s, (struct sockaddr*)&local, sizeof(local));
	int r = listen(s, 5);
	while (true) {
		sockaddr_in remote;
		int j = sizeof(remote);
		SOCKET newS = accept(s, (struct sockaddr*)&remote, &j);
		numcl++;
		print();

		_beginthread(mailWorking, 0, (void*)newS);  //создание потока(Начальный адрес процедуры, который начинает выполнение нового потока; размер стека нового потока или 0; список аргументов, передаваемый в новый поток, или NULL)
	}
	//

	WSACleanup();
	return 0;
}

