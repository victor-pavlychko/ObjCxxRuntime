//
//  objcrtxx_sel_impl.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2016 address.wtf. All rights reserved.
//

#ifdef OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

sel_t sel_t::registerName(const char *str)
{
    return sel_registerName(str);
}

sel_t sel_t::getUid(const char *str)
{
    return sel_getUid(str);
}

const char *sel_t::getName()
{
    return sel_getName(sel);
}

bool sel_t::isEqual(sel_t other)
{
    return sel_isEqual(sel, other);
}

OBJCRTXX_END_NAMESPACE

#endif // OBJCRTXX_UMBRELLA_ACTIVE
