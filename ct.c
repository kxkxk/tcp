#include <stdio.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")
#define Port 8888
#define IP_ADDRESS "47.105.221.231"

int main(int argc, char* argv[]) // argc���������ܵĲ�������
{

	WSADATA s; // �����������AfxSocketInitȫ�ֺ������ص�Windows Sockets��ʼ����Ϣ
	SOCKET ClientSocket;
	struct sockaddr_in ClientAddr; // һ��sockaddr_in�͵Ľṹ�����
	int ret = 0;
	char SendBuffer[MAX_PATH];   // Windows��MAX_PATHĬ����260

	// ��ʼ��Windows Socket
	// WSAStartup������Winsock����ĳ�ʼ��
	if (WSAStartup(MAKEWORD(2, 2), &s) != 0) // ͨ�����������������޷��Ų���,�׸�����Ϊ���ֽ�
	{
		printf("Init Windows Socket Failed! Error: %d\n", GetLastError());
		getchar();
		return -1;
	}

	while (1)
	{
		// ����һ���׽ӿ�
		// �������һ���׽ӿ���connect()��һ��ָ���˿�����
		// �����send()��recv()��ö˿ڽ������ݱ��ķ��������
		// ���Ự�����󣬵���closesocket()
		ClientSocket = socket(AF_INET, // ֻ֧��ARPA Internet��ַ��ʽ
			SOCK_STREAM, // ���׽ӿڵ���������
			IPPROTO_TCP); // �׽ӿ����õ�Э��
		if (ClientSocket == INVALID_SOCKET)
		{
			printf("Create Socket Failed! Error: %d\n", GetLastError());
			getchar();
			return -1;
		}

		ClientAddr.sin_family = AF_INET;
		ClientAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS); // ����IP��ַ
		ClientAddr.sin_port = htons(Port); // ���������޷��Ŷ�������ת���������ֽ�˳��
		memset(ClientAddr.sin_zero, 0X00, 8); // ����ͨ��Ϊ��������ڴ�����ʼ������

		// ����Socket
		ret = connect(ClientSocket,
			(struct sockaddr*)&ClientAddr,
			sizeof(ClientAddr));
		if (ret == SOCKET_ERROR)
		{
			printf("Socket Connect Failed! Error:%d\n", GetLastError());
			getchar();
			return -1;
		}
		else
		{
			printf("Socket Connect Succeed!");
		}

		printf("Input Data: ");
		while (1)
		{
			scanf_s("%s", &SendBuffer);

			// ����������������
			ret = send(ClientSocket,
				SendBuffer,
				(int)strlen(SendBuffer), // ���ط��ͻ��������ݳ���
				0);

			if (ret == SOCKET_ERROR)
			{
				printf("Send Information Failed! Error:%d\n", GetLastError());
				getchar();
				break;
			}

			break;
		}

		// �ر�socket
		closesocket(ClientSocket);
		if (SendBuffer[0] == 'q') // �趨�����һ���ַ�Ϊqʱ�˳�
		{
			printf("Quit!\n");
			break;
		}

	}
	WSACleanup();
	getchar();
	return 0;
}