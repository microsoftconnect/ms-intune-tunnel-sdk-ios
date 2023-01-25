//
//  MCPDirectoryUtils.h
//  MCPCore
//
//  Created by Tim Champagne Jr on 4/27/22.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>

__attribute__ ((visibility ("default")))
@interface MCPDirectoryUtils : NSObject

@property(class, strong, nonatomic, readonly) NSString *frameworkDirPath;

@end
