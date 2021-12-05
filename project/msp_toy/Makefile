COMMON_OBJECTS	= main.o stateMachines.o led.o wdInterruptHandler.o p2_interrupt_handler.o switches.o buzzer.o greenControls.o
CPU		= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

CC		= msp430-elf-gcc
AS		= msp430-elf-as

all: msp_toy.elf

msp_toy.elf: ${COMMON_OBJECTS}  ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: msp_toy.elf
	msp430loader.sh msp_toy.elf

clean:
	rm -f *.o *.elf *.c~ *.h~ *~

main.o: led.h switches.h buzzer.h stateMachines.h
led.o: led.h stateMachines.h
stateMachines.o: stateMachines.h led.h switches.h buzzer.h greenControlc.h 
buzzer.o: buzzer.h
switches.o: switches.h led.h buzzer.h stateMachines.h
wdInterruptHandler.o: led.h stateMachines.h
p2_interrupt_handler.o: switches.h
greenControlc.o: led.h
green-on-c.o: led.h greenControl_c.c
