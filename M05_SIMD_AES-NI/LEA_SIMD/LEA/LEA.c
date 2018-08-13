#include "LEA.h"

#include <emmintrin.h>
#include <stdio.h>

void sse2_mm_add_epi32(unsigned int a, unsigned int b){
	unsigned int x[2] = {0x11111111, 0x22222222};
	unsigned int y[2] = {0x11111111, 0x22222222};
	unsigned int z[1] = {0x00};

	__m128i x128 = _mm_loadu_si128((__m128i*)a);
	__m128i y128 = _mm_loadu_si128((__m128i*)b);

	x128 = _mm_add_epi32(x128, y128);

	_mm_storeu_si128((__m128i*)z, x128);

	for(int i=0; i<4; i++)
		printf("%08x ", z[i]);
	printf("\n");
}

static const uint32_t LEA_delta[8] = {
	0xc3efe9db,
	0x44626b02,
	0x79e27c8a,
	0x78df30ec,
	0x715ea49e,
	0xc785da0a,
	0xe04ef22a,
	0xe5c40957
};

static int LEA_ROL(unsigned int places, unsigned int value)
{ 
	//__m128i x128 = _mm_loadu_si128((__m128i*)value);

	//x128 = _mm_slli_epi32(x128, places);

	return (value<<places)|(value>>(32-places)); 
} 

static int LEA_ROR(uint32_t places, uint32_t value) 
{ 
	return (value>>places)|(value<<(32-places)); 
} 

static uint32_t LEA_w_plus(uint_fast32_t a, uint_fast32_t b)
{
	return (a+b);
}

static uint32_t LEA_w_minus(uint32_t a, uint32_t b)
{
	return (a-b);
}

void LEA_EncryptKeySchedule_128(unsigned char *K, uint32_t *RoundKey)
{
	int i;
	uint_fast32_t T[4] = {0};
	
	memcpy(T, K, 16);
	
	//sse2_mm_add_epi32(T[0], T[1]);
	printf("T: ");
	printf("%02x\n", T[0]);

	printf("T: ");
	printf("%02x\n", T[1]);

	for(i=0;i<24;i++){
		T[0] = LEA_ROL(1, LEA_w_plus(T[0], LEA_ROL(i, LEA_delta[i % 4])));
		T[1] = LEA_ROL(3, LEA_w_plus(T[1], LEA_ROL(i+1, LEA_delta[i % 4])));
		T[2] = LEA_ROL(6, LEA_w_plus(T[2], LEA_ROL(i+2, LEA_delta[i % 4])));
		T[3] = LEA_ROL(11,LEA_w_plus(T[3], LEA_ROL(i+3, LEA_delta[i % 4])));

		RoundKey[i*6+0] = T[0];
		RoundKey[i*6+1] = T[1];
		RoundKey[i*6+2] = T[2];
		RoundKey[i*6+3] = T[1];
		RoundKey[i*6+4] = T[3];
		RoundKey[i*6+5] = T[1];

	}

}

void LEA_EncryptKeySchedule_192(unsigned char *K, uint32_t *RoundKey)
{
	int i;
	uint32_t T[6] = {0};
	
	memcpy(T, K, 24);
	
	for(i=0;i<28;i++)
	{
		T[0] = LEA_ROL(1, LEA_w_plus(T[0],LEA_ROL(i,LEA_delta[i % 6])));
		T[1] = LEA_ROL(3, LEA_w_plus(T[1],LEA_ROL(i+1,LEA_delta[i % 6])));
		T[2] = LEA_ROL(6, LEA_w_plus(T[2],LEA_ROL(i+2,LEA_delta[i % 6])));
		T[3] = LEA_ROL(11,LEA_w_plus(T[3],LEA_ROL(i+3,LEA_delta[i % 6])));
		T[4] = LEA_ROL(13,LEA_w_plus(T[4],LEA_ROL(i+4,LEA_delta[i % 6])));
		T[5] = LEA_ROL(17,LEA_w_plus(T[5],LEA_ROL(i+5,LEA_delta[i % 6])));

		RoundKey[i*6+0] = T[0];
		RoundKey[i*6+1] = T[1];
		RoundKey[i*6+2] = T[2];
		RoundKey[i*6+3] = T[3];
		RoundKey[i*6+4] = T[4];
		RoundKey[i*6+5] = T[5];
	}
}

