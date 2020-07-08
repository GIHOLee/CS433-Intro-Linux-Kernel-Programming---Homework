MODULE_NAME=hello1
MODULE_OBJ=$(MODULE_NAME).o
MODULE_KO=$(MODULE_NAME).ko

KERNEL_BUILD=/lib/modules/$(shell uname -r)/build/
MODULE_BUILD=$(shell pwd)

obj-m += $(MODULE_OBJ)
#$(MODULE_NAME)-objs += hello1.o

all:
	make -C $(KERNEL_BUILD) M=$(MODULE_BUILD) modules

clean:
	make -C $(KERNEL_BUILD) M=$(MODULE_BUILD) clean
	-rm -fr modules.order Module.symvers *.o *.mod.c *.ko

load: unload
	insmod $(MODULE_KO)

unload:
	-rmmod $(MODULE_NAME)

reload: unload all load






