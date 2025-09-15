# Source files
OUTPUT=App
C_SRCS += \
	./Src/main.c \
	./Src/led.c \
	./Src/syscalls.c \
	./Src/sysmem.c 

S_SRCS += \
	../CMSIS/Startup/startup_stm32f407vgtx.s 

B_SRC += \
	./Src/bootloader.S

OBJS_s += \
	./Build/startup_stm32f401vgtx.o

OBJ_B += \
	./Build/bootloader.o 


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
all: bin

bin: $(OUTPUT).elf
	arm-none-eabi-objcopy -O binary $(OUTPUT).elf $(OUTPUT).bin 


# target 
$(OUTPUT).elf : $(OBJS) $(OBJS_s) $(OBJ_B)
	$(CC) $^ -o $@ -mcpu=cortex-m4 -T"./APP_STM32F407VGTX_FLASH.ld" -Xlinker -Map="$(OUTPUT).map" \
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
$(OBJ_B): $(B_SRC)
	$(CC) -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

$(OBJS_s): $(S_SRCS)
	$(CC) -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
# Phony target to prevent conflicts with files named 'clean'
.PHONY: clean

clean:
	rm -f $(OBJS) $(OBJ_B) $(C_DEPS) $(OBJS_s) $(OUTPUT).elf $(OUTPUT).bin $(OUTPUT).map
