#ifndef T_TUPLE_H
#define T_TUPLE_H

#include "./TNullType.h"

//未对元组元素进行严格的控制与检查.
namespace   ApplicationLayer
{

template <typename THead, typename TTail>
struct TDuo;

template<int N>
struct TTupleElementType
{
    template<typename Tuple>
    class TTupleInner
    {
        typedef typename Tuple::TailType TailType;
        typedef TTupleElementType < N - 1 > NextType;
    public:
        typedef typename TTupleElementType < N - 1 >::template TTupleInner<TailType>::type type;
    };
};

/*!
* \class TTupleElementType
* \brief 元组集元素类型特化
*  TDuo<元素位置>
*/
template<>
struct TTupleElementType<0>
{
    template<typename Tuple>
    struct TTupleInner
    {
        typedef typename Tuple::HeadType type;
    };
};

/*!
* \class TTupleElement
* \brief 元组集元素
*  TDuo<元素位置, 元组位置>
*/
template<int N, typename Tuple>
class TTupleElement
{
    typedef TTupleElementType<N>    NthType;
public:
    typedef typename NthType::template TTupleInner<Tuple>::type type;
};

/*!
* \class TTupleGetElement
* \brief 获取元组集元素
*  TDuo<元素位置>
*/
template<int N>
struct TTupleGetElement
{
    template<typename Return, typename THead, typename TTail>
    static Return get(TDuo<THead, TTail> &u)
    {
        return TTupleGetElement < N - 1 >::template get<Return>(u.tail);
    }
};

/*!
* \class TTupleGetElement
* \brief 获取元组集元素特化
*  TDuo<元素位置>
*/
template<>
struct TTupleGetElement<0>
{
    template<typename Return, typename THead, typename TTail>
    static THead &get(TDuo<THead, TTail> &u)
    {
        return u.head;
    }
};

/*!
* \class TTupleGetElementFun
* \brief 获取元组集元素函数
*  TDuo<元素位置, 二元组头, 二元组尾>
*/
template <int N, typename THead, typename TTail>
static typename TTupleElement< N, TDuo<THead, TTail> >::type &TTupleGetElementFun(TDuo<THead, TTail> &u)
{
    return TTupleGetElement<N>::template get< typename TTupleElement<N, TDuo<THead, TTail> >::type &, THead, TTail >(u);
}

/*!
* \class TDuo
* \brief 二元组
*  TDuo<二元组头, 二元组尾>
*/
template <typename THead, typename TTail>
struct TDuo
{
    typedef THead   HeadType;
    typedef TTail   TailType;
    typedef TDuo<THead, TTail>  SelfType;

    HeadType    head;
    TailType    tail;

    HeadType &get_head()
    {
        return head;
    }
    TailType &get_tail()
    {
        return tail;
    }

    TDuo() : head(), tail() {}
    TDuo(const HeadType &h, const TailType &t) : head(h), tail(t) {}

    template <typename TA, typename TB, typename TC, typename TD, typename TE, typename TF, typename TG, typename TH,
              typename TI, typename TJ, typename TK, typename TL, typename TM, typename TN, typename TO, typename TP,
              typename TQ, typename TR, typename TS, typename TT, typename TU, typename TV, typename TW, typename TX,
              typename TY, typename TZ>
    TDuo(TA &ta, TB &tb, TC &tc, TD &td, TE &te, TF &tf, TG &tg, TH &th, TI &ti, TJ &tj, TK &tk, TL &tl, TM &tm,
         TN &tn, TO &to, TP &tp, TQ &tq, TR &tr, TS &ts, TT &tt, TU &tu, TV &tv, TW &tw, TX &tx, TY &ty, TZ &tz): head(ta),
        tail(tb, tc, td, te, tf, tg, th, ti, tj, tk, tl, tm, tn, to, tp, tq, tr, ts, tt, tu, tv, tw, tx, ty, tz, NullType()) {}

    template <typename TB, typename TC, typename TD, typename TE, typename TF, typename TG, typename TH,
              typename TI, typename TJ, typename TK, typename TL, typename TM, typename TN, typename TO, typename TP,
              typename TQ, typename TR, typename TS, typename TT, typename TU, typename TV, typename TW, typename TX,
              typename TY, typename TZ>
    TDuo(const NullType &ta, TB &tb, TC &tc, TD &td, TE &te, TF &tf, TG &tg, TH &th, TI &ti, TJ &tj, TK &tk, TL &tl, TM &tm,
         TN &tn, TO &to, TP &tp, TQ &tq, TR &tr, TS &ts, TT &tt, TU &tu, TV &tv, TW &tw, TX &tx, TY &ty, TZ &tz): head(),
        tail(tb, tc, td, te, tf, tg, th, ti, tj, tk, tl, tm, tn, to, tp, tq, tr, ts, tt, tu, tv, tw, tx, ty, tz, NullType()) {}

    template<typename THead1, typename TTail1>
    TDuo(const TDuo<THead1, TTail1> &duo) : head(duo.head), tail(duo.tail) {}

    template<typename THead1, typename TTail1>
    TDuo &operator=(const TDuo<THead1, TTail1> &duo)
    {
        head = duo.head;
        tail = duo.tail;
        return (*this);
    }

    TDuo &operator=(const TDuo &duo)
    {
        head = duo.head;
        tail = duo.tail;
        return (*this);
    }

    template<int N>
    typename TTupleElement< N, SelfType >::type &
    get()
    {
        return TTupleGetElementFun<N>(*this);
    }
};

/*!
* \class TDuo
* \brief 二元组特化一元组(尾为空)
*  TDuo<二元组头>
*/
template <typename THead>
struct TDuo <THead, NullType>
{
    typedef THead   HeadType;
    typedef NullType    TailType;
    typedef TDuo<THead, NullType>   SelfType;

