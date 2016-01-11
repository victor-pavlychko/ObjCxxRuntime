//
//  objcrtxx_ivar.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

struct ivar_t
{
    OBJCXX_PRIMITIVE_WRAPPER(ivar_t, Ivar, ivar, NULL)
    
    const char *    getName()           { return ivar_getName(ivar); }
    const char *    getTypeEncoding()   { return ivar_getTypeEncoding(ivar); }
    ptrdiff_t       getOffset()         { return ivar_getOffset(ivar); }
};

OBJCRTXX_END_NAMESPACE
