/*
** ftriggerfs.h
**
** Made by xsyann
** Contact <contact@xsyann.com>
**
** Started on  Fri Apr 18 14:21:53 2014 xsyann
** Last update Fri Apr 18 16:41:41 2014 xsyann
*/

#ifndef         __FTRIGGERFS_H__
#define         __FTRIGGERFS_H__

#define SD_AUTHOR "Nicolas de Thore, Yann KOETH"
#define SD_DESC "Pseudo filesystem compatible with Linux Kernel VFS"
#define SD_VERSION "0.1"

#define SD_INFO_LOAD "Loaded"
#define SD_INFO_UNLOAD "Unloaded"

#define PR_WARNING(ERR, ...) \
        (printk(KERN_WARNING "%s: error: " ERR "\n", KBUILD_MODNAME, ##__VA_ARGS__))

#define PR_INFO(INFO, ...) \
        (printk(KERN_INFO "%s: " INFO "\n", KBUILD_MODNAME, ##__VA_ARGS__))

#define FTFS_MAGIC 0x1337

#endif          /* __FTRIGGERFS_H__ */
