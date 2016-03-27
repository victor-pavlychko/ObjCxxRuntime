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
    
    inline static class_t lookUpClass(const char *name);
    inline static class_t getClass(const char *name);
    inline static class_t getRequiredClass(const char *name);
    inline static class_t getMetaClass(const char *name);
    inline static class_t allocateClassPair(Class superclass, const char *name, size_t extraBytes);
    inline void disposeClassPair();
    inline void registerClassPair();
    inline const char *getName();
    inline class_t getSuperclass();
    inline bool isMetaClass();
    inline size_t getInstanceSize();
    inline ivar_t getInstanceVariable(const char *name);
    inline ivar_t getClassVariable(const char *name);
    inline bool addIvar(const char *name, size_t size, uint8_t alignment, const char *types);
    inline const uint8_t *getIvarLayout();
    inline void setIvarLayout(const uint8_t *layout);
    inline const uint8_t *getWeakIvarLayout();
    inline void setWeakIvarLayout(const uint8_t *layout);
    inline property_t getProperty(const char *name);
    inline bool addMethod(sel_t name, imp_t imp, const char *types);
    inline method_t getInstanceMethod(sel_t name);
    inline method_t getClassMethod(sel_t name);
    inline imp_t replaceMethod(sel_t name, imp_t imp, const char *types);
    inline imp_t getMethodImplementation(sel_t name);
    inline imp_t getMethodImplementation_stret(sel_t name);
    inline bool respondsToSelector(sel_t sel);
    inline bool addProtocol(protocol_t protocol);
    inline bool addProperty(const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount);
    inline void replaceProperty(const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount);
    inline bool conformsToProtocol(protocol_t protocol);
    inline int getVersion();
    inline void setVersion(int version);

    inline ivar_list_t copyIvarList();
    inline property_list_t copyPropertyList();
    inline method_list_t copyMethodList();
    inline protocol_list_t copyProtocolList();
    
    inline class_t setSuperclass(class_t newSuper)
        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_5, __IPHONE_2_0,__IPHONE_2_0);

    inline class_t duplicateClass(const char *name, size_t extraBytes);
    
#if OBJCRTXX_EXPOSE_LIST_ACCESSORS

    inline Ivar *copyIvarList(unsigned int *outCount);
    inline objc_property_t *copyPropertyList(unsigned int *outCount);
    inline Method *copyMethodList(unsigned int *outCount);
    inline detail::Protocol_t *copyProtocolList(unsigned int *outCount);

#endif // OBJCRTXX_EXPOSE_LIST_ACCESSORS

#if !OBJCRTXX_HAS_ARC

    inline id createInstance(size_t extraBytes);
    inline id constructInstance(void *bytes);
    inline static void *destructInstance(id obj);

#endif // !OBJCRTXX_HAS_ARC

//    inline static class_t getFutureClass(const char *name);
//    inline static void setFutureClass(const char *name);

};

OBJCRTXX_END_NAMESPACE
