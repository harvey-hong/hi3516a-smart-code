#ifndef T_TYPE_TRAITS

#define T_TYPE_TRAITS

#include "../InternalCommon.h"

namespace   ApplicationLayer
{

//定义类型特化默认匹配
#define DECLARE_TYPE_TRAITS_DEFAULT(name)                                   \
    template<typename T>                                                    \
    struct name                                                             \
    {                                                                       \
        enum{value = false};                                                \
    };

//定义类型不同匹配
#define DECLARE_TYPE_DIFFERENCE(name, T1, T2)                               \
    template<T1, T2>                                                        \
    struct name                                                             \
    {                                                                       \
        enum{value = false};                                                \
    };

//定义类型相同匹配
#define DECLARE_TYPE_SAME(name, T, S1, S2)                                  \
    template<T>                                                             \
    struct name<S1, S2>                                                     \
    {                                                                       \
        enum{value = true};                                                 \
    };

//定义指定类型特化
#define DECLARE_TYPE_TRAITS_SPECIAL(name, T, var)                           \
    template<>                                                              \
    struct name<T>                                                          \
    {                                                                       \
        enum{value = var};                                                  \
    };

//定义指定类型信息的局部
#define DECLARE_TYPE_PART_SPECIAL(name, S, var)                             \
    template<typename T>                                                    \
    struct name<S>                                                          \
    {                                                                       \
        enum{value = var};                                                  \
    };

//定义指定类型的组合
#define DECLARE_TYPE_COMPOSE(name, T1, T2, S)                               \
    template<T1, T2>                                                        \
    struct name<S>                                                          \
    {                                                                       \
        enum{value = true};                                                 \
    };

//定义移除类型修饰默认匹配
#define DECLARE_TYPE_REMOVE_DECORATE_DEFAULT(name)                          \
    template<typename T>                                                    \
    struct name                                                             \
    {                                                                       \
        typedef T type;                                                     \
    };

//定义移除部分类型修饰
#define DECLARE_TYPE_REMOVE_PART_DECORATE(name, S)                          \
    template<typename T>                                                    \
    struct name<S>                                                          \
    {                                                                       \
        typedef T type;                                                     \
    };

//定义移除部分类型修饰(两个类型)
#define DECLARE_TYPE_TWO_REMOVE_PART_DECORATE(name, T1, S)                  \
    template<typename T, T1>                                                \
    struct name<S>                                                          \
    {                                                                       \
        typedef T type;                                                     \
    };

////////////////////////////////////////////////////////////////////////

//定义基础类型特化
DECLARE_TYPE_TRAITS_DEFAULT(is_base_type)

/////////////////////////////////////////////////////////////////////////
//定义指定基础类型特化
#define DECLARE_BASE_TYPE_TRAITS(T)                                         \
    DECLARE_TYPE_TRAITS_SPECIAL(is_base_type, T, true)                      \
    DECLARE_TYPE_TRAITS_SPECIAL(is_base_type, T const, true)                \
    DECLARE_TYPE_TRAITS_SPECIAL(is_base_type, T volatile, true)             \
    DECLARE_TYPE_TRAITS_SPECIAL(is_base_type, T const volatile, true)

//定义指定基础类型特化
DECLARE_BASE_TYPE_TRAITS(char)
DECLARE_BASE_TYPE_TRAITS(bool)
//DECLARE_BASE_TYPE_TRAITS(short)
DECLARE_BASE_TYPE_TRAITS(float)
DECLARE_BASE_TYPE_TRAITS(double)
//DECLARE_BASE_TYPE_TRAITS(int)
//DECLARE_BASE_TYPE_TRAITS(long)
DECLARE_BASE_TYPE_TRAITS(long long)
DECLARE_BASE_TYPE_TRAITS(long double)
DECLARE_BASE_TYPE_TRAITS(signed char)
DECLARE_BASE_TYPE_TRAITS(unsigned char)
DECLARE_BASE_TYPE_TRAITS(signed short)
DECLARE_BASE_TYPE_TRAITS(unsigned short)
DECLARE_BASE_TYPE_TRAITS(signed int)
DECLARE_BASE_TYPE_TRAITS(unsigned int)
DECLARE_BASE_TYPE_TRAITS(signed long)
DECLARE_BASE_TYPE_TRAITS(unsigned long)
//DECLARE_BASE_TYPE_TRAITS(signed long long)
DECLARE_BASE_TYPE_TRAITS(unsigned long long)
#ifdef _NATIVE_WCHAR_T_DEFINED
DECLARE_BASE_TYPE_TRAITS(wchar_t)
#endif

#undef DECLARE_BASE_TYPE_TRAITS

//定义指定类型特化
#define DECLARE_SPECIAL_TYPE_TRAITS(D, T)                                   \
    DECLARE_TYPE_TRAITS_SPECIAL(D, T, true)                                 \
    DECLARE_TYPE_TRAITS_SPECIAL(D, T const, true)                           \
    DECLARE_TYPE_TRAITS_SPECIAL(D, T volatile, true)                        \
    DECLARE_TYPE_TRAITS_SPECIAL(D, T const volatile, true)

//是否为布尔类型
DECLARE_TYPE_TRAITS_DEFAULT(is_bool_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_bool_type, bool)

//是否为字符类型
DECLARE_TYPE_TRAITS_DEFAULT(is_char_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_char_type, char)

//是否为字节类型
DECLARE_TYPE_TRAITS_DEFAULT(is_byte_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_byte_type, unsigned char)

//是否为字符指针类型
DECLARE_TYPE_TRAITS_DEFAULT(is_char_pointer_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_char_pointer_type, char *)

//是否为字节指针类型
DECLARE_TYPE_TRAITS_DEFAULT(is_byte_pointer_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_byte_pointer_type, unsigned char *)

//是否为短整型
DECLARE_TYPE_TRAITS_DEFAULT(is_short_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_short_type, short)
DECLARE_SPECIAL_TYPE_TRAITS(is_short_type, unsigned short)

//是否为浮点型
DECLARE_TYPE_TRAITS_DEFAULT(is_float_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_float_type, float)
DECLARE_SPECIAL_TYPE_TRAITS(is_float_type, double)

//是否为长整型
DECLARE_TYPE_TRAITS_DEFAULT(is_long_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_long_type, int)
DECLARE_SPECIAL_TYPE_TRAITS(is_long_type, unsigned int)
DECLARE_SPECIAL_TYPE_TRAITS(is_long_type, long)
DECLARE_SPECIAL_TYPE_TRAITS(is_long_type, unsigned long)

//是否为超长整型
DECLARE_TYPE_TRAITS_DEFAULT(is_longlong_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_longlong_type, long long)
DECLARE_SPECIAL_TYPE_TRAITS(is_longlong_type, unsigned long long)

#undef DECLARE_SPECIAL_TYPE_TRAITS
////////////////////////////////////////////////////////////////////////

//定义不同类型匹配特化
DECLARE_TYPE_DIFFERENCE(is_same_type, typename T1, typename T2)
//定义相同类型匹配特化
DECLARE_TYPE_SAME(is_same_type, typename T, T, T)

//定义类型引用特化
DECLARE_TYPE_TRAITS_DEFAULT(is_reference_type)
//定义类型引用的局部特化
DECLARE_TYPE_PART_SPECIAL(is_reference_type, T &, true)

//定义类型指针特化
DECLARE_TYPE_TRAITS_DEFAULT(is_pointer_type)
//定义类型指针的局部特化
DECLARE_TYPE_PART_SPECIAL(is_pointer_type, T *, true)
DECLARE_TYPE_PART_SPECIAL(is_pointer_type, T *const, true)
DECLARE_TYPE_PART_SPECIAL(is_pointer_type, T *volatile, true)
DECLARE_TYPE_PART_SPECIAL(is_pointer_type, T *const volatile, true)

//定义类型数组特化
DECLARE_TYPE_TRAITS_DEFAULT(is_array_type)
DECLARE_TYPE_COMPOSE(is_array_type, typename T, int N, T[N])
DECLARE_TYPE_PART_SPECIAL(is_array_type, T[], true)

//定义类型成员指针特化
DECLARE_TYPE_TRAITS_DEFAULT(is_member_pointer)
DECLARE_TYPE_COMPOSE(is_member_pointer, typename T, typename C, T C::*)

//定义移除类型引用修饰特化
DECLARE_TYPE_REMOVE_DECORATE_DEFAULT(remove_decorate_reference)
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_reference, T &)

