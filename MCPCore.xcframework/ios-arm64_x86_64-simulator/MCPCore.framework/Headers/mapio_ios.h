//
//  mapio_ios.h
//  mobile_prometheus
//
//  Created by Tim Champagne Jr. on 10/19/15.
//  Licensed to Microsoft under Contract #7267038.
//

/**
 * @file mapio_ios.h
 *
 * Contains a secure, API-compatable implementation of many libc and BSD socket
 * functions related to file- and network-based I/O used only on iOS. See the
 * original functions' documentation for more information on general API usage.
 *
 * @note the functions located here are used on iOS only. For functions only
 *   used on multiple platforms, consult mapio.h.
 */

#ifndef mapio_ios_h
#define mapio_ios_h

#include "mapio.h"

#pragma GCC visibility push(default)

#ifdef __cplusplus
extern "C" {
#endif

void MAPIO_IOS_init(const char *tmp_dir_path);

int MAPIO_accept_NOCANCEL(int s, struct sockaddr *addr, socklen_t *addrlen);
int MAPIO_connect_NOCANCEL(int s, const struct sockaddr *name, socklen_t namelen);
ssize_t MAPIO_recv_NOCANCEL(int s, void *mem, size_t len, int flags);
ssize_t MAPIO_recvfrom_NOCANCEL(int s, void *mem, size_t len, int flags,
                                struct sockaddr *from, socklen_t *fromlen);
ssize_t MAPIO_recvmsg_NOCANCEL(int s, struct msghdr *msg, int flags);
ssize_t MAPIO_send_NOCANCEL(int s, const void *data, size_t size, int flags);
ssize_t MAPIO_sendmsg_NOCANCEL(int s, const struct msghdr *msg, int flags);
ssize_t MAPIO_sendto_NOCANCEL(int s, const void *data, size_t size, int flags,
                              const struct sockaddr *to, socklen_t tolen);
int MAPIO_close_NOCANCEL(int fd);
ssize_t MAPIO_readv_NOCANCEL(int fd, const struct iovec *iov, int iov_count);
ssize_t MAPIO_write_NOCANCEL(int fd, const void *buf, size_t count);
ssize_t MAPIO_writev_NOCANCEL(int fd, const struct iovec *iov, int iov_count);
int MAPIO_fcntl_NOCANCEL(int fd, int cmd, ...);
ssize_t MAPIO_read_NOCANCEL(int fd, void *buf, size_t count);
#ifndef CXX_INJECT
int MAPIO_connectx(int fd, const sa_endpoints_t *endpoints, sae_associd_t associd,
                   unsigned int flags, const struct iovec *iov, unsigned int iovcnt,
                   size_t *len, sae_connid_t *connid);
#endif
int MAPIO_disconnectx(int fd, sae_associd_t associd, sae_connid_t connid);
ssize_t MAPIO_recvmsg_x(int s, int arg1, int arg2, struct msghdr *msg, int flags);
ssize_t MAPIO_sendmsg_x(int s, int arg1, int arg2, const struct msghdr *msg, int flags);

int MAPIO_tcp_connection_is_viable();
int MAPIO_tcp_connection_is_ledbelly();
int MAPIO_tcp_connection_is_multipath();

int MAPIO_kevent(int kq, const struct kevent *changelist, int nchanges,
                 struct kevent *eventlist, int nevents,
                 const struct timespec *timeout);
int MAPIO_kevent64(int kq, const struct kevent64_s *changelist, int nchanges,
                   struct kevent64_s *eventlist, int nevents, unsigned int flags,
                   const struct timespec *timeout);
int MAPIO_kqueue(void);

dispatch_source_t MAPIO_dispatch_source_create(dispatch_source_type_t type,
                                               uintptr_t handle,
                                               uintptr_t mask,
                                               dispatch_queue_t queue);

// expanded variadics for Swift bindings. Swift can't call directly into a variadic C function.
int MAPIO_ioctl_void(int fd, unsigned long req);
int MAPIO_ioctl_int(int fd, unsigned long req, int value);
int MAPIO_ioctl_ptr(int fd, unsigned long req, void *value);

#ifdef __cplusplus
}
#endif

#pragma GCC visibility pop

#endif /* mapio_ios_h */
