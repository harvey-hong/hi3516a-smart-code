#ifndef T_TYPE_DISCOVERY

#define T_TYPE_DISCOVERY

#include "../InternalCommon.h"
#include "./TTypeTraits.h"

namespace   ApplicationLayer
{

#ifdef COMPILE_PLATFORM_GNU
struct  tag_data_structure_base;
struct  ISerializeBinaryObject;
struct  ISerializeXMLObject;
struct  ISerializeTextObject;
#endif

//类型匹配
typedef char match_type;
//类型不匹配
typedef int  mismatch_type;

//定义函数指针类型匹配
mismatch_type is_function_ptr_helper(...);
#if 1
template <typename R>
match_type is_function_ptr_helper(R(*)());
template <typename R, typename T0>
match_type is_function_ptr_helper(R(*)(T0));
template <typename R, typename T0, typename T1>
match_type is_function_ptr_helper(R(*)(T0, T1));
template <typename R, typename T0, typename T1, typename T2>
match_type is_function_ptr_helper(R(*)(T0, T1, T2));
template <typename R, typename T0, typename T1, typename T2, typename T3>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31));
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
match_type is_function_ptr_helper(R(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32));
#endif

//定义函数指针类型特化
template<bool is_reference = true>
struct is_function_type_helper
{
    template <typename T>
    struct is_function_type_impl
    {
        enum {value = false};
    };
};

template<>
struct is_function_type_helper<false>
{
    template<typename T>
    struct is_function_type_impl
    {
        static T *function_ptr;
        enum {value = sizeof(is_function_ptr_helper(function_ptr)) == 1};
    };
};

//定义函数特化
template<class RT = void()>
struct function_traits {};

template<class RT>
struct function_traits<RT()>
{
    typedef RT  return_type;
};

template<class RT, class AT>
struct function_traits<RT(AT)>
{
    typedef RT  return_type;
    typedef AT  argument_type;
};

template<class RT, class AT1, class AT2>
struct function_traits<RT(AT1, AT2)>
{
    typedef RT  return_type;
    typedef AT1 argument_type_first;
    typedef AT2 argument_type_second;
};

template<class RT, class OT>
struct function_traits<RT(OT::*)()>
{
    typedef RT  return_type;
};

template<class RT, class OT, class AT>
struct function_traits<RT(OT::*)(AT)>
{
    typedef RT  return_type;
    typedef AT  argument_type;
};

template<class RT, class OT, class AT1, class AT2>
struct function_traits<RT(OT::*)(AT1, AT2)>
{
    typedef RT  return_type;
    typedef AT1 argument_type_first;
    typedef AT2 argument_type_second;
};

//获取函数类型信息
template<typename T>
struct is_function_type
{
    enum {value = is_function_type_helper<is_reference_type<T>::value>::template
                  is_function_type_impl<T>::value
                                       };
};

//定义类类型特化
template<typename U> match_type         is_class_helper(void(U::*)(void));

template<typename U> mismatch_type      is_class_helper(...);

//获取类类型信息
template<typename T>
struct is_class
{
    enum {value = (sizeof(is_class_helper<T>(0)) == 1)};
};

////////////////////////////////////////////////////////////////////////

//获取类型可转换信息
template<typename S, typename T>
struct is_convertible
{
    static S _s;
    static match_type _check(T);
    static mismatch_type _check(...);
    enum {value = sizeof(_check(_s)) == 1};
};

//定义类型可转换信息特化
template<>
struct is_convertible<void, void>
{
    enum {value = true};
};

//定义指定类型可转换默认匹配
#define IS_CONVERTIBLE_SPECIAL(T1, T2)                                      \
    template<>                                                              \
    struct is_convertible<T1, T2>                                           \
    {                                                                       \
        enum {value = false};                                               \
    };

//定义指定类型可转换特化
#define IS_CONVERTIBLE_SPECCIAL_TRAITS(T1, T2)                              \
    IS_CONVERTIBLE_SPECIAL(T1, signed T2)                                   \
    IS_CONVERTIBLE_SPECIAL(T1, unsigned T2)

