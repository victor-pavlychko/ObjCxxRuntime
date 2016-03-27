//
//  objcrtxx_ivar.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

struct ivar_t
{
    OBJCXX_PRIMITIVE_WRAPPER(ivar_t, Ivar, ivar, NULL)

    inline const char *getName();
    inline const char *getTypeEncoding();
    inline ptrdiff_t getOffset();
};

namespace detail
{
    template<typename T>
    struct ivar_ref_traits
    {
        typedef const T &accessor_type;
        typedef T &reference_type;
        typedef T *pointer_type;
    };
    
    template<>
    struct ivar_ref_traits<id>
    {
        typedef id accessor_type;
    };
}

template<typename T>
struct ivar_ref_t
{
    typedef typename detail::ivar_ref_traits<T>::accessor_type accessor_type;

    id instance;
    ivar_t ivar;
    
    ivar_ref_t(id instance_, ivar_t ivar_)
        : instance(instance_)
        , ivar(ivar_)
        {}
    
    template<typename U = T>
    inline typename detail::ivar_ref_traits<U>::pointer_type ptr();

    template<typename U = T>
    inline typename detail::ivar_ref_traits<U>::reference_type operator*() { return *ptr(); }

    template<typename U = T>
    inline typename detail::ivar_ref_traits<U>::pointer_type operator->() { return ptr(); }

    inline accessor_type get() { return *ptr(); }
    inline void set(accessor_type value) { *ptr() = value; }
    inline operator accessor_type() { return get(); }
    inline ivar_ref_t &operator=(accessor_type value) { set(value); return *this; }
};

OBJCRTXX_END_NAMESPACE
