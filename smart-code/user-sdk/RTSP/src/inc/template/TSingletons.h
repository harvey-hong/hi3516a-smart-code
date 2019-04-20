#ifndef SINGLETONS_H

#define SINGLETONS_H

namespace   ApplicationLayer
{

template<class T_TYPE>
class TSingletons
{
public:
    static T_TYPE &Instance()
    {
        static T_TYPE g_Instance;
        return g_Instance;
    }

protected:
    TSingletons()
    {}
    TSingletons(const TSingletons &)
    {}
    TSingletons &operator=(const TSingletons &)
    {
        return this;
    }
    virtual ~TSingletons()
    {}
};

}

#endif