#define IS_CONVERTIBLE_FROM_FLOAT_SPECIAL(F)                                \
    IS_CONVERTIBLE_SPECIAL(F, char)                                         \
    IS_CONVERTIBLE_SPECCIAL_TRAITS(F, char)                                 \
    IS_CONVERTIBLE_SPECCIAL_TRAITS(F, short)                                \
    IS_CONVERTIBLE_SPECCIAL_TRAITS(F, int)                                  \
    IS_CONVERTIBLE_SPECCIAL_TRAITS(F, long)                                 \
    IS_CONVERTIBLE_SPECCIAL_TRAITS(F, long long)

#define IS_CONVERTIBLE_FROM_FLOAT_CV_SPECIAL(F)                             \
    IS_CONVERTIBLE_FROM_FLOAT_SPECIAL(F)                                    \
    IS_CONVERTIBLE_FROM_FLOAT_SPECIAL(F const)                              \
    IS_CONVERTIBLE_FROM_FLOAT_SPECIAL(F volatile)                           \
    IS_CONVERTIBLE_FROM_FLOAT_SPECIAL(F const volatile)

IS_CONVERTIBLE_FROM_FLOAT_CV_SPECIAL(float)
IS_CONVERTIBLE_FROM_FLOAT_CV_SPECIAL(double)
IS_CONVERTIBLE_FROM_FLOAT_CV_SPECIAL(long double)

#undef IS_CONVERTIBLE_FROM_FLOAT_CV_SPECIAL
#undef IS_CONVERTIBLE_FROM_FLOAT_SPECIAL
#undef IS_CONVERTIBLE_SPECCIAL_TRAITS
#undef IS_CONVERTIBLE_SPECIAL

////////////////////////////////////////////////////////////////////////

//获取枚举类型信息
template<typename T>
struct is_enum
{
    enum {value =
              !is_base_type<T>::value &&
              !is_reference_type<T>::value &&
              !is_function_type<T>::value &&
              !is_class<T>::value &&
              !is_array_type<T>::value &&
              is_convertible<T, int>::value
         };
};

////////////////////////////////////////////////////////////////////////

//获取类型继承关系信息
template<bool d_is_class, bool b_is_class, bool is_same>
struct is_derived_from_helper
{
    template<typename D, typename B>
    struct is_derived_from_impl
    {
        enum {value = false};
    };
};

template<>
struct is_derived_from_helper<true, true, false>
{
    template<typename D, typename B>
    struct is_derived_from_impl
    {
        enum {value = is_convertible<D *, B *>::value};
    };
};

template<typename D, typename B>
struct is_derived_from
{
    enum {value = is_derived_from_helper<is_class<D>::value, is_class<B>::value, is_same_type<D, B>::value>::template
          is_derived_from_impl<D, B>::value
                              };
};

////////////////////////////////////////////////////////////////////////

//获取字符类型信息
enum {eChar = 1, eWChar = 2};

template<typename charType>
struct charTypeDetector {};

template<>
struct charTypeDetector<char>
{
    enum {value = eChar};
};

template<>
struct charTypeDetector<const char>
{
    enum {value = eChar};
};

template<>
struct charTypeDetector<wchar_t>
{
    enum {value = eWChar};
};

template<>
struct charTypeDetector<const wchar_t>
{
    enum {value = eWChar};
};

////////////////////////////////////////////////////////////////////////

//获取数据类或结构类型
template<typename T>
struct is_structure_class
{
    enum {value =
              is_class<T>::value &&
              is_derived_from<T, tag_data_structure_base>::value
         };
};

////////////////////////////////////////////////////////////////////////

//获取具体基本类型
template<typename T>
struct is_concrete
{
    enum {value =
              (is_base_type<T>::value ||
               is_enum<T>::value ||
               is_structure_class<T>::value) &&
              !is_pointer_type<T>::value &&
              !is_reference_type<T>::value
         };
};

//获取指针类型
template<typename T>
struct is_pointer
{
    enum {value =
              is_pointer_type<T>::value &&
              !(is_same_type<typename remove_decorate_const<typename remove_decorate_pointer<T>::type>::type, char>::value ||
                is_same_type<typename remove_decorate_const<typename remove_decorate_pointer<T>::type>::type, wchar_t>::value)
         };
};

