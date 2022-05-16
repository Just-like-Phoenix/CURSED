﻿#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <iostream>
#include <cstring>
#include <string>
#include <string.h>
#include <Windows.h>
#include "Menu.h"
#include "Libs.h"

#pragma warning(disable : 4996)

using namespace std;

Menu RegMenu, UserMenu, AdminMenu;
Menu* MenuPtr = &RegMenu;
bool unreg = false;

void Replace(char* buf, char replace, char to) {
	for (int i = 0; i < 60; i++) {
		if (buf[i] == replace) buf[i] = to;
	}
}

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
	string log, pass;

	system("cls");

	cout << "Введите логин: ";
	cin >> log;
	cout << "Введите пароль: ";
	cin >> pass;

	char lbuf[100];
	char pbuf[100];
	char tfbuf[100];

	strcpy(lbuf, log.c_str());
	strcpy(pbuf, pass.c_str());

	send(soc, lbuf, sizeof(lbuf), 0);
	send(soc, pbuf, sizeof(pbuf), 0);

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

void SendAdd(SOCKET soc) {
	Menu menu;
	char buf[100];
	menu.SetHeader("Группа товара");

	menu.CreateMenu(3, "Бакалея", "Консервация", "Масла,уксусы");

	bool running = true;
	while (running) {
		menu.ShowMenu();
		menu.Navigation(&running);

		if (menu.currentID == "1") {
			system("cls");
			send(soc, "Бакалея", sizeof("Бакалея"), 0);
			cout << "Введите код товара: ";
			cin >> buf;
			send(soc, buf, 100, 0); *buf = '\0';
			cout << "Введите название товара: ";
			cin >> buf;
			send(soc, buf, 100, 0); *buf = '\0';
			cout << "Введите стоимость товара: ";
			cin >> buf;
			send(soc, buf, 100, 0); *buf = '\0';
			cout << "Введите поставщика товара: ";
			cin >> buf;
			send(soc, buf, 100, 0); *buf = '\0';

			running = false;
		}
		else if (menu.currentID == "2") {
			system("cls");
			send(soc, "Консервация", sizeof("Консервация"), 0);
			cout << "Введите код товара: ";
			cin >> buf;
			send(soc, buf, 100, 0); *buf = '\0';
			cout << "Введите название товара: ";
			cin >> buf;
			send(soc, buf, 100, 0); *buf = '\0';
			cout << "Введите стоимость товара: ";
			cin >> buf;
			send(soc, buf, 100, 0); *buf = '\0';
			cout << "Введите поставщика товара: ";
			cin >> buf;
			send(soc, buf, 100, 0); *buf = '\0';

			running = false;
		}
		else if (menu.currentID == "3") {
			system("cls");
			send(soc, "Масла,уксусы", sizeof("Масла,уксусы"), 0);
			cout << "Введите код товара: ";
			cin >> buf;
			send(soc, buf, 100, 0); *buf = '\0';
			cout << "Введите название товара: ";
			cin >> buf;
			send(soc, buf, 100, 0); *buf = '\0';
			cout << "Введите стоимость товара: ";
			cin >> buf;
			send(soc, buf, 100, 0); *buf = '\0';
			cout << "Введите поставщика товара: ";
			cin >> buf;
			send(soc, buf, 100, 0); *buf = '\0';

			running = false;
		}
	}
}

