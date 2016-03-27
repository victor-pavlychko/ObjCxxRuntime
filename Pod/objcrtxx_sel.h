//
//  objcrtxx_sel.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2016 address.wtf. All rights reserved.
//

#ifdef OBJCRTXX_UMBRELLA_ACTIVE

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

#endif // OBJCRTXX_UMBRELLA_ACTIVE