//获取数组类型
template<typename T>
struct is_array_concrete
{
    enum {value =
              is_array_type<T>::value &&
              (is_concrete<typename remove_decorate_array<T>::type>::value ||
               is_structure_class<typename remove_decorate_array<T>::type>::value)
         };
};

//获取字符串数组类型
template<typename T>
struct is_char_array
{
    enum {value =
              is_array_type<T>::value &&
              (is_char_type<typename remove_decorate_array<T>::type>::value || is_byte_type<typename remove_decorate_array<T>::type>::value)
         };
};

template<typename T>
struct is_array_nonconcrete
{
    enum {value =
              is_array_type<T>::value &&
              !(is_concrete<typename remove_decorate_array<T>::type>::value ||
                is_structure_class<typename remove_decorate_array<T>::type>::value)
         };
};

//获取字符串指针类型
template<typename T>
struct is_pointer_string
{
    enum {value =
              is_pointer_type<T>::value &&
              (is_same_type<typename remove_decorate_const<typename remove_decorate_pointer<T>::type>::type, char>::value ||
               is_same_type<typename remove_decorate_const<typename remove_decorate_pointer<T>::type>::type, wchar_t>::value)
         };
};

//获取可序列化二进制对象类型
template<typename T>
struct is_serializable_binary_class
{
    enum {value =
              is_class<T>::value &&
              is_derived_from<typename remove_decorate_const<T>::type, ISerializeBinaryObject>::value
         };
};

//获取可序列化XML对象类型
template<typename T>
struct is_serializable_xml_class
{
    enum {value =
              is_class<T>::value &&
              is_derived_from<typename remove_decorate_const<T>::type, ISerializeXMLObject>::value
         };
};

// 获取可序列化文本对象类型
template<typename T>
struct is_serializable_text_class
{
    enum {value =
              is_class<T>::value &&
              is_derived_from<typename remove_decorate_const<T>::type, ISerializeTextObject>::value
         };
};

////////////////////////////////////////////////////////////////////////

//获取标准类类型特化
template<typename T>
struct type2type
{
    typedef T type;
};

#define DECLARE_STD_CLASS_DETECTOR0(name, stdclass)                     \
    template<typename T>                                                \
    struct name                                                         \
    {                                                                   \
        static type2type<T> _ins;                                       \
        static match_type _check(type2type<stdclass>);                  \
        static mismatch_type _check(...);                               \
        enum {value = sizeof(match_type) == sizeof(_check(_ins))};      \
    };

#define DECLARE_STD_CLASS_DETECTOR2(name, stdclass)                     \
    template<typename T>                                                \
    struct name                                                         \
    {                                                                   \
        static T _ins;                                                  \
        template<typename T1, typename T2>                              \
        static match_type _check(const stdclass<T1, T2>&);              \
        static mismatch_type _check(...);                               \
        enum {value = sizeof(match_type) == sizeof(_check(_ins))};      \
    };

#define DECLARE_STD_CLASS_DETECTOR3(name, stdclass)                     \
    template<typename T>                                                \
    struct name                                                         \
    {                                                                   \
        static T _ins;                                                  \
        template<typename T1, typename T2, typename T3>                 \
        static match_type _check(const stdclass<T1, T2, T3>&);          \
        static mismatch_type _check(...);                               \
        enum {value = sizeof(match_type) == sizeof(_check(_ins))};      \
    };

#define DECLARE_STD_CLASS_DETECTOR4(name, stdclass)                     \
    template<typename T>                                                \
    struct name                                                         \
    {                                                                   \
        static T _ins;                                                  \
        template<typename T1, typename T2, typename T3, typename T4>    \
        static match_type _check(const stdclass<T1, T2, T3, T4>&);      \
        static mismatch_type _check(...);                               \
        enum {value = sizeof(match_type) == sizeof(_check(_ins))};      \
    };

