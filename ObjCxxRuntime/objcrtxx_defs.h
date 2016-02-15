//
//  objcrtxx_defs.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

#define OBJCRTXX_BEGIN_NAMESPACE    namespace address_wtf { namespace objcrtxx {
#define OBJCRTXX_END_NAMESPACE      } }

#ifndef OBJCRTXX_EXPOSE_LIST_ACCESSORS
#   define OBJCRTXX_EXPOSE_LIST_ACCESSORS 0
#endif

#define OBJCXX_PRIMITIVE_WRAPPER(self__, type__, var__, null__) \
    type__ var__ = null__; \
    self__() {} \
    self__(type__ var__ ## _): var__(var__ ## _) {}  \
    self__(const self__ &other): var__(other.var__) {} \
    self__(const self__ &&other): var__(other.var__) {} \
    self__ &operator=(const self__ &other) { var__ = other.var__; return *this; } \
    self__ &operator=(const self__ &&other) { var__ = other.var__; return *this; } \
    self__ &operator=(const type__ &other) { var__ = other; return *this; } \
    self__ &operator=(const type__ &&other) { var__ = other; return *this; } \
    operator type__() const { return var__; } \
    operator bool() { return !!var__; } \
    type__ *operator&() { return &var__; } \
    const type__ *operator&() const { return &var__; } \

//operator type__&() { return var__; } \
//operator const type__&() const { return var__; } \

#if __has_feature(objc_arc)

#   define OBJCRTXX_HAS_ARC         1
#   define OBJCRTXX_RETAIN(x)       ([(x) retain])
#   define OBJCRTXX_RELEASE(x)      ([(x) release])
#   define OBJCRTXX_AUTORELEASE(x)  ([(x) autorelease])

#else

#   define OBJCRTXX_HAS_ARC         0
#   define OBJCRTXX_RETAIN(x)       (x)
#   define OBJCRTXX_RELEASE(x)      (x)
#   define OBJCRTXX_AUTORELEASE(x)  (x)

#endif

#define OBJRTXX_CFRELEASE(x__)      do { if (x) { CFRelease(x); } x = NULL; } while (0)

#if defined(__arm__)

#   define OBJCRTXX_HAS_ABI         1
#   define OBJCRTXX_HAS_ABI_FPRET   0
#   define OBJCRTXX_HAS_ABI_FP2RET  0

#elif defined(__i386__)

#   define OBJCRTXX_HAS_ABI         1
#   define OBJCRTXX_HAS_ABI_FPRET   1
#   define OBJCRTXX_HAS_ABI_FP2RET  0

#elif defined(__x86_64__)

#   define OBJCRTXX_HAS_ABI         1
#   define OBJCRTXX_HAS_ABI_FPRET   1
#   define OBJCRTXX_HAS_ABI_FP2RET  1

#else

#   define OBJCRTXX_HAS_ABI         0
#   define OBJCRTXX_HAS_ABI_FPRET   0
#   define OBJCRTXX_HAS_ABI_FP2RET  0

#endif

OBJCRTXX_BEGIN_NAMESPACE

namespace detail
{
    typedef Protocol * __unsafe_unretained Protocol_t;
    typedef Class __unsafe_unretained Class_t;
    typedef struct objc_method_description *objc_method_description_t;
}

OBJCRTXX_END_NAMESPACE
