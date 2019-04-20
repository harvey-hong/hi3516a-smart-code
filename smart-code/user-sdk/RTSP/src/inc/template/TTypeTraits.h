#ifndef T_TYPE_TRAITS

#define T_TYPE_TRAITS

#include "../InternalCommon.h"

namespace   ApplicationLayer
{

//���������ػ�Ĭ��ƥ��
#define DECLARE_TYPE_TRAITS_DEFAULT(name)                                   \
    template<typename T>                                                    \
    struct name                                                             \
    {                                                                       \
        enum{value = false};                                                \
    };

//�������Ͳ�ͬƥ��
#define DECLARE_TYPE_DIFFERENCE(name, T1, T2)                               \
    template<T1, T2>                                                        \
    struct name                                                             \
    {                                                                       \
        enum{value = false};                                                \
    };

//����������ͬƥ��
#define DECLARE_TYPE_SAME(name, T, S1, S2)                                  \
    template<T>                                                             \
    struct name<S1, S2>                                                     \
    {                                                                       \
        enum{value = true};                                                 \
    };

//����ָ�������ػ�
#define DECLARE_TYPE_TRAITS_SPECIAL(name, T, var)                           \
    template<>                                                              \
    struct name<T>                                                          \
    {                                                                       \
        enum{value = var};                                                  \
    };

//����ָ��������Ϣ�ľֲ�
#define DECLARE_TYPE_PART_SPECIAL(name, S, var)                             \
    template<typename T>                                                    \
    struct name<S>                                                          \
    {                                                                       \
        enum{value = var};                                                  \
    };

//����ָ�����͵����
#define DECLARE_TYPE_COMPOSE(name, T1, T2, S)                               \
    template<T1, T2>                                                        \
    struct name<S>                                                          \
    {                                                                       \
        enum{value = true};                                                 \
    };

//�����Ƴ���������Ĭ��ƥ��
#define DECLARE_TYPE_REMOVE_DECORATE_DEFAULT(name)                          \
    template<typename T>                                                    \
    struct name                                                             \
    {                                                                       \
        typedef T type;                                                     \
    };

//�����Ƴ�������������
#define DECLARE_TYPE_REMOVE_PART_DECORATE(name, S)                          \
    template<typename T>                                                    \
    struct name<S>                                                          \
    {                                                                       \
        typedef T type;                                                     \
    };

//�����Ƴ�������������(��������)
#define DECLARE_TYPE_TWO_REMOVE_PART_DECORATE(name, T1, S)                  \
    template<typename T, T1>                                                \
    struct name<S>                                                          \
    {                                                                       \
        typedef T type;                                                     \
    };

////////////////////////////////////////////////////////////////////////

//������������ػ�
DECLARE_TYPE_TRAITS_DEFAULT(is_base_type)

/////////////////////////////////////////////////////////////////////////
//����ָ�����������ػ�
#define DECLARE_BASE_TYPE_TRAITS(T)                                         \
    DECLARE_TYPE_TRAITS_SPECIAL(is_base_type, T, true)                      \
    DECLARE_TYPE_TRAITS_SPECIAL(is_base_type, T const, true)                \
    DECLARE_TYPE_TRAITS_SPECIAL(is_base_type, T volatile, true)             \
    DECLARE_TYPE_TRAITS_SPECIAL(is_base_type, T const volatile, true)

//����ָ�����������ػ�
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

//����ָ�������ػ�
#define DECLARE_SPECIAL_TYPE_TRAITS(D, T)                                   \
    DECLARE_TYPE_TRAITS_SPECIAL(D, T, true)                                 \
    DECLARE_TYPE_TRAITS_SPECIAL(D, T const, true)                           \
    DECLARE_TYPE_TRAITS_SPECIAL(D, T volatile, true)                        \
    DECLARE_TYPE_TRAITS_SPECIAL(D, T const volatile, true)

//�Ƿ�Ϊ��������
DECLARE_TYPE_TRAITS_DEFAULT(is_bool_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_bool_type, bool)

//�Ƿ�Ϊ�ַ�����
DECLARE_TYPE_TRAITS_DEFAULT(is_char_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_char_type, char)

//�Ƿ�Ϊ�ֽ�����
DECLARE_TYPE_TRAITS_DEFAULT(is_byte_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_byte_type, unsigned char)

//�Ƿ�Ϊ�ַ�ָ������
DECLARE_TYPE_TRAITS_DEFAULT(is_char_pointer_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_char_pointer_type, char *)

//�Ƿ�Ϊ�ֽ�ָ������
DECLARE_TYPE_TRAITS_DEFAULT(is_byte_pointer_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_byte_pointer_type, unsigned char *)

//�Ƿ�Ϊ������
DECLARE_TYPE_TRAITS_DEFAULT(is_short_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_short_type, short)
DECLARE_SPECIAL_TYPE_TRAITS(is_short_type, unsigned short)

//�Ƿ�Ϊ������
DECLARE_TYPE_TRAITS_DEFAULT(is_float_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_float_type, float)
DECLARE_SPECIAL_TYPE_TRAITS(is_float_type, double)

//�Ƿ�Ϊ������
DECLARE_TYPE_TRAITS_DEFAULT(is_long_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_long_type, int)
DECLARE_SPECIAL_TYPE_TRAITS(is_long_type, unsigned int)
DECLARE_SPECIAL_TYPE_TRAITS(is_long_type, long)
DECLARE_SPECIAL_TYPE_TRAITS(is_long_type, unsigned long)

//�Ƿ�Ϊ��������
DECLARE_TYPE_TRAITS_DEFAULT(is_longlong_type)
DECLARE_SPECIAL_TYPE_TRAITS(is_longlong_type, long long)
DECLARE_SPECIAL_TYPE_TRAITS(is_longlong_type, unsigned long long)

#undef DECLARE_SPECIAL_TYPE_TRAITS
////////////////////////////////////////////////////////////////////////

//���岻ͬ����ƥ���ػ�
DECLARE_TYPE_DIFFERENCE(is_same_type, typename T1, typename T2)
//������ͬ����ƥ���ػ�
DECLARE_TYPE_SAME(is_same_type, typename T, T, T)

//�������������ػ�
DECLARE_TYPE_TRAITS_DEFAULT(is_reference_type)
//�����������õľֲ��ػ�
DECLARE_TYPE_PART_SPECIAL(is_reference_type, T &, true)

//��������ָ���ػ�
DECLARE_TYPE_TRAITS_DEFAULT(is_pointer_type)
//��������ָ��ľֲ��ػ�
DECLARE_TYPE_PART_SPECIAL(is_pointer_type, T *, true)
DECLARE_TYPE_PART_SPECIAL(is_pointer_type, T *const, true)
DECLARE_TYPE_PART_SPECIAL(is_pointer_type, T *volatile, true)
DECLARE_TYPE_PART_SPECIAL(is_pointer_type, T *const volatile, true)

//�������������ػ�
DECLARE_TYPE_TRAITS_DEFAULT(is_array_type)
DECLARE_TYPE_COMPOSE(is_array_type, typename T, int N, T[N])
DECLARE_TYPE_PART_SPECIAL(is_array_type, T[], true)

//�������ͳ�Աָ���ػ�
DECLARE_TYPE_TRAITS_DEFAULT(is_member_pointer)
DECLARE_TYPE_COMPOSE(is_member_pointer, typename T, typename C, T C::*)

//�����Ƴ��������������ػ�
DECLARE_TYPE_REMOVE_DECORATE_DEFAULT(remove_decorate_reference)
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_reference, T &)

