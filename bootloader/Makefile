# Source files
OUTPUT=Bootloader
C_SRCS += \
	./Src/main.c \
	./Src/led.c \
	./Src/syscalls.c \
	./Src/sysmem.c

S_SRCS += \
	../CMSIS/Startup/startup_stm32f407vgtx.s

OBJS_s+= \
	./Build/startup_stm32f401vgtx.o 

# Object files
OBJS = $(C_SRCS:./Src/%.c=./Build/%.o)

# Dependency files
C_DEPS = $(OBJS:.o=.d)
#inlcue path 
Inc = ./Inc/
# Compiler flags
CFLAGS = -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407VG -DSTM32F4 -DSTM32F407xx \
		 -I./Inc -I../CMSIS/Include -I../CMSIS/STM32F4_Headers -O0 -ffunction-sections -fdata-sections \
		 -Wall -fstack-usage -MMD -MP --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb
LD_flags =  -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
 
# Compiler command
CC = arm-none-eabi-gcc

# Rule to include all object files for the 'all' target
all: $(OUTPUT).elf

bin: $(OUTPUT).elf
	arm-none-eabi-objcopy -O binary $(OUTPUT).elf $(OUTPUT).bin 


# target 
$(OUTPUT).elf : $(OBJS) $(OBJS_s)
	$(CC) $^ -o $@ -mcpu=cortex-m4 -T"./Boot_STM32F407VGTX_FLASH.ld" \
	--specs=nosys.specs -Wl,--gc-sections -static --specs=nano.specs \
	-mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '
Flash: bin
	st-flash --reset write $(OUTPUT).bin 0x8000000


# Rule to build object files from source files
$(OBJS): ./Build/%.o: ./Src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build object files from assembly files
$(OBJS_s): $(S_SRCS)
	$(CC) -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

# Phony target to prevent conflicts with files named 'clean'
.PHONY: clean

clean:
	rm -f $(OBJS) $(C_DEPS) $(OBJS_s) $(OUTPUT).elf
