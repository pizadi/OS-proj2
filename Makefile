CONFIG_MODULE_SIG=n
BINARY			:= bank
KERNEL			:= /lib/modules/$(shell uname -r)/build
ARCH				:= x86
C_FLAGS			:= -Wall
KMOD_DIR		:= $(shell pwd)
TARGET_PATH	:= /lib/modules/$(shell uname -r)/kernel/drivers

OBJECTS			:= bank.o mkshlock.o stringop.o

ccflags-y		+= $(C_FLAGS)

obj-m 			+= $(BINARY).o

$(BINARY)-y	:= $(OBJECTS)

$(BINARY).ko:
	make -C $(KERNEL) M=$(KMOD_DIR) modules
	make -C $(KERNEL) M=$(KMOD_DIR) modules_install

install:
	cp $(BINARY).ko $(TARGET_PATH)/$(BINARY).ko
	depmod -a

uninstall:
	rm $(TARGET_PATH)/$(BINARY).ko
	depmod -a

clean:
	make -C $(KERNEL) M=$(KMOD_DIR) clean