    HeadType    head;

    HeadType &get_head()
    {
        return head;
    }
    TailType &get_tail()
    {
        return NullType();
    }

    TDuo() : head() {}
    TDuo(const HeadType &h, const TailType &t = NullType()) : head(h) {}

    template <typename TA>
    TDuo(TA &ta, const NullType &, const NullType &, const NullType &, const NullType &, const NullType &, const NullType &,
         const NullType &, const NullType &, const NullType &, const NullType &, const NullType &, const NullType &,
         const NullType &, const NullType &, const NullType &, const NullType &, const NullType &, const NullType &,
         const NullType &, const NullType &, const NullType &, const NullType &, const NullType &, const NullType &,
         const NullType &): head(ta) {}

    template<typename THead1>
    TDuo(const TDuo<THead1, NullType> &duo) : head(duo.head) {}

    template<typename THead1>
    TDuo &operator=(const TDuo<THead1, NullType> &duo)
    {
        head = duo.head;
        return (*this);
    }

    TDuo &operator=(const TDuo &duo)
    {
        head = duo.head;
        return (*this);
    }

    template<int N>
    typename TTupleElement< N, SelfType >::type &
    get()
    {
        return TTupleGetElementFun<N>(*this);
    }
};

/*!
* \class TTupleToDuo
* \brief 元组集转换为二元组
*  TTupleToDuo<元组元素集>
*/
template <typename TA, typename TB, typename TC, typename TD, typename TE, typename TF, typename TG, typename TH,
          typename TI, typename TJ, typename TK, typename TL, typename TM, typename TN, typename TO, typename TP,
          typename TQ, typename TR, typename TS, typename TT, typename TU, typename TV, typename TW, typename TX,
          typename TY, typename TZ>
struct TTupleToDuo
{
    typedef TDuo<TA, typename TTupleToDuo<TB, TC, TD, TE, TF, TG, TH, TI, TJ,
            TK, TL, TM, TN, TO, TP, TQ, TR, TS, TT, TU, TV, TW, TX, TY, TZ, NullType>::type > type;
};

/*!
* \class TTupleToDuo
* \brief 元组集转换为二元组特化
*  TTupleToDuo<元组元素集>
*/
template <>
struct TTupleToDuo<NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType,
        NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType,
        NullType, NullType, NullType, NullType, NullType, NullType>
{
    typedef NullType type;
};

/*!
* \class TTuple
* \brief 元组集类型
*  TTuple<元组元素集>
*/
template <typename TA, typename TB = NullType, typename TC = NullType, typename TD = NullType,
          typename TE = NullType, typename TF = NullType, typename TG = NullType, typename TH = NullType,
          typename TI = NullType, typename TJ = NullType, typename TK = NullType, typename TL = NullType,
          typename TM = NullType, typename TN = NullType, typename TO = NullType, typename TP = NullType,
          typename TQ = NullType, typename TR = NullType, typename TS = NullType, typename TT = NullType,
          typename TU = NullType, typename TV = NullType, typename TW = NullType, typename TX = NullType,
          typename TY = NullType, typename TZ = NullType>
struct TTuple : public TTupleToDuo<TA, TB, TC, TD, TE, TF, TG, TH, TI, TJ, TK, TL, TM, TN, TO, TP, TQ, TR, TS, TT, TU, TV, TW, TX, TY, TZ>::type
{
    typedef typename TTupleToDuo<TA, TB, TC, TD, TE, TF, TG, TH, TI, TJ, TK, TL, TM, TN, TO, TP, TQ, TR, TS, TT, TU, TV, TW, TX, TY, TZ>::type inherited;
    typedef typename inherited::HeadType HeadType;
    typedef typename inherited::TailType TailType;

    TTuple() {}

    TTuple(TA &ta, TB &tb = build_null(), TC &tc = build_null(), TD &td = build_null(),
           TE &te = build_null(), TF &tf = build_null(), TG &tg = build_null(), TH &th = build_null(),
           TI &ti = build_null(), TJ &tj = build_null(), TK &tk = build_null(), TL &tl = build_null(),
           TM &tm = build_null(), TN &tn = build_null(), TO &to = build_null(), TP &tp = build_null(),
           TQ &tq = build_null(), TR &tr = build_null(), TS &ts = build_null(), TT &tt = build_null(),
           TU &tu = build_null(), TV &tv = build_null(), TW &tw = build_null(), TX &tx = build_null(),
           TY &ty = build_null(), TZ &tz = build_null()) : inherited(ta, tb, tc, td, te, tf, tg, th, ti, tj, tk, tl,
                       tm, tn, to, tp, tq, tr, ts, tt, tu, tv, tw, tx, ty, tz) {}

    template<typename U1, typename U2>
    TTuple(const TDuo<U1, U2> &u) : inherited(u) {}

    template<typename U1, typename U2>
    TTuple &operator=(const TDuo<U1, U2> &u)
    {
        inherited::operator =(u);
        return (*this);
    }
};

/*!
* \class TTuple
* \brief 元组集类型特化
*  TTuple<元组元素集>
*/
template<>
struct TTuple<NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType,
        NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType,
        NullType, NullType, NullType, NullType, NullType, NullType, NullType>
{
    typedef NullType inherited;
};

/*!
* \class TTupleLength
* \brief 元组集类型长度
*  TTupleLength<元组类型>
*/
template <typename Tuple>
struct TTupleLength
{
    static const int value = 1 + TTupleLength<typename Tuple::TailType>::value;
};

/*!
* \class TTupleLength
* \brief 元组集类型长度特化
*  TTupleLength<元组类型>
*/
template <>
struct TTupleLength<NullType>
{
    static const int value = 0;
};

}

#endif
