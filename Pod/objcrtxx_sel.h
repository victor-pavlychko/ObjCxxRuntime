//
//  objcrtxx_sel.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

struct sel_t
{
    OBJCXX_PRIMITIVE_WRAPPER(sel_t, SEL, sel, NULL)

    inline static sel_t registerName(const char *str);
    inline static sel_t getUid(const char *str);
    inline const char *getName();
    bool isEqual(sel_t other);
};

OBJCRTXX_END_NAMESPACE
