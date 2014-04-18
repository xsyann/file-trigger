##
## Makefile
##
## Made by xsyann
## Contact <contact@xsyann.com>
##
## Started on  Fri Apr 18 14:19:58 2014 xsyann
## Last update Fri Apr 18 22:41:29 2014 xsyann
##

TARGET	= ftriggerfs

obj-m	+= $(TARGET).o

$(TARGET)-objs := src/ftriggerfs.o

KDIR	= /lib/modules/$(shell uname -r)/build

all	:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean	:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

load	:
	@mkdir -p /tmp/test
	@sudo umount /tmp/test 2> /dev/null || true
	@sudo rmmod ./$(TARGET).ko 2> /dev/null || true
	@sudo insmod ./$(TARGET).ko
	@sudo mount -t $(TARGET) none /tmp/test
	@echo "Load $(TARGET).ko"

unload	:
	@sudo umount /tmp/test || true
	@sudo rmmod ./$(TARGET).ko
	@echo "Unload $(TARGET).ko"
