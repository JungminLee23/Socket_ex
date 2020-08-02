#pragma comment(lib, "ws2_32")

#include<winsock2.h>
#include<ws2def.h>

//���� �Լ� ���� ��� �� ����
void err_quit(const TCHAR *msg) {
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf); // �Ҵ� �� �޸� ��ȯ
	exit(1);
}

int main()
{
	//���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 1;
	MessageBox(NULL, TEXT("���� �ʱ�ȭ ����"), TEXT("�˸�"), MB_OK);

	// socket()
	SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (tcp_sock == INVALID_SOCKET) // ���� ���� ���� �� INVALID_SOCKET�� ��ȯ
		err_quit(TEXT("socket()")); 
	MessageBox(NULL, TEXT("TCP ���� ���� ����"), TEXT("�˸�"), MB_OK);

	// closesocket()
	closesocket(tcp_sock);

	// ���� ����
	WSACleanup();
	return 0;
}



