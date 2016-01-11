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
    
    template<typename TRet, typename ...TArgs>
    TRet invoke(id self_, TArgs... args)
    {
        return (reinterpret_cast<TRet(*)(id, Method, TArgs...)>(method_invoke))(self_, method, args...);
    }

    template<typename TRet, typename ...TArgs>
    TRet invoke_stret(id self_, TArgs... args)
    {
        return (reinterpret_cast<TRet(*)(id, Method, TArgs...)>(method_invoke_stret))(self_, method, args...);
    }

    const sel_t                 getName()                                   { return method_getName(method); }
    imp_t                       getImplementation()                         { return method_getImplementation(method); }
    const char *                getTypeEncoding()                           { return method_getTypeEncoding(method); }
    char *                      copyReturnType()                            { return method_copyReturnType(method); }
    char *                      copyArgumentType(unsigned int index)        { return method_copyArgumentType(method, index); }
    void                        getReturnType(char *dst, size_t dst_len)    { return method_getReturnType(method, dst, dst_len); }
    unsigned int                getNumberOfArguments()                      { return method_getNumberOfArguments(method); }
    void                        getArgumentType(unsigned int index, char *dst, size_t dst_len)
    { return method_getArgumentType(method, index, dst, dst_len); }
    __objc_method_description_t getDescription()                            { return method_getDescription(method); }
    imp_t                       setImplementation(imp_t imp)                { return method_setImplementation(method, imp); }
    void                        exchangeImplementations(method_t other)     { return method_exchangeImplementations(method, other); }
};

OBJCRTXX_END_NAMESPACE
