#include <stdio.h>

int Check_CTs_For_PT01(void)
{
	FILE * ifp;
	int fail = 0;
	int i;
	char filename[256] = { 0, };
	int precision = 1000; //Checking Number
	int its;

	printf("\n############################################################\n\n");
	printf("####[Problem1-1] Find the PT01's CT!####\n");

	for (i = 1; i <= 4; i++)
	{
		//printf("Now Checking : CT0%d.dat\n", i);
		sprintf(filename, "./CT0%d.dat", i);
		ifp = fopen(filename, "rb");
		if (ifp == NULL)
			return printf("File open Error");
		fail = 0;
		its = 1;
		while (feof(ifp) != EOF && its < precision)
		{
			AES_WORD CT1[16] = { 0, };
			AES_WORD CT2[16] = { 0, };
			AES_WORD DIFF[16] = { 0, };
			b_fileread(CT1, ifp);
			b_fileread(CT2, ifp);
			_128_BLOCK_XOR(DIFF, CT1, CT2);
			Inv_MIX(DIFF, DIFF);
			if (DIFF[4] != MUL3(DIFF[14]))
			{
				fail = 1;
				break;
			}
			if (DIFF[5] != MUL2(DIFF[15]))
			{
				fail = 1;
				break;
			}
			if (MUL3(DIFF[6]) != DIFF[12])
			{
				fail = 1;
				break;
			}
			if (MUL2(DIFF[7]) != DIFF[13])
			{
				fail = 1;
				break;
			}
			its++;
		}
		if (fail != 1)
			printf("Result       : CT0%d MUST be the ciphertexts from PT01\n", i);
		else
			printf("Result       : CT0%d is NOT  the ciphertexts from PT01\n", i);
		fclose(ifp);
	}

	return 0;
}

int main(){
    //printf("dd");
    Check_CTs_For_PT01();

    return 0;
}
