/*	$OpenBSD: ultrix_sysent.c,v 1.12 2004/05/28 18:31:13 tedu Exp $	*/

/*
 * System call switch table.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from	OpenBSD: syscalls.master,v 1.10 2004/05/28 18:28:14 tedu Exp 
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/signal.h>
#include <sys/mount.h>
#include <sys/syscallargs.h>
#include <compat/ultrix/ultrix_syscallargs.h>

#define	s(type)	sizeof(type)

struct sysent ultrix_sysent[] = {
	{ 0, 0,
	    sys_nosys },			/* 0 = syscall */
	{ 1, s(struct sys_exit_args),
	    sys_exit },				/* 1 = exit */
	{ 0, 0,
	    sys_fork },				/* 2 = fork */
	{ 3, s(struct sys_read_args),
	    sys_read },				/* 3 = read */
	{ 3, s(struct sys_write_args),
	    sys_write },			/* 4 = write */
	{ 3, s(struct ultrix_sys_open_args),
	    ultrix_sys_open },			/* 5 = open */
	{ 1, s(struct sys_close_args),
	    sys_close },			/* 6 = close */
	{ 0, 0,
	    compat_43_sys_wait },		/* 7 = owait */
	{ 2, s(struct ultrix_sys_creat_args),
	    ultrix_sys_creat },			/* 8 = creat */
	{ 2, s(struct sys_link_args),
	    sys_link },				/* 9 = link */
	{ 1, s(struct sys_unlink_args),
	    sys_unlink },			/* 10 = unlink */
	{ 2, s(struct ultrix_sys_execv_args),
	    ultrix_sys_execv },			/* 11 = execv */
	{ 1, s(struct sys_chdir_args),
	    sys_chdir },			/* 12 = chdir */
	{ 0, 0,
	    sys_nosys },			/* 13 = obsolete time */
	{ 3, s(struct ultrix_sys_mknod_args),
	    ultrix_sys_mknod },			/* 14 = mknod */
	{ 2, s(struct sys_chmod_args),
	    sys_chmod },			/* 15 = chmod */
	{ 3, s(struct sys_lchown_args),
	    sys_lchown },			/* 16 = lchown */
	{ 1, s(struct sys_obreak_args),
	    sys_obreak },			/* 17 = break */
	{ 0, 0,
	    sys_nosys },			/* 18 = obsolete stat */
	{ 3, s(struct compat_43_sys_lseek_args),
	    compat_43_sys_lseek },		/* 19 = lseek */
	{ 0, 0,
	    sys_getpid },			/* 20 = getpid */
	{ 5, s(struct ultrix_sys_mount_args),
	    ultrix_sys_mount },			/* 21 = mount */
	{ 0, 0,
	    sys_nosys },			/* 22 = obsolete sysV_unmount */
	{ 1, s(struct sys_setuid_args),
	    sys_setuid },			/* 23 = setuid */
	{ 0, 0,
	    sys_getuid },			/* 24 = getuid */
	{ 0, 0,
	    sys_nosys },			/* 25 = obsolete v7 stime */
	{ 0, 0,
	    sys_nosys },			/* 26 = obsolete v7 ptrace */
	{ 0, 0,
	    sys_nosys },			/* 27 = obsolete v7 alarm */
	{ 0, 0,
	    sys_nosys },			/* 28 = obsolete v7 fstat */
	{ 0, 0,
	    sys_nosys },			/* 29 = obsolete v7 pause */
	{ 0, 0,
	    sys_nosys },			/* 30 = obsolete v7 utime */
	{ 0, 0,
	    sys_nosys },			/* 31 = obsolete v7 stty */
	{ 0, 0,
	    sys_nosys },			/* 32 = obsolete v7 gtty */
	{ 2, s(struct ultrix_sys_access_args),
	    ultrix_sys_access },		/* 33 = access */
	{ 0, 0,
	    sys_nosys },			/* 34 = obsolete v7 nice */
	{ 0, 0,
	    sys_nosys },			/* 35 = obsolete v7 ftime */
	{ 0, 0,
	    sys_sync },				/* 36 = sync */
	{ 2, s(struct sys_kill_args),
	    sys_kill },				/* 37 = kill */
	{ 2, s(struct ultrix_sys_stat_args),
	    ultrix_sys_stat },			/* 38 = ostat */
	{ 0, 0,
	    sys_nosys },			/* 39 = obsolete v7 setpgrp */
	{ 2, s(struct ultrix_sys_lstat_args),
	    ultrix_sys_lstat },			/* 40 = olstat */
	{ 1, s(struct sys_dup_args),
	    sys_dup },				/* 41 = dup */
	{ 0, 0,
	    sys_opipe },			/* 42 = opipe */
	{ 0, 0,
	    sys_nosys },			/* 43 = obsolete v7 times */
	{ 4, s(struct sys_profil_args),
	    sys_profil },			/* 44 = profil */
	{ 0, 0,
	    sys_nosys },			/* 45 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 46 = obsolete v7 setgid */
	{ 0, 0,
	    sys_getgid },			/* 47 = getgid */
	{ 0, 0,
	    sys_nosys },			/* 48 = unimplemented ssig */
	{ 0, 0,
	    sys_nosys },			/* 49 = unimplemented reserved for USG */
	{ 0, 0,
	    sys_nosys },			/* 50 = unimplemented reserved for USG */
