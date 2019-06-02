#ifndef __TCP__HEADER__
#define __TCP__HEADER__

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS 0
#define PORT 8888
const char* MIP = "66.98.123.124";
#include <WINSOCK2.H>
#include <ws2tcpip.h>
#include <stdio.h>
#include "aes.h"

static SOCKET sclient;
//TODO ����winsock2��̬��ws2_32.lib
#pragma comment(lib,"ws2_32.lib")

void mycleanup() {
	WSACleanup();
}

//TODO �����˷�����Ϣ
// byte* sendData ������Ϣ
void mysend(byte* sendData,size_t len) {
	if (send(sclient, sendData, len, 0) == SOCKET_ERROR) {
		printf("��Ϣ����ʧ��");
	}
	printf("��Ϣ���ͳɹ�!\n");
}

//TODO ���ӵ�����˺���
int myconnect() {
	int err;
	struct sockaddr_in clientService;
	//��������ģʽΪAF_INET,ip4
	clientService.sin_family = AF_INET;
	//��������ip��ַ����ת��
	clientService.sin_addr.s_addr = inet_addr(MIP);
	//�������Ӷ˿�
	clientService.sin_port = htons(PORT);
	//��ʼ����
	err = connect(sclient, (SOCKADDR*)& clientService, sizeof(clientService));
	//������
	if (err == SOCKET_ERROR) {
		printf("����ʧ��%ld\n", WSAGetLastError());
		err = closesocket(sclient);
		if (err == SOCKET_ERROR)
			printf("�ر�����ʧ��\n");
		WSACleanup();
		return 1;
	}
	printf("���ӳɹ�\n");
}

//TODO �����׽��ֺ���������SOCKET
SOCKET creatsocket() {
	//����sock�汾Ϊ2.2
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	int err;
	//�ɽ�������ws2_32.lib
	err = WSAStartup(sockVersion, &wsaData);
	if (err != 0) {
		//����dllʧ��
		printf("����dllʧ�ܣ�������룺%d\n", err);
		return 1;
	}
	//���sockVersion�汾
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		printf("�����ҵ���ʹ�õ� Winsock.dll�汾\n");
		WSACleanup();
		return 1;
	}
	else
		printf("Winsock 2.2 dll ׼�����\n");
	//��ʼ����socket
	//����Ϊ������SOCK_ATREAM
	//���ô���Э��ΪTCP
	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET) {
		printf("����socketʧ��\n");
		return 1;
	}
	printf("�ѽ���socket\n");
	return sclient;
}


#endif // !__TCP__HEADER__
