/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
#ifndef _VFS_H
#define _VFS_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include <stddef.h>
#include <stdint.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
/* ============================ [ MACROS    ] ====================================================== */
#define VFS_ISDIR(st_mode) S_ISDIR(st_mode)
#define VFS_ISREG(st_mode) S_ISREG(st_mode)
/* ============================ [ TYPES     ] ====================================================== */

struct vfs_filesystem_ops fops;

typedef struct
{
	const struct vfs_filesystem_ops* fops;
	void* priv;
} VFS_DIR;

typedef struct
{
	const struct vfs_filesystem_ops* fops;
	void* priv;
} VFS_FILE;

struct vfs_stat {
    uint32_t st_mode;     /* File mode */
    size_t   st_size;     /* File size (regular files only) */
    time_t   st_atime;    /* Last access time */
    time_t   st_mtime;    /* Last data modification time */
    time_t   st_ctime;    /* Last file status change time */
};

struct vfs_dirent
{
	unsigned short	d_namlen;	/* Length of name in d_name. */
	char		d_name[260]; /* [FILENAME_MAX] */ /* File name. */
};

/* File system operations */
struct vfs_filesystem_ops
{
    const char *name;

    /* operations for file */
    VFS_FILE* (*fopen) (const char *filename, const char *opentype);
    int (*fclose) (VFS_FILE* stream);
    int (*fread) (void *data, size_t size, size_t count, VFS_FILE *stream);
    int (*fwrite) (const void *data, size_t size, size_t count, VFS_FILE *stream);
    int (*fflush) (VFS_FILE *stream);
    int (*fseek) (VFS_FILE *stream, long int offset, int whence);

    int (*unlink) (const char *filename);
    int (*stat) (const char *filename, struct vfs_stat *buf);

    VFS_DIR * (*opendir) (const char *dirname);
    struct vfs_dirent * (*readdir) (VFS_DIR *dirstream);
    int (*closedir) (VFS_DIR *dirstream);

    int (*chdir) (const char *filename);
    char * (*getcwd)  (char *buffer, size_t size);
    int (*mkdir) (const char *filename, uint32_t mode);
    int  (*rmdir) (const char *filename);
    int (*rename) (const char *oldname, const char *newname);
};
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
VFS_FILE* vfs_fopen (const char *filename, const char *opentype);
int vfs_fclose (VFS_FILE* stream);
int vfs_fread (void *data, size_t size, size_t count, VFS_FILE *stream);
int vfs_fwrite (const void *data, size_t size, size_t count, VFS_FILE *stream);
int vfs_fflush (VFS_FILE *stream);
int vfs_fseek (VFS_FILE *stream, long int offset, int whence);

int vfs_unlink (const char *filename);
int vfs_stat (const char *filename, struct vfs_stat *buf);

VFS_DIR * vfs_opendir (const char *dirname);
struct vfs_dirent * vfs_readdir (VFS_DIR *dirstream);
int vfs_closedir (VFS_DIR *dirstream);

int vfs_chdir (const char *filename);
char * vfs_getcwd  (char *buffer, size_t size);
int vfs_mkdir (const char *filename, uint32_t mode);
int  vfs_rmdir (const char *filename);
int vfs_rename (const char *oldname, const char *newname);

#endif /* _VFS_H */
