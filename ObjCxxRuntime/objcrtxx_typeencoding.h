//
//  objcrtxx_typeencoding.h
//  ObjCxxRuntime
//
//  Created by Victor Pavlychko on 2/14/16.
//  Copyright © 2016 address.wtf. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

namespace detail
{
    template<typename ...TTail>
    struct type_encodings
    {
        static inline void appendEncodings(std::stringstream &stream)
        {
        }
    };
    
    template<typename THead, typename ...TTail>
    struct type_encodings<THead, TTail...>
    {
        static inline void appendEncodings(std::stringstream &stream)
        {
            stream << @encode(THead);
            type_encodings<TTail...>::appendEncodings(stream);
        }
    };
}

template<typename ...TTypes>
std::string encodeTypeList()
{
    std::stringstream stream;
    detail::type_encodings<TTypes...>::appendEncodings(stream);
    return stream.str();
}

template<typename TReturn, typename ...TArgs>
std::string encodeMethodType()
{
    return encodeTypeList<TReturn, id, SEL, TArgs...>();
}

template<typename TReturn, typename ...TArgs>
std::string encodeMethodType(TReturn(id, SEL, TArgs...))
{
    return encodeTypeList<TReturn, id, SEL, TArgs...>();
}

template<typename TReturn, typename ...TArgs>
std::string encodeMethodType(TReturn(^)(id, TArgs...))
{
    return encodeTypeList<TReturn, id, SEL, TArgs...>();
}

template<typename TReturn, typename TClass, typename ...TArgs>
std::string encodeMethodType(TReturn (TClass::* const)(id, TArgs...) const)
{
    return encodeTypeList<TReturn, id, SEL, TArgs...>();
}

template<typename TLambda>
std::string encodeMethodType(TLambda lambda)
{
    return encodeMethodType(&TLambda::operator());
}

OBJCRTXX_END_NAMESPACE
