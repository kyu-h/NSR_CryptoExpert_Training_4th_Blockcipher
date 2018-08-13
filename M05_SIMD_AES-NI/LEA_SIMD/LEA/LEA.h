#ifndef __LEA_H__
#define __LEA_H__


#ifdef _MSC_VER
#if _MSC_VER < 1600

#ifndef __INT_TYPES__
#define __INT_TYPES__
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif

#else
#include <stdint.h>
#endif
#else
#include <stdint.h>
#endif

extern void LEA_EncryptKeySchedule_128(unsigned char *K, uint32_t *RoundKey);
extern void LEA_EncryptKeySchedule_192(unsigned char *K, uint32_t *RoundKey);
extern void LEA_EncryptKeySchedule_256(unsigned char *K, uint32_t *RoundKey);
extern void LEA_DecryptBlock(int Nr, uint32_t *RoundKey, unsigned char *plaintext, unsigned char *ciphertext);
extern void LEA_EncryptBlock(int Nr, uint32_t *RoundKey, unsigned char *plaintext, unsigned char *ciphertext);

#endif
