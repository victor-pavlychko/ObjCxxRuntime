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

using namespace address_wtf;

void foo()
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
    });
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, World!");
    }
    
    return 0;
}
