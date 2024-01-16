/*------------------------------------------------------------------
 * Relinker.h
 *
 * Aug 2015
 *
 * Copyright (c) 2015 by Mocana Corporation.
 * All rights reserved.
 * Licensed to Microsoft under Contract #7267038.
 *------------------------------------------------------------------
 */

#ifndef RELINKER_H
#define RELINKER_H

#include <stdint.h>

#include "mberrors.h"

// Flags for Relinker which types of libraries should be relinked.
enum {
    kRelinkUserLibs   = (1 << 0),
    kRelinkSystemLibs = (1 << 1)
};
typedef uint8_t RelinkFlags;

#define RELINKER_PRIORITY_HIGHEST       -20
#define RELINKER_PRIORITY_HIGH          -10
#define RELINKER_PRIORITY_DEFAULT         0
#define RELINKER_PRIORITY_LOW            10
#define RELINKER_PRIORITY_LOWEST         20
#define RELINKER_PRIORITY_UNKNOWN   (RELINKER_PRIORITY_LOWEST + 1)

//--- Relinker violation levels ---
#define RELINKER_VIOLATION_ERROR 1
#define RELINKER_VIOLATION_QUIRK 2

//--- Relinker error codes ---
// Violations
#define RELINKER_VIOLATION_INTERNAL_RELEASENOTFOUND 1
#define RELINKER_VIOLATION_INTERNAL_ABINOTFOUND     2
#define RELINKER_VIOLATION_INTERNAL_SDKNOTFOUND     3

#define RELINKER_VIOLATION_DLSYM_RTLDDEFAULT_BROKEN 100

#define RELINKER_QUIRK_DLOPEN_PREMARSHMALLOW        500
#define RELINKER_QUIRK_DLOPEN_PRIVATE_LIBRARY       501
#define RELINKER_QUIRK_CHROME_INTERNAL_LIBRARY      502
#define RELINKER_QUIRK_DLOPEN_PRIVATE_API29_LIBRARY 503

// Run-time errors (TBD)
#define RELINKER_ERROR_INVALID_LIBINFO              1000
#define RELINKER_ERROR_FAILED_RELINK                1001
#define RELINKER_ERROR_FAILED_SYMBOL                1002

#define RELINKER_ERROR_PROCMAP_MAPSPARSE            2000
#define RELINKER_ERROR_PROCMAP_PERMISSIONPARSE      2001

#define STRING_VIOLATION_INTERNAL_RELEASE_NOT_FOUND "Release version not found"
#define STRING_VIOLATION_INTERNAL_ABINOTFOUND       "CPU ABI not found"
#define STRING_VIOLATION_SDKNOTFOUND                "SDK Version not found"
#define STRING_VIOLATION_DLSYM_RTLDDEFAULT_BROKEN   "Dlsym issue with RTLD_DEFAULT"
#define STRING_QUIRK_DLOPEN_PREMARSHMALLOW          "Pre-Marshmallow"
#define STRING_QUIRK_DLOPEN_PRIVATE_LIBRARY         "Dlopen of a private library"
#define STRING_QUIRK_CHROME_INTERNAL_LIBRARY        "Chrome contains private library"
#define STRING_QUIRK_DLOPEN_PRIVATE_API29_LIBRARY   "Dlopen of a private library Android 10 or greater"
#define STRING_UNRECOGNIZED_ERROR                   "Error Unrecognized"

//------------------------------------------//

/* If defined, disable trampoline usage */
// #define DISABLE_TRAMPOLINE

//---------//

#pragma GCC visibility push(default)

#pragma GCC visibility pop

#ifdef __cplusplus

#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <memory>
#include <mutex>
#include "RelinkerErrorListener.h"
#include "bypass.h"
#include "TypeListUtils.h"
#include "MetaUtils.h"
#include "BaseRelinkTrigger.h"
#include "RelinkPtrs.h"
#include "RelinkerUtils.h"

#pragma GCC visibility push(default)

// Forward declaration
class LibInfo;
struct RELINKER_FUNCTION_CALLBACKS;

// Forward decl of unit test helper class
namespace relink
{
    class RelinkerHelper;
}

class IDeferredImageLoadCB
{
 public:
    virtual ~IDeferredImageLoadCB() {}
    virtual MBSTATUS OnDeferredImageLoad(const std::string &imageName) = 0;
};

class Relinker
{
 protected:
    Relinker();
    Relinker(const std::string &appName, RelinkFlags flags);
    virtual ~Relinker();

 public:
    static constexpr int kRelinkFlagsDefault = kRelinkUserLibs | kRelinkSystemLibs;

