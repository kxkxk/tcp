#include "tcp.h"


int main(int argc, char* argv[]) {
	
	byte data[] = "Hello World!";

	//创建socket
	sclient = creatsocket();
	//连接到服务器
	myconnect();
	//发送消息
	mysend(data);
	//清除socket
	mycleanup();
	system("pause");
	return 0;
}
																										