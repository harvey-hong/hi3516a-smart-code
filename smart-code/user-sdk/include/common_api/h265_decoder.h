#ifndef _H265_DECODER_H_
#define _H265_DECODER_H_
#include <iostream>

#define H265API_FUNCTION_OUTPUT __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C" {
#endif
enum h265_unit_type
{
	H265_UNIT_VPS,
	H265_UNIT_SPS,
	H265_UNIT_PPS,
	H265_UNIT_DATA,
	H265_UNIT_BAD
};

H265API_FUNCTION_OUTPUT void printsome();
//功能：解析nal帧的类型
//输入：nal帧数据（包含帧头），nal帧的大小,out是输出数据指针
//输出：nal帧的类型
H265API_FUNCTION_OUTPUT h265_unit_type get_nal_type(const char * nal,unsigned int sz,char * out,int * nal_len);

//功能：根据 vps、sps和pps包解析出图像的宽高
//输入参数：sps对应的帧数据（包含帧头）以及数据大小
//输出参数：宽、高
//返回值：若成功解析返回0，若失败返回非0值
H265API_FUNCTION_OUTPUT int decode_width_height(const char * sps_buf,unsigned int sps_sz,int * width,int * height);

#ifdef __cplusplus
}
#endif
#endif

