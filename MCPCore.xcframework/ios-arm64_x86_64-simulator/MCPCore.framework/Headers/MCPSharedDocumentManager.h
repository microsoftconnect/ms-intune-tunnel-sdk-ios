//
//  MCPSharedDocumentManager.h
//  mstapnext_injectable_ios
//
//  Created by Connor Kelley on 4/7/21.
//  Copyright © 2021 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MCPSharedDocumentManager_h
#define MCPSharedDocumentManager_h

__attribute__ ((visibility ("default")))
@interface MCPSharedDocument : NSObject

- (MCPSharedDocument *)initWithOriginalURL:(NSURL *)origin destinationURL:(NSURL *)destUrl;

@property (nonatomic, strong) NSURL *originalURL;
@property (nonatomic, strong) NSURL *destinationURL;

@end

__attribute__ ((visibility ("default")))
@interface MCPSharedDocumentManager : NSObject

+ (MCPSharedDocumentManager *)sharedDocumentManager;
- (MCPSharedDocument *)documentForURL:(NSURL *)sourceURL;

@property (nonatomic, strong) NSMutableSet<MCPSharedDocument *> *sharedDocuments;

- (void)cleanupWithDate:(NSDate*) compareDate;

@end

#endif /* MCPSharedDocumentManager_h */
