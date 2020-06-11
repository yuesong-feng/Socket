#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  
int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKET servSock2 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	sockaddr_in sockAddr2;
	memset(&sockAddr2, 0, sizeof(sockAddr2));
	sockAddr2.sin_family = PF_INET;
	sockAddr2.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr2.sin_port = htons(1235);
	bind(servSock2, (SOCKADDR*)&sockAddr2, sizeof(SOCKADDR));

	listen(servSock, 20);
	listen(servSock2, 20);


	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	SOCKET clntSock2 = accept(servSock2, (SOCKADDR*)&clntAddr, &nSize);


	//reveive from 2,send to 1
	while (true) {
		char szBuffer[100] = { 0 };
		recv(clntSock, szBuffer, 100, NULL);
		send(clntSock2, szBuffer, strlen(szBuffer) + sizeof(char), NULL);
	}


	closesocket(clntSock);
	closesocket(servSock);
	closesocket(clntSock2);
	closesocket(servSock2);
	WSACleanup();
	return 0;
}