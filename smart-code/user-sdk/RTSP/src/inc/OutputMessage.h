#ifndef OUTPUT_MESSAGE_H

#define OUTPUT_MESSAGE_H

class COutputMessage
{
public:
    COutputMessage();
    ~COutputMessage();
public:
    //�����Ϣ
    static int OutputMessage(const char *format, ...);
    //����̨�����Ϣ
    static int ControlMessage(const char *format, ...);
public:
    //���ÿ���̨��Ϣ״̬
    static int SetControlMessage(bool bState);
    //������ͨ��Ϣ״̬
    static int SetOutputMessage(bool bState);
    //��ȡ����̨��Ϣ״̬
    static int GetControlMessage(bool &bState);
    //��ȡ��ͨ��Ϣ״̬
    static int GetOutputMessage(bool &bState);
private:
    //�������̨��Ϣ״̬
    static bool m_bControlMessage;
    //�����ͨ��Ϣ״̬
    static bool m_bOutputMessage;
};

#endif
