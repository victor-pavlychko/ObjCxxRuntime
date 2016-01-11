//
//  objcrtxx_imp.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

struct imp_t
{
    OBJCXX_PRIMITIVE_WRAPPER(imp_t, IMP, imp, NULL)
    
    inline static imp_t implementationWithBlock(id block);
    inline id getBlock();
    inline bool removeBlock();
};

OBJCRTXX_END_NAMESPACE
