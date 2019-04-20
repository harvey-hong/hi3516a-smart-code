#ifndef T_CONDITION_TYPE_H
#define T_CONDITION_TYPE_H

namespace   ApplicationLayer
{

template <bool condition, typename TA, typename TB>
struct TConditionType
{
    typedef TA  type;
};

template <typename TA, typename TB>
struct TConditionType<false, TA, TB>
{
    typedef TB  type;
};

}

#endif