#ifdef ACCOUNTING
	{ 1, s(struct sys_acct_args),
	    sys_acct },				/* 51 = acct */
#else
	{ 0, 0,
	    sys_nosys },			/* 51 = unimplemented acct */
#endif
	{ 0, 0,
	    sys_nosys },			/* 52 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 53 = unimplemented syslock */
	{ 3, s(struct ultrix_sys_ioctl_args),
	    ultrix_sys_ioctl },			/* 54 = ioctl */
	{ 1, s(struct sys_reboot_args),
	    sys_reboot },			/* 55 = reboot */
	{ 0, 0,
	    sys_nosys },			/* 56 = unimplemented v7 mpxchan */
	{ 2, s(struct sys_symlink_args),
	    sys_symlink },			/* 57 = symlink */
	{ 3, s(struct sys_readlink_args),
	    sys_readlink },			/* 58 = readlink */
	{ 3, s(struct ultrix_sys_execve_args),
	    ultrix_sys_execve },		/* 59 = execve */
	{ 1, s(struct sys_umask_args),
	    sys_umask },			/* 60 = umask */
	{ 1, s(struct sys_chroot_args),
	    sys_chroot },			/* 61 = chroot */
	{ 2, s(struct compat_43_sys_fstat_args),
	    compat_43_sys_fstat },		/* 62 = fstat */
	{ 0, 0,
	    sys_nosys },			/* 63 = unimplemented */
	{ 0, 0,
	    compat_43_sys_getpagesize },	/* 64 = getpagesize */
	{ 0, 0,
	    sys_nosys },			/* 65 = unimplemented mremap */
	{ 0, 0,
	    sys_vfork },			/* 66 = vfork */
	{ 0, 0,
	    sys_nosys },			/* 67 = obsolete vread */
	{ 0, 0,
	    sys_nosys },			/* 68 = obsolete vwrite */
	{ 1, s(struct sys_sbrk_args),
	    sys_sbrk },				/* 69 = sbrk */
	{ 1, s(struct sys_sstk_args),
	    sys_sstk },				/* 70 = sstk */
	{ 6, s(struct ultrix_sys_mmap_args),
	    ultrix_sys_mmap },			/* 71 = mmap */
	{ 1, s(struct sys_ovadvise_args),
	    sys_ovadvise },			/* 72 = vadvise */
	{ 2, s(struct sys_munmap_args),
	    sys_munmap },			/* 73 = munmap */
	{ 3, s(struct sys_mprotect_args),
	    sys_mprotect },			/* 74 = mprotect */
	{ 3, s(struct sys_madvise_args),
	    sys_madvise },			/* 75 = madvise */
	{ 0, 0,
	    ultrix_sys_vhangup },		/* 76 = vhangup */
	{ 0, 0,
	    sys_nosys },			/* 77 = unimplemented old vlimit */
	{ 3, s(struct sys_mincore_args),
	    sys_mincore },			/* 78 = mincore */
	{ 2, s(struct sys_getgroups_args),
	    sys_getgroups },			/* 79 = getgroups */
	{ 2, s(struct sys_setgroups_args),
	    sys_setgroups },			/* 80 = setgroups */
	{ 0, 0,
	    sys_getpgrp },			/* 81 = getpgrp */
	{ 2, s(struct ultrix_sys_setpgrp_args),
	    ultrix_sys_setpgrp },		/* 82 = setpgrp */
	{ 3, s(struct sys_setitimer_args),
	    sys_setitimer },			/* 83 = setitimer */
	{ 3, s(struct ultrix_sys_wait3_args),
	    ultrix_sys_wait3 },			/* 84 = wait3 */
	{ 1, s(struct compat_25_sys_swapon_args),
	    compat_25_sys_swapon },		/* 85 = swapon */
	{ 2, s(struct sys_getitimer_args),
	    sys_getitimer },			/* 86 = getitimer */
	{ 2, s(struct compat_43_sys_gethostname_args),
	    compat_43_sys_gethostname },	/* 87 = gethostname */
	{ 2, s(struct compat_43_sys_sethostname_args),
	    compat_43_sys_sethostname },	/* 88 = sethostname */
	{ 0, 0,
	    compat_43_sys_getdtablesize },	/* 89 = getdtablesize */
	{ 2, s(struct sys_dup2_args),
	    sys_dup2 },				/* 90 = dup2 */
	{ 0, 0,
	    sys_nosys },			/* 91 = unimplemented getdopt */
	{ 3, s(struct sys_fcntl_args),
	    sys_fcntl },			/* 92 = fcntl */
	{ 5, s(struct ultrix_sys_select_args),
	    ultrix_sys_select },		/* 93 = select */
	{ 0, 0,
	    sys_nosys },			/* 94 = unimplemented setdopt */
	{ 1, s(struct sys_fsync_args),
	    sys_fsync },			/* 95 = fsync */
	{ 3, s(struct sys_setpriority_args),
	    sys_setpriority },			/* 96 = setpriority */
	{ 3, s(struct sys_socket_args),
	    sys_socket },			/* 97 = socket */
	{ 3, s(struct sys_connect_args),
	    sys_connect },			/* 98 = connect */
	{ 3, s(struct compat_43_sys_accept_args),
	    compat_43_sys_accept },		/* 99 = accept */
	{ 2, s(struct sys_getpriority_args),
	    sys_getpriority },			/* 100 = getpriority */
	{ 4, s(struct compat_43_sys_send_args),
	    compat_43_sys_send },		/* 101 = send */
	{ 4, s(struct compat_43_sys_recv_args),
	    compat_43_sys_recv },		/* 102 = recv */
	{ 1, s(struct sys_sigreturn_args),
	    sys_sigreturn },			/* 103 = sigreturn */
	{ 3, s(struct sys_bind_args),
	    sys_bind },				/* 104 = bind */
	{ 5, s(struct ultrix_sys_setsockopt_args),
	    ultrix_sys_setsockopt },		/* 105 = setsockopt */
	{ 2, s(struct sys_listen_args),
	    sys_listen },			/* 106 = listen */
	{ 0, 0,
	    sys_nosys },			/* 107 = unimplemented vtimes */
	{ 3, s(struct compat_43_sys_sigvec_args),
	    compat_43_sys_sigvec },		/* 108 = sigvec */
	{ 1, s(struct compat_43_sys_sigblock_args),
	    compat_43_sys_sigblock },		/* 109 = sigblock */
	{ 1, s(struct compat_43_sys_sigsetmask_args),
	    compat_43_sys_sigsetmask },		/* 110 = sigsetmask */
	{ 1, s(struct sys_sigsuspend_args),
	    sys_sigsuspend },			/* 111 = sigsuspend */
	{ 2, s(struct compat_43_sys_sigstack_args),
	    compat_43_sys_sigstack },		/* 112 = sigstack */
	{ 3, s(struct compat_43_sys_recvmsg_args),
	    compat_43_sys_recvmsg },		/* 113 = recvmsg */
	{ 3, s(struct compat_43_sys_sendmsg_args),
	    compat_43_sys_sendmsg },		/* 114 = sendmsg */
	{ 0, 0,
	    sys_nosys },			/* 115 = obsolete vtrace */
	{ 2, s(struct sys_gettimeofday_args),
	    sys_gettimeofday },			/* 116 = gettimeofday */
	{ 2, s(struct sys_getrusage_args),
	    sys_getrusage },			/* 117 = getrusage */
	{ 5, s(struct sys_getsockopt_args),
	    sys_getsockopt },			/* 118 = getsockopt */
	{ 0, 0,
	    sys_nosys },			/* 119 = unimplemented resuba */
	{ 3, s(struct sys_readv_args),
	    sys_readv },			/* 120 = readv */
	{ 3, s(struct sys_writev_args),
	    sys_writev },			/* 121 = writev */
	{ 2, s(struct sys_settimeofday_args),
	    sys_settimeofday },			/* 122 = settimeofday */
	{ 3, s(struct sys_fchown_args),
	    sys_fchown },			/* 123 = fchown */
	{ 2, s(struct sys_fchmod_args),
	    sys_fchmod },			/* 124 = fchmod */
	{ 6, s(struct compat_43_sys_recvfrom_args),
	    compat_43_sys_recvfrom },		/* 125 = recvfrom */
	{ 2, s(struct sys_setreuid_args),
	    sys_setreuid },			/* 126 = setreuid */
	{ 2, s(struct sys_setregid_args),
	    sys_setregid },			/* 127 = setregid */
	{ 2, s(struct sys_rename_args),
	    sys_rename },			/* 128 = rename */
	{ 2, s(struct compat_43_sys_truncate_args),
	    compat_43_sys_truncate },		/* 129 = truncate */
	{ 2, s(struct compat_43_sys_ftruncate_args),
	    compat_43_sys_ftruncate },		/* 130 = ftruncate */
	{ 2, s(struct sys_flock_args),
	    sys_flock },			/* 131 = flock */
	{ 0, 0,
	    sys_nosys },			/* 132 = unimplemented */
	{ 6, s(struct sys_sendto_args),
	    sys_sendto },			/* 133 = sendto */
	{ 2, s(struct sys_shutdown_args),
	    sys_shutdown },			/* 134 = shutdown */
	{ 4, s(struct sys_socketpair_args),
	    sys_socketpair },			/* 135 = socketpair */
	{ 2, s(struct sys_mkdir_args),
	    sys_mkdir },			/* 136 = mkdir */
	{ 1, s(struct sys_rmdir_args),
	    sys_rmdir },			/* 137 = rmdir */
	{ 2, s(struct sys_utimes_args),
	    sys_utimes },			/* 138 = utimes */
	{ 1, s(struct ultrix_sys_sigcleanup_args),
	    ultrix_sys_sigcleanup },		/* 139 = sigcleanup */
	{ 2, s(struct sys_adjtime_args),
	    sys_adjtime },			/* 140 = adjtime */
	{ 3, s(struct compat_43_sys_getpeername_args),
	    compat_43_sys_getpeername },	/* 141 = getpeername */
	{ 0, 0,
	    compat_43_sys_gethostid },		/* 142 = gethostid */
	{ 0, 0,
	    sys_nosys },			/* 143 = unimplemented old sethostid */
	{ 2, s(struct compat_43_sys_getrlimit_args),
	    compat_43_sys_getrlimit },		/* 144 = getrlimit */
	{ 2, s(struct compat_43_sys_setrlimit_args),
	    compat_43_sys_setrlimit },		/* 145 = setrlimit */
	{ 2, s(struct compat_43_sys_killpg_args),
	    compat_43_sys_killpg },		/* 146 = killpg */
	{ 0, 0,
	    sys_nosys },			/* 147 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 148 = unimplemented setquota */
	{ 0, 0,
	    sys_nosys },			/* 149 = unimplemented quota / * needs to be nullop to boot on Ultrix root partition * / */
	{ 3, s(struct compat_43_sys_getsockname_args),
	    compat_43_sys_getsockname },	/* 150 = getsockname */
	{ 0, 0,
	    sys_nosys },			/* 151 = unimplemented sysmips / * 4 args * / */
	{ 0, 0,
	    sys_nosys },			/* 152 = unimplemented cacheflush / * 4 args * / */
	{ 0, 0,
	    sys_nosys },			/* 153 = unimplemented cachectl / * 3 args * / */
	{ 0, 0,
	    sys_nosys },			/* 154 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 155 = unimplemented atomic_op */
	{ 0, 0,
	    sys_nosys },			/* 156 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 157 = unimplemented */
