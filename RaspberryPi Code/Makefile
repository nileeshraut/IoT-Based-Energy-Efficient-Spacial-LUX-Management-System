CUSTOM_CFLAGS=-Wall -ggdb3 -O3

SYS_CFLAGS=-std=gnu99 `pkg-config --cflags libpubnub`
LIBS=`pkg-config --libs libpubnub` -lwiringPi

OBJS=project.o

all:project 

project:project.o
	$(call cmd,link)

clean:
	rm -f *.o led_control

install:

-include ./../Makefile.lib