DECLARE_STD_CLASS_DETECTOR0(is_std_string, std::string)
#ifndef COMPILE_PLATFORM_HISI_ARM
DECLARE_STD_CLASS_DETECTOR0(is_std_wstring, std::wstring)
#endif
DECLARE_STD_CLASS_DETECTOR2(is_std_vector_container, std::vector)
DECLARE_STD_CLASS_DETECTOR2(is_std_list_container, std::list)
DECLARE_STD_CLASS_DETECTOR2(is_std_deque_container, std::deque)
DECLARE_STD_CLASS_DETECTOR2(is_std_stack_container, std::stack)
DECLARE_STD_CLASS_DETECTOR2(is_std_queue_container, std::queue)
DECLARE_STD_CLASS_DETECTOR3(is_std_set_container, std::set)
DECLARE_STD_CLASS_DETECTOR3(is_std_multiset_container, std::multiset)
DECLARE_STD_CLASS_DETECTOR4(is_std_map_container, std::map)
DECLARE_STD_CLASS_DETECTOR4(is_std_multimap_container, std::multimap)
DECLARE_STD_CLASS_DETECTOR2(is_std_pair, std::pair);

#undef DECLARE_STD_CLASS_DETECTOR0
#undef DECLARE_STD_CLASS_DETECTOR2
#undef DECLARE_STD_CLASS_DETECTOR3
#undef DECLARE_STD_CLASS_DETECTOR4

////////////////////////////////////////////////////////////////////////

enum eTypeType
{
    zeroValue                       = 0,
    concrete,
    pointer,
    dataClass,
    serializableClass,
    pointerString,
    arrayConcrete,
    arrayNonconcrete,
    stdString,
#ifndef COMPILE_PLATFORM_HISI_ARM
    stdWstring = stdString,
#endif

    xmlAttribute,
    xmlText,

    textAttribute,

    stdIterator,
    stdNormalContainer,
    stdVector = stdNormalContainer,
    stdList = stdNormalContainer,
    stdDeque = stdNormalContainer,
    stdAdapterContainer,
    stdStack = stdAdapterContainer,
    stdQueue = stdAdapterContainer,
    stdAssociativeContainer,
    stdSet = stdAssociativeContainer,
    stdMultiset = stdSet,
    stdMap = stdAssociativeContainer,
    stdMultimap = stdMap,
    stdPair,
    endtype
};

enum eAtomicType
{
    invalidValue                        = 0,
    boolType,
    byteType,
    charpointerType,
    chararrayType,
    shortType,
    longType,
    floatType,
    longlongType,
    endType
};

#define DECLARE_TYPE_VALUE(type_name, type_value)                       \
    template<bool b>                                                    \
    struct type_name                                                    \
    {                                                                   \
        enum {value = zeroValue};                                       \
    };                                                                  \
    template<>                                                          \
    struct type_name <true>                                             \
    {                                                                   \
        enum {value = type_value};                                      \
    };

DECLARE_TYPE_VALUE(concreteValue, concrete)
DECLARE_TYPE_VALUE(pointerValue, pointer)
DECLARE_TYPE_VALUE(pointerStringValue, pointerString)
DECLARE_TYPE_VALUE(arrayConcreteValue, arrayConcrete)
DECLARE_TYPE_VALUE(arrayNonconcreteValue, arrayNonconcrete)
//DECLARE_TYPE_VALUE(dataClassValue, dataClass)
DECLARE_TYPE_VALUE(serializableClassValue, serializableClass)
DECLARE_TYPE_VALUE(stdStringClassValue, stdString)
#ifndef COMPILE_PLATFORM_HISI_ARM
DECLARE_TYPE_VALUE(stdWstringClassValue, stdWstring)
#endif
DECLARE_TYPE_VALUE(stdVectorClassValue, stdVector)
DECLARE_TYPE_VALUE(stdListClassValue, stdList)
DECLARE_TYPE_VALUE(stdDequeClassValue, stdDeque)
DECLARE_TYPE_VALUE(stdStackClassValue, stdStack)
DECLARE_TYPE_VALUE(stdQueueClassValue, stdQueue)
DECLARE_TYPE_VALUE(stdSetClassValue, stdSet)
DECLARE_TYPE_VALUE(stdMultisetClassValue, stdMultiset)
DECLARE_TYPE_VALUE(stdMapClassValue, stdMap)
DECLARE_TYPE_VALUE(stdMultimapClassValue, stdMultimap)
DECLARE_TYPE_VALUE(stdPairClassValue, stdPair)

