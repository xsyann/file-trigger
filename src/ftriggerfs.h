/*
** ftriggerfs.h
**
** Made by xsyann
** Contact <contact@xsyann.com>
**
** Started on  Fri Apr 18 14:21:53 2014 xsyann
** Last update Mon Apr 21 21:34:24 2014 xsyann
*/

#ifndef         __FTRIGGERFS_H__
#define         __FTRIGGERFS_H__

#define FTFS_AUTHOR "Nicolas de Thore, Yann KOETH"
#define FTFS_DESC "Pseudo filesystem compatible with Linux Kernel VFS"
#define FTFS_VERSION "0.1"

#define FTFS_MODNAME KBUILD_MODNAME
#define FTFS_INFO_LOAD "Loaded"
#define FTFS_INFO_UNLOAD "Unloaded"

#define PR_WARNING(ERR, ...) \
        (printk(KERN_WARNING "%s: error: " ERR "\n", FTFS_MODNAME, ##__VA_ARGS__))

#define PR_INFO(INFO, ...) \
        (printk(KERN_INFO "%s: " INFO "\n", FTFS_MODNAME, ##__VA_ARGS__))

#define FTFS_MAGIC 0x66747269

#endif          /* __FTRIGGERFS_H__ */
