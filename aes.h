#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/stat.h>
#define min(a,b) ((a) < (b) ? (a) : (b))
typedef uint8_t byte;
const byte* file_title = "thepasswdisright"; 
void swap(byte* a,byte* b) {
    byte tmp = *a;
    *a = *b;
    *b = tmp;
}
const byte const_round[10] = {
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36
};
const byte sbox[256] = {
    0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
    0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
    0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
    0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
    0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
    0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
    0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
    0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
    0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
    0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
    0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
    0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
    0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
    0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
    0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
    0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
};
const byte sbox_inv[256] = {
    0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
    0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
    0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
    0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
    0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
    0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
    0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
    0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
    0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
    0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
    0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
    0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
    0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
    0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
    0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
    0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d
};
void print_dword(byte* b) {
    for(int i = 0; i < 4; ++i) {
        printf("%.2x",b[i]);
    }
    printf("\n");
}
void print_cube(byte* b) {
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            printf("%c%.2d",b[i*4+j]," \n"[(j%4) == 0]);
}

void print_ti() {
    static clock_t t1 = 0;
    clock_t t2 = clock();
    printf("time len: %d\n",t2 - t1);
    t1 = t2;
}

byte* key_schedule(const byte* key) {
    byte* w = (byte*)malloc(sizeof(byte) * 4 * 4 * (10 + 1));
    memcpy(w,key,16 * sizeof(byte));
    byte* ptr = w + 16;
    for(int r = 0; r < 10; ++r) {
        ptr[0] = ptr[1 - 4],ptr[1] = ptr[2 - 4],ptr[2] = ptr[3 - 4],ptr[3] = ptr[0 - 4];
        //printf("round %d\n rot: ",(r+1)*4);
        //print_dword(ptr);
        byte s[4];
        for(int i = 0; i < 4; ++i) {
            ptr[i] = sbox[ptr[i]] ^ ptr[i - 16];
            s[i] = sbox[ptr[i]];
            if(i == 0) ptr[i] ^= const_round[r];
        }
        //printf("sbox: ");
        // print_dword(s);
        // printf("res: ");
        // print_dword(ptr);
        for(int i = 0; i < 3; ++i) {
            ptr += 4;
            for(int j = 0; j < 4; ++j) {
                ptr[j] = ptr[j - 4] ^ ptr[j - 16];
            }
            // printf("round %d\nres: ",(r+1)*4 + i + 1);
            // print_dword(ptr);
        }
        ptr += 4;
    }
    return w;
}
void byte_sub(byte* b) {
    for(int i = 0; i < 16; ++i)
    b[i] = sbox[b[i]];
}
void shift_col(byte* b) {
    byte (*(cube[4]))[4] = {(byte(*)[4])(b + 0),(byte(*)[4])(b + 4),(byte(*)[4])(b + 8),(byte(*)[4])(b + 12)};
    for(int i = 1; i < 4; ++i) {
        for(int k = 1; k <= i; ++k)
            for(int j = 0; j < 3; ++j) {
                swap(*(cube[j]) + i,*(cube[j+1]) + i);
            }
    }
}

