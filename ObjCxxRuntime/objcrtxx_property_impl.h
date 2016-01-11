//
//  objcrtxx_property_impl.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

const char *property_t::getName()
{
    return property_getName(property);
}

const char *property_t::getAttributes()
{
    return property_getAttributes(property);
}

char *property_t::copyAttributeValue(const char *attributeName)
{
    return property_copyAttributeValue(property, attributeName);
}

objc_property_attribute_t *property_t::copyAttributeList(unsigned int *outCount)
{
    return property_copyAttributeList(property, outCount);
}

OBJCRTXX_END_NAMESPACE
