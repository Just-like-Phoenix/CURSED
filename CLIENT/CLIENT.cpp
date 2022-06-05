#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include "Menu.h"
#include "Libs.h"

#pragma warning(disable : 4996)

using namespace std;

Menu RegMenu, UserMenu, AdminMenu;
Menu* MenuPtr = &RegMenu;
bool unreg = false;
int counter = 0;
float TotCost = 0;

class User {
	bool isAdmin = false;
	bool isSmth = false;

public:
	void setReg(bool status, bool reg) {
		isAdmin = status;
		isSmth = reg;
	}
	bool GetStatus() {
		return isAdmin;
	}
	bool GetSmth() {
		return isSmth;
	}
};

User user;

void SendRequest(SOCKET soc, string id) {
	char buf[100];
	strcpy(buf, id.c_str());
	send(soc, buf, sizeof(buf), 0);
}

void SendReg(SOCKET soc) {
	char tfbuf[100];
	char log[100];
	char pass[100];

	system("cls");

	cout << "Введите логин: ";
	cin.getline(log, 100);
	cout << "Введите пароль: ";
	cin.getline(pass, 100);

	send(soc, log, sizeof(log), 0);
	send(soc, pass, sizeof(pass), 0);

	recv(soc, tfbuf, sizeof(tfbuf), 0);

	if (!strcmp(tfbuf, "11")) user.setReg(true, true);
	else if (!strcmp(tfbuf, "21")) user.setReg(false, true);
	else {
		system("cls");
		cout << "Ошибка авторизации";
	}
}
void Unreg() {
	user.setReg(false, false);
	unreg = true;
}

void SendAdd(SOCKET soc)
{
	char buf[100], dell_code[100], from[100], to[100], distance[100], volume[100], weight[100];
	bool prov = true;

	system("cls");

	cout << "1) Экспрес" << endl;
	cout << "2) Эконом" << endl;
	cout << "3) Стандарт" << endl;
	cout << "Выберите тип доставки: ";
	cin.getline(buf, 100);
	send(soc, buf, sizeof(buf), 0);

	do
	{
	cout << "Введите код маршрута (от 0 до 999999): ";
	cin.getline(dell_code, 100);
	if (!(atoi(dell_code) >= 0) && !(atoi(dell_code) <= 999999)) prov = false;
	cout << "Введите место погрузки: ";
	cin.getline(from, 100);
	cout << "Введите место доставки: ";
	cin.getline(to, 100);
	cout << "Введите растояние: ";
	cin.getline(distance, 100);
	if (!(atoi(distance) > 0) && !(atoi(distance) <= 999999)) prov = false;
	cout << "Введите объем в кубических метрах: ";
	cin.getline(volume, 100);
	if (!(atoi(volume) > 0) && !(atoi(volume) <= 999999)) prov = false;
	cout << "Введите вес в тонах: ";
	cin.getline(weight, 100);
	if (!(strtod(weight, NULL) > 0) && !(strtod(weight, NULL) <= 999999)) prov = false;
	} while (!prov);

	if (prov)
	{
		send(soc, dell_code, sizeof(dell_code), 0);
		send(soc, from, sizeof(from), 0);
		send(soc, to, sizeof(to), 0);
		send(soc, distance, sizeof(distance), 0);
		send(soc, volume, sizeof(volume), 0);
		send(soc, weight, sizeof(weight), 0);
	}
	
}

void SendShow(SOCKET soc) 
{
	system("cls");
	cout << "+--------+----------------+----------------+---------------+---------------+-------------+-------------+---------------+\n";
	cout << "|  Код   |     Откуда     |      Куда      |   Дистанция   |      Тип      |     Вес     |    Объем    |     Цена      |\n";
	cout << "+--------+----------------+----------------+---------------+---------------+-------------+-------------+---------------+\n";
	char dell_code[100], from[100], to[100], distance[100], type[100], volume[100], sweight[100], sprice[100];
	double weight, price;
	while (true) 
	{
		recv(soc, dell_code, sizeof(dell_code), 0);
		if (strcmp(dell_code, "0")) 
		{
			recv(soc, from, sizeof(from), 0);
			recv(soc, to, sizeof(to), 0);
			recv(soc, distance, sizeof(distance), 0);
			recv(soc, type, sizeof(type), 0);
			recv(soc, volume, sizeof(volume), 0);
			recv(soc, sweight, sizeof(sweight), 0);
			recv(soc, sprice, sizeof(sprice), 0);
			weight = atof(sweight);
			price = atof(sprice);
			printf("|%8s|%16s|%16s|%15s|%15s|%13.1f|%13s|%15.1f|\n", dell_code, from, to, distance, type, weight, volume, price);
			cout << "+--------+----------------+----------------+---------------+---------------+-------------+-------------+---------------+\n";
		}
		else break;
	}
}

