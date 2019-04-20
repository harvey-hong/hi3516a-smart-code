#ifndef T_NULL_TYPE_H
#define T_NULL_TYPE_H

namespace   ApplicationLayer
{

struct NullType {};

inline const NullType build_null()
{
    return NullType();
}

}

#endif
