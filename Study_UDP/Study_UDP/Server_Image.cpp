#include<WinSock2.h>
#include<stdio.h>
#include<stdlib.h>

#pragma comment(lib, "ws2_32");


int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	SOCKET ServerSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_addr.s_addr = INADDR_ANY;
	ServerSockAddr.sin_port = htons(13000);

	bind(ServerSocket, (sockaddr*)&ServerSockAddr, sizeof(ServerSockAddr));

	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
	int ClientSockAddrLength = sizeof(ClientSockAddr);

	char Buffer[4096] = { 0, };
	FILE* InputFile = fopen("Diablo.jpg", "rb");

	int ReadBytes = 0;

	int RecvBytes = recvfrom(ServerSocket, Buffer, sizeof(Buffer), 0, (sockaddr*)&ClientSockAddr, &ClientSockAddrLength);

	do
	{
		ReadBytes = fread(Buffer, sizeof(char), sizeof(Buffer), InputFile);

		int SendBytes = sendto(ServerSocket, Buffer, ReadBytes, 0, (sockaddr*)&ClientSockAddr, sizeof(ClientSockAddr));
	} while (ReadBytes > 0);

	int SendBytes = sendto(ServerSocket, Buffer, 0, 0, (sockaddr*)&ClientSockAddr, sizeof(ClientSockAddr));

	fclose(InputFile);
	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}