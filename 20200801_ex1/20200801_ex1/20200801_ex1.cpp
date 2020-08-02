// 20200801_ex1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#pragma comment(lib, "ws2_32")

#include <iostream>
#include<winsock2.h>


int main()
{
	//윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 1;
	MessageBox(NULL, TEXT("윈속 초기화 성공"), TEXT("알람"), MB_OK);

	WSACleanup();
	return 0;
}
