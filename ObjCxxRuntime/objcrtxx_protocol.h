//
//  objcrtxx_protocol.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

struct protocol_t
{
    OBJCXX_PRIMITIVE_WRAPPER(protocol_t, detail::Protocol_t, protocol, nil)

    inline protocol_t getProtocol(const char *name);
    inline protocol_t allocateProtocol(const char *name);
    inline void registerProtocol();
    inline void addMethodDescription(SEL name, const char *types, BOOL isRequiredMethod, BOOL isInstanceMethod);
    inline void addProtocol(protocol_t addition);
    inline void addProperty(const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount, BOOL isRequiredProperty, BOOL isInstanceProperty);
    inline const char *getName();
    inline BOOL isEqual(protocol_t other);
    inline struct objc_method_description *copyMethodDescriptionList(BOOL isRequiredMethod, BOOL isInstanceMethod, unsigned int *outCount);
    inline struct objc_method_description getMethodDescription(SEL aSel, BOOL isRequiredMethod, BOOL isInstanceMethod);
    inline objc_property_t *copyPropertyList(unsigned int *outCount);
    inline objc_property_t getProperty(const char *name, BOOL isRequiredProperty, BOOL isInstanceProperty);
    inline detail::Protocol_t *copyProtocolList(unsigned int *outCount);
    inline BOOL conformsToProtocol(protocol_t other);
};

OBJCRTXX_END_NAMESPACE