byte mult2(byte a,int b) {
    // switch(b) {
    //     case 1:
    //         return a;
    //     case 2:
    //         if(a & 0x80) {
    //             a = (a << 1) ^ (0x1b);
    //         } else a <<= 1;
    //         return a;
    //     case 3:
    //         return mult2(a,2) ^ a;
    //     case 4: 
    //         return mult2(mult2(a,2),2);
    //     case 8:
    //         return mult2(mult2(a,4),2);
    //     case 9:
    //         return mult2(a,8) ^ a;
    //     case 11:
    //         return mult2(a,9) ^ mult2(a,2);
    //     case 12:
    //         return mult2(a,4) ^ mult2(a,8);
    //     case 13:
    //         return mult2(a,12) ^ a;
    //     case 14:
    //         return mult2(a,12) ^ mult2(a,2);
    // }
    //right 
    //https://en.wikipedia.org/wiki/Rijndael_MixColumns


    // if(b == 1) return a;
    // if(b == 2) {
    //     if(a & 0x80) {
    //         a = (a << 1) ^ (0x1b);
    //     } else a <<= 1;
    //     return a;
    // }
    // byte tmp = 0;
    // while(b) {
    //     if((b&(-b)) == b) tmp ^= mult2(mult2(a,b>>1),b>>1);
    //     else tmp ^= mult2(a,b&(-b));
    //     b -= b&(-b);
    // }
    // return tmp;
    //overflow? no! you can see https://en.wikipedia.org/wiki/Rijndael_MixColumns
    // return (a<<1)^(0x1B); //b == 2
    //wrong

    static const byte table_2[256] = {
        0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,
        32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,
        64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,
        96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,
        128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,
        160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,
        192,194,196,198,200,202,204,206,208,210,212,214,216,218,220,222,
        224,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,
        27,25,31,29,19,17,23,21,11,9,15,13,3,1,7,5,
        59,57,63,61,51,49,55,53,43,41,47,45,35,33,39,37,
        91,89,95,93,83,81,87,85,75,73,79,77,67,65,71,69,
        123,121,127,125,115,113,119,117,107,105,111,109,99,97,103,101,
        155,153,159,157,147,145,151,149,139,137,143,141,131,129,135,133,
        187,185,191,189,179,177,183,181,171,169,175,173,163,161,167,165,
        219,217,223,221,211,209,215,213,203,201,207,205,195,193,199,197,
        251,249,255,253,243,241,247,245,235,233,239,237,227,225,231,229
    };

    static const byte table_3[256] = {
        0,3,6,5,12,15,10,9,24,27,30,29,20,23,18,17,
        48,51,54,53,60,63,58,57,40,43,46,45,36,39,34,33,
        96,99,102,101,108,111,106,105,120,123,126,125,116,119,114,113,
        80,83,86,85,92,95,90,89,72,75,78,77,68,71,66,65,
        192,195,198,197,204,207,202,201,216,219,222,221,212,215,210,209,
        240,243,246,245,252,255,250,249,232,235,238,237,228,231,226,225,
        160,163,166,165,172,175,170,169,184,187,190,189,180,183,178,177,
        144,147,150,149,156,159,154,153,136,139,142,141,132,135,130,129,
        155,152,157,158,151,148,145,146,131,128,133,134,143,140,137,138,
        171,168,173,174,167,164,161,162,179,176,181,182,191,188,185,186,
        251,248,253,254,247,244,241,242,227,224,229,230,239,236,233,234,
        203,200,205,206,199,196,193,194,211,208,213,214,223,220,217,218,
        91,88,93,94,87,84,81,82,67,64,69,70,79,76,73,74,
        107,104,109,110,103,100,97,98,115,112,117,118,127,124,121,122,
        59,56,61,62,55,52,49,50,35,32,37,38,47,44,41,42,
        11,8,13,14,7,4,1,2,19,16,21,22,31,28,25,26
    };

    static const byte table_4[256] = {
        0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,
        64,68,72,76,80,84,88,92,96,100,104,108,112,116,120,124,
        128,132,136,140,144,148,152,156,160,164,168,172,176,180,184,188,
        192,196,200,204,208,212,216,220,224,228,232,236,240,244,248,252,
        27,31,19,23,11,15,3,7,59,63,51,55,43,47,35,39,
        91,95,83,87,75,79,67,71,123,127,115,119,107,111,99,103,
        155,159,147,151,139,143,131,135,187,191,179,183,171,175,163,167,
        219,223,211,215,203,207,195,199,251,255,243,247,235,239,227,231,
        54,50,62,58,38,34,46,42,22,18,30,26,6,2,14,10,
        118,114,126,122,102,98,110,106,86,82,94,90,70,66,78,74,
        182,178,190,186,166,162,174,170,150,146,158,154,134,130,142,138,
        246,242,254,250,230,226,238,234,214,210,222,218,198,194,206,202,
        45,41,37,33,61,57,53,49,13,9,5,1,29,25,21,17,
        109,105,101,97,125,121,117,113,77,73,69,65,93,89,85,81,
        173,169,165,161,189,185,181,177,141,137,133,129,157,153,149,145,
        237,233,229,225,253,249,245,241,205,201,197,193,221,217,213,209
    };

    static const byte table_8[256] = {
        0,8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,
        128,136,144,152,160,168,176,184,192,200,208,216,224,232,240,248,
        27,19,11,3,59,51,43,35,91,83,75,67,123,115,107,99,
        155,147,139,131,187,179,171,163,219,211,203,195,251,243,235,227,
        54,62,38,46,22,30,6,14,118,126,102,110,86,94,70,78,
        182,190,166,174,150,158,134,142,246,254,230,238,214,222,198,206,
        45,37,61,53,13,5,29,21,109,101,125,117,77,69,93,85,
        173,165,189,181,141,133,157,149,237,229,253,245,205,197,221,213,
        108,100,124,116,76,68,92,84,44,36,60,52,12,4,28,20,
        236,228,252,244,204,196,220,212,172,164,188,180,140,132,156,148,
        119,127,103,111,87,95,71,79,55,63,39,47,23,31,7,15,
        247,255,231,239,215,223,199,207,183,191,167,175,151,159,135,143,
        90,82,74,66,122,114,106,98,26,18,10,2,58,50,42,34,
        218,210,202,194,250,242,234,226,154,146,138,130,186,178,170,162,
        65,73,81,89,97,105,113,121,1,9,17,25,33,41,49,57,
        193,201,209,217,225,233,241,249,129,137,145,153,161,169,177,185
    };

    static const byte table_9[256] = {
        0,9,18,27,36,45,54,63,72,65,90,83,108,101,126,119,
        144,153,130,139,180,189,166,175,216,209,202,195,252,245,238,231,
        59,50,41,32,31,22,13,4,115,122,97,104,87,94,69,76,
        171,162,185,176,143,134,157,148,227,234,241,248,199,206,213,220,
        118,127,100,109,82,91,64,73,62,55,44,37,26,19,8,1,
        230,239,244,253,194,203,208,217,174,167,188,181,138,131,152,145,
        77,68,95,86,105,96,123,114,5,12,23,30,33,40,51,58,
        221,212,207,198,249,240,235,226,149,156,135,142,177,184,163,170,
        236,229,254,247,200,193,218,211,164,173,182,191,128,137,146,155,
        124,117,110,103,88,81,74,67,52,61,38,47,16,25,2,11,
        215,222,197,204,243,250,225,232,159,150,141,132,187,178,169,160,
        71,78,85,92,99,106,113,120,15,6,29,20,43,34,57,48,
        154,147,136,129,190,183,172,165,210,219,192,201,246,255,228,237,
        10,3,24,17,46,39,60,53,66,75,80,89,102,111,116,125,
        161,168,179,186,133,140,151,158,233,224,251,242,205,196,223,214,
        49,56,35,42,21,28,7,14,121,112,107,98,93,84,79,70,
    };

    static const byte table_11[256] = {
        0,11,22,29,44,39,58,49,88,83,78,69,116,127,98,105,
        176,187,166,173,156,151,138,129,232,227,254,245,196,207,210,217,
        123,112,109,102,87,92,65,74,35,40,53,62,15,4,25,18,
        203,192,221,214,231,236,241,250,147,152,133,142,191,180,169,162,
        246,253,224,235,218,209,204,199,174,165,184,179,130,137,148,159,
        70,77,80,91,106,97,124,119,30,21,8,3,50,57,36,47,
        141,134,155,144,161,170,183,188,213,222,195,200,249,242,239,228,
        61,54,43,32,17,26,7,12,101,110,115,120,73,66,95,84,
        247,252,225,234,219,208,205,198,175,164,185,178,131,136,149,158,
        71,76,81,90,107,96,125,118,31,20,9,2,51,56,37,46,
        140,135,154,145,160,171,182,189,212,223,194,201,248,243,238,229,
        60,55,42,33,16,27,6,13,100,111,114,121,72,67,94,85,
        1,10,23,28,45,38,59,48,89,82,79,68,117,126,99,104,
        177,186,167,172,157,150,139,128,233,226,255,244,197,206,211,216,
        122,113,108,103,86,93,64,75,34,41,52,63,14,5,24,19,
        202,193,220,215,230,237,240,251,146,153,132,143,190,181,168,163
    };

    static const byte table_12[256] = {
        0,12,24,20,48,60,40,36,96,108,120,116,80,92,72,68,
        192,204,216,212,240,252,232,228,160,172,184,180,144,156,136,132,
        155,151,131,143,171,167,179,191,251,247,227,239,203,199,211,223,
        91,87,67,79,107,103,115,127,59,55,35,47,11,7,19,31,
        45,33,53,57,29,17,5,9,77,65,85,89,125,113,101,105,
        237,225,245,249,221,209,197,201,141,129,149,153,189,177,165,169,
        182,186,174,162,134,138,158,146,214,218,206,194,230,234,254,242,
        118,122,110,98,70,74,94,82,22,26,14,2,38,42,62,50,
        90,86,66,78,106,102,114,126,58,54,34,46,10,6,18,30,
        154,150,130,142,170,166,178,190,250,246,226,238,202,198,210,222,
        193,205,217,213,241,253,233,229,161,173,185,181,145,157,137,133,
        1,13,25,21,49,61,41,37,97,109,121,117,81,93,73,69,
        119,123,111,99,71,75,95,83,23,27,15,3,39,43,63,51,
        183,187,175,163,135,139,159,147,215,219,207,195,231,235,255,243,
        236,224,244,248,220,208,196,200,140,128,148,152,188,176,164,168,
        44,32,52,56,28,16,4,8,76,64,84,88,124,112,100,104,
    };

    static const byte table_13[256] = {
        0,13,26,23,52,57,46,35,104,101,114,127,92,81,70,75,
        208,221,202,199,228,233,254,243,184,181,162,175,140,129,150,155,
        187,182,161,172,143,130,149,152,211,222,201,196,231,234,253,240,
        107,102,113,124,95,82,69,72,3,14,25,20,55,58,45,32,
        109,96,119,122,89,84,67,78,5,8,31,18,49,60,43,38,
        189,176,167,170,137,132,147,158,213,216,207,194,225,236,251,246,
        214,219,204,193,226,239,248,245,190,179,164,169,138,135,144,157,
        6,11,28,17,50,63,40,37,110,99,116,121,90,87,64,77,
        218,215,192,205,238,227,244,249,178,191,168,165,134,139,156,145,
        10,7,16,29,62,51,36,41,98,111,120,117,86,91,76,65,
        97,108,123,118,85,88,79,66,9,4,19,30,61,48,39,42,
        177,188,171,166,133,136,159,146,217,212,195,206,237,224,247,250,
        183,186,173,160,131,142,153,148,223,210,197,200,235,230,241,252,
        103,106,125,112,83,94,73,68,15,2,21,24,59,54,33,44,
        12,1,22,27,56,53,34,47,100,105,126,115,80,93,74,71,
        220,209,198,203,232,229,242,255,180,185,174,163,128,141,154,151
    };

    static const byte table_14[256] = {
        0,14,28,18,56,54,36,42,112,126,108,98,72,70,84,90,
        224,238,252,242,216,214,196,202,144,158,140,130,168,166,180,186,
        219,213,199,201,227,237,255,241,171,165,183,185,147,157,143,129,
        59,53,39,41,3,13,31,17,75,69,87,89,115,125,111,97,
        173,163,177,191,149,155,137,135,221,211,193,207,229,235,249,247,
        77,67,81,95,117,123,105,103,61,51,33,47,5,11,25,23,
        118,120,106,100,78,64,82,92,6,8,26,20,62,48,34,44,
        150,152,138,132,174,160,178,188,230,232,250,244,222,208,194,204,
        65,79,93,83,121,119,101,107,49,63,45,35,9,7,21,27,
        161,175,189,179,153,151,133,139,209,223,205,195,233,231,245,251,
        154,148,134,136,162,172,190,176,234,228,246,248,210,220,206,192,
        122,116,102,104,66,76,94,80,10,4,22,24,50,60,46,32,
        236,226,240,254,212,218,200,198,156,146,128,142,164,170,184,182,
        12,2,16,30,52,58,40,38,124,114,96,110,68,74,88,86,
        55,57,43,37,15,1,19,29,71,73,91,85,127,113,99,109,
        215,217,203,197,239,225,243,253,167,169,187,181,159,145,131,141
    };

    if(b == 1) return a;
    if(b == 2) return table_2[a];
    if(b == 3) return table_3[a];
    if(b == 4) return table_4[a];
    if(b == 8) return table_8[a];
    if(b == 9) return table_9[a];
    if(b == 11) return table_11[a];
    if(b == 12) return table_12[a];
    if(b == 13) return table_13[a];
    if(b == 14) return table_14[a];
}

