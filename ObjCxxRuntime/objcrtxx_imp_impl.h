//
//  objcrtxx_imp_impl.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

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

OBJCRTXX_END_NAMESPACE
