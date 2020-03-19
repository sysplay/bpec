SRC := fw_app.c
BIN := $(SRC:.c=.bin)

all: ${BIN}

show: fw_app_disasm

fw_app.elf: leds.o timer.o eeprom.o i2c.o debug.o serial.o

.dep: $(wildcard *.c)
	@${CROSS_COMPILE}gcc ${CFLAGS} -MM $^ > .dep

allclean: clean
	${RM} .dep a.out

include rules.mk
-include .dep
