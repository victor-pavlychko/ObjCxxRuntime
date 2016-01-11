//
//  objcrtxx_protocol.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//

#ifndef OBJCRTXX_UMBRELLA_ACTIVE
#error Please include objcrtxx.h umbrella header
#endif // OBJCRTXX_UMBRELLA_ACTIVE

OBJCRTXX_BEGIN_NAMESPACE

struct protocol_t
{
    OBJCXX_PRIMITIVE_WRAPPER(protocol_t, __Protocol_t, protocol, nil)
};

OBJCRTXX_END_NAMESPACE
