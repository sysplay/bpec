CROSS_COMPILE := arm-linux-gnueabihf-

CC := ${CROSS_COMPILE}gcc
AS := ${CROSS_COMPILE}as
LD := ${CROSS_COMPILE}ld
OBJCOPY := ${CROSS_COMPILE}objcopy
OBJDUMP := ${CROSS_COMPILE}objdump

#OPTIMIZATION_FLAGS = -O2
CFLAGS := -mcpu=cortex-a8
CFLAGS += ${OPTIMIZATION_FLAGS}
ASFLAGS := -mcpu=cortex-a8
LDFLAGS = -T linker.lds
LDFLAGS += -Map=$*.map

%.bin: %.elf
	${OBJCOPY} --gap-fill=0xFF -O binary $< $@

%.elf: %.o common.o startup.o interrupt.o
	${LD} ${LDFLAGS} $^ -o $@

#%.o: %.c
#	${CC} ${CFLAGS} -c $< -o $@
#
#%.o: %.s
#	${AS} ${ASFLAGS} -c $< -o $@
#

%_disasm: %.elf
	${OBJDUMP} -d $<

clean:
	${RM} *.bin *.map *.elf *.o
