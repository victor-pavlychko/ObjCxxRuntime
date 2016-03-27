//
//  objcrtxx_imp.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2016 address.wtf. All rights reserved.
//

#ifdef OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

struct imp_t
{
    OBJCXX_PRIMITIVE_WRAPPER(imp_t, IMP, imp, NULL)
    
    inline static imp_t implementationWithBlock(id block);

    inline id getBlock();
    inline bool removeBlock();

    template<typename TRet, typename ...TArgs>
    inline TRet invoke(id self_, SEL cmd_, TArgs... args) const;
};

OBJCRTXX_END_NAMESPACE

#endif // OBJCRTXX_UMBRELLA_ACTIVE
