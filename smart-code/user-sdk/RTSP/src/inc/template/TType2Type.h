#ifndef TYPE_2_TYPE_H

#define TYPE_2_TYPE_H

namespace   ApplicationLayer
{

template<bool bValue>
struct TBool2Type
{
    enum {type = bValue};
};

template<int iValue>
struct TInt2Type
{
    enum {type = iValue};
};

//True
struct TTrue
{
    enum {type = true};
    char a[1];
};

//False
struct TFalse
{
    enum {type = false};
    char a[2];
};

}

#endif
