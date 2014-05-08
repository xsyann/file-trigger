file-trigger
============

Pseudo filesystem, compatible with the Linux Kernel VFS, using a loadable module.

###Install

    git clone https://github.com/xsyann/file-trigger.git
    make
    make load
    mount | grep ftriggerfs
    cat /proc/filesystems
    cat /proc/mounts
    stat -f /tmp/test
    stat /tmp/test
    make unload