#ifdef NFSSERVER
	{ 1, s(struct ultrix_sys_nfssvc_args),
	    ultrix_sys_nfssvc },		/* 158 = nfssvc */
#else
	{ 0, 0,
	    sys_nosys },			/* 158 = unimplemented */
#endif
	{ 4, s(struct compat_43_sys_getdirentries_args),
	    compat_43_sys_getdirentries },	/* 159 = getdirentries */
	{ 2, s(struct ultrix_sys_statfs_args),
	    ultrix_sys_statfs },		/* 160 = statfs */
	{ 2, s(struct ultrix_sys_fstatfs_args),
	    ultrix_sys_fstatfs },		/* 161 = fstatfs */
	{ 0, 0,
	    sys_nosys },			/* 162 = unimplemented umount */
#ifdef NFSCLIENT
	{ 0, 0,
	    async_daemon },			/* 163 = async_daemon */
	{ 2, s(struct sys_getfh_args),
	    sys_getfh },			/* 164 = getfh */
#else
	{ 0, 0,
	    sys_nosys },			/* 163 = unimplemented async_daemon */
	{ 0, 0,
	    sys_nosys },			/* 164 = unimplemented getfh */
#endif
	{ 2, s(struct compat_09_sys_getdomainname_args),
	    compat_09_sys_getdomainname },	/* 165 = getdomainname */
	{ 2, s(struct compat_09_sys_setdomainname_args),
	    compat_09_sys_setdomainname },	/* 166 = setdomainname */
	{ 0, 0,
	    sys_nosys },			/* 167 = unimplemented */
	{ 4, s(struct ultrix_sys_quotactl_args),
	    ultrix_sys_quotactl },		/* 168 = quotactl */
	{ 2, s(struct ultrix_sys_exportfs_args),
	    ultrix_sys_exportfs },		/* 169 = exportfs */
	{ 0, 0,
	    sys_nosys },			/* 170 = unimplemented { int ultrix_sys_mount ( char * special , char * dir , int rdonly , int type , caddr_t data ) ; } */
	{ 0, 0,
	    sys_nosys },			/* 171 = unimplemented 4 hdwconf */
	{ 0, 0,
	    sys_nosys },			/* 172 = unimplemented msgctl */
	{ 0, 0,
	    sys_nosys },			/* 173 = unimplemented msgget */
	{ 0, 0,
	    sys_nosys },			/* 174 = unimplemented msgrcv */
	{ 0, 0,
	    sys_nosys },			/* 175 = unimplemented msgsnd */
	{ 0, 0,
	    sys_nosys },			/* 176 = unimplemented semctl */
	{ 0, 0,
	    sys_nosys },			/* 177 = unimplemented semget */
	{ 0, 0,
	    sys_nosys },			/* 178 = unimplemented semop */
	{ 1, s(struct ultrix_sys_uname_args),
	    ultrix_sys_uname },			/* 179 = uname */
	{ 0, 0,
	    sys_nosys },			/* 180 = unimplemented shmsys */
	{ 0, 0,
	    sys_nosys },			/* 181 = unimplemented 0 plock */
	{ 0, 0,
	    sys_nosys },			/* 182 = unimplemented 0 lockf */
	{ 2, s(struct ultrix_sys_ustat_args),
	    ultrix_sys_ustat },			/* 183 = ustat */
	{ 5, s(struct ultrix_sys_getmnt_args),
	    ultrix_sys_getmnt },		/* 184 = getmnt */
	{ 0, 0,
	    sys_nosys },			/* 185 = unimplemented notdef */
	{ 0, 0,
	    sys_nosys },			/* 186 = unimplemented notdef */
	{ 1, s(struct ultrix_sys_sigpending_args),
	    ultrix_sys_sigpending },		/* 187 = sigpending */
	{ 0, 0,
	    sys_setsid },			/* 188 = setsid */
	{ 3, s(struct ultrix_sys_waitpid_args),
	    ultrix_sys_waitpid },		/* 189 = waitpid */
	{ 0, 0,
	    sys_nosys },			/* 190 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 191 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 192 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 193 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 194 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 195 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 196 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 197 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 198 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 199 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 200 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 201 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 202 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 203 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 204 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 205 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 206 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 207 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 208 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 209 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 210 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 211 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 212 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 213 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 214 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 215 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 216 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 217 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 218 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 219 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 220 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 221 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 222 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 223 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 224 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 225 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 226 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 227 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 228 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 229 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 230 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 231 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 232 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 233 = unimplemented 1 utc_gettime */
	{ 0, 0,
	    sys_nosys },			/* 234 = unimplemented 2 utc_adjtime */
	{ 0, 0,
	    sys_nosys },			/* 235 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 236 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 237 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 238 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 239 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 240 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 241 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 242 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 243 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 244 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 245 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 246 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 247 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 248 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 249 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 250 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 251 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 252 = unimplemented audctl / * Make no-op for installation on Ultrix rootpartition? * / */
	{ 0, 0,
	    sys_nosys },			/* 253 = unimplemented audgen / * Make no-op for installation on Ultrix rootpartition? * / */
	{ 0, 0,
	    sys_nosys },			/* 254 = unimplemented startcpu */
	{ 0, 0,
	    sys_nosys },			/* 255 = unimplemented stopcpu */
	{ 5, s(struct ultrix_sys_getsysinfo_args),
	    ultrix_sys_getsysinfo },		/* 256 = getsysinfo */
	{ 5, s(struct ultrix_sys_setsysinfo_args),
	    ultrix_sys_setsysinfo },		/* 257 = setsysinfo */
};

