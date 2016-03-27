//
//  objcrtxx_ivar_impl.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2016 address.wtf. All rights reserved.
//

#ifdef OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

const char *ivar_t::getName()
{
    return ivar_getName(ivar);
}

const char *ivar_t::getTypeEncoding()
{
    return ivar_getTypeEncoding(ivar);
}

ptrdiff_t ivar_t::getOffset()
{
    return ivar_getOffset(ivar);
}

template<typename T>
template<typename U>
typename detail::ivar_ref_traits<U>::pointer_type ivar_ref_t<T>::ptr()
{
    static_assert(std::is_same<T, U>::value, "invalid explicit specialisation");
    return reinterpret_cast<T *>(reinterpret_cast<char *>((__bridge void *)instance) + ivar.getOffset());
}

template<>
id ivar_ref_t<id>::get()
{
    return object_getIvar(instance, ivar);
}

template<>
void ivar_ref_t<id>::set(id value)
{
    object_setIvar(instance, ivar, value);
}

OBJCRTXX_END_NAMESPACE

#endif // OBJCRTXX_UMBRELLA_ACTIVE