void mix_col(byte* b) {
    static const byte cubeB[16] = {2,3,1,1,1,2,3,1,1,1,2,3,3,1,1,2};
    // for(int i = 0; i < 4; ++i) {
    //     gmix_column(b + i * 4);
    // }
    byte w[16];
    memcpy(w,b,sizeof(byte) * 4 * 4);
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            b[i * 4 + j] = mult2(w[4 * i + 0],cubeB[j * 4 + 0]) ^ mult2(w[4 * i + 1],cubeB[j * 4 + 1]) 
                         ^ mult2(w[4 * i + 2],cubeB[j * 4 + 2]) ^ mult2(w[4 * i + 3],cubeB[j * 4 + 3]);
        }
    }
}

byte* aes_128_encode(byte* input,byte* key) {
    byte* round_key = key_schedule(key),*key_ptr = round_key;
    byte* result = (byte*)malloc(sizeof(byte) * 4 * 4);
    for(int i = 0; i < 16; ++i)
        result[i] = input[i] ^ key_ptr[i];
    
    for(int i = 0; i < 9; ++i) {
        key_ptr += 16;
        byte_sub(result);
        shift_col(result);
        mix_col(result);
        for(int i = 0; i < 16; ++i)
            result[i] = result[i] ^ key_ptr[i];
    }

    key_ptr += 16;
    byte_sub(result);
    shift_col(result);
    for(int i = 0; i < 16; ++i)
        result[i] = result[i] ^ key_ptr[i];
    free(round_key);
    return result;
}

