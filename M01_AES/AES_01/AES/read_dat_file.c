#include <stdio.h>


int main( )
{
	FILE *pFile = NULL;
	FILE *output_txt = NULL;

	unsigned char buffer2[16];
	int a=0;

	pFile = fopen("C:\\Users\\kyu\\Desktop\\NSR_professional-manpower\\M01_AES\\AES_01\\AES\\PT01.dat","rb");
	output_txt = fopen("C:\\Users\\kyu\\Desktop\\NSR_professional-manpower\\M01_AES\\AES_01\\AES\\PT01_txt.txt","wb");

	if( pFile == NULL ){
		printf("error");
	}else{
		while( !feof( pFile ) ){

            fread(buffer2, sizeof(unsigned char), 16, pFile);
            printf("%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x \n",
                   buffer2[0],buffer2[1],buffer2[2],buffer2[3],
                   buffer2[4],buffer2[5],buffer2[6],buffer2[7],
                   buffer2[8],buffer2[9],buffer2[10],buffer2[11],
                   buffer2[12],buffer2[13],buffer2[14],buffer2[15]);

            if(a == 5){
                break;
            }

            fwrite(buffer2, sizeof(unsigned char), 16, output_txt);

            a++;
		}

		fclose(pFile);
		fclose(output_txt);
	}

	return 0;
}

