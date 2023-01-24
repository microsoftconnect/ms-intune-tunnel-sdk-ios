//
//  MCP.h
//
//  Created by Tim Champagne Jr on 2/28/22.
//  Copyright © 2022 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MCP_h
#define MCP_h

#ifndef SWIG
#define MCP_PRAGMA(X) _Pragma(#X)
#else
// SWIG can't seem to handle _Pragma, which is fine since it doesn't need to see our pragmas anyway
#define MCP_PRAGMA(X)
#endif

#define MCP_BEGIN_EXPORT() MCP_PRAGMA(GCC visibility push(default))
#define MCP_END_EXPORT() MCP_PRAGMA(GCC visibility pop)

#ifndef SWIG
#define MCP_EXPORT __attribute__ ((visibility ("default")))
#else
#define MCP_EXPORT
#endif

#endif  // MCP_h