//�����Ƴ�����ָ�������ػ�
DECLARE_TYPE_REMOVE_DECORATE_DEFAULT(remove_decorate_pointer)
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_pointer, T *)
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_pointer, T *const)
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_pointer, T *volatile)
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_pointer, T *const volatile)

//�����Ƴ����ͳ��������ػ�
DECLARE_TYPE_REMOVE_DECORATE_DEFAULT(remove_decorate_const)
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_const, const T)

//�����Ƴ��������������ػ�
DECLARE_TYPE_REMOVE_DECORATE_DEFAULT(remove_decorate_array)
DECLARE_TYPE_TWO_REMOVE_PART_DECORATE(remove_decorate_array, int N, T[N])
DECLARE_TYPE_REMOVE_PART_DECORATE(remove_decorate_array, T[])

//���������ػ�Ĭ��ƥ��
#undef DECLARE_TYPE_TRAITS_DEFAULT
//�������Ͳ�ͬƥ��
#undef DECLARE_TYPE_DIFFERENCE
//����������ͬƥ��
#undef DECLARE_TYPE_SAME
//����ָ�������ػ�
#undef DECLARE_TYPE_TRAITS_SPECIAL
//����ָ��������Ϣ�ľֲ�
#undef DECLARE_TYPE_PART_SPECIAL
//����ָ�����͵����
#undef DECLARE_TYPE_COMPOSE
//�����Ƴ���������Ĭ��ƥ��
#undef DECLARE_TYPE_REMOVE_DECORATE_DEFAULT
//�����Ƴ�������������
#undef DECLARE_TYPE_REMOVE_PART_DECORATE
//�����Ƴ�������������(��������)
#undef DECLARE_TYPE_TWO_REMOVE_PART_DECORATE

}

#endif
