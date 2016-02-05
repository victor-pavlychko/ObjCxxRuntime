//
//  main.m
//  ObjCxxRuntime
//
//  Created by Victor Pavlychko on 1/8/16.
//  Copyright © 2016 address.wtf. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import "ObjCxxRuntime.h"
#import "objcrtxx.h"

#include <iostream>

using namespace address_wtf;

template<typename ...TList>
struct type_list_t
{
    template<template<typename ...> class T>
    using apply = T<TList...>;
    
    template<typename ...TList_>
    using push_front = type_list_t<TList_..., TList...>;
    
    template<typename ...TList_>
    using push_back = type_list_t<TList..., TList_...>;
};

template<typename T>
struct pointer_applicator_t
{
    static inline T *apply(void *arg)
    {
        return reinterpret_cast<T *>(arg);
    }
};

template<typename T>
struct value_applicator_t
{
    static inline T apply(void *arg)
    {
        return *reinterpret_cast<T *>(arg);
    }
};

template<typename T>
struct reference_applicator_t
{
    static inline T &apply(void *arg)
    {
        return *reinterpret_cast<T *>(arg);
    }
};

template<typename THead, typename ...TTail>
struct runtime_visitor_t
{
    template<template<typename> class TApplicator = pointer_applicator_t, typename TFunc>
    static inline bool visit(const char *typeEncoding, void *arg, TFunc fn)
    {
        return false
            || runtime_visitor_t<THead>::template visit<TApplicator, TFunc>(typeEncoding, arg, fn)
            || runtime_visitor_t<TTail...>::template visit<TApplicator, TFunc>(typeEncoding, arg, fn)
        ;
    }
};

template<typename THead>
struct runtime_visitor_t<THead>
{
    static constexpr const char *thisEncoding = @encode(THead);

    template<template<typename> class TApplicator = pointer_applicator_t, typename TFunc>
    static inline bool visit(const char *typeEncoding, void *arg, TFunc fn)
    {
        if ((*typeEncoding == '@' && *thisEncoding == '@') || !strcmp(thisEncoding, typeEncoding))
        {
            fn(TApplicator<THead>::apply(arg));
            return true;
        }
        
        return false;
    }
};

#define OBJCRTXX_IMPLEMENT_VISITOR(applicator__, ...) \
    inline bool operator()(const char *typeEncoding, void *arg) \
    { \
        return runtime_visitor_t<__VA_ARGS__>::template visit<applicator__>(typeEncoding, arg, *this); \
    }

struct my_visitor
{
    using types = type_list_t<int, char, id>;

    template<typename T>
    using applicator = reference_applicator_t<T>;

    template<typename T>
    void operator()(T)
    {
        std::cout << "visit " << typeid(T).name() << std::endl;
    }
    
    void operator()(int x)
    {
        std::cout << "visit int " << x << std::endl;
    }
    
    void operator()(char x)
    {
        std::cout << "visit char " << x << std::endl;
    }

    void operator()(id x)
    {
        std::cout << [x description].UTF8String << std::endl;
    }
};

void fn()
{
    id x = @"Hola";

//    my_visitor()(@encode(id), &x);

    using types = type_list_t<int, char, id>;
    
    runtime_visitor_t<int, char, id>::visit(@encode(id), &x, my_visitor());
    runtime_visitor_t<int, char, id>::visit<pointer_applicator_t>(@encode(id), &x, my_visitor());
    runtime_visitor_t<int, char, id>::visit<reference_applicator_t>(@encode(id), &x, my_visitor());
    runtime_visitor_t<int, char, id>::visit<value_applicator_t>(@encode(id), &x, my_visitor());

    runtime_visitor_t<int, char, id>::visit<reference_applicator_t>(@encode(id), &x,
                                                                    [](auto &&var)
                                                                    {
                                                                        std::cout << typeid(var).name() << std::endl;
                                                                    });
}

void foo()
{
    CGRect rcZero = { 0, 0, 0, 0 };
    
    objcrtxx::ivar_ref_t<id> r1(nil, NULL);
    r1 = nil;

    objcrtxx::ivar_ref_t<CGRect> r2(nil, NULL);
    r2 = rcZero;
    r2->size.width = 0;
    
    objcrtxx::msgSend<float>(nil, @selector(init), 2, 3);
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        
        fn();
//        foo();
        
        std::cout << std::boolalpha;
        std::cout << std::is_pointer<id>::value << std::endl;
        std::cout << std::is_pointer<NSObject *>::value << std::endl;
        
        NSLog(@"Hello, World!");
    }
    
    return 0;
}
