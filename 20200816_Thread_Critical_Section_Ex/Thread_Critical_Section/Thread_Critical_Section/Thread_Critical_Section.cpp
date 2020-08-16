﻿#include<windows.h>
#include<stdio.h>

#define MAXCNT 100000000
int g_count = 0;

DWORD WINAPI MyThread1(LPVOID arg) {
	for (int i = 0; i < MAXCNT; i++) g_count += 2;
	return 0;
}

DWORD WINAPI MyThread2(LPVOID arg) {
	for (int i = 0; i < MAXCNT; i++) g_count -= 2;
	return 0;
}

int main() {
	//스레드 두 개 생성
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, MyThread1, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, MyThread2, NULL, 0, NULL);
	//스레드 두 개 종료 대기
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	//결과 출력
	printf("g_count = %d\n", g_count);
	return 0;
}
