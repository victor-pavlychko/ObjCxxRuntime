//
//  objcrtxx_list_impl.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

template<typename T>
template<typename TFactory, typename TOwner, typename ...TArgs>
runtime_list_t<T>::runtime_list_t(TFactory factory, TOwner owner, TArgs... args)
{
    unsigned int count_ = 0;
    items = factory(owner, args..., &count_);
    count = static_cast<size_t>(count_);
}

template<typename T>
runtime_list_t<T>::runtime_list_t(runtime_list_t<value_type> &&other)
{
    count = other.count;
    items = other.items;
    other.count = 0;
    other.items = nullptr;
}

template<typename T>
runtime_list_t<T>::~runtime_list_t()
{
    free(items);
}

template<typename T>
size_t runtime_list_t<T>::size() const
{
    return count;
}

template<typename T>
typename runtime_list_t<T>::const_iterator runtime_list_t<T>::begin() const
{
    return items;
}

template<typename T>
typename runtime_list_t<T>::const_iterator runtime_list_t<T>::end() const
{
    return items + count;
}

OBJCRTXX_END_NAMESPACE
