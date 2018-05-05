#include <stdio.h>
#include "des.h"

int main()
{
	des3_context 	ctx3 ;

	unsigned char 	key1[8] = 
		{0x10, 0x91, 0x8C, 0x68, 0x45, 0xAB, 0x98, 0xEF};
	
	unsigned char 	key2[8] =
		{0x89, 0x4C, 0x6B, 0x57, 0xBC, 0x67, 0x76, 0xDC};

	unsigned char 	plaintext[2][8] = {{0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00},
					{0x00, 0x00,0x00,0x00,0x12,0x34,0x56,0x78}};

	unsigned char 	enc[8] ;

	int ii, jj ;

	des3_set_2keys(&ctx3, key1, key2) ;

	for(ii = 0; ii < 2; ii++)
	{
		des3_encrypt(&ctx3, plaintext[ii], enc) ;

		for(jj = 0; jj < 8; jj++)
			printf("%02x ", enc[jj] & 0xff) ;
	}
	printf("\n") ;
	return 1 ;
}