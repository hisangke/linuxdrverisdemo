obj-m += hello.o
KDIR:=/home/user/linux-5.10.217

PWD?=$(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
	rm -rf *.mod.c *.mod.o *.mod *.o *.symvers *.order .hello* .modules* .Module*
clean:
	rm -rf *.mod.c *.mod.o *.ko *.mod *.o *.symvers *.order .hello* .modules* .Module*
