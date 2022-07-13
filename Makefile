##############################original makefile for full scenario#####################
#CC = gcc
#CFLAGS = -Wall -O2 -m32

#OBJS = main.o daq.o tx.o motor.o

#main: $(OBJS)
#	$(CC) $(CFLAGS) -o main $(OBJS) -lpthread -lrt -lm
#######################################################################################

#all: DAQ

CC = gcc

# where the include files are
INCLUDE = -I./Include -I./CsAppSupport -I./C_Common -I./Include/Public -I./Public


# options for development
CFLAGS = -Wall -O2 #-m32 -m elf_i386 -s


LDFLAGS = -lCsSsm -lCsAppSupport -lpthread -lrt -lm 


DAQ: daq.o CsSdkMisc.o main.o motor.o tx.o 
	$(CC) daq.o CsSdkMisc.o main.o motor.o tx.o $(LDFLAGS) -o DAQ

main.o : main.c 
	$(CC) $(INCLUDE) $(CFLAGS) -c main.c

motor.o : motor.c 
	$(CC) $(INCLUDE) $(CFLAGS) -c motor.c

tx.o : tx.c 
	$(CC) $(INCLUDE) $(CFLAGS) -c tx.c

daq.o: daq.c
	$(CC) $(INCLUDE) $(CFLAGS) -c daq.c	

CsSdkMisc.o: ./C_Common/CsSdkMisc.c
	$(CC) $(INCLUDE) $(CFLAGS) -c ./C_Common/CsSdkMisc.c

.PHONY : clean install uninstall

clean:
	rm -rf *.o DAQ

install: all
#	cp GageAcquire ../../Bin/

uninstall: clean
#	rm -rf ../../Bin/GageAcquire
