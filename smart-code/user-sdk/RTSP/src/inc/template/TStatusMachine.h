#ifndef STATUS_MACHINE_H

#define STATUS_MACHINE_H

namespace   ApplicationLayer
{

template<class T_TYPE, int tiMax>
class TStatusMachine
{
public:
    TStatusMachine() {}
    virtual ~TStatusMachine() {}
    TStatusMachine(const TStatusMachine &rObj)
    {
        (*this) = rObj;
    }
    TStatusMachine &operator=(const TStatusMachine &rObj)
    {
        for (int iCount = 0; iCount < tiMax; iCount++)
        {
            //��ʼ��
            m_cState[iCount] = rObj.Get(iCount);
        }

        return (*this);
    }
    T_TYPE &operator[](int iIndex)
    {
        return m_cState[iIndex];
    }
public:
    //��ʼ��
    int Initialize(T_TYPE cState)
    {
        for (int iCount = 0; iCount < tiMax; iCount++)
        {
            //��ʼ��
            m_cState[iCount] = cState;
        }

        return 0;
    }
    //��ȡ״̬
    T_TYPE Get(int iIndex) const
    {
        return m_cState[iIndex];
    }
    //����״̬
    int Set(int iIndex, T_TYPE cState)
    {
        m_cState[iIndex] = cState;
        return 0;
    }
    //���״̬
    int Check(int iIndex, T_TYPE cState)
    {
        if (m_cState[iIndex] > cState)
        {
            //����ָ��ֵ
            return 2;
        }
        else if (m_cState[iIndex] < cState)
        {
            //С��ָ��ֵ
            return 1;
        }

        //���
        return 0;
    }
private:
    T_TYPE  m_cState[tiMax];
};

}

#endif
