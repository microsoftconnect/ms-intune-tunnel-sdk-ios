//
//  MCPColorUtils.h
//  MCPCore
//
//  Created by Tim Champagne Jr on 4/27/22.
//

#import <UIKit/UIKit.h>

#include <memory>

#include "ConfigProfileElements.h"

__attribute__ ((visibility ("default")))
@interface MCPColorUtils : NSObject

+ (UIColor *)convertOptionalColor:(std::shared_ptr<AtlasColor> &)spColor;

@end
