#ifndef _WS_3DES_H_
#define _WS_3DES_H_

#include <stdio.h>
#include "ws_comm_errno.h"

namespace ws_3des
{
    int enc_3des(const char *src_buf, size_t src_size, char *dst_buf, const char *key);
    int dec_3des(const char *src_buf, size_t src_size, char *dst_buf, const char *key);
    
    int Des_Go(char *Out, char *In, long datalen, const char *Key, int keylen, bool Type);
}
#endif 

