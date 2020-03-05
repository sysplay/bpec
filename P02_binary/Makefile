SRC := first.c
BIN := $(SRC:.c=.bin)

all: ${BIN}

show: first_disasm

.dep: $(wildcard *.c)
	@${CROSS_COMPILE}gcc ${CFLAGS} -MM $^ > .dep

allclean: clean
	${RM} .dep a.out

include rules.mk
-include .dep
