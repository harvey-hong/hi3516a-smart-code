#include "../inc/GlobalObject.h"
#include "../inc/Property.h"
#include "../inc/RtspUriParser.h"

namespace ApplicationLayer
{
CRtspUriParser::CRtspUriParser()
{
    Initialize();
}

CRtspUriParser::~CRtspUriParser()
{
    Initialize();
}

// ��ʼ��
int CRtspUriParser::Initialize()
{
    memset(m_acUri, 0, MAX_RTSP_URI_LEN);
    memset(m_acUserName, 0, USERNAME_LEN);
    memset(m_acPassword, 0, USERPASS_LEN);
    memset(m_acStartTime, 0, DATE_TIME_LEN);
    memset(m_acEndTime, 0, DATE_TIME_LEN);
    m_eStreamType = eRtspStreamTypeBegin;
    m_eCodeType = eRtspMediaCodeTypeBegin;
    m_nChannel = -1;
    return RET_SUCCESS;
}

//\\ ��pRemainUriStartPos��ʼѰ�ҵ�nLevel��DestStr�������ڣ�������λ��ָ�룻���򷵻�NULL
char *CRtspUriParser::GetPos(const char *pRemainUriStartPos, int nLevel, char *pDestStr)
{
    if (NULL == pRemainUriStartPos || NULL == pDestStr || nLevel <= 0)
    {
        return NULL;
    }

    int     nDestStrLen = strlen(pDestStr);
    // Ѱ�����������ĵ�nLevel��pDestStr
    char *pUriPtr = (char *)pRemainUriStartPos;

    while (1)
    {
        pUriPtr = strstr(pUriPtr, pDestStr);

        if (pUriPtr == NULL)
        {
            break;
        }

        nLevel--;

        if (0 == nLevel)
        {
            break;
        }

        pUriPtr = pUriPtr + nDestStrLen;
    }

    return pUriPtr;
}


// ʵʱ�� rtsp://address/username[@password]/stream_mark[/stream_type]
// ��ʷ�� rtsp://address/username[@password]/stream_mark/start_time[@stop_time]
// rtsp://%s:%d/admin@admin/ch1_s1  or rtsp://%s:%d/admin@admin/ch1_s2
//\\ ��URI�н������û��������롢ͨ���š�������������������Ϣ��ʵʱ��������ʷ����Ϣ(Ŀǰֻ�ܽ���ʵʱ������ͨ��ʱ�쳣)
//\\2012.10.22 Hzg rtsp://xxx.xxx.xxx.xxx/ch1_s1  or rtsp://xxx.xxx.xxx.xxx/ch1_s2
int CRtspUriParser::SetURI(const char *pURI)
{
    if (CHECK_POINT_NULL(pURI) || strlen(pURI) >= MAX_RTSP_URI_LEN)
    {
        return eErrorParameter;
    }

    int nRet = RET_SUCCESS;
    int i;
    //\\ ����RTSP�����URI
    Initialize();
    strcpy(m_acUri, pURI);
    int     nUriLen = strlen(pURI);
    char *pStart = NULL;
    char *pEnd = NULL;
    pStart = GetPos(pURI, 3, "/");

    if (NULL == pStart || (pStart + 1 == pURI + nUriLen))
    {
        memset(m_acUserName, 0, USERNAME_LEN);
        memset(m_acPassword, 0, USERPASS_LEN);
        m_eStreamType = eRtspStreamReal;
        m_eCodeType = eRtspMediaCodeAdapt;
        m_nChannel = 0;
        return RET_SUCCESS;
    }

    pEnd = GetPos(pStart + 1, 1, "/");

    if (NULL == pEnd)
    {
            pEnd = (char *)pURI + nUriLen;
        }
        if (int(pEnd - 1 - pStart) < 0 || int(pEnd - 1 - pStart) >= 64)
        {
            return RET_FAIL;
        }

        m_nChannel      = 0;
        // Hongzg added for MileStone, dahua NVR select stream1 or stream2 start read stream string "ch1_s1" or "ch1_s2"
        pEnd = GetPos(pStart + 1, 1, "/");
        if (NULL == pEnd)
        {
            pEnd = (char *)pURI + nUriLen;
        }
        if (int(pEnd - 1 - pStart) < 0 || int(pEnd - 1 - pStart) >= 64)
        {
            return RET_FAIL;
        }

        char acStreamMark[64] = {0};
        memmove(acStreamMark, pStart + 1, int(pEnd - 1 - pStart));
        int nStreamMarkLen = strlen(acStreamMark);
        m_eStreamType = eRtspStreamReal;
        int ret = sscanf(acStreamMark, "ch%d_s%d", &m_nChannel, &m_eCodeType);
        if (2 != ret)
        {
            return RET_FAIL;
        }
        else
        {
            return RET_SUCCESS;
        }
    }


// ��ȡrtsp������
    int CRtspUriParser::GetRtspStreamType(eRtspStreamType &eStreamType)
{
    eStreamType = m_eStreamType;
    return RET_SUCCESS;
}

// ����rtsp������
int CRtspUriParser::SetRtspStreamType(eRtspStreamType eStreamType)
{
    if (eRtspStreamTypeBegin >= eStreamType || eStreamType >= eRtspStreamTypeEnd)
    {
        OUTC_SIMPLE_FAILED;
        return RET_FAIL;
    }

    m_eStreamType = eStreamType;
    return RET_SUCCESS;
}

// ��ȡ�û���������
const char *CRtspUriParser::GetUserName()
{
    return m_acUserName;
}

// ��ȡ����
const char *CRtspUriParser::GetPassword()
{
    return m_acPassword;
}

// �����û���������
int CRtspUriParser::SetUserNameAndPass(char *pUserName, char *pPassword)
{
    if (strlen(pUserName) > USERNAME_LEN - 1 || strlen(pPassword) > USERPASS_LEN - 1)
    {
        OUTC_SIMPLE_FAILED;
        return RET_FAIL;
    }

    strcpy(m_acUserName, pUserName);
    strcpy(m_acPassword, pPassword);
    return RET_SUCCESS;
}

// ��ȡͨ����
int CRtspUriParser::GetChannel(int &nChannel)
{
    nChannel = m_nChannel;
    return RET_SUCCESS;
}

// ����ͨ����
int CRtspUriParser::SetChannel(int nChannel)
{
    if (nChannel < 0 || nChannel >= MAX_CHANNEL_NUMBER)
    {
        OUTC_SIMPLE_FAILED;
        return RET_FAIL;
    }

    m_nChannel = nChannel;
    return RET_SUCCESS;
}

// ��ȡ������
int CRtspUriParser::GetMediaCodeType(eRtspMediaCodeType &eCodeType)
{
    eCodeType = m_eCodeType;
    return RET_SUCCESS;
}

// ����������
int CRtspUriParser::SetMediaCodeType(eRtspMediaCodeType eCodeType)
{
    if (eRtspMediaCodeTypeBegin >= eCodeType || eCodeType >= eRtspMediaCodeTypeEnd)
    {
        OUTC_SIMPLE_FAILED;
        return RET_FAIL;
    }

    m_eCodeType = eCodeType;
    return RET_SUCCESS;
}

// ��ȡ��ʷ����ʼʱ��
const char *CRtspUriParser::GetHistoryStartTime()
{
    return m_acStartTime;
}

// ��ȡ��ʷ������ʱ��
const char *CRtspUriParser::GetHistoryEndTime()
{
    return m_acEndTime;
}

// ������ʷ��ʱ���
int CRtspUriParser::SetHistoryTime(char *pStartTime, char *pEndTime)
{
    if (strlen(pStartTime) > DATE_TIME_LEN - 1 || strlen(pEndTime) > DATE_TIME_LEN - 1)
    {
        OUTC_SIMPLE_FAILED;
        return RET_FAIL;
    }

    strcpy(m_acStartTime, pStartTime);
    strcpy(m_acEndTime, pEndTime);
    return RET_SUCCESS;
}

int CRtspUriParser::ShowUrlOnScreen()
{
    //      OUTC_TRACK("url = %s\n", m_acUri);
    //      OUTC_TRACK("Username = %s, Password = %s\n", m_acUserName, m_acPassword);
    //      OUTC_TRACK("channel = %d\n", m_nChannel);
    //      OUTC_TRACK("Streamtype = %d\n", (int)m_eStreamType);
    //      OUTC_TRACK("CodeType = %d\n", (int)m_eCodeType);
    //      OUTC_TRACK("StartTime = %s, EndTime = %s\n", m_acStartTime, m_acEndTime);
    return RET_SUCCESS;
}

//\\ ȷ���Ƿ���յ�URI��Ϣ
int CRtspUriParser::IsParamValid()
{
    if (strlen(m_acUri) > 0)
    {
        return RET_SUCCESS;
    }
    else
    {
        return RET_FAIL;
    }
}

}
