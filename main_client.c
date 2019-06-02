#include "tcp.h"

char key[100];
byte data[] = "Hello World!";
int main(int argc, char* argv[]) {
	
	printf("input passwd len <= 16:");
	fgets(key, 100, stdin);
	char* r_key = passwd_cpy(key);
	memcpy(key, r_key, 16 * sizeof(char));
	free(r_key);
	size_t enc_len;
	byte* enc_data = encode_data(data, 16, key, &enc_len);
	/*
	char* r_key = passwd_cpy(key);
	memcpy(key, r_key, 16 * sizeof(char));
	free(r_key);
	size_t len = strlen(data);
	size_t t;
	byte* enc = encode_data(data, len, key,&t);
	byte* dec = decode_data(enc, t, key, &len);
	dec = malloc((len + 1) * sizeof(byte));
	dec[len] = '\0';
	printf("%s", data);
	system("pause");*/

	
	//创建socket
	sclient = creatsocket();
	//连接到服务器
	myconnect();
	//发送消息
	mysend(enc_data,enc_len);
	//清除socket
	mycleanup();
	system("pause");
	return 0;
}
																										