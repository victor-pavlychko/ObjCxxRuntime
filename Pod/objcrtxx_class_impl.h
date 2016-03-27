//
//  objcrtxx_class_impl.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

class_t class_t::lookUpClass(const char *name)
{
    return objc_lookUpClass(name);
}

class_t class_t::getClass(const char *name)
{
    return objc_getClass(name);
}

class_t class_t::getRequiredClass(const char *name)
{
    return objc_getRequiredClass(name);
}

class_t class_t::getMetaClass(const char *name)
{
    return objc_getMetaClass(name);
}

class_t class_t::allocateClassPair(Class superclass, const char *name, size_t extraBytes)
{
    return objc_allocateClassPair(superclass, name, extraBytes);
}

void class_t::disposeClassPair()
{
    return objc_disposeClassPair(cls);
}

void class_t::registerClassPair()
{
    return objc_registerClassPair(cls);
}

const char *class_t::getName()
{
    return class_getName(cls);
}

class_t class_t::getSuperclass()
{
    return class_getSuperclass(cls);
}

bool class_t::isMetaClass()
{
    return class_isMetaClass(cls);
}

size_t class_t::getInstanceSize()
{
    return class_getInstanceSize(cls);
}

ivar_t class_t::getInstanceVariable(const char *name)
{
    return class_getInstanceVariable(cls, name);
}

ivar_t class_t::getClassVariable(const char *name)
{
    return class_getClassVariable(cls, name);
}

bool class_t::addIvar(const char *name, size_t size, uint8_t alignment, const char *types)
{
    return class_addIvar(cls, name, size, alignment, types);
}

const uint8_t *class_t::getIvarLayout()
{
    return class_getIvarLayout(cls);
}

void class_t::setIvarLayout(const uint8_t *layout)
{
    return class_setIvarLayout(cls, layout);
}

const uint8_t *class_t::getWeakIvarLayout()
{
    return class_getWeakIvarLayout(cls);
}

void class_t::setWeakIvarLayout(const uint8_t *layout)
{
    return class_setWeakIvarLayout(cls, layout);
}

property_t class_t::getProperty(const char *name)
{
    return class_getProperty(cls, name);
}

bool class_t::addMethod(sel_t name, imp_t imp, const char *types)
{
    return class_addMethod(cls, name, imp, types);
}

method_t class_t::getInstanceMethod(sel_t name)
{
    return class_getInstanceMethod(cls, name);
}

method_t class_t::getClassMethod(sel_t name)
{
    return class_getClassMethod(cls, name);
}

imp_t class_t::replaceMethod(sel_t name, imp_t imp, const char *types)
{
    return class_replaceMethod(cls, name, imp, types);
}

imp_t class_t::getMethodImplementation(sel_t name)
{
    return class_getMethodImplementation(cls, name);
}

imp_t class_t::getMethodImplementation_stret(sel_t name)
{
    return class_getMethodImplementation_stret(cls, name);
}

bool class_t::respondsToSelector(sel_t sel)
{
    return class_respondsToSelector(cls, sel);
}

bool class_t::addProtocol(protocol_t protocol)
{
    return class_addProtocol(cls, protocol);
}

bool class_t::addProperty(const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount)
{
    return class_addProperty(cls, name, attributes, attributeCount);
}

void class_t::replaceProperty(const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount)
{
    return class_replaceProperty(cls, name, attributes, attributeCount);
}

bool class_t::conformsToProtocol(protocol_t protocol)
{
    return class_conformsToProtocol(cls, protocol);
}

int class_t::getVersion()
{
    return class_getVersion(cls);
}

void class_t::setVersion(int version)
{
    return class_setVersion(cls, version);
}

ivar_list_t class_t::copyIvarList()
{
    return ivar_list_t(class_copyIvarList, cls);
}

property_list_t class_t::copyPropertyList()
{
    return property_list_t(class_copyPropertyList, cls);
}

method_list_t class_t::copyMethodList()
{
    return method_list_t(class_copyMethodList, cls);
}

protocol_list_t class_t::copyProtocolList()
{
    return protocol_list_t(class_copyProtocolList, cls);
}

class_t class_t::setSuperclass(class_t newSuper)
{
    return class_setSuperclass(cls, newSuper);
}

class_t class_t::duplicateClass(const char *name, size_t extraBytes)
{
    return objc_duplicateClass(cls, name, extraBytes);
}

#if OBJCRTXX_EXPOSE_LIST_ACCESSORS

Ivar *class_t::copyIvarList(unsigned int *outCount)
{
    return class_copyIvarList(cls, outCount);
}

objc_property_t *class_t::copyPropertyList(unsigned int *outCount)
{
    return class_copyPropertyList(cls, outCount);
}

Method *class_t::copyMethodList(unsigned int *outCount)
{
    return class_copyMethodList(cls, outCount);
}

detail::Protocol_t *class_t::copyProtocolList(unsigned int *outCount)
{
    return class_copyProtocolList(cls, outCount);
}

#endif // OBJCRTXX_EXPOSE_LIST_ACCESSORS

#if !OBJCRTXX_HAS_ARC

id class_t::createInstance(size_t extraBytes)
{
    return class_createInstance(cls, extraBytes);
}

id class_t::constructInstance(void *bytes)
{
    return objc_constructInstance(cls, bytes);
}

void *class_t::destructInstance(id obj)
{
    return objc_destructInstance(obj);
}

#endif // !OBJCRTXX_HAS_ARC

OBJCRTXX_END_NAMESPACE
