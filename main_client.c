#define _CRT_SECURE_NO_WARNINGS
#include "tcp.h"

char key[100];
byte data[1024];
int main(int argc, char* argv[]) {
	printf("input ip addr:");
	scanf("%s", MIP);
	printf("input passwd len <= 16:");
	scanf("%s", key);
	char* r_key = passwd_cpy(key);
	memcpy(key, r_key, 16 * sizeof(char));
	free(r_key);
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

	while (1) {
		printf("input your value:\n");
		scanf("%s", data);
		size_t len = strlen(data);
		size_t enc_len;
		byte* enc_data = encode_data(data, len, key, &enc_len);
		printf("enc_len = %d\n", enc_len);
	    //创建socket
		sclient = creatsocket();
		//连接到服务器
		myconnect();
		//发送消息
		mysend(enc_data,enc_len);
		//清除socket
		mycleanup();
		free(enc_data);
	}
	
	system("pause");
	return 0;
}
																										