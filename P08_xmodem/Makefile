SRCS := blink_led.c decode_xmodem.c
BINS := $(SRCS:.c=.bin)

all: ${BINS}

show: decode_xmodem_test_disasm

decode_xmodem.elf: serial.o debug.o

.dep: $(wildcard *.c)
	@${CROSS_COMPILE}gcc ${CFLAGS} -MM $^ > .dep

allclean: clean
	${RM} .dep a.out

include rules.mk
-include .dep
