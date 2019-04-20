#ifndef __WS_BASE64__
#define __WS_BASE64__

#include <stdio.h>

namespace ws_base64
{
    int Base64Encode(char *InPutText, int InputSize, char *OutPutBuf, int *InOutBufLen);
    int Base64Decode(const char *InPutBuf, int InPutBufLen, char *OutPutText, int *InOutTextLen);
}

#endif
