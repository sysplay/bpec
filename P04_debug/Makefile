SRC := serial_test.c
#SRC := serial_test.c switch_test.c timer_test.c
BIN := $(SRC:.c=.bin)

all: ${BIN}

show: serial_test_disasm

serial_test.elf: serial.o

switch_test.elf: switch.o leds.o debug.o serial.o

timer_test.elf: timer.o leds.o debug.o serial.o

.dep: $(wildcard *.c)
	@${CROSS_COMPILE}gcc ${CFLAGS} -MM $^ > .dep

allclean: clean
	${RM} .dep a.out

include rules.mk
-include .dep
