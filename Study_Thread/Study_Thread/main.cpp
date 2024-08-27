#include <stdio.h>
#include <process.h>

#include <Windows.h>

int Sum = 0;



//	Dead Lock
//	LOCK 프로그래밍

unsigned __stdcall InCrease(void* Arg)	//	RecvThread..
{

	for (int i=0;i < 90000;++i)
	{
		Sum++;
	}

	return 0;

}

unsigned __stdcall DeCrease(void* Arg)	//	Process.
{

	for (int i = 0; i < 90000; ++i)
	{
		Sum--;
	}

	return 0;

}

//	main Thread
int main()
{



	HANDLE ThreadHandle = (HANDLE)_beginthreadex(nullptr, 0, InCrease, nullptr, 0, nullptr);
	HANDLE ThreadHandle = (HANDLE)_beginthreadex(nullptr, 0, DeCrease, nullptr, 0, nullptr);

	Sleep(90000);

	printf("%d", Sum);
	
	return 0;

}