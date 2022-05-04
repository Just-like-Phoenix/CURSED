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

#pragma warning(disable : 4996)

using namespace std;

DWORD WINAPI ThreadFunc(LPVOID client_socket)
{
	SOCKET s2 = ((SOCKET*)client_socket)[0];
	char buf[100];
	while (recv(s2, buf, sizeof(buf), 0))
	{
		if (!strcmp(buf, "0_1")){
			bool exist = false, isAdmin = false;
			char lbuf[100], pbuf[100];
			recv(s2, lbuf, 100, 0);
			recv(s2, pbuf, 100, 0);

			ifstream Afile("admin.txt", ios::in);
		}
		
	}
	
	closesocket(s2);
	return 0;
}

int numcl = 0;

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