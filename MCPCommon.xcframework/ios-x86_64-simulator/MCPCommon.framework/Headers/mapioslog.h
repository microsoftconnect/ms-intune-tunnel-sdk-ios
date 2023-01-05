//
//  mapioslog.h
//  mstapnext_injectable_ios
//
//  Created by Tim Champagne Jr. on 9/30/15.
//  Copyright © 2015 Mocana. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef mapioslog_h
#define mapioslog_h

#include <stdarg.h>

#import <Foundation/Foundation.h>

#import "log_defs.h"
#import "ExternalLogger.h"

#pragma GCC visibility push(default)

void IOSLogCb(ATLAS_CLIENT_LOG_LEVEL level,
              unsigned logClass,
              const char *pTime,
              const char *pLevel,
              const char *pClassLabel,
              const char *pLog,
              void *pUserContext);

void IOSSDKLogCb(ATLAS_CLIENT_LOG_LEVEL level,
              unsigned logClass,
              const char *pTime,
              const char *pLevel,
              const char *pClassLabel,
              const char *pLog,
              void *pUserContext);

void MAPIOSSetLogCb(ATLAS_CLIENT_logCb logCb);
void MAPIOSForceSDKLogging(bool alwaysLog);


#ifdef __cplusplus
extern "C" {
#endif

typedef NS_ENUM(NSInteger, MAPIOSLogLevel)
{
    MAPIOSLogLevelDebug,
    MAPIOSLogLevelInfo,
    MAPIOSLogLevelWarning,
    MAPIOSLogLevelMinor,
    MAPIOSLogLevelMajor,
    MAPIOSLogLevelCritical
};

void MAPIOSLoggerInit(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType);

MAPIOSLogLevel MAPIOSGetLogLevel(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType);
void MAPIOSSetLogLevel(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, const MAPIOSLogLevel mapiosLogLevel);

__attribute__ ((format (NSString, 2, 3)))
static inline void MAPIOSLogDebug(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, NSString *format, ...)
{
    va_list vargs;
    va_start(vargs, format);

#if __has_feature(objc_arc)
    NSString *str = [[NSString alloc] initWithFormat:format arguments:vargs];
#else
    NSString *str = [[[NSString alloc] initWithFormat:format arguments:vargs] autorelease];
#endif
    
    AC_LOG_EXT_debug(extLogType, "%s", [str UTF8String]);

    va_end(vargs);
}

static inline void MAPIOSLogDebugv(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, NSString *format, va_list vargs)
{
    AC_LOG_EXT_debug_l(extLogType, [format UTF8String], vargs);
}

__attribute__ ((format (NSString, 2, 3)))
static inline void MAPIOSLogInfo(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, NSString *format, ...)
{
    va_list vargs;
    va_start(vargs, format);

#if __has_feature(objc_arc)
    NSString *str = [[NSString alloc] initWithFormat:format arguments:vargs];
#else
    NSString *str = [[[NSString alloc] initWithFormat:format arguments:vargs] autorelease];
#endif
    
    AC_LOG_EXT_info(extLogType, "%s", [str UTF8String]);

    va_end(vargs);
}

static inline void MAPIOSLogInfov(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, NSString *format, va_list vargs)
{
    AC_LOG_EXT_info_l(extLogType, [format UTF8String], vargs);
}

__attribute__ ((format (NSString, 2, 3)))
static inline void MAPIOSLogWarn(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, NSString *format, ...)
{
    va_list vargs;
    va_start(vargs, format);

#if __has_feature(objc_arc)
    NSString *str = [[NSString alloc] initWithFormat:format arguments:vargs];
#else
    NSString *str = [[[NSString alloc] initWithFormat:format arguments:vargs] autorelease];
#endif
    
    AC_LOG_EXT_warn(extLogType, "%s", [str UTF8String]);

    va_end(vargs);
}

static inline void MAPIOSLogWarnv(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, NSString *format, va_list vargs)
{
    AC_LOG_EXT_warn_l(extLogType, [format UTF8String], vargs);
}

__attribute__ ((format (NSString, 2, 3)))
static inline void MAPIOSLogMinor(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, NSString *format, ...)
{
    va_list vargs;
    va_start(vargs, format);

#if __has_feature(objc_arc)
    NSString *str = [[NSString alloc] initWithFormat:format arguments:vargs];
#else
    NSString *str = [[[NSString alloc] initWithFormat:format arguments:vargs] autorelease];
#endif
    
    AC_LOG_EXT_minor(extLogType, "%s", [str UTF8String]);

    va_end(vargs);
}

static inline void MAPIOSLogMinorv(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, NSString *format, va_list vargs)
{
    AC_LOG_EXT_minor_l(extLogType, [format UTF8String], vargs);
}

__attribute__ ((format (NSString, 2, 3)))
static inline void MAPIOSLogMajor(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, NSString *format, ...)
{
    va_list vargs;
    va_start(vargs, format);

#if __has_feature(objc_arc)
    NSString *str = [[NSString alloc] initWithFormat:format arguments:vargs];
#else
    NSString *str = [[[NSString alloc] initWithFormat:format arguments:vargs] autorelease];
#endif
    
    AC_LOG_EXT_major(extLogType, "%s", [str UTF8String]);

    va_end(vargs);
}

static inline void MAPIOSLogMajorv(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, NSString *format, va_list vargs)
{
    AC_LOG_EXT_major_l(extLogType, [format UTF8String], vargs);
}

__attribute__ ((format (NSString, 2, 3)))
static inline void MAPIOSLogCritical(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, NSString *format, ...)
{
    va_list vargs;
    va_start(vargs, format);

#if __has_feature(objc_arc)
    NSString *str = [[NSString alloc] initWithFormat:format arguments:vargs];
#else
    NSString *str = [[[NSString alloc] initWithFormat:format arguments:vargs] autorelease];
#endif
    
    AC_LOG_EXT_critical(extLogType, "%s", [str UTF8String]);

    va_end(vargs);
}

static inline void MAPIOSLogCriticalv(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, NSString *format, va_list vargs)
{
    AC_LOG_EXT_critical_l(extLogType, [format UTF8String], vargs);
}

__attribute__ ((format (NSString, 3, 4)))
static inline void MAPIOSLog(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, ATLAS_CLIENT_LOG_LEVEL logLevel, NSString *format, ...)
{
    va_list vargs;
    va_start(vargs, format);

#if __has_feature(objc_arc)
    NSString *str = [[NSString alloc] initWithFormat:format arguments:vargs];
#else
    NSString *str = [[[NSString alloc] initWithFormat:format arguments:vargs] autorelease];
#endif

    AC_LOG_EXT_log(extLogType, logLevel, "%s", [str UTF8String]);

    va_end(vargs);
}

static inline void MAPIOSLogv(ATLAS_CLIENT_LOG_CLASS_EXTERNAL extLogType, ATLAS_CLIENT_LOG_LEVEL logLevel, NSString *format, va_list vargs)
{
    AC_LOG_EXT_log_l(extLogType, logLevel, [format UTF8String], vargs);
}

#define MAPIOSInjGetLogLevel() \
MAPIOSGetLogLevel(ACLC_EXT_INJECTABLE)

#define MAPIOSInjDebug(fmt, args...) \
MAPIOSLogDebug(ACLC_EXT_INJECTABLE, fmt, ##args)

#define MAPIOSInjInfo(fmt, args...) \
MAPIOSLogInfo(ACLC_EXT_INJECTABLE, fmt, ##args)

#define MAPIOSInjWarn(fmt, args...) \
MAPIOSLogWarn(ACLC_EXT_INJECTABLE, fmt, ##args)

#define MAPIOSInjMinor(fmt, args...) \
MAPIOSLogMinor(ACLC_EXT_INJECTABLE, fmt, ##args)

#define MAPIOSInjMajor(fmt, args...) \
MAPIOSLogMajor(ACLC_EXT_INJECTABLE, fmt, ##args)

#define MAPIOSInjCritical(fmt, args...) \
MAPIOSLogCritical(ACLC_EXT_INJECTABLE, fmt, ##args)

#define MAPIOSInjLog(logLevel, fmt, args...) \
MAPIOSLog(ACLC_EXT_INJECTABLE, logLevel, fmt, ##args)

    //
#define MAPIOSIntuneGetLogLevel() \
MAPIOSGetLogLevel(ACLC_EXT_INTUNE)

#define MAPIOSIntuneLog(logLevel, fmt, args...) \
MAPIOSLog(ACLC_EXT_INTUNE, logLevel, fmt, ##args)

#define MAPIOSIntuneDebug(fmt, args...) \
MAPIOSIntuneLog(ACL_DEBUG, fmt, ##args)

#define MAPIOSIntuneInfo(fmt, args...) \
MAPIOSIntuneLog(ACL_INFO, fmt, ##args)

#define MAPIOSIntuneWarn(fmt, args...) \
MAPIOSIntuneLog(ACL_WARN, fmt, ##args)

#define MAPIOSIntuneMinor(fmt, args...) \
MAPIOSIntuneLog(ACL_MINOR, fmt, ##args)

#define MAPIOSIntuneMajor(fmt, args...) \
MAPIOSIntuneLog(ACL_MAJOR, fmt, ##args)

#define MAPIOSIntuneCritical(fmt, args...) \
MAPIOSIntuneLog(ACL_CRIT, fmt, ##args)

#ifdef __cplusplus
}
#endif

#pragma GCC visibility pop

#endif /* mapioslog_h */
