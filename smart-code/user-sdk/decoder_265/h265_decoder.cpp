#include "h265_decoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "nal.h"
#include "vps.h"
#include "sps.h"


//#define DE265_MAX_VPS_SETS 16   // this is the maximum as defined in the standard
#define DE265_MAX_SPS_SETS 16   // this is the maximum as defined in the standard
//#define DE265_MAX_PPS_SETS 64   // this is the maximum as defined in the standard


/*static const char NALCharSet[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";*/

//static video_parameter_set*  vps[ DE265_MAX_VPS_SETS ] = {NULL};
static seq_parameter_set *   sps[ DE265_MAX_SPS_SETS ] = {NULL};
//static pic_parameter_set *   pps[ DE265_MAX_PPS_SETS ] = {NULL};

/*
int ConvertToNALString(char *DestPtr, const char *SourcePtr, int DataLen)
{
    char    *tempPtr;     
    int   indexCnt;      

    tempPtr = DestPtr;

  
    for (indexCnt = 0; indexCnt < DataLen - 2; indexCnt += 3)
    {
        *tempPtr++ = NALCharSet[(SourcePtr[indexCnt] >> 2) & 0x3F];
        *tempPtr++ = NALCharSet[((SourcePtr[indexCnt] & 0x3) << 4) |
                                ((int)(SourcePtr[indexCnt + 1] & 0xF0) >> 4)];
        *tempPtr++ = NALCharSet[((SourcePtr[indexCnt + 1] & 0xF) << 2) |
                                ((int)(SourcePtr[indexCnt + 2] & 0xC0) >> 6)];
        *tempPtr++ = NALCharSet[SourcePtr[indexCnt + 2] & 0x3F];
    }


    if (indexCnt < DataLen)
    {
        *tempPtr++ = NALCharSet[(SourcePtr[indexCnt] >> 2) & 0x3F];

        if (indexCnt == (DataLen - 1))
        {
            *tempPtr++ = NALCharSet[((SourcePtr[indexCnt] & 0x3) << 4)];
            *tempPtr++ = '=';
        }
        else
        {
            *tempPtr++ = NALCharSet[((SourcePtr[indexCnt] & 0x3) << 4) |
                                    ((int)(SourcePtr[indexCnt + 1] & 0xF0) >> 4)];
            *tempPtr++ = NALCharSet[((SourcePtr[indexCnt + 1] & 0xF) << 2)];
        }

        *tempPtr++     = '=';
    }


    *tempPtr++ = '\0';
    return tempPtr - DestPtr;
}
*/
const seq_parameter_set* get_sps(int id) { return sps[id]; }

//const pic_parameter_set* get_pps(int id) { return pps[id]; }

bool has_sps(int id) {return sps[id] != NULL;}

void printsome()
{
	printf("hello world");
}

//跳过前置信息和00 00 00 01信息，返回nal包开始的地址，若出错返回NULL
void locate_nal_start(const char * buf,unsigned int sz,char * out ,int * nal_len)
{
	const char * data = buf;
	char * out_start = out;
	int input_push_state = 0;	
	*nal_len = 0;
	for ( int i = 0 ; i < sz ; ++i)
	{
		switch(input_push_state)
			{
				case 0:
				case 1:
					if (*data == 0) { input_push_state++; }
					else { input_push_state=0; }		//跳过不满足格式的数据
					break;
				case 2:
					if(*data == 1) { input_push_state=3; } 
					else if (*data == 0) { } // *out++ = 0; }
					else { input_push_state=0; }
					break;
				case 3:
					*out++ = *data;
					input_push_state = 4;
					break;
				case 4:
					*out++ = *data;
					input_push_state = 5;
					break;
				case 5:
					if (*data==0) { input_push_state=6; }
					else {*out++ = *data; }
					break;
				case 6:
					//printf("enter 6 \n");
					if (*data==0) { input_push_state=7; }
					else {
						*out++ = 0x00;
						*out++ = *data;
						input_push_state=5;
					}
					break;

				case 7:
					//printf("enter 7\n");
					if(*data==0) {*out++ = 0x00; }
					else if (*data==3) {
						*out++ = 0x00;
						*out++ = 0x00;
						*out++ = *data;
						input_push_state=5;
					}
					else if (*data==1) {
						*nal_len = out - out_start;
						return;

					}
					else {
						*out++ = 0x00;
						*out++ = 0x00;
						*out++ = *data;

						input_push_state=5;
					}
					break;
			}//end of switch
		++data;
	}
	//*out++ = 0x00;
	*nal_len = out - out_start ;
	//printf("len %d\n",*nal_len);
	return;
}

