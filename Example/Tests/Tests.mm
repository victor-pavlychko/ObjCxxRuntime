//
//  objcrtxxTests.m
//  objcrtxxTests
//
//  Created by Victor Pavlychko on 03/27/2016.
//  Copyright (c) 2016 Victor Pavlychko. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <objcrtxx/objcrtxx.h>

@interface Tests : XCTestCase

@end

@implementation Tests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample
{
    XCTFail(@"No implementation for \"%s\"", __PRETTY_FUNCTION__);
}

@end

