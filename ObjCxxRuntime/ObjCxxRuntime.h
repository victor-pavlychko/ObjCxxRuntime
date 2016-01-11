//
//  ObjCxxRuntime.h
//  Experiments
//
//  Created by Victor Pavlychko on 03.10.2015.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef ObjCxxRuntime_h
#define ObjCxxRuntime_h

#include <string>
#import <objc/runtime.h>

//#define OBJCXX_PRIMITIVE_WRAPPER(self__, type__, var__, null__) \
//    type__ var__ = null__; \
//    explicit self__(type__ var__ ## _): var__(var__ ## _) {}  \
//    self__(const self__ &other): var__(other.var__) {} \
//    self__ &operator=(const self__ &other) { var__ = other.var__; return *this; } \

#define OBJCXX_PRIMITIVE_WRAPPER(self__, type__, var__, null__) \
    type__ var__ = null__; \
    self__(type__ var__ ## _): var__(var__ ## _) {}  \
    self__(const self__ &other): var__(other.var__) {} \
    self__(const self__ &&other): var__(other.var__) {} \
    self__ &operator=(const self__ &other) { var__ = other.var__; return *this; } \
    self__ &operator=(const type__ &other) { var__ = other; return *this; } \
    operator type__() { return var__; } \
    operator const type__&() const { return var__; } \
    operator bool() { return !!var__; } \
    type__ *operator&() { return &var__; } \
    const type__ *operator&() const { return &var__; } \

namespace address_wtf {
namespace objcxx {
    
    typedef Protocol * __unsafe_unretained Protocol_t;
    typedef Class __unsafe_unretained Class_t;
    typedef struct objc_method_description *objc_method_description_t;

    struct class_t;
    struct protocol_t;
    struct method_t;
    struct ivar_t;
    struct category_t;
    struct property_t;
    struct imp_t;
    struct sel_t;

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
    
    typedef global_runtime_list_t<Class_t,                  objc_copyClassList>     global_class_list_t;
    typedef global_runtime_list_t<Protocol_t,               objc_copyProtocolList>  global_protocol_list_t;

    typedef object_runtime_list_t<Ivar,             Class,  class_copyIvarList>     ivar_list_t;
    typedef object_runtime_list_t<objc_property_t,  Class,  class_copyPropertyList> property_list_t;
    typedef object_runtime_list_t<Method,           Class,  class_copyMethodList>   method_list_t;
    typedef object_runtime_list_t<Protocol_t,       Class,  class_copyProtocolList> protocol_list_t;

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
    
    struct protocol_t
    {
        OBJCXX_PRIMITIVE_WRAPPER(protocol_t, Protocol_t, protocol, nil)
    };
    
    struct sel_t
    {
        OBJCXX_PRIMITIVE_WRAPPER(sel_t, SEL, sel, NULL)
    };
    
    struct imp_t
    {
        OBJCXX_PRIMITIVE_WRAPPER(imp_t, IMP, imp, NULL)
    };
    
    struct method_t
    {
        OBJCXX_PRIMITIVE_WRAPPER(method_t, Method, method, NULL)

//        invoke() { return method_invoke(method); }
//        invoke_stret() { return method_invoke_stret(method); }
        const sel_t                 getName()                                   { return method_getName(method); }
        imp_t                       getImplementation()                         { return method_getImplementation(method); }
        const char *                getTypeEncoding()                           { return method_getTypeEncoding(method); }
        char *                      copyReturnType()                            { return method_copyReturnType(method); }
        char *                      copyArgumentType(unsigned int index)        { return method_copyArgumentType(method, index); }
        void                        getReturnType(char *dst, size_t dst_len)    { return method_getReturnType(method, dst, dst_len); }
        unsigned int                getNumberOfArguments()                      { return method_getNumberOfArguments(method); }
        void                        getArgumentType(unsigned int index, char *dst, size_t dst_len)
                                                                                { return method_getArgumentType(method, index, dst, dst_len); }
        objc_method_description_t   getDescription()                            { return method_getDescription(method); }
        imp_t                       setImplementation(imp_t imp)                { return method_setImplementation(method, imp); }
        void                        exchangeImplementations(method_t other)     { return method_exchangeImplementations(method, other); }
    };
    
    struct ivar_t
    {
        OBJCXX_PRIMITIVE_WRAPPER(ivar_t, Ivar, ivar, NULL)

        const char *    getName()           { return ivar_getName(ivar); }
        const char *    getTypeEncoding()   { return ivar_getTypeEncoding(ivar); }
        ptrdiff_t       getOffset()         { return ivar_getOffset(ivar); }
    };
    
    struct category_t
    {
        OBJCXX_PRIMITIVE_WRAPPER(category_t, Category, category, NULL)
    };
    
    struct property_t
    {
        OBJCXX_PRIMITIVE_WRAPPER(property_t, objc_property_t, property, NULL)
    };
    
    struct class_t
    {
        OBJCXX_PRIMITIVE_WRAPPER(class_t, Class, cls, Nil)

        static class_t      lookUpClass(const char *name)               { return objc_lookUpClass(name); }
        static class_t      getClass(const char *name)                  { return objc_getClass(name); }
        static class_t      getRequiredClass(const char *name)          { return objc_getRequiredClass(name); }
        static class_t      getMetaClass(const char *name)              { return objc_getMetaClass(name); }

        static class_t      allocateClassPair(Class superclass, const char *name, size_t extraBytes)
                                                                        { return objc_allocateClassPair(superclass, name, extraBytes); }
        void                disposeClassPair()                          { return objc_disposeClassPair(cls); }
        void                registerClassPair()                         { return objc_registerClassPair(cls); }
        
        
        const char *        getName()                                   { return class_getName(cls); }
        class_t             getSuperclass()                             { return class_getSuperclass(cls); }
        bool                isMetaClass()                               { return class_isMetaClass(cls); }
        size_t              getInstanceSize()                           { return class_getInstanceSize(cls); }
        ivar_t              getInstanceVariable(const char *name)       { return class_getInstanceVariable(cls, name); }
        ivar_t              getClassVariable(const char *name)          { return class_getClassVariable(cls, name); }
        bool                addIvar(const char *name, size_t size, uint8_t alignment, const char *types)
                                                                        { return class_addIvar(cls, name, size, alignment, types); }
        const uint8_t *     getIvarLayout()                             { return class_getIvarLayout(cls); }
        void                setIvarLayout(const uint8_t *layout)        { return class_setIvarLayout(cls, layout); }
        const uint8_t *     getWeakIvarLayout()                         { return class_getWeakIvarLayout(cls); }
        void                setWeakIvarLayout(const uint8_t *layout)    { return class_setWeakIvarLayout(cls, layout); }
        property_t          getProperty(const char *name)               { return class_getProperty(cls, name); }
        bool                addMethod(sel_t name, imp_t imp, const char *types)
                                                                        { return class_addMethod(cls, name, imp, types); }
        method_t            getInstanceMethod(sel_t name)               { return class_getInstanceMethod(cls, name); }
        method_t            getClassMethod(sel_t name)                  { return class_getClassMethod(cls, name); }
        imp_t               replaceMethod(sel_t name, imp_t imp, const char *types)
                                                                        { return class_replaceMethod(cls, name, imp, types); }
        imp_t               getMethodImplementation(sel_t name)         { return class_getMethodImplementation(cls, name); }
        imp_t               getMethodImplementation_stret(sel_t name)   { return class_getMethodImplementation_stret(cls, name); }
        bool                respondsToSelector(sel_t sel)               { return class_respondsToSelector(cls, sel); }
        bool                addProtocol(protocol_t protocol)            { return class_addProtocol(cls, protocol); }
        bool                addProperty(const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount)
                                                                        { return class_addProperty(cls, name, attributes, attributeCount); }
        void                replaceProperty(const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount)
                                                                        { return class_replaceProperty(cls, name, attributes, attributeCount); }
        bool                conformsToProtocol(protocol_t protocol)     { return class_conformsToProtocol(cls, protocol); }
        int                 getVersion()                                { return class_getVersion(cls); }
        void                setVersion(int version)                     { return class_setVersion(cls, version); }

        ivar_list_t         copyIvarList()                              { return ivar_list_t(cls); }
        property_list_t     copyPropertyList()                          { return property_list_t(cls); }
        method_list_t       copyMethodList()                            { return method_list_t(cls); }
        protocol_list_t     copyProtocolList()                          { return protocol_list_t(cls); }

        Ivar *              copyIvarList(unsigned int *outCount)        { return class_copyIvarList(cls, outCount); }
        objc_property_t *   copyPropertyList(unsigned int *outCount)    { return class_copyPropertyList(cls, outCount); }
        Method *            copyMethodList(unsigned int *outCount)      { return class_copyMethodList(cls, outCount); }
        Protocol_t *        copyProtocolList(unsigned int *outCount)    { return class_copyProtocolList(cls, outCount); }
        
        class_t             setSuperclass(class_t newSuper)             { return class_setSuperclass(cls, newSuper); }

//        objc_getFutureClass
//        objc_setFutureClass
//        objc_duplicateClass
//        class_createInstance
//        objc_constructInstance
//        objc_destructInstance
    };
    
}}

#endif /* ObjCxxRuntime_h */
