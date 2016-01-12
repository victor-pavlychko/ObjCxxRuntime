//
//  objcrtxx.h
//
//  Created by Victor Pavlychko on 08.01.2016.
//  Copyright © 2015 Address WTF. All rights reserved.
//
//  The MIT License (MIT)
//  Copyright (c) 2016 Victor Pavlychko
//
//  Permission is hereby granted, free of charge, to any person obtaining
//  a copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included
//  in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifndef objcrtxx_h__
#define objcrtxx_h__

#include <type_traits>

#import <objc/runtime.h>
#import <objc/message.h>

#define OBJCRTXX_UMBRELLA_ACTIVE

#include "objcrtxx_defs.h"
#include "objcrtxx_forwards.h"
#include "objcrtxx_msgsend.h"

#include "objcrtxx_list.h"

#include "objcrtxx_category.h"
#include "objcrtxx_class.h"
#include "objcrtxx_imp.h"
#include "objcrtxx_ivar.h"
#include "objcrtxx_method.h"
#include "objcrtxx_property.h"
#include "objcrtxx_protocol.h"
#include "objcrtxx_sel.h"

#include "objcrtxx_list_impl.h"

#include "objcrtxx_category_impl.h"
#include "objcrtxx_class_impl.h"
#include "objcrtxx_imp_impl.h"
#include "objcrtxx_ivar_impl.h"
#include "objcrtxx_method_impl.h"
#include "objcrtxx_property_impl.h"
#include "objcrtxx_protocol_impl.h"
#include "objcrtxx_sel_impl.h"

#include "objcrtxx_defs_cleanup.h"

#undef OBJCRTXX_UMBRELLA_ACTIVE

#endif // objcrtxx_h__
