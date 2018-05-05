#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XOR(a,b) (a==b?0:1)

int pc1[56] = {57,49,41,33,25,17,9,
                1,58,50,42,34,36,18,
                10,2,59,51,43,35,27,
                19,11,3,60,52,44,36,
                63,55,47,39,31,23,15,
                7,62,54,46,38,30,22,
                14,6,61,53,45,37,29,
                21,13,5,28,20,12,4};

int pc2[48] = {14,17,11,24,1,5,
                3,28,15,6,21,10,
                23,19,12,4,26,8,
                16,7,27,20,13,2,
                41,52,31,37,47,55,
                30,40,51,45,33,48,
                44,49,39,56,34,53,
                46,42,50,36,29,32};

int expand[48] = {32,1,2,3,4,5,4,5,6,7,8,9,
                    8,9,10,11,12,13,12,13,
                    14,15,16,17,16,17,18,19,
                    20,21,20,21,22,23,24,25,
                    24,25,26,27,28,29,28,29,
                    30,31,32,1};

int permutate[32] = {16,7,20,21,29,12,28,
                    17,1,15,23,26,5,18,31,
                    10,2,8,24,14,32,27,3,
                    9,19,13,30,6,22,11,4,25};

int S_Box[8][4][16] = {
{
    // 1라운드
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
},
{
    // 2라운드
    {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
    { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
    { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
    {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
},
{
    // 3라운드
    {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
    {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
    {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
    { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
},
{
    // 4라운드
    { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
    {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
    {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
    { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
},
{
    // 5라운드
    { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
    {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
    { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
    {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
},
{
    // 6라운드
    {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
    {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
    { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
    { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
},
{
    // 7라운드
    { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
    {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 2, 2, 15, 8, 6},
    { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
    { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
},
{
    // 8라운드
    {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
    { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
    { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
    { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
}
};

int current_number = 0;
int key[16][48];

int* getKey(){
    int i, k=0;
    char ck[8] = {0, };
    int *tkey;
    int tmp;
    tkey = (int*)malloc(sizeof(int)*64);

    printf("Type 8 letters to generate key stream \n");
    gets(ck);

    for(i=0; i<8; i++){
        tmp = (int)ck[i];
        for(k=7; k>=0; k--){
            tkey[(i*8)+k] = tmp % 2;
            tmp /= 2;
        }
    }

    printf("Key is: ");
    for(i=0; i<64; i++){
        printf("%d", tkey[i]);
    }
    printf("\n\n");
    return tkey;
}

int* getp(){
    int i,k = 0;
    char cp[8] = {0, };
    int *tp;
    int tmp;
    tp = (int*)malloc(sizeof(int) * 64);

    printf("Type 8 letters to encrypt \n");
    gets(cp);

    for(i=0; i<8; i++){
        tmp = (int)cp[i];
        for(k=7; k>=0; k--){
            tp[(i*8)+k] = tmp % 2;
            tmp /= 2;
        }
    }
    return tp;
}

int* lshift(int *array, int length){
    int *out;
    int i=0;
    int tmp;
    out = (int*)malloc(sizeof(int)*(length + 1));
    tmp = array[0];

    for(;i<length-1; i++){
        out[i] = array[i+1];
    }
    out[length - 1] = tmp;

    return out;
}

void makerKey(int *tkey){
    int i;
    int lstable[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
    int *c, *d, *tmp1, *tmp2;
    int temp[56], temp2[48];

    c = (int*)malloc(sizeof(int) * 29);
    d = (int*)malloc(sizeof(int) * 29);
    tmp1 = (int*)malloc(sizeof(int) * 29);
    tmp2 = (int*)malloc(sizeof(int) * 29);

    for(i=0; i<56; i++){
        temp[i] = tkey[pc1[i]-1];
    }
    printf("After pc 1 is: ");
    for(i=0; i<56; i++){
        printf("%d", temp[i]);
    }
    printf("\n\n");

    for(i=0; i<28; i++){
        c[i] = temp[i];
        d[i] = temp[i+28];
    }
    for(int rn=0; rn<16; rn++){
        for(i=0; i<lstable[rn]; i++){
            tmp1 = lshift(c, 28);
            tmp2 = lshift(d, 28);
            c = tmp1;
            d = tmp2;
        }

        for(i=0; i<28; i++){
            printf("%d", tmp1[i]);
        }
        printf("\n");
        for(i=0; i<28; i++){
            printf("%d", tmp2[i]);
        }
        printf("\n");

        for(i=0; i<48; i++){
            if((pc2[i]-1) > 27){
                temp2[i] = tmp2[pc2[i]-29];
            }else {
                temp2[i] = tmp1[pc2[i]-1];
            }
            key[rn][i] = temp2[i];
        }
    }

    for(i=0; i<16; i++){
        printf("%d \tth Round Key is: ", i+1);
        for(int k=0; k<48; k++){
            printf("%d", key[i][k]);
        }
        printf("\n");
    }
}

int* f(int r[32], int rkey[48]){
    int rtmp[48];
    int ftmp[32];
    int *fout;
    int stmp[8];
    int i;
    fout = (int*)malloc(sizeof(int) * 32);

    printf("Key is: ");
    for(i=0; i<48; i++){
        printf("%d", rkey[i]);
    }
    printf("\n");

    for(i=0; i<48; i++){
        rtmp[i] = r[expand[i]-1];
    }
    printf("R is: ");

    for(i=0; i<48; i++){
        printf("%d", rtmp[i]);
    }
    printf("\n");
    printf("XOR is: ");
    for(i=0; i<48; i++){
        rtmp[i] = XOR(rtmp[i], rkey[i]);
        printf("%d", rtmp[i]);
    }
    printf("\n");

    for(i=0; i<8; i++){
        stmp[i] = S_Box[i][2*rtmp[6*i] + rtmp[5+6*i]][8*rtmp[1+6*i] + 4*rtmp[2+6*i] + 2*rtmp[3+6*i] + rtmp[4+6*i]];
        printf("Sbox output is: %d\n", stmp[i]);
    }

    for(i=0; i<8; i++){
        for(int k =3; k>=0; k--){
            ftmp[4*i+k] = stmp[i] % 2;
            stmp[i] /= 2;
        }
    }

    printf("Output of F: ");
    for(i=0; i<32; i++){
        fout[i] = ftmp[permutate[i]-1];
        printf("%d", fout[i]);
    }
    printf("\n");

    return fout;
}

int* encrypt(int plain[64], int round){
    int l[32];
    int r[32];
    int tmp[32];
    int *fout;
    int *c;
    int k;

    for(int i=0; i<32; i++){
        l[i] = plain[i];
        r[i] = plain[i+32];
    }

    printf("L is: ");
    for(int i=0; i<32; i++){
        if(!(i%4)){
            printf(" / ");
        }
        printf("%d", l[i]);
    }
    printf("\n");

    printf("R is: ");
    for(int i=0; i<32; i++){
        if(!(i%4)){
            printf(" / ");
        }
        printf("%d", r[i]);
    }
    printf("\n");

    for(int i=0; i<round; i++){
        for(k=0; k<32; k++){
            tmp[k] = l[k];
            l[k] = r[k];
        }
        fout = f(r,key[i]);
        for(k=0; k<32; k++){
            r[k] = XOR(tmp[k], fout[k]);
        }
    }

    c = (int*)malloc(sizeof(int) * 64);
    for(int i=0; i<32; i++){
        c[i] = l[i];
        c[i+32] = r[i];
    }

    return c;
}

int* decrypt(int cipher[64], int round){
    int l[32];
    int r[32];
    int tmp[32];
    int *fout;
    int *p;
    int k;

    for(int i=0; i<32; i++){
        r[i] = cipher[i];
        l[i] = cipher[i+32];
    }

    printf("L is: ");
    for(int i=0; i<32; i++){
        if(!(i%4)){
            printf(" / ");
        }
        printf("%d", l[i]);
    }
    printf("\n");
    printf("R is: ");

    for(int i=0; i<32; i++){
        if(!(i%4)){
            printf(" / ");
        }
        printf("%d", r[i]);
    }
    printf("\n");

    for(int i =0; i<round; i++){
        for (k=0; k<32; k++){
            tmp[k] = l[k];
            l[k] = r[k];
        }

        fout = f(r,key[round-1-i]);
        for(k=0; k<32; k++){
            r[k] = XOR(tmp[k], fout[k]);
        }
        printf("Corrent L is: ");
        for(k=0; k<32; k++){
            printf("%d", l[k]);
        }
        printf("\n");

        printf("Corrent R is: ");
        for(k=0; k<32; k++){
            printf("%d", r[k]);
        }
        printf("\n");
    }

    p = (int*)malloc(sizeof(int) *64);
    for(int i=0; i<32; i++){
        p[i] = r[i];
        p[i+32] = l[i];
    }

    return p;
}

void main(){
    printf("for test\n");

    makerKey(getKey());

    for(int i=0; i<16; i++){
        printf("%d th Round key: ", i);
        for(int k=0; k<48; k++){
            printf("%d", key[i][k]);
        }
        printf("\n");
    }

    int *plaintext;
    int *tube;
    int i;

    plaintext = getp();
    tube = (int*)malloc(sizeof(int) * 64);

    for(i=0; i<64; i++){
        printf("%d", plaintext[i]);
    }
    printf("\n");

    tube = encrypt(plaintext, 16);
    for(i=0; i<64; i++){
        printf("%d", tube[i]);
    }
    printf("\n");

    plaintext = decrypt(tube, 16);
    for(i=0; i<64; i++){
        printf("%d", plaintext[i]);
    }
    printf("\n");
}