void SendSearch(SOCKET soc) {
	system("cls");
	bool exist = false;
	char str[100];
	cout << "Поиск: ";
	cin.getline(str, 100);
	send(soc, str, sizeof(str), 0);
	system("cls");
	cout << "+--------+----------------+----------------+---------------+---------------+-------------+-------------+---------------+\n";
	cout << "|  Код   |     Откуда     |      Куда      |   Дистанция   |      Тип      |     Вес     |    Объем    |     Цена      |\n";
	cout << "+--------+----------------+----------------+---------------+---------------+-------------+-------------+---------------+\n";
	char dell_code[100], from[100], to[100], distance[100], type[100], volume[100], sweight[100], sprice[100];
	double weight, price;
	while (true) {

		recv(soc, dell_code, sizeof(dell_code), 0);

		if (strlen(dell_code) > 1)
		{
			exist = true;
			recv(soc, from, sizeof(from), 0);
			recv(soc, to, sizeof(to), 0);
			recv(soc, distance, sizeof(distance), 0);
			recv(soc, type, sizeof(type), 0);
			recv(soc, volume, sizeof(volume), 0);
			recv(soc, sweight, sizeof(sweight), 0);
			recv(soc, sprice, sizeof(sprice), 0);
			weight = atof(sweight);
			price = atof(sprice);
			printf("|%8s|%16s|%16s|%15s|%15s|%13.1f|%13s|%15.1f|\n", dell_code, from, to, distance, type, weight, volume, price);
			cout << "+--------+----------------+----------------+---------------+---------------+-------------+-------------+---------------+\n";
			*dell_code = '\0';
		}
		else break;
	}
	if (exist == false) {
		printf("|                                              Совпадений не найдено                                                   |\n");
		printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	}
}

void SendShowForSort(SOCKET soc)
{
	system("cls");
	bool exist = false;
	char str[100];
	system("cls");
	cout << "+--------+----------------+----------------+---------------+---------------+-------------+-------------+---------------+\n";
	cout << "|  Код   |     Откуда     |      Куда      |   Дистанция   |      Тип      |     Вес     |    Объем    |     Цена      |\n";
	cout << "+--------+----------------+----------------+---------------+---------------+-------------+-------------+---------------+\n";
	char dell_code[100], from[100], to[100], distance[100], type[100], volume[100], sweight[100], sprice[100];
	double weight, price;
	while (true) {

		recv(soc, dell_code, sizeof(dell_code), 0);

		if (strlen(dell_code) > 1)
		{
			exist = true;
			recv(soc, from, sizeof(from), 0);
			recv(soc, to, sizeof(to), 0);
			recv(soc, distance, sizeof(distance), 0);
			recv(soc, type, sizeof(type), 0);
			recv(soc, volume, sizeof(volume), 0);
			recv(soc, sweight, sizeof(sweight), 0);
			recv(soc, sprice, sizeof(sprice), 0);
			weight = atof(sweight);
			price = atof(sprice);
			printf("|%8s|%16s|%16s|%15s|%15s|%13.1f|%13s|%15.1f\n", dell_code, from, to, distance, type, weight, volume, price);
			cout << "+--------+----------------+----------------+---------------+---------------+-------------+-------------+---------------+\n";
			*dell_code = '\0';
		}
		else break;
	}
	if (exist == false) {
		printf("|                                              Совпадений не найдено                                                   |\n");
		printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	}
}
void SendSort(SOCKET soc)
{
	Menu SortMenu;

	
	SortMenu.CreateMenu(2, "По месту погрузки", "По месту доставки");
	{
		SortMenu.sub[0].CreateMenu(2, "По возрастанию", "По убыванию");
		SortMenu.sub[1].CreateMenu(2, "По возрастанию", "По убыванию");
	}
	

	bool running = true;
	while (running) 
	{
		MenuPtr = &SortMenu;

		MenuPtr->SetHeader("Сортировка");
		MenuPtr->currentID = "0";
		MenuPtr->ShowMenu();
		MenuPtr->Navigation(&running);

		if (MenuPtr->currentID == "11") 
		{
			SendRequest(soc, "2_3" + MenuPtr->currentID);
			SendShowForSort(soc);
			_getch();
		}
		else if (MenuPtr->currentID == "12") 
		{
			SendRequest(soc, "2_3" + MenuPtr->currentID);
			SendShowForSort(soc);
			_getch();
		}
		else if (MenuPtr->currentID == "21")
		{
			SendRequest(soc, "2_3" + MenuPtr->currentID);
			SendShowForSort(soc);
			_getch();
		}
		else if (MenuPtr->currentID == "22") 
		{
			SendRequest(soc, "2_3" + MenuPtr->currentID);
			SendShowForSort(soc);
			_getch();
		}
	}
}

