#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

using namespace std;

static const unsigned int sbox[256] = {

    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

 static const unsigned int Inverse_sbox[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
 };

static const int rcon[10] = {
    0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000
};

void Subbytes(unsigned char* block) {
    for (int i = 0; i<16; i++)
        block[i] = sbox[block[i]];
}

void Inverse_Subbytes(unsigned char* block) {
    for (int i = 0; i<16; i++)
        block[i] = Inverse_sbox[block[i]];
}

void Copy(unsigned char* A, unsigned char* B) {
    for (int i = 0; i < 16; i++)
        A[i] = B[i];
}

void ShiftRows(unsigned char* block) {
    unsigned char A[16];
    Copy(A, block);

    block[0] = A[0];
    block[4] = A[4];
    block[8] = A[8];
    block[12] = A[12];

    block[1] = A[5];
    block[5] = A[9];
    block[9] = A[13];
    block[13] = A[1];

    block[2] = A[10];
    block[6] = A[14];
    block[10] = A[2];
    block[14] = A[6];

    block[3] = A[15];
    block[7] = A[3];
    block[11] = A[7];
    block[15] = A[11];
}

void Inverse_ShiftRows(unsigned char* block) {
    unsigned char A[16];
    Copy(A, block);

    block[0] = A[0];
    block[4] = A[4];
    block[8] = A[8];
    block[12] = A[12];

    block[1] = A[13];
    block[5] = A[1];
    block[9] = A[5];
    block[13] = A[9];

    block[2] = A[10];
    block[6] = A[14];
    block[10] = A[2];
    block[14] = A[6];

    block[3] = A[7];
    block[7] = A[11];
    block[11] = A[15];
    block[15] = A[3];
}

#define MUL2(a)    (a << 1) ^ (a & 0x80 ? 0x1b : 0)
#define MUL3(a)    MUL2(a) ^ a
#define MUL4(a)    MUL2( MUL2(a) )
#define MUL8(a)    MUL2( MUL2( MUL2(a)))
#define MUL9(a)    MUL8(a) ^ a
#define MULB(a)    MUL8(a) ^ MUL2(a) ^ a
#define MULD(a)    MUL8(a) ^ MUL4(a) ^ a
#define MULE(a)    MUL8(a) ^ MUL4(a) ^ MUL2(a)

void Mixcolumn(unsigned char* block) {
    unsigned char tmp[16];

    tmp[0] = MUL2(block[0]) ^ MUL3(block[1]) ^ block[2] ^ block[3];
    tmp[1] = block[0] ^ MUL2(block[1]) ^ MUL3(block[2]) ^ block[3];
    tmp[2] = block[0] ^ block[1] ^ MUL2(block[2]) ^ MUL3(block[3]);
    tmp[3] = MUL3(block[0]) ^ block[1] ^ block[2] ^ MUL2(block[3]);

    tmp[4] = MUL2(block[4]) ^ MUL3(block[5]) ^ block[6] ^ block[7];
    tmp[5] = block[4] ^ MUL2(block[5]) ^ MUL3(block[6]) ^ block[7];
    tmp[6] = block[4] ^ block[5] ^ MUL2(block[6]) ^ MUL3(block[7]);
    tmp[7] = MUL3(block[4]) ^ block[5] ^ block[6] ^ MUL2(block[7]);

    tmp[8] = MUL2(block[8]) ^ MUL3(block[9]) ^ block[10] ^ block[11];
    tmp[9] = block[8] ^ MUL2(block[9]) ^ MUL3(block[10]) ^ block[11];
    tmp[10] = block[8] ^ block[9] ^ MUL2(block[10]) ^ MUL3(block[11]);
    tmp[11] = MUL3(block[8]) ^ block[9] ^ block[10] ^ MUL2(block[11]);

    tmp[12] = MUL2(block[12]) ^ MUL3(block[13]) ^ block[14] ^ block[15];
    tmp[13] = block[12] ^ MUL2(block[13]) ^ MUL3(block[14]) ^ block[15];
    tmp[14] = block[12] ^ block[13] ^ MUL2(block[14]) ^ MUL3(block[15]);
    tmp[15] = MUL3(block[12]) ^ block[13] ^ block[14] ^ MUL2(block[15]);

    for (int i = 0; i<16; i++)
        block[i] = tmp[i];
}

void Inverse_Mixcolumn(unsigned char* block){
    unsigned char tmp[16];

    tmp[ 0] = MULE(block[0]) ^ MULB(block[1]) ^ MULD(block[2]) ^ MUL9(block[3]) ;
    tmp[ 1] = MUL9(block[0]) ^ MULE(block[1]) ^ MULB(block[2]) ^ MULD(block[3]) ;
    tmp[ 2] = MULD(block[0]) ^ MUL9(block[1]) ^ MULE(block[2]) ^ MULB(block[3]) ;
    tmp[ 3] = MULB(block[0]) ^ MULD(block[1]) ^ MUL9(block[2]) ^ MULE(block[3]) ;

    tmp[ 4] = MULE(block[4]) ^ MULB(block[5]) ^ MULD(block[6]) ^ MUL9(block[7]) ;
    tmp[ 5] = MUL9(block[4]) ^ MULE(block[5]) ^ MULB(block[6]) ^ MULD(block[7]) ;
    tmp[ 6] = MULD(block[4]) ^ MUL9(block[5]) ^ MULE(block[6]) ^ MULB(block[7]) ;
    tmp[ 7] = MULB(block[4]) ^ MULD(block[5]) ^ MUL9(block[6]) ^ MULE(block[7]) ;

    tmp[ 8] = MULE(block[8]) ^ MULB(block[9]) ^ MULD(block[10]) ^ MUL9(block[11]) ;
    tmp[ 9] = MUL9(block[8]) ^ MULE(block[9]) ^ MULB(block[10]) ^ MULD(block[11]) ;
    tmp[10] = MULD(block[8]) ^ MUL9(block[9]) ^ MULE(block[10]) ^ MULB(block[11]) ;
    tmp[11] = MULB(block[8]) ^ MULD(block[9]) ^ MUL9(block[10]) ^ MULE(block[11]) ;

    tmp[12] = MULE(block[12]) ^ MULB(block[13]) ^ MULD(block[14]) ^ MUL9(block[15]) ;
    tmp[13] = MUL9(block[12]) ^ MULE(block[13]) ^ MULB(block[14]) ^ MULD(block[15]) ;
    tmp[14] = MULD(block[12]) ^ MUL9(block[13]) ^ MULE(block[14]) ^ MULB(block[15]) ;
    tmp[15] = MULB(block[12]) ^ MULD(block[13]) ^ MUL9(block[14]) ^ MULE(block[15]) ;
}

void KeySchedule(unsigned char* Key,unsigned char(* RoundKey)[16]) {
    Copy(RoundKey[0], Key);

    int tmp[44] = { 0 };

    tmp[0] = ((int)Key[0] << 24) + ((int)Key[1] << 16) + ((int)Key[2] << 8) + (int)Key[3];
    tmp[1] = ((int)Key[4] << 24) + ((int)Key[5] << 16) + ((int)Key[6] << 8) + (int)Key[7];
    tmp[2] = ((int)Key[8] << 24) + ((int)Key[9] << 16) + ((int)Key[10] << 8) + (int)Key[11];
    tmp[3] = ((int)Key[12] << 24) + ((int)Key[13] << 16) + ((int)Key[14] << 8) + (int)Key[15];

    for (int i = 1; i <= 10; i++) {
        unsigned int TMP = (tmp[4 * i - 1] << 8) | (tmp[4 * i - 1] >> 24);        //rotate

        TMP = sbox[(TMP & (unsigned int)0xFF000000)>>24] | sbox[(TMP & (unsigned int)0x00FF0000)>>16] | sbox[(TMP & (unsigned int)0x0000FF00)>>8] | sbox[TMP & (unsigned int)0x000000FF];    //subword

        TMP ^= rcon[i - 1];        //rcon

        tmp[4 * i] = tmp[4 * (i - 1)] ^ TMP;
        tmp[4 * i + 1] = tmp[4 * i] ^ tmp[4 * (i - 1) + 1];
        tmp[4 * i + 2] = tmp[4 * i + 1] ^ tmp[4 * (i - 1) + 2];
        tmp[4 * i + 3] = tmp[4 * i + 2] ^ tmp[4 * (i - 1) + 3];
    }

    for (int i = 1; i <= 10; i++) {
        unsigned char tmp_roundkey[16];

        for (int j = 0; j<4; j++) {
            tmp_roundkey[4 * j + 0] = (char)(tmp[4 * i + j] >> 24);
            tmp_roundkey[4 * j + 1] = (char)(tmp[4 * i + j] << 8 >> 24);
            tmp_roundkey[4 * j + 2] = (char)(tmp[4 * i + j] << 16 >> 24);
            tmp_roundkey[4 * j + 3] = (char)(tmp[4 * i + j] << 24 >> 24);
        }
        Copy(RoundKey[i], tmp_roundkey);
    }
}

void Inverse_KeySchedule(unsigned char* Key,unsigned char(* RoundKey)[16]) {
    Copy(RoundKey[11], Key);

    int tmp[44] = { 0 };

    tmp[0] = ((int)Key[0] << 24) + ((int)Key[1] << 16) + ((int)Key[2] << 8) + (int)Key[3];
    tmp[1] = ((int)Key[4] << 24) + ((int)Key[5] << 16) + ((int)Key[6] << 8) + (int)Key[7];
    tmp[2] = ((int)Key[8] << 24) + ((int)Key[9] << 16) + ((int)Key[10] << 8) + (int)Key[11];
    tmp[3] = ((int)Key[12] << 24) + ((int)Key[13] << 16) + ((int)Key[14] << 8) + (int)Key[15];

    for (int i = 1; i <= 10; i++) {
        unsigned int TMP = (tmp[4 * i - 1] << 8) | (tmp[4 * i - 1] >> 24);        //rotate

        TMP = sbox[(TMP & (unsigned int)0xFF000000)>>24] | sbox[(TMP & (unsigned int)0x00FF0000)>>16] | sbox[(TMP & (unsigned int)0x0000FF00)>>8] | sbox[TMP & (unsigned int)0x000000FF];    //subword

        TMP ^= rcon[i - 1];        //rcon

        tmp[4 * i] = tmp[4 * (i - 1)] ^ TMP;
        tmp[4 * i + 1] = tmp[4 * i] ^ tmp[4 * (i - 1) + 1];
        tmp[4 * i + 2] = tmp[4 * i + 1] ^ tmp[4 * (i - 1) + 2];
        tmp[4 * i + 3] = tmp[4 * i + 2] ^ tmp[4 * (i - 1) + 3];
    }

    for (int i = 1; i <= 10; i++) {
        unsigned char tmp_roundkey[16];

        for (int j = 0; j<4; j++) {
            tmp_roundkey[4 * j + 0] = (char)(tmp[4 * i + j] >> 24);
            tmp_roundkey[4 * j + 1] = (char)(tmp[4 * i + j] << 8 >> 24);
            tmp_roundkey[4 * j + 2] = (char)(tmp[4 * i + j] << 16 >> 24);
            tmp_roundkey[4 * j + 3] = (char)(tmp[4 * i + j] << 24 >> 24);
        }
        Copy(RoundKey[10-i], tmp_roundkey);
    }
}

void Add_RoundKey(unsigned char* block,unsigned char* RoundKey) {
    for (int i = 0; i<16; i++)
        block[i] ^= RoundKey[i];
}

void AES_Encrypt(char* input_data, char* output_data, int size) {
    unsigned char block[16];                //block 은 평문을 16바이트 단위로 쪼갠것.
    unsigned char Key[] = "ABCDEFGHIJKLMNOP";
    unsigned char RoundKey[11][16];

    int block_number = size / 16;

    KeySchedule(Key, RoundKey);

    for (int i = 0; i<block_number; i++) {
        for(int k=0;k<16;k++)
            block[k]=input_data[i*k];

        Add_RoundKey(block, RoundKey[0]);

        for (int j = 0; j<10; j++) {
            Subbytes(block);
            ShiftRows(block);
            if (j != 10)
                Mixcolumn(block);
            Add_RoundKey(block, RoundKey[j + 1]);
        }
        for (int m = 0; m < 16; m++)
            output_data[i * 16 + m] = block[m];
    }
}


void AES_Decrypt(char* input_data, char* output_data, int size) {
    unsigned char block[16];                //block 은 평문을 16바이트 단위로 쪼갠것.
    unsigned char Key[] = "ABCDEFGHIJKLMNOP";
    unsigned char RoundKey[11][16];

    int block_number = size / 16;

    Inverse_KeySchedule(Key, RoundKey);

    for (int i = 0; i<block_number; i++) {
        for(int k=0;k<16;k++)
            block[k]=input_data[i*k];

        Add_RoundKey(block, RoundKey[0]);

        for (int j = 0; j<9; j++) {
            Inverse_ShiftRows(block);
            Inverse_Subbytes(block);
            Inverse_Mixcolumn(block);
            Add_RoundKey(block, RoundKey[j+1]);
        }
        Inverse_ShiftRows(block);
        Inverse_Subbytes(block);
        Add_RoundKey(block, RoundKey[10]);

        for (int m = 0; m < 16; m++)
            output_data[i * 16 + m] = block[m];
    }
}

int main() {

    ifstream input("aaa.txt", ios::binary);
    string input_data = "";
    ofstream output("bbb.txt", ios::binary);
    ofstream output2("ccc.txt", ios::binary);


    int size, padding=0;

    if (input.is_open()) {
        input.seekg(0, ios::end);
        size = input.tellg();
        input_data.resize(size);
        input.seekg(0, ios::beg);
        input.read(&input_data[0], size);
    }
    else
        cout << "file not found" << endl;

    while(size % 16 != 0) {
        if (size % 16 == 0)
            break;
        size++;
        padding++;
    }

    char* p = new char[size];
    char* output_data = new char[size];
    char* output2_data = new char[size];

    for(int i=0;i<size-padding;i++)
        p[i]=input_data[i];
    for(int i=0;i<padding;i++)
        p[i]=NULL;

    AES_Encrypt(p, output_data,size);

    if (output.is_open()) {
        output << output_data;
    }

    //cout << output_data << endl;

    AES_Decrypt(output_data, output2_data,size);

    if (output2.is_open()) {
        output2 << output2_data;
    }
    //cout << output2_data << endl;
    system("pause");
}
