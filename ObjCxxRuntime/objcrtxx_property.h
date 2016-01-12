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

    inline const char *getName();
    inline const char *getAttributes();
    inline char *copyAttributeValue(const char *attributeName);

    inline property_attribute_list_t copyAttributeList();

    inline objc_property_attribute_t *copyAttributeList(unsigned int *outCount);
};

struct property_info_t
{
    property_attribute_list_t attributes;

    const char *name = nullptr;
    
    bool isReadOnly = false;
    bool isCopy = false;
    bool isRetain = false;
    bool isNonAtomic = false;
    bool isDynamic = false;
    bool isWeak = false;
    
    const char *typeEncoding = nullptr;
    const char *customGetterName = nullptr;
    const char *customSetterName = nullptr;
    
    SEL getterSelector = NULL;
    SEL setterSelector = NULL;
    objc_AssociationPolicy associatonPolicy = OBJC_ASSOCIATION_RETAIN;

    explicit property_info_t(property_t property);
};

OBJCRTXX_END_NAMESPACE
