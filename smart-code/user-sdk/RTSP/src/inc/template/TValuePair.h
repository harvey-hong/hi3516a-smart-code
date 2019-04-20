#ifndef VALUE_PAIR_H
#define VALUE_PAIR_H

namespace   ApplicationLayer
{

template <class T_LEFT, class T_RIGHT>
class TValuePair
{
public:
    TValuePair()
    {
    }
    TValuePair(T_LEFT cLeft, T_RIGHT cRight)
    {
        Initialize(cLeft, cRight);
    }
    TValuePair(const TValuePair &rObj)
    {
        (*this) = rObj;
    }
    TValuePair &operator=(const TValuePair &rObj)
    {
        if (this != &rObj)
        {
            this->m_cLeft = rObj.m_cLeft;
            this->m_cRight = rObj.m_cRight;
        }

        return (*this);
    }
    bool operator==(TValuePair &rObj)
    {
        return ((this->m_cLeft == rObj.m_cLeft) || (this->m_cRight == rObj.m_cRight));
    }
    virtual ~TValuePair()
    {
    }
    int Initialize(T_LEFT cLeft, T_RIGHT cRight)
    {
        m_cLeft = cLeft;
        m_cRight = cRight;
        return 0;
    }
    int SetLeft(T_LEFT cLeft)
    {
        m_cLeft = cLeft;
        return 0;
    }
    int GetLeft(T_LEFT &cLeft)
    {
        cLeft = m_cLeft;
        return 0;
    }
    int SetRight(T_RIGHT cRight)
    {
        m_cRight = cRight;
        return 0;
    }
    int GetRight(T_RIGHT cRight)
    {
        cRight = m_cRight;
        return 0;
    }
    T_LEFT GetLeft()
    {
        //获取左值
        return m_cLeft;
    }
    T_RIGHT GetRight()
    {
        //获取左值
        return m_cRight;
    }
private:
    //左值
    T_LEFT m_cLeft;
    //右值
    T_RIGHT m_cRight;
};

}

#endif
