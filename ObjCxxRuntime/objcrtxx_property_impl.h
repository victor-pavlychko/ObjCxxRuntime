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

char *property_t::copyClassName()
{
    char *className = copyAttributeValue("T");
    if (!className)
    {
        return nullptr;
    }
    
    size_t length = strlen(className);

    if (length <= 3 || className[0] != '@' || className[1] != '\"' || className[length - 1] != '\"')
    {
        *className = 0;
    }
    else
    {
        className[length - 1] = 0;
        memmove(className, className + 2, length - 2);
    }

    return className;
}

property_attribute_list_t property_t::copyAttributeList()
{
    return property_attribute_list_t(property_copyAttributeList, property);
}

#if OBJCRTXX_EXPOSE_LIST_ACCESSORS

objc_property_attribute_t *property_t::copyAttributeList(unsigned int *outCount)
{
    return property_copyAttributeList(property, outCount);
}

#endif // OBJCRTXX_EXPOSE_LIST_ACCESSORS

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
            // weak not supported by associative references!
            return OBJC_ASSOCIATION_ASSIGN;
        }
        else
        {
            return OBJC_ASSOCIATION_ASSIGN;
        }
    }
    
    inline sel_t getGetterSelector(const property_info_t &info)
    {
        if (info.customGetterName)
        {
            return sel_t::getUid(info.customGetterName);
        }
        
        const char *getterName = info.name;
        return sel_t::getUid(getterName);
    }
    
    inline sel_t getSetterSelector(const property_info_t &info)
    {
        if (info.customSetterName)
        {
            return sel_t::getUid(info.customSetterName);
        }
        
        size_t bufferSize = strlen(info.name) + 2;
        char setterName[bufferSize];
        sprintf(setterName, "set%c%s:", toupper(*info.name), info.name + 1);
        return sel_t::getUid(setterName);
    }
}

property_info_t::property_info_t(property_t property)
    : attributes(property.copyAttributeList())
{
    name = property.getName();

    for (auto &attribute: attributes)
    {
        switch (*attribute.name)
        {
            case 'T':
                typeEncoding = attribute.value;
                break;
            case 'R':
                isReadOnly = true;
                break;
            case 'C':
                isCopy = true;
                break;
            case '&':
                isRetain = true;
                break;
            case 'N':
                isNonAtomic = true;
                break;
            case 'G':
                customGetterName = attribute.value;
                break;
            case 'S':
                customSetterName = attribute.value;
                break;
            case 'D':
                isDynamic = true;
                break;
            case 'W':
                isWeak = true;
                break;
        }
    }
    
    associatonPolicy = getAssociationPolicy(*this);
    getterSelector = getGetterSelector(*this);
    setterSelector = getSetterSelector(*this);
}

OBJCRTXX_END_NAMESPACE
