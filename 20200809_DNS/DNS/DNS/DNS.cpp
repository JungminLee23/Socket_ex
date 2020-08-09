#pragma comment(lib, "ws2_32")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include<tchar.h>
#include <stdio.h>

#define TESTNAME "www.google.com"

// 소켓 함수 오류 출력
void err_display(const TCHAR *msg)
{

	LPVOID * lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL
	);
	_tprintf(_T("[%s]"), msg);
	_tprintf(_T("%s"), (LPCTSTR)lpMsgBuf);// 왜 물음표로 나오는데에에에ㅔ......
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
}

// 도메인 이름 -> IPv4 주소
BOOL GetIPAddr(const char * name, IN_ADDR *addr) {
	HOSTENT *ptr = gethostbyname(name);
	if (ptr == NULL) {
		err_display(TEXT("gethostbyname()"));
		return FALSE;
	}

	if (ptr->h_addrtype != AF_INET) return FALSE;
	memcpy(addr, ptr->h_addr, ptr->h_length);
	return TRUE;
}

// IPv4 주소 -> 도메인 이름
BOOL GetDomainName(IN_ADDR addr, char *name, int namelen) {
	HOSTENT *ptr = gethostbyaddr((const char *)&addr, sizeof(addr), AF_INET);
	if (ptr == NULL) {
		printf("ptr is null\n");
		err_display(TEXT("gethostbyaddr()"));
		return FALSE;
	}

	if (ptr->h_addrtype != AF_INET) return FALSE;
	strncpy_s(name, namelen, ptr->h_name, namelen);
	return TRUE;
}


int main() {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 1;

	printf("도메인 이름(변환 전) = %s\n", TESTNAME);

	//도메인 이름 -> IP주소
	IN_ADDR addr;
	if (GetIPAddr(TESTNAME, &addr)) {
		//성공이면 결과 출력
		printf("IP주소(변환 후) = %s\n", inet_ntoa(addr));

		//IP 주소 -> 도메인 이름
		char name[256];
		if (GetDomainName(addr, name, sizeof(name))) {
			//성공이면 결과 출력
			printf("도메인 이름(다시 변환 후) = %s\n", name);
		}
	}

	WSACleanup();
	return 0;
}