    static MBSTATUS CreateRelinker(const std::string &appName = "",
                                   RelinkFlags flags = kRelinkUserLibs | kRelinkSystemLibs,
                                   const std::string &tmpDir = "",
                                   const std::vector<std::string> &relinkerBlacklist = std::vector<std::string>());
    static void ReleaseRelinker(Relinker *relinker);

    void ResetRelinkedLibraries();
    MBSTATUS AddRelinkEntries(RelinkMap &relinkEntries, bool forced = false);
    MBSTATUS AddForcedRelinkEntries(RelinkMap &relinkEntries);
    MBSTATUS PerformRelink();

    /* Priority, -20 (highest) to 20 (lowest) */
    MBSTATUS RegisterDeferredImageLoadCallback(IDeferredImageLoadCB *callback,
                                               int priority=RELINKER_PRIORITY_DEFAULT);

    MBSTATUS DeregisterDeferredImageLoadCallback(IDeferredImageLoadCB *callback,
                                                 int priority=RELINKER_PRIORITY_UNKNOWN);

    MBSTATUS PerformDeferredImageInit();
    MBSTATUS performForcedRelink(const std::string &imageName, RelinkMap &relinkEntries, BaseRelinkTrigger::PartialRelinkType partialType);
    MBSTATUS performForcedRelinkForAll(RelinkMap &relinkEntries, BaseRelinkTrigger::PartialRelinkType partialType);

    MBSTATUS performRelinksAgain();

    /* NOTE
     * This function is exposed STRICTLY for essential relinks ONLY.
     * If you are calling this, you better know what you are doing!
     */
    MBSTATUS _PerformPriorityRelink();

    MBSTATUS GetCallerPath(void* addr, std::string& pathOut);

    MBSTATUS AddIgnoreLibrary(const std::string &libraryName,
                              const BaseRelinkTrigger::PartialRelinkType partialRelinkType = BaseRelinkTrigger::PRT_RELINK_ALL);
    MBSTATUS AddIgnoreSymbol(const std::string &symbolName);
    /* NOTE: Relinker will own the passed in instance and release it */
    MBSTATUS AddIgnoreLibrary(BaseRelinkTrigger *trigger);
    /**
     * Ignore plugins are like ignore libraries, but they can be added after
     * relinks have been performed.
     */
    MBSTATUS AddIgnorePlugin(const std::string &libraryName,
                             const BaseRelinkTrigger::PartialRelinkType partialRelinkType = BaseRelinkTrigger::PRT_RELINK_ALL);
    
    void OnLibraryRemoved(const std::string &library);
    void OnLibraryAdded(const std::string &library, bool bypassLibrary);
    bool ContainsRelinkedLibrary(const std::string &libName);
    
    MBSTATUS CheckLibrariesLoaded(const std::list<std::string> &libraryNames, bool& loaded);

    static Relinker*& GetRelinker();

    MBSTATUS GetRelinkEntryFunction(const std::string &symbolName, void*& func, bool skipAdded = false);

    MBSTATUS GetOriginalFunction(const std::string &symbolName, void*& func, bool isPassthru = false);

    MBSTATUS GetFunctionFromLibrary(const std::string &libraryName, const std::string &symbolName, void*& func);

    MBSTATUS CheckSymbolExists(const std::string &libraryName, const std::string &symbolName, bool& result);
    MBSTATUS CheckAddressInLibrary(const std::string &libraryName, void *addr);
    MBSTATUS CheckAddressInOpaqueLibraryInfo(void *opaqueLibInfo, void *addr);

    MBSTATUS AddExclusiveRelink(BaseRelinkTrigger* trigger,  RelinkMap& relink);
    MBSTATUS AddSupplementalRelink(BaseRelinkTrigger* trigger,  RelinkMap& relink);

    MBSTATUS UpdateRelink(const std::string &symbolName, void *func);
    void *GetOpaqueLibraryInfo(const std::string &libraryName);

    std::string GetFullImageName(const std::string &imageName);

    class Violation
    {
     public:
        Violation(unsigned int i, unsigned int s) : id(i), severity(s) {}
        unsigned int id;
        unsigned int severity;
    };

    static MBSTATUS isPlatformValid(int& numViolations);
    static MBSTATUS getPlatformViolations(std::list<Violation>& violations);
    static bool isViolatedOnPlatform(unsigned int id);

    static std::string getStringFromErrorCode(unsigned int errorCode);

    static MBSTATUS setErrorListener(RelinkerErrorListener* cb);

#if defined(__APPLE__)
    virtual void* getCodeSignature(const std::string &libraryName) = 0;
    virtual void* getEmbeddedEntitlements(const std::string &libraryName, uint32_t &size) = 0;
#endif

    // Send error condition to listener and obtain flag whether the error should be ignored (result = true)
    static bool foundErrorCondition(unsigned int errorCode, const std::string& explanation);

