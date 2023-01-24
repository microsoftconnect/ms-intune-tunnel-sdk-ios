//
//  MCP_UIActivityViewController.h
//  MSTAPNextLink
//
//  Created by Richard Perry on 1/19/21.
//  Copyright © 2021 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <UIKit/UIKit.h>

#import "MCP.h"

NS_ASSUME_NONNULL_BEGIN

MCP_EXPORT
@interface MCP_UIActivityViewController : UIActivityViewController
-(instancetype)initWithActivityItems:(NSArray *)activityItems applicationActivities:(NSArray<__kindof UIActivity *> *)applicationActivities withBackingController:(UIActivityViewController*)backingController;
- (NSArray *)MCP_availableActivitiesForItems:(NSArray *)items;
@end

NS_ASSUME_NONNULL_END
