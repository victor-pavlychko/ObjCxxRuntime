//
//  objcrtxx_typeencoding.h
//
//  Created by Victor Pavlychko on 2/14/16.
//  Copyright © 2016 address.wtf. All rights reserved.
//

#ifdef OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

namespace detail
{
    template<typename ...TTail>
    struct type_encoding_builder
    {
        enum { size = 1 };

        static inline void build(char *p)
        {
            *p = 0;
        }
    };
    
    template<typename THead, typename ...TTail>
    struct type_encoding_builder<THead, TTail...>
    {
        enum { size = type_encoding_builder<TTail...>::size + sizeof(@encode(THead)) - 1 };

        static inline void build(char *p)
        {
            strcpy(p, @encode(THead));
            type_encoding_builder<TTail...>::build(p + sizeof(@encode(THead)) - 1);
        }
    };
}

template<typename ...TTypes>
const char *encodeTypeList()
{
    static char value[detail::type_encoding_builder<TTypes...>::size];
    static dispatch_once_t onceToken = 0;
    dispatch_once(&onceToken, ^{
        detail::type_encoding_builder<TTypes...>::build(value);
    });

    return value;
}

template<typename TReturn, typename ...TArgs>
inline const char *encodeMethodType()
{
    return encodeTypeList<TReturn, id, SEL, TArgs...>();
}

template<typename TReturn, typename ...TArgs>
inline const char *encodeMethodType(TReturn(id, SEL, TArgs...))
{
    return encodeTypeList<TReturn, id, SEL, TArgs...>();
}

template<typename TReturn, typename ...TArgs>
inline const char *encodeMethodType(TReturn(^)(id, TArgs...))
{
    return encodeTypeList<TReturn, id, SEL, TArgs...>();
}

template<typename TReturn, typename TClass, typename ...TArgs>
inline const char *encodeMethodType(TReturn (TClass::* const)(id, TArgs...) const)
{
    return encodeTypeList<TReturn, id, SEL, TArgs...>();
}

template<typename TLambda>
inline const char *encodeMethodType(TLambda lambda)
{
    return encodeMethodType(&TLambda::operator());
}

OBJCRTXX_END_NAMESPACE

#endif // OBJCRTXX_UMBRELLA_ACTIVE
