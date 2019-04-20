#include "../inc/OutputMessage.h"
#include "../inc/GlobalObject.h"

bool COutputMessage::m_bControlMessage = true;
bool COutputMessage::m_bOutputMessage = true;

COutputMessage::COutputMessage()
{
    m_bControlMessage = true;
    m_bOutputMessage = true;
}

COutputMessage::~COutputMessage()
{
    m_bControlMessage = true;
    m_bOutputMessage = true;
}


//���ÿ���̨��Ϣ״̬
int COutputMessage::SetControlMessage(bool bState)
{
    m_bControlMessage = bState;
    return RET_SUCCESS;
}

//������ͨ��Ϣ״̬
int COutputMessage::SetOutputMessage(bool bState)
{
    m_bOutputMessage = bState;
    return RET_SUCCESS;
}

//��ȡ����̨��Ϣ״̬
int COutputMessage::GetControlMessage(bool &bState)
{
    bState = m_bControlMessage;
    return RET_SUCCESS;
}

//��ȡ��ͨ��Ϣ״̬
int COutputMessage::GetOutputMessage(bool &bState)
{
    bState = m_bOutputMessage;
    return RET_SUCCESS;
}

//���������Ϣ
int COutputMessage::OutputMessage(const char *format, ...)
{
    char buf[1024];
    va_list ap;
    va_start(ap, format);
#ifdef SYSTEM_WIN32
    int ilen = _vsnprintf(buf, sizeof(buf), format, ap);
#else
    int ilen = vsnprintf(buf, sizeof(buf), format, ap);
#endif
    va_end(ap);
    //�����Ϣ����׼���
    printf(buf);
#ifdef SYSTEM_WIN32

    if (m_bOutputMessage)
    {
        //�����Ϣ��Debug����
        OutputDebugString(buf);
    }

#endif
    return 0;
}

//����̨�����Ϣ
int COutputMessage::ControlMessage(const char *format, ...)
{
    if (!m_bControlMessage)
    {
        return 1;
    }

    char buf[1024];
    va_list ap;
    va_start(ap, format);
#ifdef SYSTEM_WIN32
    int ilen = _vsnprintf(buf, sizeof(buf), format, ap);
#else
    int ilen = vsnprintf(buf, sizeof(buf), format, ap);
#endif
    va_end(ap);
    //�����Ϣ����׼���
    printf(buf);
#ifdef SYSTEM_WIN32
    //�����Ϣ��Debug����
    OutputDebugString(buf);
#endif
    return 0;
}

