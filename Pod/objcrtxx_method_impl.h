//
//  objcrtxx_method_impl.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2016 address.wtf. All rights reserved.
//

#ifdef OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

#if OBJCRTXX_HAS_ABI

template<typename TRet, typename ...TArgs>
typename std::enable_if<!traits::is_objc_stret<TRet>::value, TRet>::type method_t::invoke(id self_, TArgs... args)
{
    return (reinterpret_cast<TRet(*)(id, Method, TArgs...)>(method_invoke))(self_, method, args...);
}

template<typename TRet, typename ...TArgs>
typename std::enable_if<traits::is_objc_stret<TRet>::value, TRet>::type method_t::invoke(id self_, TArgs... args)
{
    return (reinterpret_cast<TRet(*)(id, Method, TArgs...)>(method_invoke_stret))(self_, method, args...);
}

#endif // OBJCRTXX_HAS_ABI

const sel_t method_t::getName()
{
    return method_getName(method);
}

imp_t method_t::getImplementation()
{
    return method_getImplementation(method);
}

const char *method_t::getTypeEncoding()
{
    return method_getTypeEncoding(method);
}

char *method_t::copyReturnType()
{
    return method_copyReturnType(method);
}

char *method_t::copyArgumentType(unsigned int index)
{
    return method_copyArgumentType(method, index);
}

void method_t::getReturnType(char *dst, size_t dst_len)
{
    return method_getReturnType(method, dst, dst_len);
}

unsigned int method_t::getNumberOfArguments()
{
    return method_getNumberOfArguments(method);
}

void method_t::getArgumentType(unsigned int index, char *dst, size_t dst_len)
{
    return method_getArgumentType(method, index, dst, dst_len);
}

detail::objc_method_description_t method_t::getDescription()
{
    return method_getDescription(method);
}

imp_t method_t::setImplementation(imp_t imp)
{
    return method_setImplementation(method, imp);
}

void method_t::exchangeImplementations(method_t other)
{
    return method_exchangeImplementations(method, other);
}

OBJCRTXX_END_NAMESPACE

#endif // OBJCRTXX_UMBRELLA_ACTIVE
