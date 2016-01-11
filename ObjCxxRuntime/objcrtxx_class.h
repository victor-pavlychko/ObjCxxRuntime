//
//  objcrtxx_class.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

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
    __Protocol_t *      copyProtocolList(unsigned int *outCount)    { return class_copyProtocolList(cls, outCount); }
    
    class_t             setSuperclass(class_t newSuper)             { return class_setSuperclass(cls, newSuper); }
    
    //        objc_getFutureClass
    //        objc_setFutureClass
    //        objc_duplicateClass
    //        class_createInstance
    //        objc_constructInstance
    //        objc_destructInstance
};

OBJCRTXX_END_NAMESPACE
