#ifndef OUTPUT_MESSAGE_H

#define OUTPUT_MESSAGE_H

class COutputMessage
{
public:
    COutputMessage();
    ~COutputMessage();
public:
    //输出消息
    static int OutputMessage(const char *format, ...);
    //控制台输出消息
    static int ControlMessage(const char *format, ...);
public:
    //设置控制台消息状态
    static int SetControlMessage(bool bState);
    //设置普通消息状态
    static int SetOutputMessage(bool bState);
    //获取控制台消息状态
    static int GetControlMessage(bool &bState);
    //获取普通消息状态
    static int GetOutputMessage(bool &bState);
private:
    //输出控制台消息状态
    static bool m_bControlMessage;
    //输出普通消息状态
    static bool m_bOutputMessage;
};

#endif
