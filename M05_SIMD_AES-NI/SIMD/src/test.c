/*
 * test.c
 *
 *  Created on: 2018. 7. 27.
 *      Author: kyu
 */


#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>
#include <tmmintrin.h>

void show_array_word(unsigned int* x, int len){
    int i=0;

    while(i<len){
    	printf("%08x ", x[i++]);
    }

    printf("\n");
}

void show_array_byte(unsigned char* x, int len){
    int i=0;

    while(i<len){
    	printf("%08x ", x[i++]);
    }

    printf("\n");
}

void test_sse2_mm_add_epi32(){ //32bit
    unsigned int x[4] = {0x11111111, 0x22222222, 0x33333333, 0x44444444};

    //************for add*************//
    //unsigned int y[4] = {0xeeeeeeee, 0xdddddddd, 0xcccccccc, 0xbbbbbbbb};
    unsigned int z[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

    show_array_word(x, 4);

    //************for add*************//
    //show_array_word(y, 4);

    __m128i x128 = _mm_loadu_si128((__m128i*)x);

    //************for add*************//
    //__m128i y128 = _mm_loadu_si128((__m128i*)y);

    //************for add*************//
    /*x128 = _mm_add_epi32(x128, y128);

    _mm_storeu_si128((__m128i*)z, x128);

    show_array_word(z, 4);*/

    x128 = _mm_shuffle_epi32(x128, _MM_SHUFFLE(3,2,1,0));
    _mm_storeu_si128((__m128i*)z, x128);
    show_array_word(z, 4);

    x128 = _mm_shuffle_epi32(x128, _MM_SHUFFLE(0,1,2,3));
	_mm_storeu_si128((__m128i*)z, x128);
	show_array_word(z, 4);

	x128 = _mm_shuffle_epi32(x128, _MM_SHUFFLE(0,0,1,1));
	_mm_storeu_si128((__m128i*)z, x128);
	show_array_word(z, 4);
}

void test_ssse3_mm_suffle_epi8(){
	unsigned char x[16] = {
		0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
		0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
	};

	unsigned char z[16] = {0x00,};

	show_array_byte(x, 16);

	__m128i x128 = _mm_loadu_si128((__m128i*)x);

	x128 = _mm_shuffle_epi8(x128, _mm_set_epi8(15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0));
	_mm_storeu_si128((__m128i*)z, x128);
	show_array_byte(z, 16);

	x128 = _mm_shuffle_epi8(x128, _mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15));
	_mm_storeu_si128((__m128i*)z, x128);
	show_array_byte(z, 16);

	x128 = _mm_shuffle_epi8(x128, _mm_set_epi8(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0));
	_mm_storeu_si128((__m128i*)z, x128);
	show_array_byte(z, 16);
}

int main()
{
    test_sse2_mm_add_epi32();
	//test_ssse3_mm_suffle_epi8();

    return 0;
}
