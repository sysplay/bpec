SRC := blink_led.c
#SRC := blink_led.c leds_test.c
BIN := $(SRC:.c=.bin)

all: ${BIN}

show: first_disasm

leds_test.elf: leds.o

.dep: $(wildcard *.c)
	@${CROSS_COMPILE}gcc ${CFLAGS} -MM $^ > .dep

allclean: clean
	${RM} .dep a.out

include rules.mk
-include .dep
