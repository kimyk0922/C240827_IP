#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32")

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	SOCKET ServerSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSockAddr.sin_port = htons(13000);

	char Buffer[4096] = { 0, };
	FILE* OutputFile = fopen("image.webp", "wb");

	int RecvBytes = 0;

	int SendBytes = sendto(ServerSocket, Buffer, 0, 0, (sockaddr*)&ServerSockAddr, sizeof(ServerSockAddr));

	do
	{
		int ServerSockAddrLength = sizeof(ServerSockAddr);
		RecvBytes = recvfrom(ServerSocket, Buffer, sizeof(Buffer), 0, (sockaddr*)&ServerSockAddr, &ServerSockAddrLength);

		fwrite(Buffer, sizeof(char), RecvBytes, OutputFile);

	} while (RecvBytes > 0);

	fclose(OutputFile);

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}