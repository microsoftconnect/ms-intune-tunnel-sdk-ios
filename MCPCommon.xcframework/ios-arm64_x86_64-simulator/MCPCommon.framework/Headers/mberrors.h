/*------------------------------------------------------------------
 * mberrors.h
 *
 * Feb 2013, user
 *
 * Copyright (c) 2013 by Mocana Corporation.
 * All rights reserved. 
 * Licensed to Microsoft under Contract #7267038.
 *------------------------------------------------------------------
 */

#ifndef MBERRORS_H
#define MBERRORS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum MBSTATUS {
    MB_OK = 0,
    MB_ERR_OK = 0,
    MB_ERR_STACK,
    MB_ERR_INV,
    MB_ERR_MEM,
    MB_ERR_EXIST,
    MB_ERR_ARG,               // 5
    MB_ERR_USE,
    MB_ERR_IF,
    MB_ERR_INPROGRESS,
    MB_ERR_TIME,
    MB_ERR_SEND,              // 10
    MB_ERR_ATTACH,
    MB_ERR_TIMEOUT,
    MB_ERR_FREE,
    MB_ERR_RESOURCE,
    MB_ERR_NOT_SUPPORTED,     // 15
    MB_ERR_INIT,
    MB_ERR_NOTCONN,
    MB_ERR_NOTOPEN,
    MB_ERR_STALE,
    MB_ERR_NOSUCH,            // 20
    MB_ERR_ACCESS,
    MB_ERR_PARSE,
    MB_ERR_RANGE,
    MB_ERR_REQUIRED,
    MB_ERR_UNEXPECTED,        // 25
    MB_ERR_CLIENT,
    MB_ERR_GRACEFUL_CLOSE,
    MB_ERR_NEW_AUTH_TOK_REQ,
    MB_ERR_EXTERNAL,
    MB_ERR_NOOP,              // 30
    MB_ERR_DSF,
    MB_ERR_CURL,
    MB_ERR_DUPLICATE,
    MB_ERROR,
    MB_ERR_EMPTY,             // 35
    MB_ERR_MAX_FEDSESSION_EXCEEDED,
    MB_ERR_EOF,
    MB_ERR_DORMANT,
    MB_ERR_UNKNOWN,
    MB_ERR_REMOTE_TERMINATE,  // 40
    MB_ERR_NOT_NOW,
    MB_ERR_PERP,
    MB_ERR_UNINIT,
    MB_ERR_OPENSSL,
    // ADD NEW ERRORS ABOVE THIS LINE.
    // Please update "libutils/strstatus.c" with friendly string mappings for
    // any new status codes.
    MB_ERR_END
} mb_err_t;

typedef mb_err_t MBSTATUS;

#ifdef __cplusplus
}               /* extern "C" */
#endif

#endif /* MBERRORS_H */
