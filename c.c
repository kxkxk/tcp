#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS 0
#define PORT 8888
#define MIP "47.105.221.231"
#include <WINSOCK2.H>
#include <ws2tcpip.h>
#include <stdio.h>
SOCKET creatsocket();
void myconnect();
void mysend( char* sendData);
void mycleanup();
SOCKET sclient;
//TODO 引入winsock2动态库ws2_32.lib
#pragma comment(lib,"ws2_32.lib")

int main(int argc, char*argv[]) {

	char data[] = "Hello World!";
	sclient = creatsocket();
	myconnect();
	mysend( &data);
	
	mycleanup();
	system("pause");
}

void mycleanup() {
	WSACleanup();
}

//TODO 向服务端发送信息
// char* sendData 发送信息
void mysend(char* sendData) {
	if (send(sclient, sendData, strlen(sendData), 0) == SOCKET_ERROR) {
		printf("信息发送失败");
	}
	printf("信息发送成功!\n");
}

//TODO 连接到服务端函数
void myconnect() {
	int err;
	struct sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr(MIP);
	clientService.sin_port = htons(PORT);
	err = connect(sclient, (SOCKADDR *)& clientService, sizeof(clientService));
	if (err == SOCKET_ERROR) {
		printf("连接失败%ld\n", WSAGetLastError());
		err = closesocket(sclient);
		if (err == SOCKET_ERROR)
			printf("关闭连接失败\n");
		WSACleanup();
		return 1;
	}
	printf("连接成功\n");
}

//TODO 创建套接字函数，返回SOCKET
SOCKET creatsocket() {
	//设置sock版本为2.2
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	int err;
	//由进程启动ws2_32.lib
	err = WSAStartup(sockVersion, &wsaData);
	if (err != 0) {
		//启动dll失败
		printf("启动dll失败，错误代码：%d\n", err);
		return 1;
	}
	//检查sockVersion版本
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		printf("不能找到可使用的 Winsock.dll版本\n");
		WSACleanup();
		return 1;
	}
	else
		printf("Winsock 2.2 dll 准备完成\n");

	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET) {
		printf("建立socket失败\n");
		return 1;
	}
	printf("已建立socket\n");
	return sclient;
}
																												