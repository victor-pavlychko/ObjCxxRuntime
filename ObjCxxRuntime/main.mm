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
        
        foo();
        
        std::cout << std::boolalpha;
        std::cout << std::is_pointer<id>::value << std::endl;
        std::cout << std::is_pointer<NSObject *>::value << std::endl;
        
        NSLog(@"Hello, World!");
    }
    
    return 0;
}
