// Class4 - TMTO 1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "openssl/des.h"
#include <memory.h>
#include <stdio.h>
#include <random>

void f(unsigned long long &plaintext, unsigned long long &key, unsigned long long &ciphertext)
{
	DES_key_schedule schedule;
	DES_set_key((DES_cblock*)&key, &schedule);
	DES_ecb_encrypt((DES_cblock*)&plaintext, (DES_cblock*)&ciphertext, &schedule, DES_ENCRYPT);
}

void r(unsigned long long &Y, int i, unsigned long long &X)
{
	*((unsigned long long*)(&X)) = (*((unsigned long long*)(&Y)) >> i) & 0xffff;
}

void g(unsigned long long &plaintext, int i, unsigned long long &X1, unsigned long long &X2)
{
	unsigned long long ciphertext;
	f(plaintext, X1, ciphertext);
	r(ciphertext, i, X2);
}

int main()
{
	int Ti, m, t, i, j, k;
	unsigned long long **table;
	unsigned long long SP, EP;
	unsigned long long plaintext, ciphertext;
	unsigned long long key;

	m = 0x01 << 6;
	t = 0x01 << 5;

	plaintext = 0x0001020304050607ui64;

	// generating table
	table = new unsigned long long*[t];
	for (Ti = 0; Ti < t; ++Ti)
	{
		table[Ti] = new unsigned long long[m * 2];
		for (i = 0; i < m; ++i)
		{
			//SP = rand() & 0xffff;//(Ti << 7) + (i << 1);
			SP = (Ti << 7) + (i << 1);
			EP = SP;
			for (j = 0; j < t; ++j)
			{
				g(plaintext, Ti, EP, EP);
			}
			table[Ti][i] = SP;
			table[Ti][i + m] = EP;
		}
	}

	char charkey[1024];
	printf("Input your key (upto 2 chars, in ASCII)");
	scanf("%s", charkey);

	key = (charkey[0] + (charkey[1] << 8)) & 0xffff;				// little endian
	f(plaintext, key, ciphertext);

	printf("Your key is        : ");
	for (i = 0; i < 8; ++i)
	{
		printf("%02X ", 0xff & ((char*)&key)[i]);
	}
	printf("\n");

	printf("Your ciphertext is : ");
	for (i = 0; i < 8; ++i)
	{
		printf("%02X ", 0xff & ((char*)&ciphertext)[i]);
	}
	printf("\n");

	// online phase
	unsigned long long y0, rx0;
	y0 = ciphertext;
	for (Ti = 0; Ti < t; ++Ti)
	{
		// rx0 = r(x0)
		r(y0, Ti, rx0);
		for (k = 0; k < t; ++k)
		{
			for (i = 0; i < m; ++i)
			{
				// x == EP?
				if (table[Ti][i + m] == rx0)
				{
					// false alarm?
					unsigned long long x = table[Ti][i];		// x <- SP
					unsigned long long y;

					// x <- g^(t - k - 1)(SP)
					for (j = k + 1; j < t; ++j)
					{
						g(plaintext, Ti, x, x);
					}
					// y <- f(x)
					f(plaintext, x, y);
					
					if (y == y0)
					{
						printf("Eureka!\nI've found your key : ");
						for (j = 0; j < 8; ++j)
						{
							printf("%02X ", 0xff & ((char*)&x)[j]);
						}
						printf("\n");

						goto cleanup;
					}
					else
					{
						printf("False alarm (Ti = %5d, i = %5d, k = %5d : ", Ti, i, k);
						for (j = 0; j < 8; ++j)
						{
							printf("%02X ", 0xff & ((char*)&x)[j]);
						}
						printf("\n");
					}
				}
			}
			// x = g^k(r(y))
			g(plaintext, Ti, rx0, rx0);
		}
	}
	printf("Failed...\n");

cleanup:
	for (Ti = 0; Ti < t; ++Ti)
	{
		delete[] table[Ti];
	}
	delete[] table;

	fflush(stdin);
	getchar();

    return 0;
}

