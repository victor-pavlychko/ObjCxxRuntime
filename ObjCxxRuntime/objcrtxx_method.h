//
//  objcrtxx_method.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

struct method_t
{
    OBJCXX_PRIMITIVE_WRAPPER(method_t, Method, method, NULL)
    
#if OBJCRTXX_HAS_ABI

    template<typename TRet, typename ...TArgs>
    typename std::enable_if<!detail::is_objc_stret<TRet>::value, TRet>::type invoke(id self_, TArgs... args);
    
    template<typename TRet, typename ...TArgs>
    typename std::enable_if<detail::is_objc_stret<TRet>::value, TRet>::type invoke(id self_, TArgs... args);

#endif // OBJCRTXX_HAS_ABI
    
    inline const sel_t getName();
    inline imp_t getImplementation();
    inline const char *getTypeEncoding();
    inline char *copyReturnType();
    inline char *copyArgumentType(unsigned int index);
    inline void getReturnType(char *dst, size_t dst_len);
    inline unsigned int getNumberOfArguments();
    inline void getArgumentType(unsigned int index, char *dst, size_t dst_len);
    inline detail::objc_method_description_t getDescription();
    inline imp_t setImplementation(imp_t imp);
    inline void exchangeImplementations(method_t other);
};

OBJCRTXX_END_NAMESPACE
