/*!
* \file     RtspUrlParser.h
* \brief    rtsp url������
* \author   Cheng Yanfang
* \date     2010/08/16
* \version  1.0.0
*/

#ifndef RTSP_URL_PARSER_H_

#define RTSP_URL_PARSER_H_

#include "./HYRtspCommon.h"


// ʵʱ��·����rtsp://address/username@password/stream_mark/stream_type
// ��ʷ��·����rtsp://address/username@password/stream_mark/start_time@stop_time

namespace   ApplicationLayer
{

class CRtspUrlParser
{
public:
    CRtspUrlParser();
    ~CRtspUrlParser();
public:
    // ����url
    int SetURL(char *pURL);
    // ��ȡRTSP������
    int GetRtspStreamType(eRtspStreamType &eStreamType);
    // ��ȡ�û���������
    int GetUserNameAndPass(char *pUserName, char *pPassword);
    // ��ȡͨ����
    int GetChannel(DWORD &dwChannel);
    // ��ȡ������
    int GetMediaCodeType(eMediaCodeType &eCodeType);
    // ��ȡ��ʷ��ʱ���
    int GetHistoryTime(char *pStartTime, char *pEndTime);

protected:
    // ��ʼ��
    int Initialize();
    // ����RTSP������
    int SetRtspStreamType(eRtspStreamType eStreamType);
    // �����û���������
    int SetUserNameAndPass(char *pUserName, char *pPassword);
    // ����ͨ����
    int SetChannel(DWORD dwChannel);
    // ���ñ�������
    int SetMediaCodeType(eMediaCodeType eCodeType);
    // ������ʷ��ʱ���
    int SetHistoryTime(char *pStartTime, char *pEndTime);

private:
    char m_acUrl[MAX_RTSP_URL_LEN];                 //!< rtsp url
    eRtspStreamType m_eStreamType;                  //!< rtsp������
    char m_acUserName[USERNAME_LEN];                //!< �û���
    char m_acPassword[USERPASS_LEN];                //!< ����
    DWORD m_dwChannel;                              //!< ͨ����
    eMediaCodeType m_eCodeType;                     //!< ʵʱ����������
    char m_acStartTime[DATE_TIME_LEN];              //!< ��ʷ����ʼʱ��
    char m_acEndTime[DATE_TIME_LEN];                //!< ��ʷ������ʱ��

};


}

#endif
