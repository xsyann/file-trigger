/*
** ftriggerfs.c
**
** Made by xsyann
** Contact <contact@xsyann.com>
**
** Started on  Fri Apr 18 14:23:44 2014 xsyann
** Last update Mon Apr 21 22:10:51 2014 xsyann
*/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/pagemap.h>
#include <linux/sched.h>
#include <linux/fs.h>

#include "ftriggerfs.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(FTFS_AUTHOR);
MODULE_DESCRIPTION(FTFS_DESC);
MODULE_VERSION(FTFS_VERSION);

/* ************************************************************ */

static struct file_operations ftfs_file_ops = {
};

struct inode_operations ftfs_file_inode_ops = {
};

/* ************************************************************ */

static void ftfs_put_super(struct super_block *sb)
{
        return;
}

static const struct super_operations ftfs_s_ops =
{
        .statfs = simple_statfs,
        .put_super = ftfs_put_super,
};

static struct inode *ftfs_make_inode(struct super_block *sb, int mode)
{
        struct inode *inode = new_inode(sb);

        if (inode) {
                inode->i_mode = mode;
                inode->i_uid = current_fsuid();
                inode->i_gid = current_fsgid();
                inode->i_blocks = 0;
                /* Last access / modify / change time */
                inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;

                switch (mode & S_IFMT) {
                case S_IFREG: /* Regular file */
                        inode->i_op = &ftfs_file_inode_ops;
                        inode->i_fop = &ftfs_file_ops;
                        break;
                case S_IFDIR: /* Directory */
                        inode->i_op = &simple_dir_inode_operations;
                        inode->i_fop = &simple_dir_operations;
                        break;
                }

        }
        return inode;
}

static void ftfs_create_files(struct super_block *sb, struct dentry *root)
{
        PR_INFO("Create files");
}

int ftfs_fill_super(struct super_block *sb, void *data, int silent)
{
        struct inode *root;

        sb->s_maxbytes = MAX_LFS_FILESIZE;
        sb->s_blocksize_bits = PAGE_CACHE_SHIFT;
        sb->s_blocksize = PAGE_CACHE_SIZE;
        sb->s_op = &ftfs_s_ops;
        sb->s_magic = FTFS_MAGIC;

        /* Create root directory */
        root = ftfs_make_inode(sb, S_IFDIR | 0755);
        if (root == NULL)
                return -ENOMEM;
        sb->s_root = d_make_root(root);
        if (sb->s_root == NULL)
                return -ENOMEM;
        ftfs_create_files(sb, sb->s_root);
        return 0;
}

struct dentry *ftfs_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
{
        /* nodev, bdev, single */
        return mount_nodev(fs_type, flags, data, ftfs_fill_super);
}

void ftfs_kill_sb(struct super_block *sb)
{
        /* kill_anon_super, kill_block_super */
        kill_litter_super(sb);
}

static struct file_system_type ftfs_type = {
        .name = FTFS_MODNAME,
        .mount = ftfs_mount,
        .kill_sb = ftfs_kill_sb,
        .owner = THIS_MODULE,
        .next = NULL,
        /* .fs_flags = */
};

/* ************************************************************ */

static int __init ftfs_init_module(void)
{
        PR_INFO(FTFS_INFO_LOAD);
        return register_filesystem(&ftfs_type);
}

static void __exit ftfs_exit_module(void)
{
        PR_INFO(FTFS_INFO_UNLOAD);
        unregister_filesystem(&ftfs_type);
}

module_init(ftfs_init_module);
module_exit(ftfs_exit_module);
