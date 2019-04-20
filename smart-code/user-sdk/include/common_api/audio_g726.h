#ifndef _TECOM_ADPCMCODEC_API_H_
#define _TECOM_ADPCMCODEC_API_H_  

#define ADPCMCODEC_FUNCTION_OUTPUT __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C" {

namespace ws_CAdpcmCodec
{
#endif

// decode g726 to PCM, input 120 Byte and output 640 Byte
ADPCMCODEC_FUNCTION_OUTPUT int  AUDIO_AdpcmDecode(unsigned char inbuf[],short outbuf[],int size);

//��PCM����Ƶ�ź�ת����G726����Ƶ�ź�..
ADPCMCODEC_FUNCTION_OUTPUT int  AUDIO_AdpcmEncode(short inbuf[],unsigned char outbuf[],int size);


#ifdef __cplusplus
}

}
#endif


#endif  /*#ifndef _TECOM_ADPCMCODEC_API_H_*/
