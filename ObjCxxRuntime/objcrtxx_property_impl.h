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

property_attribute_list_t property_t::copyAttributeList()
{
    return property_attribute_list_t(property_copyAttributeList, property);
}

objc_property_attribute_t *property_t::copyAttributeList(unsigned int *outCount)
{
    return property_copyAttributeList(property, outCount);
}

namespace
{
    inline objc_AssociationPolicy getAssociationPolicy(const property_info_t &info)
    {
        if (info.isRetain)
        {
            if (info.isNonAtomic)
            {
                return OBJC_ASSOCIATION_RETAIN_NONATOMIC;
            }
            else
            {
                return OBJC_ASSOCIATION_RETAIN;
            }
        }
        else if (info.isCopy)
        {
            if (info.isNonAtomic)
            {
                return OBJC_ASSOCIATION_COPY_NONATOMIC;
            }
            else
            {
                return OBJC_ASSOCIATION_COPY;
            }
        }
        else if (info.isWeak)
        {
            // retain holder as non-atomic
            return OBJC_ASSOCIATION_RETAIN_NONATOMIC;
        }
        else
        {
            return OBJC_ASSOCIATION_ASSIGN;
        }
    }
    
    inline SEL getGetterSelector(const property_info_t &info)
    {
        if (info.customGetterName)
        {
            return sel_getUid(info.customGetterName);
        }
        
        const char *getterName = info.name;
        return sel_getUid(getterName);
    }
    
    inline SEL getSetterSelector(const property_info_t &info)
    {
        if (info.customSetterName)
        {
            return sel_getUid(info.customSetterName);
        }
        
        size_t bufferSize = strlen(info.name) + 2;
        char setterName[bufferSize];
        sprintf(setterName, "set%c%s:", toupper(*info.name), info.name + 1);
        return sel_getUid(setterName);
    }
}

property_info_t::property_info_t(property_t property)
{
    name = property_getName(property);
    
    for (auto &attribute: property.copyAttributeList())
    {
        switch (*attribute.name)
        {
            case 'T':
                typeEncoding = attribute.value;
                break;
            case 'R':
                isReadOnly = YES;
                break;
            case 'C':
                isCopy = YES;
                break;
            case '&':
                isRetain = YES;
                break;
            case 'N':
                isNonAtomic = YES;
                break;
            case 'G':
                customGetterName = attribute.value;
                break;
            case 'S':
                customSetterName = attribute.value;
                break;
            case 'D':
                isDynamic = YES;
                break;
            case 'W':
                isWeak = YES;
                break;
        }
    }
    
    associatonPolicy = getAssociationPolicy(*this);
    getterSelector = getGetterSelector(*this);
    setterSelector = getSetterSelector(*this);
}

OBJCRTXX_END_NAMESPACE
