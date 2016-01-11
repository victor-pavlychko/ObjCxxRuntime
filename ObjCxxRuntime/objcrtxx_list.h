//
//  objcrtxx_list.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

template<typename TItem>
struct runtime_list_base_t
{
    typedef const TItem *const_iterator;
    
    unsigned int size = 0;
    TItem *items = nullptr;
    
    const_iterator begin() const
    {
        return items;
    }
    
    const_iterator end() const
    {
        return items + size;
    }
    
protected:
    runtime_list_base_t() {}
    ~runtime_list_base_t() {}
    runtime_list_base_t(const runtime_list_base_t &) = delete;
    runtime_list_base_t &operator=(const runtime_list_base_t &) = delete;
};

template<typename TItem, typename TOwner, TItem *(*Factory)(TOwner, unsigned int *)>
struct object_runtime_list_t: public runtime_list_base_t<TItem>
{
    using runtime_list_base_t<TItem>::items;
    using runtime_list_base_t<TItem>::size;
    
    explicit object_runtime_list_t(TOwner owner)
    {
        items = Factory(owner, &size);
    }
    
    object_runtime_list_t(object_runtime_list_t &&other)
    {
        size = other.size;
        items = other.items;
        other.size = 0;
        other.items = nullptr;
    }
    
    ~object_runtime_list_t()
    {
        free(items);
    }
};

template<typename TItem, TItem *(*Factory)(unsigned int *)>
struct global_runtime_list_t: public runtime_list_base_t<TItem>
{
    using runtime_list_base_t<TItem>::items;
    using runtime_list_base_t<TItem>::size;
    
    explicit global_runtime_list_t()
    {
        items = Factory(&size);
    }
    
    global_runtime_list_t(global_runtime_list_t &&other)
    {
        size = other.size;
        items = other.items;
        other.size = 0;
        other.items = nullptr;
    }
    
    ~global_runtime_list_t()
    {
        free(items);
    }
};

typedef global_runtime_list_t<detail::Class_t,      objc_copyClassList>     global_class_list_t;
typedef global_runtime_list_t<detail::Protocol_t,   objc_copyProtocolList>  global_protocol_list_t;

typedef object_runtime_list_t<Ivar,                 Class,  class_copyIvarList>     ivar_list_t;
typedef object_runtime_list_t<objc_property_t,      Class,  class_copyPropertyList> property_list_t;
typedef object_runtime_list_t<Method,               Class,  class_copyMethodList>   method_list_t;
typedef object_runtime_list_t<detail::Protocol_t,   Class,  class_copyProtocolList> protocol_list_t;

struct property_attribute_list_t: public object_runtime_list_t<objc_property_attribute_t, objc_property_t, property_copyAttributeList>
{
    const char *name = nullptr;
    
    BOOL isReadOnly = NO;
    BOOL isCopy = NO;
    BOOL isRetain = NO;
    BOOL isNonAtomic = NO;
    BOOL isDynamic = NO;
    BOOL isWeak = NO;
    
    const char *typeEncoding = nullptr;
    const char *customGetterName = nullptr;
    const char *customSetterName = nullptr;
    
    explicit property_attribute_list_t(objc_property_t property): object_runtime_list_t(property)
    {
        name = property_getName(property);
        
        for (auto &attribute: *this)
        {
            switch (attribute.name[0])
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
    }
    
    objc_AssociationPolicy getAssociationPolicy() const
    {
        if (isRetain)
        {
            if (isNonAtomic)
            {
                return OBJC_ASSOCIATION_RETAIN_NONATOMIC;
            }
            else
            {
                return OBJC_ASSOCIATION_RETAIN;
            }
        }
        else if (isCopy)
        {
            if (isNonAtomic)
            {
                return OBJC_ASSOCIATION_COPY_NONATOMIC;
            }
            else
            {
                return OBJC_ASSOCIATION_COPY;
            }
        }
        else if (isWeak)
        {
            // retain holder as non-atomic
            return OBJC_ASSOCIATION_RETAIN_NONATOMIC;
        }
        else
        {
            return OBJC_ASSOCIATION_ASSIGN;
        }
    }
    
    SEL getterSelector() const
    {
        if (customGetterName)
        {
            return sel_getUid(customGetterName);
        }
        
        const char *getterName = name;
        return sel_getUid(getterName);
    }
    
    SEL setterSelector() const
    {
        if (customSetterName)
        {
            return sel_getUid(customSetterName);
        }
        
        size_t bufferSize = strlen(name) + 2;
        char setterName[bufferSize];
        sprintf(setterName, "set%c%s:", toupper(name[0]), name + 1);
        return sel_getUid(setterName);
    }
};

OBJCRTXX_END_NAMESPACE
