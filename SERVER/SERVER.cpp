#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <iostream>
#include <cstring>
#include <string>
#include <string.h>
#include <Windows.h>

#pragma warning(disable : 4996)

using namespace std;

int numcl = 0;

DWORD WINAPI ThreadFunc(LPVOID client_socket)
{
	int num = numcl;
	SOCKET s2 = ((SOCKET*)client_socket)[0];
	char buf[100];
	char buf1[100];
	char lbuf[100];
	char pbuf[100];
	char boolbuf[100];

	while (recv(s2, buf, sizeof(buf), 0))
	{
		
		if (!strcmp(buf, "1")) {
			recv(s2, lbuf, sizeof(lbuf), 0);
			recv(s2, pbuf, sizeof(pbuf), 0);
			if (!strcmp(lbuf, "user") && !strcmp(pbuf, "user"))
			{
				//strcpy(buf1, "���� �������� �������!");
				strcpy(boolbuf, "t");
				//send(s2, buf1, sizeof(buf1), 0);
				send(s2, boolbuf, sizeof(boolbuf), 0);
			}
			else
			{
				//strcpy(buf1, "�������� � �������");
				strcpy(boolbuf, "f");
				//send(s2, buf1, sizeof(buf1), 0);
				send(s2, boolbuf, sizeof(boolbuf), 0);
			}
		}
		else if (!strcmp(buf, "2")) {
			recv(s2, lbuf, sizeof(lbuf), 0);
			recv(s2, pbuf, sizeof(pbuf), 0);
			if (!strcmp(lbuf, "admin") && !strcmp(pbuf, "admin"))
			{
				strcpy(buf1, "���� �������� �������!");
				send(s2, buf1, sizeof(buf1), 0);
			}
			else
			{
				strcpy(buf1, "�������� � �������");
				send(s2, buf1, sizeof(buf1), 0);
			}
		}
		else if (!strcmp(buf, "11")) {
			strcpy(buf1, "�������");
			send(s2, buf1, sizeof(buf1), 0);
		}
		else if (!strcmp(buf, "12")) {
			strcpy(buf1, "�������");
			send(s2, buf1, sizeof(buf1), 0);
		}
		else if (!strcmp(buf, "13")) {
			strcpy(buf1, "������");
			send(s2, buf1, sizeof(buf1), 0);
		}
		else if (!strcmp(buf, "141")) {
			strcpy(buf1, "�������");
			send(s2, buf1, sizeof(buf1), 0);
		}
		else if (!strcmp(buf, "142")) {
			strcpy(buf1, "��������");
			send(s2, buf1, sizeof(buf1), 0);
		}
		else if (!strcmp(buf, "151")) {
			strcpy(buf1, "��������");
			send(s2, buf1, sizeof(buf1), 0);
		}
		else if (!strcmp(buf, "152")) {
			strcpy(buf1, "��������");
			send(s2, buf1, sizeof(buf1), 0);
		}
	}
	
	closesocket(s2);
	cout << "client " << num << " disconnected\n";
	return 0;
}

void print()
{
	if (numcl) printf("%d client connected\n", numcl);
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
	// ��������� ��������� �� �������
	SOCKET client_socket;    // ����� ��� �������
	sockaddr_in client_addr; // ����� ������� (����������� ��������)
	int client_addr_size = sizeof(client_addr);
	// ���� ���������� �������� �� ����������� �� �������
	while ((client_socket = accept(s, (sockaddr*)&client_addr, &client_addr_size))) {
		numcl++;
		print();
		// ����� ������ ������ ��� ������������ �������
		DWORD thID;// thID ������������� ���� DWORD
		CreateThread(NULL, NULL, ThreadFunc, &client_socket, NULL, &thID);
	}
}