#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32")

#pragma pack(push, 1)
struct Data
{
	int X;
	int Y;

};
#pragma pack(pop)

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

	char Buffer[1024] = { "Client Connect." };
	int SendBytes = sendto(ServerSocket, Buffer, (int)strlen(Buffer),
		0, (sockaddr*)&ServerSockAddr, sizeof(ServerSockAddr));

	int PlayerX = 0;
	int PlayerY = 0;
	while (true)
	{
		SOCKADDR_IN ClientSockAddr;
		memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));

		Data Packet;

		int ClientSockAddrLength = sizeof(ClientSockAddr);
		recvfrom(ServerSocket, (char*)&Packet, sizeof(Packet), 0, (sockaddr*)&ClientSockAddr, &ClientSockAddrLength);

		PlayerX = ntohl(Packet.X);
		PlayerY = ntohl(Packet.Y);

		system("cls");
		COORD Cur;
		Cur.X = PlayerX;
		Cur.Y = PlayerY;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
		printf("*");
	}


	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}