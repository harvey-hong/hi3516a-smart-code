#ifndef _SYS_MD5_H_
#define _SYS_MD5_H_
#include "InternalCommon.h"

/* MD5 context. */
typedef struct MD5Context
{
    unsigned state[4];    /* state (ABCD) */
    unsigned count[2];    /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64]; /* input buffer */
} MD5_CTX;

void   MD5Init(MD5_CTX *);
void   MD5Update(MD5_CTX *, const unsigned char *, unsigned int);
void   MD5Pad(MD5_CTX *);
void   MD5Final(unsigned char [16], MD5_CTX *);
char *MD5End(MD5_CTX *, char *);
char *MD5Data(const unsigned char *, unsigned int, char *);
#endif /* _SYS_MD5_H_ */
