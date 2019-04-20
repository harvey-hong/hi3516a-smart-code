#ifndef T_ATOMIC_H
#define T_ATOMIC_H

namespace   ApplicationLayer
{

template<class T_ATOMIC>
class TAtomic
{
public:
    TAtomic() {}
    virtual ~TAtomic() {}
    TAtomic(const TAtomic &rObj)
    {
        (*this) = rObj;
    }
    TAtomic(const T_ATOMIC &rObj)
    {
        (*this) = rObj;
    }
    TAtomic &operator=(const TAtomic &rObj)
    {
        if (this != &rObj)
        {
            this->m_value = rObj;
        }

        return (*this);
    }
    TAtomic &operator=(const T_ATOMIC &rObj)
    {
        this->m_value = rObj;
        return (*this);
    }
    bool operator==(const TAtomic &rObj) const
    {
        return (this->m_value == rObj.m_value);
    }
    bool operator==(const T_ATOMIC &rObj) const
    {
        return (this->m_value == rObj);
    }
    operator T_ATOMIC() const
    {
        return this->m_value;
    }
    TAtomic operator++()
    {
        return (++(this->m_value));
    }
    TAtomic operator++(int)
    {
        return ((this->m_value)++);
    }
    TAtomic operator--()
    {
        return (--(this->m_value));
    }
    TAtomic operator--(int)
    {
        return ((this->m_value)--);
    }
    bool operator>(const TAtomic &rObj) const
    {
        return (this->m_value > rObj.m_value);
    }
    bool operator>(const T_ATOMIC &rObj) const
    {
        return (this->m_value > rObj);
    }
    bool operator<(const TAtomic &rObj) const
    {
        return (this->m_value < rObj.m_value);
    }
    bool operator<(const T_ATOMIC &rObj) const
    {
        return (this->m_value < rObj);
    }
    bool operator>=(const TAtomic &rObj) const
    {
        return (this->m_value >= rObj.m_value);
    }
    bool operator>=(const T_ATOMIC &rObj) const
    {
        return (this->m_value >= rObj);
    }
    bool operator<=(const TAtomic &rObj) const
    {
        return (this->m_value <= rObj.m_value);
    }
    bool operator<=(const T_ATOMIC &rObj) const
    {
        return (this->m_value <= rObj);
    }
    T_ATOMIC value() const
    {
        return this->m_value;
    }
    T_ATOMIC &value_ref()
    {
        return this->m_value;
    }
    T_ATOMIC *value_addr()
    {
        return (&(this->m_value));
    }
    int size() const
    {
        return sizeof(T_ATOMIC);
    }
private:
    T_ATOMIC    m_value;
};

#define DECLARE_OVERLOAD_ATOMIC_OPERATOR(x) \
    x(const x &rObj)\
    {\
        (*this) = rObj;\
    }\
    x(const T_ATOMIC &rObj)\
    {\
        (*this) = rObj;\
    }\
    x& operator=(const x &rObj)\
    {\
        if (this != &rObj)\
        {\
            TAtomic<T_ATOMIC>::operator=(rObj);\
        }\
        return (*this);\
    }\
    x& operator=(const T_ATOMIC &rObj)\
    {\
        TAtomic<T_ATOMIC>::operator=(rObj);\
        return (*this);\
    }\
    bool operator==(const x &rObj) const\
    {\
        return (TAtomic<T_ATOMIC>::operator==(rObj));\
    }\
    bool operator==(const T_ATOMIC &rObj) const\
    {\
        return (TAtomic<T_ATOMIC>::operator==(rObj));\
    }\
    operator T_ATOMIC() const\
    {\
        return TAtomic<T_ATOMIC>::value();\
    }\
    x operator++()\
    {\
        return (TAtomic<T_ATOMIC>::operator++());\
    }\
    x operator++(int iCount)\
    {\
        return (TAtomic<T_ATOMIC>::operator++(iCount));\
    }\
    x operator--()\
    {\
        return (TAtomic<T_ATOMIC>::operator--());\
    }\
    x operator--(int iCount)\
    {\
        return (TAtomic<T_ATOMIC>::operator--(iCount));\
    }\
    bool operator>(const x &rObj) const\
    {\
        return (TAtomic<T_ATOMIC>::operator>(rObj));\
    }\
    bool operator>(const T_ATOMIC &rObj) const\
    {\
        return (TAtomic<T_ATOMIC>::operator>(rObj));\
    }\
    bool operator<(const x &rObj) const\
    {\
        return (TAtomic<T_ATOMIC>::operator<(rObj));\
    }\
    bool operator<(const T_ATOMIC &rObj) const\
    {\
        return (TAtomic<T_ATOMIC>::operator<(rObj));\
    }\
    bool operator>=(const x &rObj) const\
    {\
        return (TAtomic<T_ATOMIC>::operator>=(rObj));\
    }\
    bool operator>=(const T_ATOMIC &rObj) const\
    {\
        return (TAtomic<T_ATOMIC>::operator>=(rObj));\
    }\
    bool operator<=(const x &rObj) const\
    {\
        return (TAtomic<T_ATOMIC>::operator<=(rObj));\
    }\
    bool operator<=(const T_ATOMIC &rObj) const\
    {\
        return (TAtomic<T_ATOMIC>::operator<=(rObj));\
    }

}

#endif
