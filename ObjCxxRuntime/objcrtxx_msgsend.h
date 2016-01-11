//
//  objcrtxx_defs.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

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
