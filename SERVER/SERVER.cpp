#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <iostream>
#include <cstring>
#include <string>
#include <string.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Classes.h"
#include "Libs.h"

#pragma warning(disable : 4996)

using namespace std;

int numcl = 0;
ifstream Afile;
ifstream Ufile;

vector<Air_Route> air;
vector<Train_Route> train;
vector<Motor_Route> motor;

void Init() {
	vector<Air_Route>::iterator aptr = air.begin();;
	vector<Train_Route>::iterator tptr = train.begin();;
	vector<Motor_Route>::iterator mptr = motor.begin();;
	
	ifstream Air, Train, Motor;

	Air_Route atmp;
	Train_Route ttmp;
	Motor_Route mtmp;

	Air.open("Air.txt", ios::in);
	while (Air) {
		Air >> atmp;
		air.push_back(atmp);
	}
	//air.erase(air.end() - 1);
	Air.close();

	Train.open("Train.txt", ios::in);
	while (Train) {
		Train >> ttmp;
		train.push_back(ttmp);
	}
	//train.erase(train.end() - 1);
	Train.close();

	Motor.open("Motor.txt", ios::in);
	while (Motor) {
		Motor >> mtmp;
		motor.push_back(mtmp);
	}
	//motor.erase(motor.end() - 1);
	Motor.close();
}
void Save() {
	vector<Air_Route>::iterator aptr = air.begin();;
	vector<Train_Route>::iterator tptr = train.begin();;
	vector<Motor_Route>::iterator mptr = motor.begin();;

	ofstream Air, Train, Motor;

	Air.open("Air.txt", ios::out);
	Train.open("Train.txt", ios::out);
	Motor.open("Motor.txt", ios::out);

	for (; aptr != air.end(); aptr++) {
		if (aptr->Get_type() == "Воздушный") Air << *aptr;
	}
	for (; tptr != train.end(); tptr++) {
		if (tptr->Get_type() == "Железнодорожный") Train << *tptr;
	}
	for (; mptr != motor.end(); mptr++) {
		if (mptr->Get_type() == "Дорожный") Motor << *mptr;
	}

	Air.close();
	Train.close();
	Motor.close();
}

void AirAdd(SOCKET s2, char* buf) {
	stringstream ss;
	*buf = '\0';
	string dell_code, from, to, distance, type, volume, weight;
	int bufv, bufw;
	
	recv(s2, buf, 100, 0); type = buf; *buf = '\0';
	recv(s2, buf, 100, 0); type = buf; *buf = '\0';
	recv(s2, buf, 100, 0); dell_code = buf; *buf = '\0';
	recv(s2, buf, 100, 0); from = buf; *buf = '\0';
	recv(s2, buf, 100, 0); to = buf; *buf = '\0';
	recv(s2, buf, 100, 0); distance = buf; *buf = '\0';
	recv(s2, buf, 100, 0); volume = buf; *buf = '\0';
	recv(s2, buf, 100, 0); weight = buf; *buf = '\0';

	ss << volume;
	ss >> bufv;

	ss << weight;
	ss >> bufw;
	
	Air_Route air_rote(bufv, bufw);
	air_rote.Set_type(type);
	air_rote.Set_dell_code(dell_code);
	air_rote.Set_from(from);
	air_rote.Set_to(to);
	air_rote.Set_distance(distance);
	
	air.push_back(air_rote);
}

