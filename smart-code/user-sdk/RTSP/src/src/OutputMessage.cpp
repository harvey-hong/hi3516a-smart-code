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


//设置控制台消息状态
int COutputMessage::SetControlMessage(bool bState)
{
    m_bControlMessage = bState;
    return RET_SUCCESS;
}

//设置普通消息状态
int COutputMessage::SetOutputMessage(bool bState)
{
    m_bOutputMessage = bState;
    return RET_SUCCESS;
}

//获取控制台消息状态
int COutputMessage::GetControlMessage(bool &bState)
{
    bState = m_bControlMessage;
    return RET_SUCCESS;
}

//获取普通消息状态
int COutputMessage::GetOutputMessage(bool &bState)
{
    bState = m_bOutputMessage;
    return RET_SUCCESS;
}

//本地输出消息
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
    //输出信息到标准输出
    printf(buf);
#ifdef SYSTEM_WIN32

    if (m_bOutputMessage)
    {
        //输出信息到Debug窗口
        OutputDebugString(buf);
    }

#endif
    return 0;
}

//控制台输出消息
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
    //输出信息到标准输出
    printf(buf);
#ifdef SYSTEM_WIN32
    //输出信息到Debug窗口
    OutputDebugString(buf);
#endif
    return 0;
}