void SendFiltr(SOCKET soc)
{
	system("cls");
	bool exist = false;
	char str[100];
	cout << "Фльтр: ";
	cin.getline(str, 100);
	send(soc, str, sizeof(str), 0);
	system("cls");
	cout << "+--------+----------------+----------------+---------------+---------------+-------------+-------------+---------------+\n";
	cout << "|  Код   |     Откуда     |      Куда      |   Дистанция   |      Тип      |     Вес     |    Объем    |     Цена      |\n";
	cout << "+--------+----------------+----------------+---------------+---------------+-------------+-------------+---------------+\n";
	char dell_code[100], from[100], to[100], distance[100], type[100], volume[100], sweight[100], sprice[100];
	double weight, price;
	while (true) {

		recv(soc, dell_code, sizeof(dell_code), 0);

		if (strlen(dell_code) > 1)
		{
			exist = true;
			recv(soc, from, sizeof(from), 0);
			recv(soc, to, sizeof(to), 0);
			recv(soc, distance, sizeof(distance), 0);
			recv(soc, type, sizeof(type), 0);
			recv(soc, volume, sizeof(volume), 0);
			recv(soc, sweight, sizeof(sweight), 0);
			recv(soc, sprice, sizeof(sprice), 0);
			weight = atof(sweight);
			price = atof(sprice);
			printf("|%8s|%16s|%16s|%15s|%15s|%13.1f|%13s|%15.1f|\n", dell_code, from, to, distance, type, weight, volume, price);
			cout << "+--------+--------------+--------------+---------------+---------------+---------------+---------------+---------------+\n";
			*dell_code = '\0';
		}
		else break;
	}
	if (exist == false) {
		printf("|                                              Совпадений не найдено                                                   |\n");
		printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	}
}

void Delete(SOCKET soc)
{
	char buf[100], prov[10];
	int n = 1;

	system("cls");
	
	recv(soc, prov, sizeof(prov), 0);

	if (atoi(prov) > 0)
	{
		cout << "+---+--------+----------------+----------------+--------------+---------------+------------+------------+--------------+\n";
		cout << "| № |  Код   |     Откуда     |      Куда      |   Дистанция  |      Тип      |     Вес    |    Объем   |     Цена     |\n";
		cout << "+---+--------+----------------+----------------+--------------+---------------+------------+------------+--------------+\n";
		char dell_code[100], from[100], to[100], distance[100], type[100], volume[100], sweight[100], sprice[100];
		double weight, price;
		while (true)
		{
			recv(soc, dell_code, sizeof(dell_code), 0);
			if (strlen(dell_code) > 1)
			{
				recv(soc, from, sizeof(from), 0);
				recv(soc, to, sizeof(to), 0);
				recv(soc, distance, sizeof(distance), 0);
				recv(soc, type, sizeof(type), 0);
				recv(soc, volume, sizeof(volume), 0);
				recv(soc, sweight, sizeof(sweight), 0);
				recv(soc, sprice, sizeof(sprice), 0);
				weight = atof(sweight);
				price = atof(sprice);
				printf("|%3d|%8s|%16s|%16s|%14s|%15s|%12.1f|%12s|%14.1f|\n", n, dell_code, from, to, distance, type, weight, volume, price);
				cout << "+---+--------+----------------+----------------+--------------+---------------+------------+------------+--------------+\n";
				n++;
			}
			else break;
		}

		cout << "Выберите строку для удаления: ";
		cin.getline(buf, 100);
		if (atoi(buf) <= n && atoi(buf) > 0)
		{
			send(soc, buf, sizeof(buf), 0);
		}
		else
		{
			cout << "Такого номера нет!";
		}
	}
	else
	{
		cout << "Файл пустой!";
	}
}

