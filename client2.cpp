#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <conio.h>
#include<thread>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
void Recv(int);
void Send(int);
int main() {
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	Send(1234);


	//终止使用 DLL
	WSACleanup();

	system("pause");
	return 0;
}
void Recv(int port) {
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//向服务器发起请求
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(port);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	while (true) {
		char szBuffer[100] = { 0 };
		recv(sock, szBuffer, 100, NULL);
		printf("Message form client: %s\n", szBuffer);
	}
	closesocket(sock);
}
void Send(int port) {
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//向服务器发起请求
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(port);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	while (true) {
		char a[100] = { 0 };
		//if (_kbhit()) {
			scanf("%s", a);
			send(sock, a, strlen(a) + sizeof(char), NULL);
		//}
	}
	closesocket(sock);
}
