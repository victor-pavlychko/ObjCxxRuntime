//
//  objcrtxx_defs.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

#define OBJCRTXX_BEGIN_NAMESPACE    namespace address_wtf { namespace objcrtxx {
#define OBJCRTXX_END_NAMESPACE      } }

#define OBJCXX_PRIMITIVE_WRAPPER(self__, type__, var__, null__) \
    type__ var__ = null__; \
    self__(type__ var__ ## _): var__(var__ ## _) {}  \
    self__(const self__ &other): var__(other.var__) {} \
    self__(const self__ &&other): var__(other.var__) {} \
    self__ &operator=(const self__ &other) { var__ = other.var__; return *this; } \
    self__ &operator=(const type__ &other) { var__ = other; return *this; } \
    operator type__() { return var__; } \
    operator const type__&() const { return var__; } \
    operator bool() { return !!var__; } \
    type__ *operator&() { return &var__; } \
    const type__ *operator&() const { return &var__; } \

OBJCRTXX_BEGIN_NAMESPACE

typedef Protocol * __unsafe_unretained __Protocol_t;
typedef Class __unsafe_unretained __Class_t;
typedef struct objc_method_description *__objc_method_description_t;

template<typename TRet, typename ...TArgs>
TRet msgSend(id self_, SEL cmd_, TArgs... args)
{
    return (reinterpret_cast<TRet(*)(id, SEL, TArgs...)>(objc_msgSend))(self_, cmd_, args...);
}

template<typename TRet, typename ...TArgs>
TRet msgSend_stret(id self_, SEL cmd_, TArgs... args)
{
    return (reinterpret_cast<TRet(*)(id, SEL, TArgs...)>(objc_msgSend_stret))(self_, cmd_, args...);
}

template<typename TRet, typename ...TArgs>
TRet msgSendSuper(id self_, Class super_class, SEL cmd_, TArgs... args)
{
    struct objc_super super_ = {
        .receiver = self_,
        .super_class = super_class,
    };
    
    return (reinterpret_cast<TRet(*)(struct objc_super *, SEL, TArgs...)>(objc_msgSendSuper))(&super_, cmd_, args...);
}

template<typename TRet, typename ...TArgs>
TRet msgSendSuper_stret(id self_, Class super_class, SEL cmd_, TArgs... args)
{
    struct objc_super super_ = {
        .receiver = self_,
        .super_class = super_class,
    };
    
    return (reinterpret_cast<TRet(*)(struct objc_super *, SEL, TArgs...)>(objc_msgSendSuper_stret))(&super_, cmd_, args...);
}

OBJCRTXX_END_NAMESPACE