    MBSTATUS invokeDeferredImageLoadForImage(const std::string &imageName);

    // These have been made public for future intune work

    static void *dlopen(const char *library, int flag);

    static int dlclose(void *pHdl);

    static void *dlsym(void *handle, const char *symbolName);

    bool shouldIgnore(const std::string &lib,
                      BaseRelinkTrigger::PartialRelinkType &outPartialRelinkType);

 protected:
    virtual std::string normalizeLibraryName(const std::string &library);
    void* findLibHandle(const std::string &libName);
    RelinkPtrs *getRelinkEntry(std::lock_guard<std::recursive_mutex> &lck, const std::string &symbolName, bool skipAdded);

    std::string m_appName;
    RelinkFlags m_relinkFlags;

    static RelinkerErrorListener* getErrorListener();
    static std::unique_ptr<RelinkerErrorListener> m_ErrorCb;

    std::recursive_mutex  m_allInternalLock;
    std::recursive_mutex  m_supplementalLock;
    std::recursive_mutex  m_fpCacheLock;

    enum RelinkResult
    {
        Success = 0,
        Ignored,
    };

 private:
    static MBSTATUS removeRelinker(Relinker *relinker);
    static MBSTATUS relinkDynamic(Relinker* rel,
                                  const std::string& library,
                                  const bool bypassLibrary,
                                  BaseRelinkTrigger::PartialRelinkType partialRelinkType = BaseRelinkTrigger::PRT_RELINK_ALL);

    /*
     * Note: The libraries returned from here should fulfill the invariant:
     *       libraryName == normalizeLibaryName(libraryName)
     */
    virtual MBSTATUS getLoadedLibraries(std::set<std::string> &outLibraries, bool repopulateLibraryList = false) = 0;

    virtual MBSTATUS performRelink(const std::string &libraryName,
                                   const bool bypassLibrary,
                                   RelinkMap &relinkEntries,
                                   RelinkResult &result,
                                   BaseRelinkTrigger *trigger = nullptr,
                                   BaseRelinkTrigger::PartialRelinkType partialType = BaseRelinkTrigger::PRT_RELINK_ALL,
                                   bool forced = 0) = 0;

    virtual MBSTATUS performRelinkAgain(RelinkMap &relinkEntries) = 0;

    virtual MBSTATUS getImageLoadOrder(std::list<std::string> &loadOrder) = 0;

    virtual MBSTATUS performCheckSymbol(const std::string &libraryName, const std::string &symbolName, bool& result) = 0;
    virtual MBSTATUS performCheckAddressInLibrary(const std::string &libraryName, void *addr) = 0;
    virtual MBSTATUS performCheckAddressInOpaqueLibraryInfo(void *opaqueLibInfo, void *addr) = 0;
    virtual void *performGetOpaqueLibraryInfo(const std::string &libraryName) = 0;

    virtual MBSTATUS performLocateAddress(void* addr, LibInfo &out) = 0;

    virtual MBSTATUS performTrampolineLookup(bool install, const std::string &fctName,
                                             const std::string &caller, void* &target) = 0;
    virtual MBSTATUS getLinkerDLFunc(const std::string &dlFuncName, void*& pDlFuncAddr) = 0;

    virtual std::string getFullImageName(const std::string &imageName) = 0;

    bool removeCallbacksFromList(std::vector<IDeferredImageLoadCB *> rCallbackList,
                                 IDeferredImageLoadCB *callback);

    MBSTATUS invokeDeferredImageLoadCallbacks(const std::string &imageName);

    virtual void removeLibInfo(const std::string &libraryName);

    virtual void removeLibInfoMap();

    void saveLibHandle(void *pHdl, const std::string &libName);
    std::string findLibName(void *pHdl);
    bool removeLibHandle(void *pHdl);

    MBSTATUS performRelinkInternal(bool recordLinkedLibraries = true);
   
    MBSTATUS addIgnoreLibrary(const std::string &libraryName,
                              const BaseRelinkTrigger::PartialRelinkType partialRelinkType);
    MBSTATUS addIgnoreLibrary(BaseRelinkTrigger* tr);

    bool shouldIgnore(const std::string &lib);

    /* Function used by unit tests to influence list of ignored libraries */
    static void SetupIgnoreLibraryList(const std::string &libraryName);

    struct RelinkedLibrary
    {
        RelinkedLibrary(const std::string &libraryNameArg, const bool bypassLibraryArg)
            : libraryName(libraryNameArg),
              bypassLibrary(bypassLibraryArg)
        {

        }

        RelinkedLibrary()
            : bypassLibrary(false)
        {

        }

        bool operator<(const RelinkedLibrary &rhs) const
        {
            return (libraryName < rhs.libraryName);
        }