void Update(SOCKET soc, int interf)
{
	char buf[100], prov[100];
	int n = 1;
	bool provforcin = true;

	system("cls");

	cout << "+---+--------+--------------+--------------+--------------+---------------+--------------+--------------+--------------+\n";
	cout << "| № |  Код   |    Откуда    |     Куда     |   Дистанция  |      Тип      |      Вес     |     Объем    |     Цена     |\n";
	cout << "+---+--------+--------------+--------------+--------------+---------------+--------------+--------------+--------------+\n";
	char dell_code[100], from[100], to[100], distance[100], type[100], volume[100], sweight[100], sprice[100];
	double weight, price;
	while (true)
	{
		recv(soc, dell_code, sizeof(dell_code), 0);
		if (strlen(dell_code) > 1)
		{
			recv(soc, from, sizeof(from), 0);
			recv(soc, to, sizeof(to), 0);
			recv(soc, distance, sizeof(distance), 0);
			recv(soc, type, sizeof(type), 0);
			recv(soc, volume, sizeof(volume), 0);
			recv(soc, sweight, sizeof(sweight), 0);
			recv(soc, sprice, sizeof(sprice), 0);
			weight = atof(sweight);
			price = atof(sprice);
			printf("|%8s|%16s|%16s|%15s|%15s|%13.1f|%13s|%15.1f|\n", dell_code, from, to, distance, type, weight, volume, price);
			cout << "+--------+--------------+--------------+---------------+---------------+---------------+---------------+---------------+\n";
			n++;
		}
		else break;
	}
	*buf = '\0';
	cout << "Выберите строку для изменения: ";
	cin.getline(buf, 100);
	send(soc, buf, sizeof(buf), 0);
	if (atoi(buf) <= n && atoi(buf) > 0)
	{
		if (interf == 1)
		{
			do
			{
				*dell_code = '\0';
				cout << "Введите новый код маршрута: ";
				cin.getline(dell_code, 100);
				if (!(atoi(dell_code) > 0) && !(atoi(dell_code) <= 999999)) provforcin = false;
			} while (!provforcin);
			send(soc, dell_code, sizeof(dell_code), 0);
		}
		else if (interf == 2)
		{
			do
			{
				cout << "Введите место погрузки: ";
				cin.getline(from, 100);
				cout << "Введите место доставки: ";
				cin.getline(to, 100);
				cout << "Введите растояние: ";
				cin.getline(distance, 100);
				if (!(atoi(distance) > 0) && !(atoi(distance) <= 999999)) provforcin = false;
			} while (!provforcin);
			send(soc, from, sizeof(from), 0);
			send(soc, to, sizeof(to), 0);
			send(soc, distance, sizeof(distance), 0);
		}
		else if (interf == 3)
		{
			do
			{
				cout << "Введите объем в кубических метрах: ";
				cin.getline(volume, 100);
				if (!(atoi(volume) > 0) && !(atoi(volume) <= 999999)) provforcin = false;
				cout << "Введите вес в тонах: ";
				cin.getline(weight, 100);
				if (!(strtod(weight, NULL) > 0) && !(strtod(weight, NULL) <= 999999)) provforcin = false;
			} while (!provforcin);

			send(soc, volume, sizeof(volume), 0);
			send(soc, weight, sizeof(weight), 0);
		}
	}
	else
	{
		cout << "Такого номера нет!";
	}
}
void UpdateMenu(SOCKET soc)
{
	Menu UpdateMenu;

	UpdateMenu.CreateMenu(3, "Воздушный", "Железнодорожный", "Дорожный");
	{
		UpdateMenu.sub[0].CreateMenu(3, "Код доставки", "Информация о доставке", "Информация о грузе");
		UpdateMenu.sub[1].CreateMenu(3, "Код доставки", "Информация о доставке", "Информация о грузе");
		UpdateMenu.sub[2].CreateMenu(3, "Код доставки", "Информация о доставке", "Информация о грузе");
	}

	bool running = true;
	while (running)
	{
		MenuPtr = &UpdateMenu;

		MenuPtr->SetHeader("Изменить");
		MenuPtr->currentID = "0";
		MenuPtr->ShowMenu();
		MenuPtr->Navigation(&running);

		if (MenuPtr->currentID == "11")
		{
			SendRequest(soc, "1_3" + MenuPtr->currentID);
			Update(soc, 1);
			_getch();
		}
		else if (MenuPtr->currentID == "12")
		{
			SendRequest(soc, "1_3" + MenuPtr->currentID);
			Update(soc, 2);
			_getch();
		}
		else if (MenuPtr->currentID == "13")
		{
			SendRequest(soc, "1_3" + MenuPtr->currentID);
			Update(soc, 3);
			_getch();
		}
		else if (MenuPtr->currentID == "21")
		{
			SendRequest(soc, "1_3" + MenuPtr->currentID);
			Update(soc, 1);
			_getch();
		}
		else if (MenuPtr->currentID == "22")
		{
			SendRequest(soc, "1_3" + MenuPtr->currentID);
			Update(soc, 2);
			_getch();
		}
		else if (MenuPtr->currentID == "23")
		{
			SendRequest(soc, "1_3" + MenuPtr->currentID);
			Update(soc, 3);
			_getch();
		}
		else if (MenuPtr->currentID == "31")
		{
			SendRequest(soc, "1_3" + MenuPtr->currentID);
			Update(soc, 1);
			_getch();
		}
		else if (MenuPtr->currentID == "32")
		{
			SendRequest(soc, "1_3" + MenuPtr->currentID);
			Update(soc, 2);
			_getch();
		}
		else if (MenuPtr->currentID == "33")
		{
			SendRequest(soc, "1_3" + MenuPtr->currentID);
			Update(soc, 3);
			_getch();
		}
	}
}