DECLARE_TYPE_VALUE(xmlAttributeValue, xmlAttribute)
DECLARE_TYPE_VALUE(xmlTextValue, xmlText)

DECLARE_TYPE_VALUE(textAttributeValue, textAttribute)

DECLARE_TYPE_VALUE(boolValue, boolType)
DECLARE_TYPE_VALUE(byteValue, byteType)
DECLARE_TYPE_VALUE(charpointerValue, charpointerType)
DECLARE_TYPE_VALUE(chararrayValue, chararrayType)
DECLARE_TYPE_VALUE(shortValue, shortType)
DECLARE_TYPE_VALUE(longValue, longType)
DECLARE_TYPE_VALUE(floatValue, floatType)
DECLARE_TYPE_VALUE(longlongValue, longlongType)
#undef DECLARE_TYPE_VALUE

template<typename T>
struct typeValue
{
    enum
    {
        value =
            concreteValue           <is_concrete<T>::value>::value +
            pointerValue            <is_pointer<T>::value>::value +
            pointerStringValue      <is_pointer_string<T>::value>::value +
            arrayConcreteValue      <is_array_concrete<T>::value>::value +
            arrayNonconcreteValue   <is_array_nonconcrete<T>::value>::value +
            //dataClassValue            <is_structure_class<T>::value>::value +
            serializableClassValue  <is_serializable_binary_class<T>::value>::value +
            stdStringClassValue     <is_std_string<T>::value>::value +
#ifndef COMPILE_PLATFORM_HISI_ARM
            stdWstringClassValue    <is_std_wstring<T>::value>::value +
#endif
            stdVectorClassValue     <is_std_vector_container<T>::value>::value +
            stdListClassValue       <is_std_list_container<T>::value>::value +
            stdDequeClassValue      <is_std_deque_container<T>::value>::value +
            stdStackClassValue      <is_std_stack_container<T>::value>::value +
            stdQueueClassValue      <is_std_queue_container<T>::value>::value +
            stdSetClassValue        <is_std_set_container<T>::value>::value +
            stdMultisetClassValue   <is_std_multiset_container<T>::value>::value +
            stdMapClassValue        <is_std_map_container<T>::value>::value +
            stdMultimapClassValue   <is_std_multimap_container<T>::value>::value +
            stdPairClassValue       <is_std_pair<T>::value>::value
    };
};

template<typename T>
struct AtomicValue
{
    enum
    {
        value =
            boolValue               <is_bool_type<T>::value>::value +
            byteValue               < (is_char_type<T>::value || is_byte_type<T>::value) && !is_char_array<T>::value >::value +
            charpointerValue        < is_char_pointer_type<T>::value || is_byte_pointer_type<T>::value >::value +
            chararrayValue          <is_char_array<T>::value>::value +
            shortValue              <is_short_type<T>::value>::value +
            longValue               < is_long_type<T>::value || is_enum<T>::value >::value +
            floatValue              <is_float_type<T>::value>::value +
            longlongValue           <is_longlong_type<T>::value>::value
    };
};

//获取数组或容器等集合类型
template<typename T>
struct is_assembly_type
{
    enum
    {
        value =
            pointerStringValue      <is_pointer_string<T>::value>::value ||
            arrayConcreteValue      <is_array_concrete<T>::value>::value ||
            arrayNonconcreteValue   <is_array_nonconcrete<T>::value>::value ||
            stdVectorClassValue     <is_std_vector_container<T>::value>::value ||
            stdListClassValue       <is_std_list_container<T>::value>::value ||
            stdDequeClassValue      <is_std_deque_container<T>::value>::value ||
            stdStackClassValue      <is_std_stack_container<T>::value>::value ||
            stdQueueClassValue      <is_std_queue_container<T>::value>::value ||
            stdSetClassValue        <is_std_set_container<T>::value>::value ||
            stdMultisetClassValue   <is_std_multiset_container<T>::value>::value ||
            stdMapClassValue        <is_std_map_container<T>::value>::value ||
            stdMultimapClassValue   <is_std_multimap_container<T>::value>::value
    };
};

}

#endif