void byte_sub_inv(byte* b) {
    for(int i = 0; i < 16; ++i)
    b[i] = sbox_inv[b[i]];
}

void shift_col_inv(byte* b) {
    byte (*(cube[4]))[4] = {(byte(*)[4])(b + 0),(byte(*)[4])(b + 4),(byte(*)[4])(b + 8),(byte(*)[4])(b + 12)};
    for(int i = 1; i < 4; ++i) {
        for(int k = 1; k <= i; ++k)
            for(int j = 2; j >= 0; --j) {
                swap(*(cube[j]) + i,*(cube[j+1]) + i);
            }
    }
}

void mix_col_inv(byte* b) {
    static const byte cubeB[16] = {
        14,11,13,9,
        9,14,11,13,
        13,9,14,11,
        11,13,9,14
    };
    // for(int i = 0; i < 4; ++i) {
    //     gmix_column(b + i * 4);
    // }
    byte w[16];
    memcpy(w,b,sizeof(byte) * 4 * 4);
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            b[i * 4 + j] = mult2(w[4 * i + 0],cubeB[j * 4 + 0]) ^ mult2(w[4 * i + 1],cubeB[j * 4 + 1]) 
                         ^ mult2(w[4 * i + 2],cubeB[j * 4 + 2]) ^ mult2(w[4 * i + 3],cubeB[j * 4 + 3]);
        }
    }
}

