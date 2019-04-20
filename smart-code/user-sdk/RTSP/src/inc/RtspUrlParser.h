/*!
* \file     RtspUrlParser.h
* \brief    rtsp url解析器
* \author   Cheng Yanfang
* \date     2010/08/16
* \version  1.0.0
*/

#ifndef RTSP_URL_PARSER_H_

#define RTSP_URL_PARSER_H_

#include "./HYRtspCommon.h"


// 实时流路径：rtsp://address/username@password/stream_mark/stream_type
// 历史流路径：rtsp://address/username@password/stream_mark/start_time@stop_time

namespace   ApplicationLayer
{

class CRtspUrlParser
{
public:
    CRtspUrlParser();
    ~CRtspUrlParser();
public:
    // 设置url
    int SetURL(char *pURL);
    // 获取RTSP流类型
    int GetRtspStreamType(eRtspStreamType &eStreamType);
    // 获取用户名和密码
    int GetUserNameAndPass(char *pUserName, char *pPassword);
    // 获取通道号
    int GetChannel(DWORD &dwChannel);
    // 获取流类型
    int GetMediaCodeType(eMediaCodeType &eCodeType);
    // 获取历史流时间段
    int GetHistoryTime(char *pStartTime, char *pEndTime);

protected:
    // 初始化
    int Initialize();
    // 设置RTSP流类型
    int SetRtspStreamType(eRtspStreamType eStreamType);
    // 设置用户名和密码
    int SetUserNameAndPass(char *pUserName, char *pPassword);
    // 设置通道号
    int SetChannel(DWORD dwChannel);
    // 设置编码类型
    int SetMediaCodeType(eMediaCodeType eCodeType);
    // 设置历史流时间段
    int SetHistoryTime(char *pStartTime, char *pEndTime);

private:
    char m_acUrl[MAX_RTSP_URL_LEN];                 //!< rtsp url
    eRtspStreamType m_eStreamType;                  //!< rtsp流类型
    char m_acUserName[USERNAME_LEN];                //!< 用户名
    char m_acPassword[USERPASS_LEN];                //!< 密码
    DWORD m_dwChannel;                              //!< 通道号
    eMediaCodeType m_eCodeType;                     //!< 实时流码流类型
    char m_acStartTime[DATE_TIME_LEN];              //!< 历史流起始时间
    char m_acEndTime[DATE_TIME_LEN];                //!< 历史流结束时间

};


}

#endif
