#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//*************************************
//find [0][1] data
//*************************************


int main()
{
    int x,y=0;
    unsigned char example_Secret[4] = {0xb2, 0x30, 0x00, 0x4d};
    unsigned char example_RoundKey[4];
    unsigned char z; //sample data

    unsigned char RoundKey [0x02][0x02] = {
        {0xb2, 0x00},
        {0x00, 0x4f}
    };

    unsigned char SecretKey [0x02][0x02] = {
        {0xb2, 0x30},
        {0x00, 0x4d}
    };

    for(x=0; x<4; x++){
        printf("%#04x ", example_Secret[x]);
    }

    printf("\n");

    for(z=0; z<0xff; z++){
        RoundKey[0][1] = z;

        printf("%#04x \n", z);

        for(x=0; x<2; x++){
            for(y=0; y<2; y++){
                example_RoundKey[x*2 + y] = RoundKey[x][y];
            }
        }
        if(strcmp(example_Secret, example_RoundKey)==0){
            printf("same!!");
            for(x=0; x<4; x++){
                printf("%#04x ", example_RoundKey[x]);
            }
            return;
        }
    }

    printf("\n");
    for(x=0; x<4; x++){
        printf("%#04x ", example_RoundKey[x]);
    }

    return 0;
}