typedef struct _byte {
    byte* p;
    size_t count;
} _byte;

byte* aes_128_decode(byte* input,byte* key) {
    byte* round_key = key_schedule(key),*key_ptr = round_key + 160;
    byte* result = (byte*)malloc(sizeof(byte) * 4 * 4);


    for(int i = 0; i < 16; ++i)
        result[i] = input[i] ^ key_ptr[i];
    shift_col_inv(result);
    byte_sub_inv(result);

    for(int i = 0; i < 9; ++i) {
        key_ptr -= 16;
        for(int i = 0; i < 16; ++i)
            result[i] = result[i] ^ key_ptr[i];
        mix_col_inv(result);
        shift_col_inv(result);
        byte_sub_inv(result);
    }

    key_ptr -= 16;
    
    for(int i = 0; i < 16; ++i)
        result[i] = result[i] ^ key_ptr[i];
    free(round_key);
    return result;
}

size_t get_file_size(FILE* fp) {
    size_t pos = ftell(fp);
    fseek(fp,0,SEEK_END);
    size_t res = ftell(fp);
    fseek(fp,pos,SEEK_SET);
    return res;
}

// unsigned long long get_file_size2(char* filename)
// {
//     struct stat statbuf;
//     stat(filename,&statbuf);
//     unsigned long long size = statbuf.st_size;
//     return size;
// }

