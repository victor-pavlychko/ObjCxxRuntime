//
//  objcrtxx_defs.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

#if OBJCRTXX_HAS_ABI

OBJCRTXX_BEGIN_NAMESPACE

namespace detail
{
    template<typename T> struct is_objc_stret: public std::integral_constant<bool,
        std::is_class<T>::value ||
        std::is_union<T>::value
    > {};

    template<typename T> struct is_objc_fpret:  public std::integral_constant<bool, false> {};
    template<typename T> struct is_objc_fp2ret: public std::integral_constant<bool, false> {};
 
#if defined(__arm__)

#elif defined(__i386__)

    template<> struct is_objc_fpret<float>:       public std::integral_constant<bool, true> {};
    template<> struct is_objc_fpret<double>:      public std::integral_constant<bool, true> {};
    template<> struct is_objc_fpret<long double>: public std::integral_constant<bool, true> {};

#elif defined(__x86_64__)

    template<> struct is_objc_fpret<long double>:           public std::integral_constant<bool, true> {};
    template<> struct is_objc_fp2ret<_Complex long double>: public std::integral_constant<bool, true> {};

#endif

    template<typename T> struct is_objc_plain: public std::integral_constant<bool,
        !is_objc_stret<T>::value &&
        !is_objc_fpret<T>::value &&
        !is_objc_fp2ret<T>::value
    > {};
}

template<typename TRet, typename ...TArgs>
static inline typename std::enable_if<detail::is_objc_plain<TRet>::value, TRet>::type msgSend(id self_, SEL cmd_, TArgs... args)
{
    return (reinterpret_cast<TRet(*)(id, SEL, TArgs...)>(objc_msgSend))(self_, cmd_, args...);
}

template<typename TRet, typename ...TArgs>
static inline typename std::enable_if<detail::is_objc_stret<TRet>::value, TRet>::type msgSend(id self_, SEL cmd_, TArgs... args)
{
    return (reinterpret_cast<TRet(*)(id, SEL, TArgs...)>(objc_msgSend_stret))(self_, cmd_, args...);
}

#if OBJCRTXX_HAS_ABI_FPRET

template<typename TRet, typename ...TArgs>
static inline typename std::enable_if<detail::is_objc_fpret<TRet>::value, TRet>::type msgSend(id self_, SEL cmd_, TArgs... args)
{
    return (reinterpret_cast<TRet(*)(id, SEL, TArgs...)>(objc_msgSend_fpret))(self_, cmd_, args...);
}

#endif // OBJCRTXX_HAS_ABI_FPRET

#if OBJCRTXX_HAS_ABI_FP2RET

template<typename TRet, typename ...TArgs>
static inline typename std::enable_if<detail::is_objc_fp2ret<TRet>::value, TRet>::type msgSend(id self_, SEL cmd_, TArgs... args)
{
    return (reinterpret_cast<TRet(*)(id, SEL, TArgs...)>(objc_msgSend_fp2ret))(self_, cmd_, args...);
}

#endif // OBJCRTXX_HAS_ABI_FP2RET

template<typename TRet, typename ...TArgs>
static inline typename std::enable_if<!detail::is_objc_stret<TRet>::value, TRet>::type msgSendSuper(id self_, Class super_class, SEL cmd_, TArgs... args)
{
    struct objc_super super_ = {
        .receiver = self_,
        .super_class = super_class,
    };
    
    return (reinterpret_cast<TRet(*)(struct objc_super *, SEL, TArgs...)>(objc_msgSendSuper))(super_, cmd_, args...);
}

template<typename TRet, typename ...TArgs>
static inline typename std::enable_if<detail::is_objc_stret<TRet>::value, TRet>::type msgSendSuper(id self_, Class super_class, SEL cmd_, TArgs... args)
{
    struct objc_super super_ = {
        .receiver = self_,
        .super_class = super_class,
    };
    
    return (reinterpret_cast<TRet(*)(struct objc_super *, SEL, TArgs...)>(objc_msgSendSuper_stret))(super_, cmd_, args...);
}

OBJCRTXX_END_NAMESPACE

#endif // OBJCRTXX_HAS_ABI
