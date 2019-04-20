/*!
* \file     RtspUriParser.h
* \brief    rtsp uri������
* \author   lixiang
* \date     2010/08/16
* \version  1.0.0
*/

#ifndef RTSP_URI_PARSER_H_

#define RTSP_URI_PARSER_H_

#include "HYRtspCommon.h"
#include "InternalCommon.h"


// ʵʱ��·����rtsp://address/username@password/stream_mark/stream_type
// ��ʷ��·����rtsp://address/username@password/stream_mark/start_time@stop_time

namespace   ApplicationLayer
{

class CRtspUriParser
{
public:
    CRtspUriParser();
    ~CRtspUriParser();
public:
    // ����uri
    int SetURI(const char *pURI);
    // ��ȡRTSP������
    int GetRtspStreamType(eRtspStreamType &eStreamType);
    // ��ȡ�û���������
    const char *GetUserName();
    // ��ȡ����
    const char *GetPassword();
    // ��ȡͨ����
    int GetChannel(int &nChannel);
    // ��ȡʵʱ������
    int GetMediaCodeType(eRtspMediaCodeType &eCodeType);
    // ��ȡ��ʷ����ʼʱ��
    const char *GetHistoryStartTime();
    // ��ȡ��ʷ������ʱ��
    const char *GetHistoryEndTime();

    // ��ʾurl��Ϣ
    int ShowUrlOnScreen();
    // �������Ƿ���Ч
    int IsParamValid();

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CRtspUriParser);

protected:
    // ��ʼ��
    int Initialize();
    // ����RTSP������
    int SetRtspStreamType(eRtspStreamType eStreamType);
    // �����û���������
    int SetUserNameAndPass(char *pUserName, char *pPassword);
    // ����ͨ����
    int SetChannel(int nChannel);
    // ���ñ�������
    int SetMediaCodeType(eRtspMediaCodeType eCodeType);
    // ������ʷ��ʱ���
    int SetHistoryTime(char *pStartTime, char *pEndTime);

private:
    // ��pRemainUriStartPos��ʼѰ�ҵ�nLevel��DestStr�������ڣ�������λ��ָ�룻���򷵻�NULL
    char *GetPos(const char *pRemainUriStartPos, int nLevel, char *pDestStr);

private:
    char m_acUri[MAX_RTSP_URI_LEN];                 //!< rtsp uri
    eRtspStreamType m_eStreamType;                  //!< rtsp������
    char m_acUserName[USERNAME_LEN];                //!< �û���
    char m_acPassword[USERPASS_LEN];                //!< ����
    int  m_nChannel;                                //!< ͨ����
    eRtspMediaCodeType m_eCodeType;                 //!< ��������
    char m_acStartTime[DATE_TIME_LEN];              //!< ��ʷ����ʼʱ��
    char m_acEndTime[DATE_TIME_LEN];                //!< ��ʷ������ʱ��

};


}

#endif