byte* encode_data(byte* data,size_t len,byte *key,size_t* enc_len) {
    size_t total = 16;
    // size_t file_size;
    // byte* enc_file = (byte*)malloc(sizeof(byte)*);
    byte part_16[16];
	byte* encData = NULL;
    //write file_title
    memcpy(part_16,file_title,sizeof(byte) * 16);

    byte* enc = aes_128_encode(part_16,key);
	encData = realloc(encData, total * sizeof(byte));
	memcpy(encData, enc, sizeof(byte) * 16);
	//fwrite(enc,sizeof(byte),16,sp);
    free(enc);
	byte* data_ptr = data;
    int fixed = 0;
    //printf("pos is:%d\n",ftell(fp));
    while(data_ptr < data + len) {
        //printf("pos is:%d\n",ftell(fp));
		size_t part_cnt = min(16, data + len - data_ptr);
		
		memcpy(part_16, data_ptr, sizeof(byte) * part_cnt);
		data_ptr += part_cnt;

		byte contain_num = 16 - part_cnt;
        while(part_cnt < 16) {
            fixed = 1;
            part_16[part_cnt] = contain_num;
            ++part_cnt;
        }

        total += part_cnt;
        if(total % (1024*1024) == 0 && total != 0)
            printf("now is %d MiB\n",total / 1024 / 1024);
        //print_ti();
        enc = aes_128_encode(part_16,key);
        // printf("jiange ");
        // print_ti();
		encData = realloc(encData, total * sizeof(byte));
		memcpy(encData + total - part_cnt, enc, sizeof(byte) * part_cnt);
		//fwrite(enc,sizeof(byte),16,sp);
        
		// byte* tail = enc_file + total - cnt;
        // memcpy(tail,enc,sizeof(byte)*cnt);
        free(enc);
    }
    if(!fixed) {
        //printf("pos is:%d\n",ftell(fp));
        total += 16;
        for(int i = 0; i < 16; ++i) 
            part_16[i] = 16;
        byte* enc = aes_128_encode(part_16,key);
        //fwrite(enc,sizeof(byte),16,sp);
		encData = realloc(encData, total * sizeof(byte));
		memcpy(encData + total - 16, enc, sizeof(byte) * 16);
		// enc_file = realloc(enc_file,sizeof(byte)*total);
        // byte* tail = enc_file + total - 16;
        // memcpy(tail,enc,sizeof(byte)*16);
        free(enc);
        //printf("pos is:%d\n",ftell(fp));
    }

	*enc_len = total;
	return encData;
    //return (_byte){enc_file,total};
}

int passwd_right(byte* ft) {
    for(int i = 0; i < 16; ++i) 
        if(ft[i] != file_title[i]) return 0;
    return 1;
}

byte* decode_data(byte* data,size_t len,byte* key,size_t* dec_len) {
    size_t total = 0,part_cnt;
	byte* decData = NULL,*data_ptr = data;
	if (len < 16 || dec_len == NULL) return NULL;
    // byte* dec_file = NULL;
    byte part_16[16];
	memcpy(part_16, data_ptr, 16 * sizeof(byte));
	data_ptr += 16;
	//fread(part_16,sizeof(byte),16,fp);
    byte* dec = aes_128_decode(part_16,key);
    if(!passwd_right(dec)) return NULL;
    free(dec);
    //printf("pos is:%d\n",ftell(fp));
    while(data_ptr < data + len) {
        //fseek(fp,cnt,SEEK_CUR);
        //printf("pos is:%d\n",ftell(fp));
        //print_ti();
		part_cnt = min(16, data + len - data_ptr);
		memcpy(part_16, data_ptr, sizeof(byte) * part_cnt);
		data_ptr += part_cnt;

        dec = aes_128_decode(part_16,key);
        // printf("jiange ");
        // print_ti();
        // if(total == 1792)
        // printf("aaa");
        
        
        if(total % (1024*1024) == 0 && total != 0)
            printf("now is %d MiB\n",total / 1024 / 1024);
        
        if(data_ptr == data + len) {
			part_cnt -= dec[15];
        }

		total += part_cnt;
		decData = realloc(decData, total * sizeof(byte));
		memcpy(decData + total - part_cnt, dec, part_cnt * sizeof(byte));
        //fwrite(dec,sizeof(byte),cnt,sp);
        // dec_file = realloc(dec_file,sizeof(byte)*total);
        // byte* tail = dec_file + total - 16;
        // memcpy(tail,dec,sizeof(byte)*16);
        free(dec);
    }
	*dec_len = total;
    return decData;
    // clearerr(fp);
    //  if(fread(part_16,sizeof(byte),16,fp)) printf("ok");
    //return (_byte){dec_file,total};
}

