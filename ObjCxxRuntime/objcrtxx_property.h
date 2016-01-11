//
//  objcrtxx_property.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

struct property_t
{
    OBJCXX_PRIMITIVE_WRAPPER(property_t, objc_property_t, property, NULL)
};

OBJCRTXX_END_NAMESPACE
