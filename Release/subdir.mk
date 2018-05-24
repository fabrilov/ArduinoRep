################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../simulebox.ino 

CPP_SRCS += \
../Dum.cpp \
../NewBridge.cpp \
../PWMCOM_SimulEbox.cpp \
../Parametri.cpp \
../PseudoTimer.cpp \
../sloeber.ino.cpp 

LINK_OBJ += \
./Dum.cpp.o \
./NewBridge.cpp.o \
./PWMCOM_SimulEbox.cpp.o \
./Parametri.cpp.o \
./PseudoTimer.cpp.o \
./sloeber.ino.cpp.o 

INO_DEPS += \
./simulebox.ino.d 

CPP_DEPS += \
./Dum.cpp.d \
./NewBridge.cpp.d \
./PWMCOM_SimulEbox.cpp.d \
./Parametri.cpp.d \
./PseudoTimer.cpp.d \
./sloeber.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
Dum.cpp.o: ../Dum.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

NewBridge.cpp.o: ../NewBridge.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

PWMCOM_SimulEbox.cpp.o: ../PWMCOM_SimulEbox.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Parametri.cpp.o: ../Parametri.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

PseudoTimer.cpp.o: ../PseudoTimer.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

simulebox.o: ../simulebox.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

sloeber.ino.cpp.o: ../sloeber.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


