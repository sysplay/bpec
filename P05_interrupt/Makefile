SRC := timer_test.c
BIN := $(SRC:.c=.bin)

all: ${BIN}

show: timer_test_disasm

timer_test.elf: timer.o leds.o debug.o serial.o

.dep: $(wildcard *.c)
	@${CROSS_COMPILE}gcc ${CFLAGS} -MM $^ > .dep

allclean: clean
	${RM} .dep a.out

include rules.mk
-include .dep