void AdminSendShow(SOCKET soc) {
	system("cls");
	cout << "+--------+---------------+--------------------------------------------------+-----+---------------+\n";
	cout << "|   Код  |     Группа    |                     Название                     | Цена|    Постащик   |\n";
	cout << "+--------+---------------+--------------------------------------------------+-----+---------------+\n";
	char group[100], name[100], cost[100], code[100], dealer[100];
	while (true) {
		recv(soc, group, sizeof(group), 0);
		if (strcmp(group, "0")) {
			recv(soc, name, sizeof(name), 0);
			Replace(name, '_', ' ');
			recv(soc, cost, sizeof(cost), 0);
			recv(soc, code, sizeof(code), 0);
			recv(soc, dealer, sizeof(dealer), 0);
			printf("|%8s|%15s|%50s|%5s|%15s|\n", code, group, name, cost, dealer);
			cout << "+--------+---------------+--------------------------------------------------+-----+---------------+\n";
		}
		else break;
	}
}
void UserSendShow(SOCKET soc) {
	system("cls");
	cout << "+---------------+--------------------------------------------------+-----+\n";
	cout << "|     Группа    |                     Название                     | Цена|\n";
	cout << "+---------------+--------------------------------------------------+-----+\n";
	char group[100], name[100], cost[100];
	while (true) {
		recv(soc, group, sizeof(group), 0);
		if (strcmp(group, "0")) {
			recv(soc, name, sizeof(name), 0);
			Replace(name, '_', ' ');
			recv(soc, cost, sizeof(cost), 0);
			printf("|%15s|%50s|%5s|\n", group, name, cost);
			cout << "+---------------+--------------------------------------------------+-----+\n";
		}
		else break;
	}
}
void AdminSendShowWarehouse(SOCKET soc) {
	system("cls");
	cout << "+----+--------+---------------+--------------------------------------------------+-----+---------------+------+\n";
	cout << "|  № |   Код  |     Группа    |                     Название                     | Цена|    Постащик   |Кол-во|\n";
	cout << "+----+--------+---------------+--------------------------------------------------+-----+---------------+------+\n";
	char group[100], name[100], cost[100], code[100], dealer[100], amount[100];
	int i = 1;
	while (true) {
		recv(soc, group, sizeof(group), 0);
		if (strcmp(group, "0")) {
			recv(soc, name, sizeof(name), 0);
			Replace(name, '_', ' ');
			recv(soc, cost, sizeof(cost), 0);
			recv(soc, code, sizeof(code), 0);
			recv(soc, dealer, sizeof(dealer), 0);
			recv(soc, amount, sizeof(amount), 0);
			printf("|%4d|%8s|%15s|%50s|%5s|%15s|%6s|\n", i, code, group, name, cost, dealer, amount);
			cout << "+----+--------+---------------+--------------------------------------------------+-----+---------------+------+\n";
			i++;
		}
		else break;
	}
	_getch();
}

void WarehouseOrder(SOCKET soc) {
	AdminSendShowWarehouse(soc);
}

void SendSearch(SOCKET soc) {
	system("cls");
	bool exist = false;
	char str[100];
	cout << "Поиск: ";
	cin >> str;
	send(soc, str, sizeof(str), 0);
	system("cls");
	cout << "+---------------+--------------------------------------------------+-----+\n";
	cout << "|     Группа    |                     Название                     | Цена|\n";
	cout << "+---------------+--------------------------------------------------+-----+\n";
	char group[100], name[100], cost[100];
	while (true) {
		recv(soc, group, sizeof(group), 0);
		if (strcmp(group, "0")) {
			exist = true;
			recv(soc, name, sizeof(name), 0);
			Replace(name, '_', ' ');
			recv(soc, cost, sizeof(cost), 0);
			printf("|%15s|%50s|%5s|\n", group, name, cost);
			cout << "+---------------+--------------------------------------------------+-----+\n";
		}
		else break;
	}
	if (exist == false) {
		printf("|                         Совпадений не найдено                          |\n");
		printf("+------------------------------------------------------------------------+\n");
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
	UserMenu.CreateMenu(3, "Показать товары", "Поиск", "Выйти из уч.з.");
	{
		UserMenu.function[2] = Unreg;
	}
	AdminMenu.CreateMenu(4, "Добавить наим-ние", "Показать наим-ния", "Склад", "Выйти из уч.з.");
	{
		AdminMenu.sub[2].CreateMenu(2, "Показать товары", "Заказать товар");
		AdminMenu.function[3] = Unreg;
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
			}
			if (MenuPtr->currentID == "2") {
				SendRequest(s, "0_" + MenuPtr->currentID);
				SendReg(s);
			}
			_getch();
		}
		else if (user.GetStatus() && user.GetSmth()) {             //Admin 
			if (MenuPtr->currentID == "1") {
				SendRequest(s, "1_" + MenuPtr->currentID);
				SendAdd(s);
			}
			else if (MenuPtr->currentID == "2") {
				SendRequest(s, "1_" + MenuPtr->currentID);
				AdminSendShow(s);
			}
			else if (MenuPtr->currentID == "31") {
				SendRequest(s, "1_" + MenuPtr->currentID);
				AdminSendShowWarehouse(s);
			}
			else if (MenuPtr->currentID == "32") {
				SendRequest(s, "1_" + MenuPtr->currentID);
				WarehouseOrder(s);
			}
			_getch();
		}
		else if (!user.GetStatus() && user.GetSmth()) {             //User 
			if (MenuPtr->currentID == "1") {
				SendRequest(s, "2_" + MenuPtr->currentID);
				UserSendShow(s);
			}
			if (MenuPtr->currentID == "2") {
				SendRequest(s, "2_" + MenuPtr->currentID);
				SendSearch(s);
			}
			_getch();
		}
		if (unreg == true) {
			SendRequest(s, "0_0");
			unreg = false;
		}
	}

	closesocket(s);
	WSACleanup();
}