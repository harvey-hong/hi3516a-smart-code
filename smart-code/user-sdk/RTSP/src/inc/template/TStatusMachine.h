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
            //初始化
            m_cState[iCount] = rObj.Get(iCount);
        }

        return (*this);
    }
    T_TYPE &operator[](int iIndex)
    {
        return m_cState[iIndex];
    }
public:
    //初始化
    int Initialize(T_TYPE cState)
    {
        for (int iCount = 0; iCount < tiMax; iCount++)
        {
            //初始化
            m_cState[iCount] = cState;
        }

        return 0;
    }
    //获取状态
    T_TYPE Get(int iIndex) const
    {
        return m_cState[iIndex];
    }
    //设置状态
    int Set(int iIndex, T_TYPE cState)
    {
        m_cState[iIndex] = cState;
        return 0;
    }
    //检查状态
    int Check(int iIndex, T_TYPE cState)
    {
        if (m_cState[iIndex] > cState)
        {
            //大于指定值
            return 2;
        }
        else if (m_cState[iIndex] < cState)
        {
            //小于指定值
            return 1;
        }

        //相等
        return 0;
    }
private:
    T_TYPE  m_cState[tiMax];
};

}

#endif
