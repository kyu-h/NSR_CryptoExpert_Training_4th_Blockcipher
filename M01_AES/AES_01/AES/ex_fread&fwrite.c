#include <stdio.h>

int main()

{
    unsigned char buffer2[16];

    FILE* stream;

    stream=fopen("C:\\Users\\kyu\\Desktop\\NSR_professional-manpower\\M01_AES\\AES_01\\AES\\PT01.dat","rb");
    fread(buffer2,sizeof(unsigned char),16,stream);
    printf("%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x \n",
           buffer2[0],buffer2[1],buffer2[2],buffer2[3],
           buffer2[4],buffer2[5],buffer2[6],buffer2[7],
           buffer2[8],buffer2[9],buffer2[10],buffer2[11],
           buffer2[12],buffer2[13],buffer2[14],buffer2[15]);
    fclose(stream);

    return 0;
}
