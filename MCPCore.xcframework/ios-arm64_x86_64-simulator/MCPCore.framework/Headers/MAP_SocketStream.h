//
//  MAP_SocketStream.h
//  mstapnext_injectable_ios
//
//  Created by Connor Kelley on 2/4/19.
//  Copyright © 2019 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MAP_SocketStream_h
#define MAP_SocketStream_h

#import "NSStream+MCP_SocketStream.h"
#import "SocketSSLConnector.h"

@interface MAP_SocketStream : NSObject<MCP_SocketStreamProvider, SSLConnectorDelegate>

@end

#endif /* MAP_SocketStream_h */