void main() {
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { return; }
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(1280);
	dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(s, (sockaddr*)&dest_addr, sizeof(dest_addr));

	RegMenu.CreateMenu(1, "Войти"); 
	UserMenu.CreateMenu(5, "Показать", "Поиск", "Сортировка", "Фильтрация", "Выйти из уч.з.");
	{
		UserMenu.sub[3].CreateMenu(3, "По месту погрузки", "По месту доставки", "По типу");

		UserMenu.function[4] = Unreg;
	}
	AdminMenu.CreateMenu(5, "Показать", "Добавить", "Изменить", "Удалить", "Выйти из уч.з.");
	{
		AdminMenu.sub[3].CreateMenu(3, "Воздушный", "Железнодорожный", "Дорожный");
		AdminMenu.function[4] = Unreg;
	}
	
	bool running = true;
	while (running) {
		if (!user.GetStatus() && user.GetSmth()) MenuPtr = &UserMenu;
		else if (!user.GetStatus() && !user.GetSmth()) MenuPtr = &RegMenu;
		else if (user.GetStatus() && user.GetSmth()) MenuPtr = &AdminMenu;

		MenuPtr->currentID = "0";
		MenuPtr->ShowMenu();
		MenuPtr->Navigation(&running);

		if (!user.GetStatus() && !user.GetSmth()) {					//Unreg user or admin
			if (MenuPtr->currentID == "1") {
				SendRequest(s, "0_" + MenuPtr->currentID);
				SendReg(s);
				_getch();
			}
		}
		else if (user.GetStatus() && user.GetSmth()) {             //Admin 
			if (MenuPtr->currentID == "1") {
				SendRequest(s, "1_" + MenuPtr->currentID);
				SendShow(s);
				_getch();
			}
			else if (MenuPtr->currentID == "2") {
				SendRequest(s, "1_" + MenuPtr->currentID);
				SendAdd(s);
				_getch();
			}
			else if (MenuPtr->currentID == "3") {
				UpdateMenu(s);
			}
			else if (MenuPtr->currentID == "41") {
				SendRequest(s, "1_" + MenuPtr->currentID);
				Delete(s);
				_getch();
			}
			else if (MenuPtr->currentID == "42") {
				SendRequest(s, "1_" + MenuPtr->currentID);
				Delete(s);
				_getch();
			}
			else if (MenuPtr->currentID == "43") {
				SendRequest(s, "1_" + MenuPtr->currentID);
				Delete(s);
				_getch();
			}
		}
		else if (!user.GetStatus() && user.GetSmth()) {             //User 
			if (MenuPtr->currentID == "1") {
				SendRequest(s, "2_" + MenuPtr->currentID);
				SendShow(s);
				_getch();
			}
			else if (MenuPtr->currentID == "2") {
				SendRequest(s, "2_" + MenuPtr->currentID);
				SendSearch(s);
				_getch();
			}
			else if (MenuPtr->currentID == "3") {
				SendSort(s);
			}
			else if (MenuPtr->currentID == "41") {
				SendRequest(s, "2_" + MenuPtr->currentID);
				SendFiltr(s);
				_getch();
			}
			else if (MenuPtr->currentID == "42") {
				SendRequest(s, "2_" + MenuPtr->currentID);
				SendFiltr(s);
				_getch();
			}
			else if (MenuPtr->currentID == "43") {
				SendRequest(s, "2_" + MenuPtr->currentID);
				SendFiltr(s);
				_getch();
			}
		}
		if (unreg == true) {
			SendRequest(s, "0_0");
			unreg = false;
		}
	}

	closesocket(s);
	WSACleanup();
}