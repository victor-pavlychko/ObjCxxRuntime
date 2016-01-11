//
//  objcrtxx_protocol_impl.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

protocol_t protocol_t::getProtocol(const char *name)
{
    return objc_getProtocol(name);
}

protocol_t protocol_t::allocateProtocol(const char *name)
{
    return objc_allocateProtocol(name);
}

void protocol_t::registerProtocol()
{
    return objc_registerProtocol(protocol);
}

void protocol_t::addMethodDescription(SEL name, const char *types, BOOL isRequiredMethod, BOOL isInstanceMethod)
{
    return protocol_addMethodDescription(protocol, name, types, isRequiredMethod, isInstanceMethod);
}

void protocol_t::addProtocol(protocol_t addition)
{
    return protocol_addProtocol(protocol, addition);
}

void protocol_t::addProperty(const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount, BOOL isRequiredProperty, BOOL isInstanceProperty)
{
    return protocol_addProperty(protocol, name, attributes, attributeCount, isRequiredProperty, isInstanceProperty);
}

const char *protocol_t::getName()
{
    return protocol_getName(protocol);
}

BOOL protocol_t::isEqual(protocol_t other)
{
    return protocol_isEqual(protocol, other);
}

struct objc_method_description *protocol_t::copyMethodDescriptionList(BOOL isRequiredMethod, BOOL isInstanceMethod, unsigned int *outCount)
{
    return protocol_copyMethodDescriptionList(protocol, isRequiredMethod, isInstanceMethod, outCount);
}

struct objc_method_description protocol_t::getMethodDescription(SEL aSel, BOOL isRequiredMethod, BOOL isInstanceMethod)
{
    return protocol_getMethodDescription(protocol, aSel, isRequiredMethod, isInstanceMethod);
}

objc_property_t *protocol_t::copyPropertyList(unsigned int *outCount)
{
    return protocol_copyPropertyList(protocol, outCount);
}

objc_property_t protocol_t::getProperty(const char *name, BOOL isRequiredProperty, BOOL isInstanceProperty)
{
    return protocol_getProperty(protocol, name, isRequiredProperty, isInstanceProperty);
}

detail::Protocol_t *protocol_t::copyProtocolList(unsigned int *outCount)
{
    return protocol_copyProtocolList(protocol, outCount);
}

BOOL protocol_t::conformsToProtocol(protocol_t other)
{
    return protocol_conformsToProtocol(protocol, other);
}

OBJCRTXX_END_NAMESPACE
