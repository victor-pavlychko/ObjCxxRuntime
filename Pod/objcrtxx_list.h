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

template<typename T>
struct runtime_list_t
{
    typedef T value_type;
    typedef const T *const_iterator;

    size_t count = 0;
    value_type *items = nullptr;

    runtime_list_t() = delete;
    runtime_list_t(const runtime_list_t<value_type> &) = delete;
    runtime_list_t &operator=(const runtime_list_t<value_type> &) = delete;
    
    template<typename TFactory, typename TOwner, typename ...TArgs>
    inline runtime_list_t(TFactory factory, TOwner owner, TArgs... args);

    inline runtime_list_t(runtime_list_t<value_type> &&other);
    inline ~runtime_list_t();

    inline size_t size() const;
    inline const_iterator begin() const;
    inline const_iterator end() const;
};

typedef runtime_list_t<detail::Class_t>             class_list_t;
typedef runtime_list_t<detail::Protocol_t>          protocol_list_t;
typedef runtime_list_t<Ivar>                        ivar_list_t;
typedef runtime_list_t<objc_property_t>             property_list_t;
typedef runtime_list_t<objc_property_attribute_t>   property_attribute_list_t;
typedef runtime_list_t<Method>                      method_list_t;
typedef runtime_list_t<objc_method_description>     method_description_list_t;

OBJCRTXX_END_NAMESPACE