//void ShowProdAdmin(SOCKET s2, char* buf) {
//	vector<Product>::iterator ptr = arr.begin();
//
//	for (; ptr != arr.end(); ptr++) {
//		char group[100], name[100], cost[100], dealer[100], code[100];
//		ptr->getFields_to_Admin(group, name, cost, code, dealer);
//		send(s2, group, sizeof(group), 0);
//		send(s2, name, sizeof(name), 0);
//		send(s2, cost, sizeof(cost), 0);
//		send(s2, code, sizeof(code), 0);
//		send(s2, dealer, sizeof(dealer), 0);
//	}
//	send(s2, "0", sizeof("0"), 0);
//}
//void ShowProdUser(SOCKET s2, char* buf) {
//	vector<Product>::iterator ptr = arr.begin();
//
//	for (; ptr != arr.end(); ptr++) {
//		char group[100], name[100], cost[100], state[100];
//		ptr->getFields_to_User(group, name, cost);
//		send(s2, group, sizeof(group), 0);
//		send(s2, name, sizeof(name), 0);
//		send(s2, cost, sizeof(cost), 0);
//		if (ptr->isExist()) {
//			strcpy(state, "Есть в наличии");
//		}
//		else if (!ptr->isExist()) {
//			strcpy(state, "Нет в наличии");
//		}
//		send(s2, state, sizeof(state), 0);
//	}
//	send(s2, "0", sizeof("0"), 0);
//}
//void ShowProdWarehouse(SOCKET s2, char* buf) {
//	vector<Product>::iterator ptr = arr.begin();
//
//	for (; ptr != arr.end(); ptr++) {
//		char group[100], name[100], cost[100], dealer[100], code[100], amount[100];
//		ptr->getFields_to_Warehouse(group, name, cost, code, dealer, amount);
//		send(s2, group, sizeof(group), 0);
//		send(s2, name, sizeof(name), 0);
//		send(s2, cost, sizeof(cost), 0);
//		send(s2, code, sizeof(code), 0);
//		send(s2, dealer, sizeof(dealer), 0);
//		send(s2, amount, sizeof(amount), 0);
//	}
//	send(s2, "0", sizeof("0"), 0);
//}

//void SearchProd(SOCKET s2, char* buf) {
//	char str[100];
//	recv(s2, str, sizeof(str), 0);
//	recv(s2, str, sizeof(str), 0);
//
//	vector<Product>::iterator ptr = arr.begin();
//
//	for (; ptr != arr.end(); ptr++) {
//		char group[100], name[100], cost[100], state[100];
//		ptr->getFields_to_User(group, name, cost);
//		if (strstr(group, str) || strstr(name, str)) {
//			send(s2, group, sizeof(group), 0);
//			send(s2, name, sizeof(name), 0);
//			send(s2, cost, sizeof(cost), 0);
//			if (ptr->isExist()) {
//				strcpy(state, "Есть в наличии");
//			}
//			else if (!ptr->isExist()) {
//				strcpy(state, "Нет в наличии");
//			}
//			send(s2, state, sizeof(state), 0);
//		}
//	}
//	send(s2, "\0", sizeof("\0"), 0);
//}
//
//void AdminOrder(SOCKET s2){
//	char buf[100], amount[100];
//	recv(s2, buf, sizeof(buf), 0);
//	recv(s2, buf, sizeof(buf), 0);
//	recv(s2, amount, sizeof(amount), 0);
//	int i = atoi(buf);
//	if (!(i < 0 || i > arr.size())) arr[i].AddAmount(amount);
//}
//
//void AddToCart(SOCKET s2) {
//	char buf[100], amount[100];
//	recv(s2, buf, sizeof(buf), 0);
//	recv(s2, buf, sizeof(buf), 0);
//	recv(s2, amount, sizeof(amount), 0);
//	int i = atoi(buf);
//	if (!(i < 0 || i > arr.size())) {
//		cart.push_back(arr[i]);
//		cart[cart.size() - 1].SetAmount(amount);
//	}
//}
//void ShowCart(SOCKET s2) {
//	vector<Product>::iterator ptr = cart.begin();
//
//	for (; ptr != cart.end(); ptr++) {
//		char group[100], name[100], cost[100], state[100];
//		ptr->getFields_to_User(group, name, cost);
//		send(s2, group, sizeof(group), 0);
//		send(s2, name, sizeof(name), 0);
//		send(s2, cost, sizeof(cost), 0);
//		strcpy(state, ptr->GetAmount().c_str());
//		send(s2, state, sizeof(state), 0);
//	}
//	send(s2, "\0", sizeof("\0"), 0);
//}
//void DeleteCart(SOCKET s2) {
//	char buf[100];
//	recv(s2, buf, sizeof(buf), 0);
//	recv(s2, buf, sizeof(buf), 0);
//	int i = atoi(buf);
//	if (!(i < 0 || i > arr.size())) {
//		cart.erase(cart.begin() + i);
//	}
//}

