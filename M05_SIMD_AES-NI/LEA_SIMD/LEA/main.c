#include <stdio.h>
#include <string.h>

#include "LEA.h"

int main(){
	int i, j;

	int Nk = 0;
	int Nr = 0;
	int n = 0;

	unsigned char K[32] = // 16 24 32
				{
					0x0f,0x1e,0x2d,0x3c,0x4b,0x5a,0x69,0x78,0x87,0x96,0xa5,0xb4,0xc3,0xd2,0xe1,0xf0,
					0xf0, 0xe1, 0xd2, 0xc3, 0xb4, 0xa5, 0x96, 0x87, 0x78, 0x69, 0x5a, 0x4b, 0x3c, 0x2d, 0x1e, 0x0f
				};
	uint32_t RoundKey[192] = {0}; // 144 168 192

	unsigned char P[16];
	unsigned char P_128[16] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
	unsigned char P_192[16] = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f};
	unsigned char P_256[16] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f};
	unsigned char C[16] = {0};
	unsigned char D[16] = {0};

	printf("please enter the bits. ex, 128\n");
	scanf("%d", &n);
	printf("You select %d bits\n", n);

	switch(n){
		case 128:
			Nk = 16;
			Nr = 24;
			
			LEA_EncryptKeySchedule_128(K,RoundKey);
			memcpy(P, P_128, 16);
			
			break;
		case 192:
			Nk = 24;
			Nr = 28;
			
			LEA_EncryptKeySchedule_192(K,RoundKey);
			memcpy(P, P_192, 16);
			
			break;
		case 256:
			Nk = 32;
			Nr = 32;
			
			LEA_EncryptKeySchedule_256(K,RoundKey);
			memcpy(P, P_256, 16);
			
			break;
		default:
			printf("인수가 잘못되었습니다!\n");
			return 1;
		}
	
	printf("Nk = %d\n", Nk);
	printf("Nr = %d\n", Nr);
	
	printf("K : ");
	for(i=0;i<Nk;i++){
		printf("%02x ", K[i]);
	}
	printf("\n");
	
	printf("RK : \n");
	for(i=0;i<Nr;i++){
		printf("RoundKey[%2d] : ", i);
		for(j=0;j<6;j++){
			printf("%08x ", RoundKey[i*6+j]);
		}
		printf("\n");
	}
	printf("\n");
	
	printf("P : ");
	for(i=0;i<16;i++){
		printf("%02x ", P[i]);
	}
	printf("\n");
	
	LEA_EncryptBlock(Nr, RoundKey, P, C);
	
	printf("C : ");
	for(i=0;i<16;i++){
		printf("%02x ", C[i]);
	}
	printf("\n");

	LEA_DecryptBlock(Nr, RoundKey, D, C);
	
	printf("D : ");
	for(i=0;i<16;i++){
		printf("%02x ", D[i]);
	}
	printf("\n");
	
	return 0;
}
