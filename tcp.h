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
//TODO 引入winsock2动态库ws2_32.lib
#pragma comment(lib,"ws2_32.lib")

void mycleanup() {
	WSACleanup();
}

//TODO 向服务端发送信息
// byte* sendData 发送信息
void mysend(byte* sendData,size_t len) {
	if (send(sclient, sendData, len, 0) == SOCKET_ERROR) {
		printf("信息发送失败");
	}
	printf("信息发送成功!\n");
}

//TODO 连接到服务端函数
int myconnect() {
	int err;
	struct sockaddr_in clientService;
	//设置连接模式为AF_INET,ip4
	clientService.sin_family = AF_INET;
	//设置连接ip地址，并转形
	clientService.sin_addr.s_addr = inet_addr(MIP);
	//设置连接端口
	clientService.sin_port = htons(PORT);
	//开始连接
	err = connect(sclient, (SOCKADDR*)& clientService, sizeof(clientService));
	//错误处理
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
	//开始创建socket
	//设置为流传输SOCK_ATREAM
	//设置传输协议为TCP
	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET) {
		printf("建立socket失败\n");
		return 1;
	}
	printf("已建立socket\n");
	return sclient;
}


#endif // !__TCP__HEADER__