        bool operator==(const RelinkedLibrary &rhs) const
        {
            return (libraryName == rhs.libraryName &&
                    bypassLibrary == rhs.bypassLibrary);
        }
        
        std::string libraryName;
        bool bypassLibrary;
    };


    RelinkMap             m_allRelinks;
    std::set<RelinkedLibrary> m_relinkedLibraries;
    std::set<BaseRelinkTrigger *> m_ignoreLibraries;
    bool m_relinkPerformed;
    /* Set by unit test code */
    static std::set<std::string> sm_ignoreLibraries;

    /* Override standard relink list */
    std::map<BaseRelinkTrigger *, RelinkMap> m_exclusiveRelinks;

    /* Add to standard relink list */
    std::map<BaseRelinkTrigger *, RelinkMap> m_addedRelinks;

    std::map<std::string, void *> m_originalFunctions;

    struct RefCountedLibName
    {
        RefCountedLibName(std::string libName)
            : refCount(1), libName(libName)
        {}
        RefCountedLibName(const RefCountedLibName&) = delete;
        RefCountedLibName(RefCountedLibName&&) = delete;

        size_t incRefCount() { return ++refCount; }
        size_t decRefCount() { return --refCount; }

        size_t refCount;
        const std::string libName;
    };
    std::map<void*, RefCountedLibName> m_libHandles;
    std::map<int, std::vector<IDeferredImageLoadCB *>> m_deferredImageInitCallbacks;

    static std::list<Violation> m_Violations;
    static bool                 m_ViolationsInited;

    friend class relink::RelinkerHelper;  // RelinkerHelper used for testing purposes only.

    static Relinker *g_spInstance;
};

#pragma GCC visibility pop

#endif

#pragma GCC visibility push(default)

#ifdef __cplusplus
extern "C" {

MBSTATUS RELINKER_InitRelinkerWithAppName(RelinkFlags flags, const char* pAppName);
MBSTATUS RELINKER_AddRelinkEntries(RelinkMap &relinkEntries);
MBSTATUS RELINKER_AddForcedRelinkEntries(RelinkMap &relinkEntries);
MBSTATUS RELINKER_AddExclusiveRelink(BaseRelinkTrigger *trigger, RelinkMap &relinkEntries);
MBSTATUS RELINKER_AddSupplementalRelink(BaseRelinkTrigger *trigger, RelinkMap &relinkEntries);
MBSTATUS RELINKER_PerformForcedRelink(const std::string &imageName, RelinkMap &relinkEntries, BaseRelinkTrigger::PartialRelinkType partialType);
MBSTATUS RELINKER_PerformForcedRelinkForAll(RelinkMap &relinkEntries, BaseRelinkTrigger::PartialRelinkType partialType);
#if defined(__APPLE__)
void *RELINKER_GetEmbeddedEntitlements(const char *libraryName, uint32_t &size);
#endif
/* Assign Relinker function pointers to passed in struct. */
MBSTATUS RELINKER_setCallbacks(RELINKER_FUNCTION_CALLBACKS *pCallbacks);
#endif

MBSTATUS RELINKER_InitRelinker();
MBSTATUS RELINKER_InitRelinkerWithTempDir(const char *pTmpDir, const char *relinkerBlacklist);

MBSTATUS RELINKER_ResetRelinkedLibraries();
MBSTATUS RELINKER_PerformRelink();
MBSTATUS RELINKER_PerformRelinksAgain();

MBSTATUS RELINKER_AddIgnoreLibrary(const char *libraryName);
bool RELINKER_ShouldIgnoreLibrary(const char *libraryName);
MBSTATUS RELINKER_AddPartialIgnoreLibrary(const char *libraryName,
                                          uint32_t partialRelinkType);
MBSTATUS RELINKER_AddIgnorePlugin(const char *libraryName,
                                  uint32_t partialRelinkType);

MBSTATUS RELINKER_CheckLibrariesLoaded(const char **libraries);

void *RELINKER_GetOriginalFunction(const char *symbolName, bool isPassthru);
void *RELINKER_GetDlsymFunction();
MBSTATUS RELINKER_UpdateRelink(const char *symbolName, void *func);
MBSTATUS RELINKER_CheckAddressInLibrary(const char *libraryName, void *addr);
MBSTATUS RELINKER_CheckAddressInOpaqueLibraryInfo(void *opaqueLibInfo, void *addr);
void *RELINKER_GetOpaqueLibraryInfo(const char *libraryName);
bool RELINKER_CheckSymbolExists(const char *libraryName, const char *symbolName);
#if defined(__APPLE__)
void *RELINKER_GetCodeSignature(const char *libraryName);
#endif

#pragma GCC visibility pop

#ifdef __cplusplus
}
#endif

#endif /* RELINKER_H */
