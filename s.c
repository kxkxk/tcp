#include<stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <linux/in.h>
#include <sys/types.h>
#define PORT 8888
int socketfd, accsocfd;
int creatsocket();
int mybind();
int mylisten();
int myaccept();
char* myrecv();


int main(void) {
	int recdata;
	//���ý����ַ���������ڴ�
	char buf[1024];
	memset(buf, 0x00, sizeof(buf));
	//�����׽���
	socketfd = creatsocket();
	//�󶨶˿�
	mybind();
	//��������
	mylisten();

	while (1) {
		//��������
		myaccept();
		//������Ϣ
		char* mass = myrecv();
		printf("recvBuf  = [%s]\n", mass);
		free(mass);
		//�ر�����
		close(accsocfd);
	}
}

//TODO �����׽��ֺ���������SOCKET
int creatsocket() {
	int socketfd;
	//��ʼ����socket
	//����Ϊ������SOCK_ATREAM
	//���ô���Э��ΪTCP
	if (-1 == (socketfd = socket(AF_INET, SOCK_STREAM, 0))) {
		printf("socketfd is created failed!\n");
		return -1;
	};
	printf("socket create success!\n");
	return socketfd;
}
//�󶨵�����
int mybind() {
	struct sockaddr_in s_addr;
	memset(&s_addr, 0x00, sizeof(s_addr));
	//��������ģʽΪPF_INET,ip4
	s_addr.sin_family = PF_INET;
	//�������Ӷ˿�
	s_addr.sin_port = htons(PORT);
	//��������ip����
	s_addr.sin_addr.s_addr = htons(INADDR_ANY);
	//inet_addr_any һ�������������ж��������������ѡ1��
	if (-1 == bind(socketfd, (struct sockaddr*)&s_addr, sizeof(s_addr))) {
		printf("bind failed!\n");
		return -1;
	}
	printf("bind suc!\n");
}

//��������
int mylisten() {
	//�������������ü������
	if (-1 == listen(socketfd, 10)) {
		printf("listen failed!\n");
		return -1;

	}
	printf("listen suc!\n");
}

//��ȡ����
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
char* myrecv() {
	char* recvBufp;
	recvBufp = (char *)malloc(100);
	if (-1 == recv(accsocfd, recvBufp, 100, 0)) {
		printf("recv failed!\n");
		return;
	}
	printf("recv suc!\n");
	return recvBufp;
	
}