char* passwd_cpy(char* src) {
	int str_len = strlen(src);
	int len = min(str_len, 16);
	char* passwd = malloc(sizeof(byte) * 16);
	memcpy(passwd, src, sizeof(byte) * len);
	for (int i = 0; len < 16; i = (i + 1) % str_len) {
		passwd[len++] = src[i];
	}
	return passwd;
}

// int main() {
//     // byte val[16] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
//     // byte key[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
//     // byte s[16] = {
//     //     0x63 ,0x53 ,0xe0 ,0x8c ,0x09 ,0x60 ,0xe1 ,0x04 ,0xcd ,0x70 ,0xb7 ,0x51 ,0xba ,0xca ,0xd0 ,0xe7
//     // };
//     // byte v[20],keys[20];
//     // fgets(v,sizeof v,stdin);
//     // fgets(keys,sizeof keys,stdin);
//     // v[16] = '\0';

//     // mix_col(s);
//     // for(int i = 0; i < 4; ++i)
//     //     print_dword(s + i * 4);
//     // printf("\n");

//     // mix_col_inv(s);
//     // for(int i = 0; i < 4; ++i)
//     //     print_dword(s + i * 4);
//     // byte* ans = key_schedule(key);
//     // for(int i = 0; i < 176; i += 4) {
//     //     print_dword(ans + i);
//     // }

//     // byte* encode = aes_128_encode(v,keys);
//     // encode[16] = '\0';
//     // printf("%s",encode);
//     // printf("\n");
//     // FILE* p;
//     // byte* decode = aes_128_decode(encode,keys);
//     // decode[16] = '\0';
//     // printf("%s",decode);

//     //byte k[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
//     // shift_col(k);
//     // for(int i = 0; i < 4; ++i) {
//     //     for(int j = 0; j < 4; ++j)
//     //         printf("%.2d",k[i*4 + j]);
//     //     printf("\n");
//     // }
//     // printf("\n");
//     // shift_col_inv(k);
//     //     for(int i = 0; i < 4; ++i) {
//     //     for(int j = 0; j < 4; ++j)
//     //         printf("%.2d",k[i*4 + j]);
//     //     printf("\n");
//     // }

//     // FILE* fp = fopen("csd.in","r");
//     // FILE* sp = fopen("b.txt","wb");
//     // _byte x = encode_file(fp,"i love you two!!");
//     // printf("pos is:%d\n",ftell(sp));
//     // fwrite(x.p,sizeof(byte),x.count,sp);
//     // printf("pos is:%d\n",ftell(sp));
//     // fclose(sp);
//     // fflush(sp);

//     // FILE* fp = fopen("b.txt","rb");
    
//     // FILE* sp = fopen("c.txt","w");
//     // _byte x = decode_file(fp,"i love you two!!");
//     // fwrite(x.p,sizeof(byte),x.count,sp);
//     // fclose(sp);
//     // fflush(sp);

//     // FILE* sp = fopen("b.txt","w");
//     // byte x[16] = {16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16};
//     // byte* enc = aes_128_encode(x,"1234567890123456");
//     // fwrite(enc,sizeof(byte),16,sp);
//     // fclose(sp);
//     // fflush(sp);
//     // FILE* fp = fopen("b.txt","r");
//     // fread(x,sizeof(byte),16,fp);
//     // byte* dec = aes_128_decode(x,"1234567890123456");
//     // sp = fopen("c.txt","w");
//     // fwrite(dec,sizeof(byte),16,sp);
//     // fclose(sp);
//     // fflush(sp);
//     return 0;
// }
