MODULE_NAME=hello3
MODULE_OBJ=$(MODULE_NAME).o
MODULE_KO=$(MODULE_NAME).ko

KERNEL_BUILD=/lib/modules/$(shell uname -r)/build/
MODULE_BUILD=$(shell pwd)

obj-m += $(MODULE_OBJ)

all:
	$(MAKE) -C $(KERNEL_BUILD) M=$(MODULE_BUILD) modules

clean:
	$(MAKE) -C $(KERNEL_BUILD) M=$(MODULE_BUILD) clean

load: all
	insmod $(MODULE_KO) name='"Giho Lee"' street='"123 My Way"' city="ShenZhen" zip_code="98765" 

unload:
	-rmmod $(MODULE_NAME)

reload: unload load

