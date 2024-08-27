#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

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
	ServerSockAddr.sin_addr.s_addr = INADDR_ANY;
	ServerSockAddr.sin_port = htons(13000);

	bind(ServerSocket, (sockaddr*)&ServerSockAddr, sizeof(ServerSockAddr));

	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
	int ClientSockAddrLength = sizeof(ClientSockAddr);
	char Buffer[1024] = { 0, };
	recvfrom(ServerSocket, Buffer, sizeof(Buffer), 0, (sockaddr*)&ClientSockAddr, &ClientSockAddrLength);

	int PlayerX = 10;
	int PlayerY = 10;
	while (true)
	{
		int KeyCode = _getch();

		switch (KeyCode)
		{
		case 'w':
			PlayerY--;
			break;
		case 's':
			PlayerY++;
			break;
		case 'a':
			PlayerX--;
			break;
		case 'd':
			PlayerX++;
			break;
		}

		system("cls");
		COORD Cur;
		Cur.X = PlayerX;
		Cur.Y = PlayerY;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
		printf("*");

		Data Packet;
		Packet.X = htonl(PlayerX);
		Packet.Y = htonl(PlayerY);

		int SendBytes = sendto(ServerSocket, (char*)&Packet, sizeof(Packet), 0, (sockaddr*)&ClientSockAddr, sizeof(ClientSockAddr));
	}
}