//
//  objcrtxx_swizzle.h
//  ObjCxxRuntime
//
//  Created by Victor Pavlychko on 2/15/16.
//  Copyright © 2016 address.wtf. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

template<typename TResult, typename ...TArgs>
using swizzle_trampoline_t = TResult(^)(id, TArgs...);

template<typename TResult, typename ...TArgs>
using swizzle_block_t = TResult(^)(swizzle_trampoline_t<TResult, TArgs...>, id, TArgs...);

template<typename TResult, typename ...TArgs>
static void swizzle(class_t cls, sel_t selector, TResult(^block)(TResult(^trampoline)(id self_, TArgs... args), id self_, TArgs... args))
{
    __block imp_t original;

    auto super_class = cls.getSuperclass();
    auto method = cls.getInstanceMethod(selector);
    auto typeEncoding = method.getTypeEncoding();

    auto trampoline = ^TResult(id self_, TArgs... args) {
        return original
            ? original.invoke<TResult>(self_, selector, args...)
            : msgSendSuper<TResult>(self_, super_class, selector, args...);
    };
    
    auto replacement = imp_t::implementationWithBlock(^TResult(id self_, TArgs... args) {
        return block(trampoline, self_, args...);
    });

    if (!cls.addMethod(selector, replacement, typeEncoding))
    {
        original = method.setImplementation(replacement);
    }
}

OBJCRTXX_END_NAMESPACE
