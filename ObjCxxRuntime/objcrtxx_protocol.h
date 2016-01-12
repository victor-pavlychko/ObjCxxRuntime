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
    inline void addMethodDescription(sel_t name, const char *types, bool isRequiredMethod, bool isInstanceMethod);
    inline void addProtocol(protocol_t addition);
    inline void addProperty(const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount, bool isRequiredProperty, bool isInstanceProperty);
    inline const char *getName();
    inline bool isEqual(protocol_t other);
    inline struct objc_method_description getMethodDescription(sel_t aSel, bool isRequiredMethod, bool isInstanceMethod);
    inline objc_property_t getProperty(const char *name, bool isRequiredProperty, bool isInstanceProperty);
    inline bool conformsToProtocol(protocol_t other);
    
    inline method_description_list_t copyMethodDescriptionList(bool isRequiredMethod, bool isInstanceMethod);
    inline property_list_t copyPropertyList();
    inline protocol_list_t copyProtocolList();
    
    inline struct objc_method_description *copyMethodDescriptionList(bool isRequiredMethod, bool isInstanceMethod, unsigned int *outCount);
    inline objc_property_t *copyPropertyList(unsigned int *outCount);
    inline detail::Protocol_t *copyProtocolList(unsigned int *outCount);
};

OBJCRTXX_END_NAMESPACE
