//
//  CLIArgs.h
//  MCPCore
//
//  Created by Tim Champagne Jr on 5/2/22.
//  Licensed to Microsoft under Contract #7267038.  
//

#ifndef CLIArgs_h
#define CLIArgs_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#pragma GCC visibility push(default)

struct CLIArgs
{
    CLIArgs()
    : m_argc(0),
    m_argv(nullptr)
    {
        // Intentionally blank
    }
    
    CLIArgs(int argc, char *argv[])
    : m_argc(argc),
    m_argv(argv)
    {
        // Intentionally blank
    }
    
    CLIArgs(const CLIArgs &rhs) = default;
    CLIArgs(CLIArgs &&rhs) = default;
    
    CLIArgs &operator=(const CLIArgs &rhs) = default;
    CLIArgs &operator=(CLIArgs &&rhs) = default;
    
    int m_argc;
    char **m_argv;
};

#pragma GCC visibility pop

#endif  // CLIArgs_h
