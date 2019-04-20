#ifndef SHARE_POINT_H
#define SHARE_POINT_H

#include "../InternalCommon.h"

namespace   ApplicationLayer
{

template <class T_RESOURCE>
class TSharePoint
{
protected:
    class TSharePoint_Alone
    {
    public:
        TSharePoint_Alone(T_RESOURCE pRes)
        {
            m_pRes = pRes;
            m_uiCount = 1;
        }
        virtual ~TSharePoint_Alone()
        {
            if (0 == m_uiCount)
            {
                FREE_POINT_SAFE(m_pRes);
            }
        }
        //增加引用计数
        void AddCount()
        {
            m_uiCount += 1;
        }
        //减少引用计数
        unsigned int DecCount()
        {
            if (0 < m_uiCount)
            {
                m_uiCount -= 1;
            }
            else
            {
                return -1;
            }

            return m_uiCount;
        }
        //获取资源
        T_RESOURCE Resource()
        {
            return m_pRes;
        }
    protected:
        TSharePoint_Alone(const TSharePoint_Alone &rObj)
        {
            (*this) = rObj;
        }
        TSharePoint_Alone &operator=(const TSharePoint_Alone &rObj)
        {
            return (*this);
        }
    private:
        T_RESOURCE  m_pRes;                                                             //!< 资源指针
        unsigned int m_uiCount;                                                         //!< 资源引用计数
    };
public:
    TSharePoint()
    {
        Initialize(NULL);
    }
    TSharePoint(T_RESOURCE pRes)
    {
        Initialize(pRes);
    }
    TSharePoint(const TSharePoint &rRes)
    {
        (*this) = rRes;
    }
    TSharePoint &operator=(const TSharePoint &rRes)
    {
        this->m_pAlone = rRes.m_pAlone;

        //增加引用计数
        if (NULL != this->m_pAlone)
        {
            this->m_pAlone->AddCount();
        }

        return (*this);
    }
    bool operator==(TSharePoint &rRes)
    {
        return (this->m_pAlone == rRes.m_pAlone);
    }
    operator T_RESOURCE()
    {
        return Resource();
    }
    T_RESOURCE operator->()
    {
        return Resource();
    }
    void Initialize(T_RESOURCE pRes)
    {
        if (NULL != pRes)
        {
            //资源为空,创建资源
            this->m_pAlone = new TSharePoint_Alone(pRes);
        }
        else
        {
            this->m_pAlone = NULL;
        }
    }
    T_RESOURCE Resource()
    {
        //获取资源
        return m_pAlone->Resource();
    }
    virtual ~TSharePoint()
    {
        if (NULL != this->m_pAlone)
        {
            //减少引用计数
            if (0 == this->m_pAlone->DecCount())
            {
                //引用计数归零,释放资源
                FREE_POINT_SAFE(this->m_pAlone);
            }
            else
            {
                m_pAlone = NULL;
            }
        }
    }
private:
    TSharePoint_Alone *m_pAlone;
};

}

#endif
