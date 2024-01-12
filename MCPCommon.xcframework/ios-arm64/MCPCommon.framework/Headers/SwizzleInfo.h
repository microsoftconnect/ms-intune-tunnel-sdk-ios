//
//  SwizzleInfo.h
//  MCPCommon
//
//  Created by Richard Perry on 4/19/23.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

NS_ASSUME_NONNULL_BEGIN

@interface SwizzleInfo : NSObject
@property (nonatomic, assign) SEL originalSel;
@property (nonatomic, assign) SEL swizzleSel;
@property (nonatomic, assign) Method originalMeth;
@property (nonatomic, assign) Method SwizzleMeth;
@property (nonatomic, assign) IMP originalImp;
@property (nonatomic, assign) IMP swizzleImp;
@end

NS_ASSUME_NONNULL_END