//定义移除类型指针修饰特化
DECLARE_TYPE_REMOVE_DECORATE_DEFAULT(remove_decorate_pointer)
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_pointer, T *)
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_pointer, T *const)
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_pointer, T *volatile)
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_pointer, T *const volatile)

//定义移除类型常量修饰特化
DECLARE_TYPE_REMOVE_DECORATE_DEFAULT(remove_decorate_const)
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_const, const T)

//定义移除类型数组修饰特化
DECLARE_TYPE_REMOVE_DECORATE_DEFAULT(remove_decorate_array)
DECLARE_TYPE_TWO_REMOVE_PART_DECORATE(remove_decorate_array, int N, T[N])
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_array, T[])

//定义类型特化默认匹配
#undef DECLARE_TYPE_TRAITS_DEFAULT
//定义类型不同匹配
#undef DECLARE_TYPE_DIFFERENCE
//定义类型相同匹配
#undef DECLARE_TYPE_SAME
//定义指定类型特化
#undef DECLARE_TYPE_TRAITS_SPECIAL
//定义指定类型信息的局部
#undef DECLARE_TYPE_PART_SPECIAL
//定义指定类型的组合
#undef DECLARE_TYPE_COMPOSE
//定义移除类型修饰默认匹配
#undef DECLARE_TYPE_REMOVE_DECORATE_DEFAULT
//定义移除部分类型修饰
#undef DECLARE_TYPE_REMOVE_PART_DECORATE
//定义移除部分类型修饰(两个类型)
#undef DECLARE_TYPE_TWO_REMOVE_PART_DECORATE

}

#endif
