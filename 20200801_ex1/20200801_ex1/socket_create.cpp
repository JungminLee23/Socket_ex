#pragma comment(lib, "ws2_32")

#include<winsock2.h>
#include<ws2def.h>

//소켓 함수 오류 출력 후 종료
void err_quit(const TCHAR *msg) {
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf); // 할당 된 메모리 반환
	exit(1);
}

int main()
{
	//윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 1;
	MessageBox(NULL, TEXT("윈속 초기화 성공"), TEXT("알림"), MB_OK);

	// socket()
	SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (tcp_sock == INVALID_SOCKET) // 소켓 생성 실패 시 INVALID_SOCKET을 반환
		err_quit(TEXT("socket()")); 
	MessageBox(NULL, TEXT("TCP 소켓 생성 성공"), TEXT("알림"), MB_OK);

	// closesocket()
	closesocket(tcp_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}