DWORD WINAPI ThreadFunc(LPVOID client_socket)
{
	Init();

	int num = numcl;
	SOCKET s2 = ((SOCKET*)client_socket)[0];
	char buf[50];
	string _log;
	while (recv(s2, buf, sizeof(buf), 0))
	{
		if (buf[0] == '0') 
		{
			if (!strcmp(buf, "0_0")) cout << "client N-" << numcl << " unauthorised\n";
			else if (!strcmp(buf, "0_1")) {
				bool exist = false;
				char lbuf[100], pbuf[100];
				recv(s2, lbuf, 100, 0);
				recv(s2, lbuf, 100, 0);
				recv(s2, pbuf, 100, 0);

				while (!exist) {
					string log, pass;
					Afile.open("admin.txt", ios::in);
					while (Afile) {
						Afile >> log;
						Afile >> pass;

						if (!strcmp(log.c_str(), lbuf) && !strcmp(pass.c_str(), pbuf)) {
							send(s2, "11", sizeof("11"), 0);
							_log = log;
							cout << "client N-" << num << " authorised like " << "\"" << log << "\"\n" << "";
							exist = true;
							Afile.close();
							break;
						}
					}
					Afile.close();

					if (exist == false) {
						Ufile.open("user.txt", ios::in);
						while (Ufile) {
							Ufile >> log;
							Ufile >> pass;

							if (!strcmp(log.c_str(), lbuf) && !strcmp(pass.c_str(), pbuf)) {
								send(s2, "21", sizeof("21"), 0);
								_log = log;
								cout << "client N-" << num << " authorised like " << "\"" << log << "\"\n" << "";
								exist = true;
								Ufile.close();
								break;
							}
						}
						Ufile.close();
					}

					if (exist == false) {
						send(s2, "00", sizeof("00"), 0);
						cout << "client N-" << num << " failed his authorisation\n";
						exist = true;
					}
				}
			}
		}
		else if (buf[0] == '1') 
		{
		/*	if (!strcmp(buf, "1_1")) AddProd(s2, buf);
			else if (!strcmp(buf, "1_2")) ShowProdAdmin(s2, buf);
			else if (!strcmp(buf, "1_31")) ShowProdWarehouse(s2, buf);
			else if (!strcmp(buf, "1_32")) {
				ShowProdWarehouse(s2, buf);
				AdminOrder(s2);
			}*/
		}
		else if (buf[0] == '2'){
			if (!strcmp(buf, "2_2")) AirAdd(s2, buf);
			
		}
		*buf = '\0';
	}
	
	Save();

	closesocket(s2);
	cout << "client N-" << num << " disconnected\n";

	return 0;
}

void print()
{
	if (numcl) cout << "client N-" << numcl << " connected\n";
	else printf("No clients connected\n");
}

void main() {
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { return; }

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(1280);
	local_addr.sin_addr.s_addr = 0;
	bind(s, (sockaddr*)&local_addr, sizeof(local_addr));
	int c = listen(s, 5);
	cout << "Server receive ready" << endl;
	cout << endl;
	SOCKET client_socket;
	sockaddr_in client_addr;
	int client_addr_size = sizeof(client_addr);
	while ((client_socket = accept(s, (sockaddr*)&client_addr, &client_addr_size))) {
		numcl++;
		print();
		DWORD thID;
		CreateThread(NULL, NULL, ThreadFunc, &client_socket, NULL, &thID);
	}
}