h265_unit_type get_nal_type(const char * buf,unsigned int sz,char * out,int * nal_len)
{
	if(NULL == buf || sz < 2 )	//NAL header must bigger than 2 bytes
	{
		return H265_UNIT_BAD;
	}
	locate_nal_start(buf,sz,out,nal_len);
	if (nal_len <= 0)
	{
		return H265_UNIT_BAD;
	}
	//char txt[1024];
	//ConvertToNALString(txt,out,*nal_len);
	//printf("text : %s\n",txt);
	bitreader reader;
	bitreader_init(&reader,(unsigned char*)out,sz);
	nal_header nal_hdr;
	nal_hdr.read(&reader);
	int type = nal_hdr.nal_unit_type;
	return (type == NAL_UNIT_VPS_NUT ? H265_UNIT_VPS :( type == NAL_UNIT_SPS_NUT ? H265_UNIT_SPS : (type == NAL_UNIT_PPS_NUT ? H265_UNIT_PPS : H265_UNIT_DATA)));
	//return (buf[0]&0x7e)>>1;
}


/*
//if success return the id of decoded vps
//if error return value blow 0
int decode_vps(const char * buf,unsigned int sz)
{
	if (NULL == buf || sz < 2)
	{
		return -1;
	}
	bitreader reader;
	bitreader_init(&reader,(unsigned char*)(buf+2),sz);
	
	video_parameter_set* new_vps =new video_parameter_set();
	de265_error err = new_vps->read(&reader);
	
	if(err != DE265_OK)
		return -1;
	vps[new_vps->video_parameter_set_id] = new_vps;
	return new_vps->video_parameter_set_id;
}
*/
//if success return the id of decoded vps
//if error return value blow 0
int decode_sps(const char * buf,unsigned int sz)
{
	if (NULL == buf || sz < 2)
	{
		return -1;
	}
	bitreader reader;
	bitreader_init(&reader,(unsigned char*)(buf+2),sz);
	
	seq_parameter_set* new_sps = new seq_parameter_set();
	de265_error err;

	if ((err=new_sps->read(&reader)) != DE265_OK) {
		printf("not ok\n");
		return -1;
	}
	//printf("-----%d----\n",new_sps->seq_parameter_set_id);
	sps[ new_sps->seq_parameter_set_id ] = new_sps;
	return new_sps->seq_parameter_set_id;
}

//if success return the id of decoded vps
//if error return value blow 0
/*
int decode_pps(const char * buf,unsigned int sz)
{
	if (NULL == buf || sz < 2)
	{
		return -1;
	}
	bitreader reader;
	bitreader_init(&reader,(unsigned char*)(buf+2),sz);
	
	pic_parameter_set* new_pps = new pic_parameter_set();

	bool success = new_pps->read(&reader);
	if (!success)
		return -1;
	pps[ (int)new_pps->pic_parameter_set_id ] = new_pps;
	return (int)new_pps->pic_parameter_set_id;
}
*/

void strip_data(const char * buf,int buf_len,char * out,int * out_len)
{
	int state = 0;
	*out_len = buf_len;
	for (int i = 0 ; i < buf_len ; ++i)
	{
		switch(state)
		{
			case 0:
			case 1:
				*out++ = *buf;
				if(*buf == 0)	
					++state;
				else
					state = 0;	
				break;	
			case 2:
				if(*buf == 3 )
				{
					state = 0;
					--(*out_len);
				}
				else
				{
					*out++ =*buf;
					if(*buf != 0)	
						state = 0;
				}
			break;
				
		}
		++buf;
	}
}


int decode_width_height(const char * sps_buf,unsigned int sps_size,int * width,int * height)
{
	if(sps_buf == NULL || sps_size <= 2)
	{
		printf("input parameter error\n");
		return -1;
	}
	int sps_strip_len = sps_size;
	char * sps_strip_buf = (char *)malloc(sps_size);
	assert(NULL != sps_strip_buf);
	strip_data(sps_buf,sps_size,sps_strip_buf,&sps_strip_len);
	int sps_id = decode_sps(sps_strip_buf,sps_strip_len);
	if(sps_id <0)
		printf("decode sps failed\n") ;
	
	if(sps_id < 0 || sps_id >= DE265_MAX_SPS_SETS)
	{
		return -1;
	}
	const seq_parameter_set* cur_sps = get_sps(sps_id);
	if (cur_sps == NULL)
	{
		return -1;
	}
	*width = cur_sps->pic_width_in_luma_samples;
	*height = cur_sps->pic_height_in_luma_samples;
	return 0;
}
