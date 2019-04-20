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
//���ܣ�����nal֡������
//���룺nal֡���ݣ�����֡ͷ����nal֡�Ĵ�С,out���������ָ��
//�����nal֡������
H265API_FUNCTION_OUTPUT h265_unit_type get_nal_type(const char * nal,unsigned int sz,char * out,int * nal_len);

//���ܣ����� vps��sps��pps��������ͼ��Ŀ��
//���������sps��Ӧ��֡���ݣ�����֡ͷ���Լ����ݴ�С
//�������������
//����ֵ�����ɹ���������0����ʧ�ܷ��ط�0ֵ
H265API_FUNCTION_OUTPUT int decode_width_height(const char * sps_buf,unsigned int sps_sz,int * width,int * height);

#ifdef __cplusplus
}
#endif
#endif

