SRC := eeprom_test.c
BIN := $(SRC:.c=.bin)

all: ${BIN}

show: eeprom_test_disasm

eeprom_test.elf: eeprom.o i2c.o debug.o serial.o

.dep: $(wildcard *.c)
	@${CROSS_COMPILE}gcc ${CFLAGS} -MM $^ > .dep

allclean: clean
	${RM} .dep a.out

include rules.mk
-include .dep
