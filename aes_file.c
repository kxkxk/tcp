#include "aes.h"
#include <string.h>
#define min(a,b) ((a < b) ? (a) : (b))


const char* usage = "uasge:\ndecrypt: ./aes_file 1 input_filename output_filename your_password(len <= 16)\nencrypt: ./aes_file 2 input_filename output_filename your_password(len <= 16)";
int main(int argc,char** argv) {
    if(argc != 5) { puts(usage); return 0; }
    if(strcmp(argv[1],"1") == 0) {
		FILE fp,sp;
        fopen_s(&fp,argv[2],"rb");
        fopen_s(&sp,argv[3],"wb");
        char* passwd = passwd_cpy(argv[4]);
        encode_file(&fp,&sp,passwd);
        puts("end.");
    } else if(strcmp(argv[1],"2") == 0) {
		FILE fp, sp;
        fopen_s(&fp,argv[2],"rb");
        fopen_s(&sp,argv[3],"wb");
        char* passwd = passwd_cpy(argv[4]);
        if(!decode_file(&fp,&sp,passwd)) puts("passwd error!"); 
        puts("end.");
    }
    
    return 0;
}