void LEA_EncryptKeySchedule_256(unsigned char *K, uint32_t *RoundKey)
{
	int i;
	uint32_t T[8] = {0};
	
	memcpy(T, K, 32);
	
	for(i=0;i<32;i++)
	{
		T[(6*i+0)%8] = LEA_ROL(1, LEA_w_plus(T[0],LEA_ROL(i,LEA_delta[i % 8])));
		T[(6*i+1)%8] = LEA_ROL(3, LEA_w_plus(T[1],LEA_ROL(i+1,LEA_delta[i % 8])));
		T[(6*i+2)%8] = LEA_ROL(6, LEA_w_plus(T[2],LEA_ROL(i+2,LEA_delta[i % 8])));
		T[(6*i+3)%8] = LEA_ROL(11,LEA_w_plus(T[3],LEA_ROL(i+3,LEA_delta[i % 8])));
		T[(6*i+4)%8] = LEA_ROL(13,LEA_w_plus(T[4],LEA_ROL(i+4,LEA_delta[i % 8])));
		T[(6*i+5)%8] = LEA_ROL(17,LEA_w_plus(T[5],LEA_ROL(i+5,LEA_delta[i % 8])));
		
		RoundKey[i*6+0] = T[(6*i+0)%8];
		RoundKey[i*6+1] = T[(6*i+1)%8];
		RoundKey[i*6+2] = T[(6*i+2)%8];
		RoundKey[i*6+3] = T[(6*i+3)%8];
		RoundKey[i*6+4] = T[(6*i+4)%8];
		RoundKey[i*6+5] = T[(6*i+5)%8];
	}
}


static void LEA_Round_Encrypt(uint32_t *Xout, uint32_t *Xin, uint32_t *RKe)
{
	Xout[0] = LEA_ROL(9, LEA_w_plus(Xin[0]^RKe[0], Xin[1]^RKe[1]));
	Xout[1] = LEA_ROR(5, LEA_w_plus(Xin[1]^RKe[2], Xin[2]^RKe[3]));
	Xout[2] = LEA_ROR(3, LEA_w_plus(Xin[2]^RKe[4], Xin[3]^RKe[5]));
	Xout[3] = Xin[0];
}

static void LEA_Round_Decrypt(uint32_t *Xout, uint32_t *Xin, uint32_t *RKd)
{
	Xout[0] = Xin[3];
	Xout[1] = LEA_w_minus(LEA_ROR(9, Xin[0]), Xout[0]^RKd[0]) ^ RKd[1];
	Xout[2] = LEA_w_minus(LEA_ROL(5, Xin[1]), Xout[1]^RKd[2]) ^ RKd[3];
	Xout[3] = LEA_w_minus(LEA_ROL(3, Xin[2]), Xout[2]^RKd[4]) ^ RKd[5];
}


void LEA_EncryptBlock(int Nr, uint32_t *RoundKey, unsigned char *plaintext, unsigned char *ciphertext)
{
	int i;
	uint32_t X_cur[4];
	uint32_t X_next[4];

	memcpy(X_cur, plaintext, 16);
	
	for(i=0; i<Nr; i++)
	{
		LEA_Round_Encrypt(X_next, X_cur, &RoundKey[i*6]);
		memcpy(X_cur, X_next, 16);
	}
	
	memcpy(ciphertext, X_cur, 16);
}

void LEA_DecryptBlock(int Nr, uint32_t *RoundKey, unsigned char *plaintext, unsigned char *ciphertext)
{
	int i;
	uint32_t X_cur[4];
	uint32_t X_next[4];

	memcpy(X_cur, ciphertext, 16);

	for(i=0; i<Nr; i++)
	{
		LEA_Round_Decrypt(X_next, X_cur, &RoundKey[(Nr-i-1)*6]);
		memcpy(X_cur, X_next, 16);
	}

	memcpy(plaintext, X_cur, 16);
}

