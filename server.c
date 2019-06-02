#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <linux/in.h>
#include <sys/types.h>
#include "../aes.h"
#define PORT 8888
int socketfd, accsocfd;
int creatsocket();
int mybind();
int mylisten();
int myaccept();
byte* myrecv();
byte* key[1024];

input_passwd() {
	printf("input passwd len <= 16:");
	fgets(key, 100, stdin);
	char* r_key = passwd_cpy(key);
	memcpy(key, r_key, 16 * sizeof(char));
	free(r_key);
}

int main(void) {

	input_passwd();

	int recdata;
	//设置接受字符串并清空内存
	byte buf[1024];
	memset(buf, 0x00, sizeof(buf));
	//创建套接字
	socketfd = creatsocket();
	//绑定端口
	mybind();
	//开启监听
	mylisten();

	while (1) {
		//接收请求
		myaccept();
		//接受信息
		size_t recv_len,dec_len;
		byte* mass = decode_data(myrecv(&recv_len),recv_len,key,&dec_len);
		if (mass == NULL) {
			input_passwd();
			free(mass);
			close(accsocfd);
			continue;
		}
		mass = realloc(mass,sizeof(byte) * (dec_len + 1));
		mass[dec_len] = '\0';
		printf("recv_len = %d,dec_len = %d, recvBuf  = [%s]\n",recv_len,dec_len, mass);
		free(mass);
		//关闭连接
		close(accsocfd);
	}
}

//TODO 创建套接字函数，返回SOCKET
int creatsocket() {
	int socketfd;
	//开始创建socket
	//设置为流传输SOCK_ATREAM
	//设置传输协议为TCP
	if (-1 == (socketfd = socket(AF_INET, SOCK_STREAM, 0))) {
		printf("socketfd is created failed!\n");
		return -1;
	};
	printf("socket create success!\n");
	return socketfd;
}
//绑定到网卡
int mybind() {
	struct sockaddr_in s_addr;
	memset(&s_addr, 0x00, sizeof(s_addr));
	//设置连接模式为PF_INET,ip4
	s_addr.sin_family = PF_INET;
	//设置连接端口
	s_addr.sin_port = htons(PORT);
	//设置连接ip限制
	s_addr.sin_addr.s_addr = htons(INADDR_ANY);
	//inet_addr_any 一个服务器可能有多个网卡，随便从中选1个
	if (-1 == bind(socketfd, (struct sockaddr*)&s_addr, sizeof(s_addr))) {
		printf("bind failed!\n");
		return -1;
	}
	printf("bind suc!\n");
}

//监听函数
int mylisten() {
	//开启监听，设置监听间隔
	if (-1 == listen(socketfd, 10)) {
		printf("listen failed!\n");
		return -1;

	}
	printf("listen suc!\n");
}

//获取函数
int myaccept() {
	struct sockaddr_in  r_addr;
	socklen_t len;
	len = sizeof(struct sockaddr);
	accsocfd = accept(socketfd, (struct sockaddr *)&r_addr, &len);
	if (-1 == accsocfd) {
		printf("accept failed!\n");
		return -1;
	}
	printf("accept suc !\nServer get connect from %x port is %x", ntohl(r_addr.sin_addr.s_addr), ntohl(r_addr.sin_port));
}
byte* myrecv(size_t* data_len) {
	byte* recvBufp;
	recvBufp = (char *)malloc(256);
	*data_len = recv(accsocfd, recvBufp, 256, 0);
	if (-1 == *data_len) {
		printf("recv failed!\n");
		return NULL;
	}
	printf("recv suc!\n");
	return recvBufp;
	
}
