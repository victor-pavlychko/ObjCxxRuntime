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

namespace traits
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

OBJCRTXX_END_NAMESPACE

#endif // OBJCRTXX_HAS_ABI
