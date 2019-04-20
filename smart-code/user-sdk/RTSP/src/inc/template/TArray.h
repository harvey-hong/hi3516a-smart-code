#ifndef T_ARRAY_H
#define T_ARRAY_H

namespace   ApplicationLayer
{

template<class T_ATOMIC, int iIndex>
class TArray
{
public:
    TArray() {}
    virtual ~TArray() {}
    TArray(const TArray &rObj)
    {
        (*this) = rObj;
    }
    TArray(const T_ATOMIC *rObj, const int iLength)
    {
        copy(this->value_addr(), rObj, iIndex);
    }
    TArray &operator=(const TArray &rObj)
    {
        if (this != &rObj)
        {
            copy(this->value_addr(), rObj.value_addr(), iIndex);
        }

        return (*this);
    }
    bool operator==(const TArray &rObj) const
    {
        return (0 == compare(this->value_addr(), rObj.value_addr()));
    }
    T_ATOMIC &operator[](int iCount)
    {
        return this->m_value[iCount];
    }
    T_ATOMIC *value_addr()
    {
        return this->m_value;
    }
    //从源拷贝信息到对象
    int copy(const T_ATOMIC *pSrc, const int iLength)
    {
        return copy(pSrc, m_value, iLength > iIndex ? iIndex : iLength);
    }
    //从对象拷贝信息到目地地
    int paste(const T_ATOMIC *pDst, const int iLength)
    {
        return copy(m_value, pDst, iLength > iIndex ? iIndex : iLength);
    }
    int size() const
    {
        return (sizeof(T_ATOMIC) * iIndex);
    }
    int length() const
    {
        return iIndex;
    }
protected:
    int compare(const T_ATOMIC *pSrc, const T_ATOMIC *pDst, int iLength)
    {
        int iCount ;

        for (iCount = 0; iCount < iLength; iCount++)
        {
            if (pSrc[iCount] > pDst[iCount])
            {
                return 1;
            }
            else if (pSrc[iCount] < pDst[iCount])
            {
                return 2;
            }
        }

        return 0;
    }
    int copy(const T_ATOMIC *pSrc, T_ATOMIC *pDst, int iLength)
    {
        int iCount;

        for (iCount = 0; iCount < iLength; iCount++)
        {
            pDst[iCount] = pSrc[iCount];
        }

        return 0;
    }
private:
    T_ATOMIC    m_value[iIndex];
};

//自动重载操作符(注意元素类型)
#define DECLARE_OVERLOAD_ARRAY_OPERATOR(x)  \
    x(const T_ATOMIC *rObj, const int iLength): TArray<T_ATOMIC, iIndex>(rObj, iIndex)\
    {\
    }\
    x& operator=(const x &rObj)\
    {\
        if (this != &rObj)\
        {\
            copy(this->TArray<T_ATOMIC, iIndex>::value_addr(), rObj.TArray<T_ATOMIC, iIndex>::value_addr(), iIndex);\
        }\
        return (*this);\
    }\
    bool operator==(const x &rObj) const\
    {\
        return (0 == compare(this->TArray<T_ATOMIC, iIndex>::value_addr(), rObj.TArray<T_ATOMIC, iIndex>::value_addr()));\
    }\
    T_ATOMIC& operator[](int iCount)\
    {\
        return this->TArray<T_ATOMIC, iIndex>::operator[](iCount);\
    }

}

#endif
