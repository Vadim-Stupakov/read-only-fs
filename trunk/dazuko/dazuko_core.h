/* DazukoXP. Allow cross platform file access control for 3rd-party applications.
   Written by John Ogness <dazukocode@ogness.net>

   Copyright (c) 2002, 2003, 2004, 2005, 2006 H+BEDV Datentechnik GmbH
   Copyright (c) 2006 Avira GmbH
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

   3. Neither the name of Dazuko nor the names of its contributors may be used
   to endorse or promote products derived from this software without specific
   prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef DAZUKO_XP_H
#define DAZUKO_XP_H

#include "dazuko_transport.h"
#include "dazuko_events.h"

/* xp_id compare results */
#define DAZUKO_DIFFERENT	0
#define DAZUKO_SUSPICIOUS	1
#define DAZUKO_CHILD		2
#define DAZUKO_SAME		3

/* file types */
#define DAZUKO_NONE		0
#define DAZUKO_REGULAR		1
#define DAZUKO_DIRECTORY	2
#define DAZUKO_LINK		3


/*********************************************************
 * structures that MUST be implemented by platform-layer *
 *********************************************************/

/*
struct xp_mutex;
struct xp_atomic;
struct xp_file_struct;
struct xp_queue;
struct xp_rwlock;
struct xp_daemon_id;
*/


/******************************************
 * structures available to platform-layer *
 ******************************************/

struct event_properties
{
	int	flags;
	char	set_flags;
	int	mode;
	char	set_mode;
	int	uid;
	char	set_uid;
	int	pid;
	char	set_pid;
};

struct file_properties
{
	unsigned long	size;
	char		set_size;
	int		uid;
	char		set_uid;
	int		gid;
	char		set_gid;
	int		mode;
	char		set_mode;
	int		device_type;
	char		set_device_type;
	int		type;
	char		set_type;
};

struct dazuko_file_listnode
{
	char				*filename;
	int				filename_length;
	struct dazuko_file_listnode	*next;
};

struct dazuko_file_struct
{
	/* A structure designed for simple and
	 * intelligent memory management when
	 * doing filename lookups in the kernel. */

	char				*filename;		/* filename to report (pointer in alias list) */
	int				filename_length;	/* length of filename reported */
	struct dazuko_file_listnode	*aliases;		/* list of file names (alias names) */
	struct file_properties		file_p;			/* properties of file */
	struct xp_file_struct		*extra_data;		/* extra platform-dependant data */
};


/********************************************************
 * functions that MUST be implemented by platform-layer *
 ********************************************************/

/* mutex */
void xp_init_mutex(struct xp_mutex *mutex);
void xp_down(struct xp_mutex *mutex);
void xp_up(struct xp_mutex *mutex);
void xp_destroy_mutex(struct xp_mutex *mutex);

/* read-write lock */
void xp_init_rwlock(struct xp_rwlock *rwlock);
void xp_write_lock(struct xp_rwlock *rwlock);
void xp_write_unlock(struct xp_rwlock *rwlock);
void xp_read_lock(struct xp_rwlock *rlock);
void xp_read_unlock(struct xp_rwlock *rlock);
void xp_destroy_rwlock(struct xp_rwlock *rwlock);

/* wait-notify queue */
int xp_init_queue(struct xp_queue *queue);
int xp_wait_until_condition(struct xp_queue *queue, int (*cfunction)(void *), void *cparam, int allow_interrupt);
int xp_notify(struct xp_queue *queue);
int xp_destroy_queue(struct xp_queue *queue);

/* memory */
void* xp_malloc(size_t size);
int xp_free(void *ptr);
int xp_copyin(const void *user_src, void *kernel_dest, size_t size);
int xp_copyout(const void *kernel_src, void *user_dest, size_t size);
int xp_verify_user_writable(const void *user_ptr, size_t size);
int xp_verify_user_readable(const void *user_ptr, size_t size);

/* path attribute */
int xp_is_absolute_path(const char *path);

/* atomic */
int xp_atomic_set(struct xp_atomic *atomic, int value);
int xp_atomic_inc(struct xp_atomic *atomic);
int xp_atomic_dec(struct xp_atomic *atomic);
int xp_atomic_read(struct xp_atomic *atomic);

/* system hook */
int xp_sys_hook(void);
int xp_sys_unhook(void);

/* file structure */
int xp_fill_file_struct(struct dazuko_file_struct *dfs);

/* daemon id */
int xp_id_compare(struct xp_daemon_id *id1, struct xp_daemon_id *id2, int check_related);
int xp_id_free(struct xp_daemon_id *id);
struct xp_daemon_id* xp_id_copy(struct xp_daemon_id *id);

/* event */
int xp_set_event_properties(struct event_properties *event_p, struct xp_daemon_id *xp_id);

/* cache settings */
int xp_init_cache(unsigned long ttl);

/* include/exclude paths */
int xp_set_path(const char *path, int type);

/* output */
int xp_print(const char *fmt, ...);

/* debug */
#ifdef DEBUG
#define DPRINT(fmt) xp_print fmt
#else
#define DPRINT(fmt)
#endif


/*****************************************
 * functions available to platform-layer *
 *****************************************/

struct slot_list;
struct slot;

int dazuko_vsnprintf(char *str, size_t size, const char *format, va_list ap);
int dazuko_snprintf(char *str, size_t size, const char *format, ...);
int dazuko_is_our_daemon(struct xp_daemon_id *xp_id, struct slot_list **slotlist, struct slot **slot);
int dazuko_get_value(const char *key, const char *string, char **value);
int dazuko_unregister_daemon(struct xp_daemon_id *xp_id);
int dazuko_handle_user_request(const char *request_buffer, struct xp_daemon_id *xp_id);
int dazuko_handle_user_request_compat1(void *ptr, int cmd, struct xp_daemon_id *xp_id);
int dazuko_strlen(const char *string);
char* dazuko_strdup(const char *string, int *newlength);
unsigned long dazuko_strtoul(const char *string);
void dazuko_bzero(void *p, int len);
int dazuko_active(void);
int dazuko_check_access(unsigned long event, int daemon_is_allowed, struct xp_daemon_id *xp_id, struct slot_list **cached_lookup);
int dazuko_process_access(unsigned long event, struct dazuko_file_struct *kfs, struct event_properties *event_p, struct slot_list *cached_lookup);
int dazuko_init(void);
int dazuko_exit(void);

#endif
