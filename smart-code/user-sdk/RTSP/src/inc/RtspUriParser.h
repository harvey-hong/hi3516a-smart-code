/*!
* \file     RtspUriParser.h
* \brief    rtsp uri解析器
* \author   lixiang
* \date     2010/08/16
* \version  1.0.0
*/

#ifndef RTSP_URI_PARSER_H_

#define RTSP_URI_PARSER_H_

#include "HYRtspCommon.h"
#include "InternalCommon.h"


// 实时流路径：rtsp://address/username@password/stream_mark/stream_type
// 历史流路径：rtsp://address/username@password/stream_mark/start_time@stop_time

namespace   ApplicationLayer
{

class CRtspUriParser
{
public:
    CRtspUriParser();
    ~CRtspUriParser();
public:
    // 设置uri
    int SetURI(const char *pURI);
    // 获取RTSP流类型
    int GetRtspStreamType(eRtspStreamType &eStreamType);
    // 获取用户名和密码
    const char *GetUserName();
    // 获取密码
    const char *GetPassword();
    // 获取通道号
    int GetChannel(int &nChannel);
    // 获取实时流类型
    int GetMediaCodeType(eRtspMediaCodeType &eCodeType);
    // 获取历史流开始时间
    const char *GetHistoryStartTime();
    // 获取历史流结束时间
    const char *GetHistoryEndTime();

    // 显示url信息
    int ShowUrlOnScreen();
    // 检查参数是否有效
    int IsParamValid();

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CRtspUriParser);

protected:
    // 初始化
    int Initialize();
    // 设置RTSP流类型
    int SetRtspStreamType(eRtspStreamType eStreamType);
    // 设置用户名和密码
    int SetUserNameAndPass(char *pUserName, char *pPassword);
    // 设置通道号
    int SetChannel(int nChannel);
    // 设置编码类型
    int SetMediaCodeType(eRtspMediaCodeType eCodeType);
    // 设置历史流时间段
    int SetHistoryTime(char *pStartTime, char *pEndTime);

private:
    // 从pRemainUriStartPos开始寻找第nLevel个DestStr，若存在，返回其位置指针；否则返回NULL
    char *GetPos(const char *pRemainUriStartPos, int nLevel, char *pDestStr);

private:
    char m_acUri[MAX_RTSP_URI_LEN];                 //!< rtsp uri
    eRtspStreamType m_eStreamType;                  //!< rtsp流类型
    char m_acUserName[USERNAME_LEN];                //!< 用户名
    char m_acPassword[USERPASS_LEN];                //!< 密码
    int  m_nChannel;                                //!< 通道号
    eRtspMediaCodeType m_eCodeType;                 //!< 码流类型
    char m_acStartTime[DATE_TIME_LEN];              //!< 历史流起始时间
    char m_acEndTime[DATE_TIME_LEN];                //!< 历史流结束时间

};


}

#endif
