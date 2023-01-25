#ifndef __BYPASS_H_
#define __BYPASS_H_

#include <pthread.h>
#include "mberrors.h"

#pragma GCC visibility push(default)

#ifdef __cplusplus
extern "C" {
#endif

#define BYPASS_STATE_CONTEXT void*

int BYPASS_pthread_create(pthread_t *thread, const pthread_attr_t * attr,
                          void *(*start_routine)(void *), void *arg);

/*
 *
 */
pthread_key_t BYPASS_getDefaultKey();

/*
 * Call this to initialize the bypass module.
 * Behavior is undefined if this is not called.
 * Safe to be called multiple times, so all consumers should call init.
 */
MBSTATUS BYPASS_init();

/*
 * This exists as a separate function because relinks can't be initialized
 * during the initial call to BYPASS_init on Android because the relinker isn't
 * set up early enough.
 */
MBSTATUS BYPASS_initRelinks();

/*
 * Initializes a non-default bypass key. If the key is inheritable, any thread
 * spawned will inherit the value of the key from its parent thread.
 */
MBSTATUS BYPASS_init_key(pthread_key_t *key);
MBSTATUS BYPASS_init_inheritable_key(pthread_key_t *key);

/*
 * Returns TRUE/1 if the bypass lock was acquired,
 * and 0 if the bypass lock was already held.
 */
int BYPASS_try_acquire();
int BYPASS_try_acquire_key(pthread_key_t key);

/*
 * Sets the bypass state to acquired regardless of the current state
 *
 * If provided, outWasPreviouslyAcquired will be set according to the
 * state prior to alteration: TRUE - locked, FALSE - unlocked.
 */
void BYPASS_acquire(int *outWasPreviouslyAcquired);
void BYPASS_acquire_key(pthread_key_t key, int *outWasPreviouslyAcquired);

/*
 * Sets the bypass state to release, regardless of current state.
 *
 * If provided, outWasPreviouslyAcquired will be set according to the
 * state prior to alteration: TRUE - locked, FALSE - unlocked.
 */
void BYPASS_release(int *outWasPreviouslyAcquired);
void BYPASS_release_key(pthread_key_t key, int *outWasPreviouslyAcquired);

/*
 * Resets the state as indicated by provided state boolean, True for locked,
 * false for unlocked.
 *
 * Typically used with a prior call to BYPASS_acquire or BYPASS_release to
 * reset the state to its former value.
 */
void BYPASS_resetState(int state);
void BYPASS_resetState_key(pthread_key_t key, int state);

/*
 * Returns 0 is bypass is currently disabled and 1 if it is enabled.
 */
int BYPASS_isEnabled(void);
int BYPASS_isKeyEnabled(pthread_key_t key);

// Make sure any threads keep bypass information
int BYPASS_pthread_create(pthread_t *thread, const pthread_attr_t * attr,
void *(*start_routine)(void *), void *arg);


// Get the current state of all tracked keys
BYPASS_STATE_CONTEXT BYPASS_getState_ctx();
// Apply the state of tracked keys on a new thread
void BYPASS_applyState_ctx(BYPASS_STATE_CONTEXT bypassCtx);


#ifdef __cplusplus
}

#include "scope_guard.h"

struct release_bypass_t {};
constexpr release_bypass_t release_bypass = release_bypass_t();

class bypass_guard : public scope_guard
{
public:
    bypass_guard(const pthread_key_t key = BYPASS_getDefaultKey())
        : scope_guard([this]() {
              BYPASS_resetState_key(m_key, m_state);
          }),
          m_key(key),
          m_state(0)
    {
        BYPASS_acquire_key(m_key, &m_state);
    }

    bypass_guard(release_bypass_t, const pthread_key_t key = BYPASS_getDefaultKey())
        : scope_guard([this]() {
            BYPASS_resetState_key(m_key, m_state);
          }),
          m_key(key),
          m_state(0)
    {
        BYPASS_release_key(m_key, &m_state);
    }
    
    bypass_guard(const bypass_guard &originalThread)
        : scope_guard([this]() {
            BYPASS_resetState_key(m_key, m_state);
          }),
          m_key(originalThread.m_key),
          m_state(BYPASS_isKeyEnabled(m_key))
    {
        BYPASS_resetState_key(originalThread.m_key, originalThread.m_state);
    }

    bool WasBypassAcquired() const
    {
        // the bypass was acquired if the state wasn't already 1
        return (m_state == 0);
    }

private:
    const pthread_key_t m_key;
    int m_state;
};

#endif

#pragma GCC visibility pop

#endif // __BYPASS_H__
