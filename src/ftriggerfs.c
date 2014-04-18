/*
** ftriggerfs.c
**
** Made by xsyann
** Contact <contact@xsyann.com>
**
** Started on  Fri Apr 18 14:23:44 2014 xsyann
** Last update Fri Apr 18 22:44:33 2014 xsyann
*/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/pagemap.h>
#include <linux/fs.h>

#include "ftriggerfs.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(SD_AUTHOR);
MODULE_DESCRIPTION(SD_DESC);
MODULE_VERSION(SD_VERSION);

/* ************************************************************ */

static void ftfs_put_super(struct super_block *sb)
{
        return;
}

static const struct super_operations ftfs_s_ops =
{
        .put_super = ftfs_put_super, /* unmount */
};

static struct inode *ftfs_make_inode(struct super_block *sb, int mode)
{
        struct inode *inode = new_inode(sb);

        if (inode) {
                inode->i_mode = mode;
                inode->i_uid = 0;
                inode->i_gid = 0;
                /* Last access / modify / change time */
/*                inode->i_atime = CURRENT_TIME;
                  inode->i_mtime = CURRENT_TIME;
                  inode->i_ctime = CURRENT_TIME;
                  inode->i_uid =
                    ...
*/
        }
        return inode;
}

static void ftfs_create_files(struct super_block *sb, struct dentry *root)
{
        PR_INFO("Create files");
        /* Create files */
}

int ftfs_fill_super(struct super_block *sb, void *data, int silent)
{
        struct inode *root;

        sb->s_blocksize_bits = PAGE_CACHE_SHIFT;
        sb->s_blocksize = PAGE_CACHE_SIZE;
        sb->s_op = &ftfs_s_ops;
        sb->s_magic = FTFS_MAGIC;


        /* Create root directory */
        root = ftfs_make_inode(sb, S_IFDIR | 0755);
        if (root == NULL)
                return -ENOMEM;
        root->i_op = &simple_dir_inode_operations;
        root->i_fop = &simple_dir_operations;
        sb->s_root = d_make_root(root);
        if (sb->s_root == NULL)
                return -EINVAL;
                ftfs_create_files(sb, sb->s_root);
        return 0;
}

struct dentry *ftfs_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
{
        /* nodev, bdev */
        return mount_single(fs_type, flags, data, ftfs_fill_super);
}

void ftfs_kill_sb(struct super_block *sb)
{
        /* kill_anon_super, kill_block_super */
        kill_litter_super(sb);
}

static struct file_system_type ftfs_type = {
        .name = KBUILD_MODNAME,
        /*.fs_flags = */
        .mount = ftfs_mount,
        .kill_sb = ftfs_kill_sb,
        .owner = THIS_MODULE,
        .next = NULL
};

/* ************************************************************ */

static int __init ftfs_init_module(void)
{
        PR_INFO(SD_INFO_LOAD);
        return register_filesystem(&ftfs_type);
}

static void __exit ftfs_exit_module(void)
{
        unregister_filesystem(&ftfs_type);
        PR_INFO(SD_INFO_UNLOAD);
}

module_init(ftfs_init_module);
module_exit(ftfs_exit_module);
