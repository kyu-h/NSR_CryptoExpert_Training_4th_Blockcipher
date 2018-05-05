#include <stdio.h>


int main( )
{
	FILE *pFile = NULL;
	FILE *output_txt = NULL;

    unsigned char buffer1[16];
	unsigned char buffer2[16];
	unsigned char XORbuffer[16];

	int a=0;

	pFile = fopen("C:\\Users\\kyu\\Desktop\\NSR_professional-manpower\\M01_AES\\AES_01\\AES\\PT01.dat","rb");
	output_txt = fopen("C:\\Users\\kyu\\Desktop\\NSR_professional-manpower\\M01_AES\\AES_01\\AES\\PT01_txt.txt","wb");

	if( pFile == NULL ){
		printf("error");
	}else{
		while( !feof( pFile ) ){

            fread(buffer1, sizeof(unsigned char), 16, pFile);
            fread(buffer2, sizeof(unsigned char), 16, pFile);

            printf("%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x \n",
                   buffer1[0],buffer1[1],buffer1[2],buffer1[3],
                   buffer1[4],buffer1[5],buffer1[6],buffer1[7],
                   buffer1[8],buffer1[9],buffer1[10],buffer1[11],
                   buffer1[12],buffer1[13],buffer1[14],buffer1[15]);

            printf("%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x \n",
                   buffer2[0],buffer2[1],buffer2[2],buffer2[3],
                   buffer2[4],buffer2[5],buffer2[6],buffer2[7],
                   buffer2[8],buffer2[9],buffer2[10],buffer2[11],
                   buffer2[12],buffer2[13],buffer2[14],buffer2[15]);

            for(int i=0; i<16; i++){
                XORbuffer[i] = buffer1[i] ^ buffer2[i];
                printf("%02x ", XORbuffer[i]);
            }
            if(a == 100){
                break;
            }

            for(int i=0; i<16; i++){
                fprintf(output_txt, "%02x ", XORbuffer[i]);
            }

            a++;
		}

		fclose(pFile);
		fclose(output_txt);
	}

	return 0;
}

