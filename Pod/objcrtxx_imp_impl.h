//
//  objcrtxx_imp_impl.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2016 address.wtf. All rights reserved.
//

#ifdef OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

imp_t imp_t::implementationWithBlock(id block)
{
    return imp_implementationWithBlock(block);
}

id imp_t::getBlock()
{
    return imp_getBlock(imp);
}

bool imp_t::removeBlock()
{
    return imp_removeBlock(imp);
}

template<typename TRet, typename ...TArgs>
TRet imp_t::invoke(id self_, SEL cmd_, TArgs... args) const
{
    return (reinterpret_cast<TRet(*)(id, SEL, TArgs...)>(imp))(self_, cmd_, args...);
}

OBJCRTXX_END_NAMESPACE

#endif // OBJCRTXX_UMBRELLA_ACTIVE
