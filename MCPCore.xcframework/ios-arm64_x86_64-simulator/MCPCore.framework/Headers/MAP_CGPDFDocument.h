//
//  MAP_ CGPDFDocument.h
//  mstapnext_injectable_ios
//
//  Created by Vadim Lozko on 3/28/17.
//  Copyright © 2017 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MAP__CGPDFDocument_h
#define MAP__CGPDFDocument_h

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

#ifdef __cplusplus
extern "C" {
#endif

CGPDFDocumentRef MAP_CGPDFDocumentCreateWithURL(CFURLRef url);

void MAP_CGPDFDocumentClassInit(void);

#ifdef __cplusplus
}
#endif

#endif /* MAP__CGPDFDocument_h */
