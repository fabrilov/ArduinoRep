################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../simulebox.ino 

CPP_SRCS += \
../Crono.cpp \
../Dum.cpp \
../EA_12845.cpp \
../ModbusMaster.cpp \
../NewBridge.cpp \
../PWMCOM_SimulEbox.cpp \
../Parametri.cpp \
../PseudoTimer.cpp \
../Scheduler.cpp \
../Time.cpp \
../c_12845.cpp \
../cea_12845.cpp \
../evo.cpp \
../sloeber.ino.cpp 

LINK_OBJ += \
./Crono.cpp.o \
./Dum.cpp.o \
./EA_12845.cpp.o \
./ModbusMaster.cpp.o \
./NewBridge.cpp.o \
./PWMCOM_SimulEbox.cpp.o \
./Parametri.cpp.o \
./PseudoTimer.cpp.o \
./Scheduler.cpp.o \
./Time.cpp.o \
./c_12845.cpp.o \
./cea_12845.cpp.o \
./evo.cpp.o \
./sloeber.ino.cpp.o 

INO_DEPS += \
./simulebox.ino.d 

CPP_DEPS += \
./Crono.cpp.d \
./Dum.cpp.d \
./EA_12845.cpp.d \
./ModbusMaster.cpp.d \
./NewBridge.cpp.d \
./PWMCOM_SimulEbox.cpp.d \
./Parametri.cpp.d \
./PseudoTimer.cpp.d \
./Scheduler.cpp.d \
./Time.cpp.d \
./c_12845.cpp.d \
./cea_12845.cpp.d \
./evo.cpp.d \
./sloeber.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
Crono.cpp.o: ../Crono.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Dum.cpp.o: ../Dum.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

EA_12845.cpp.o: ../EA_12845.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

ModbusMaster.cpp.o: ../ModbusMaster.cpp
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

Scheduler.cpp.o: ../Scheduler.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Time.cpp.o: ../Time.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

c_12845.cpp.o: ../c_12845.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

cea_12845.cpp.o: ../cea_12845.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10802 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino Due"' "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/libsam" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/CMSIS/Include/" "-I/home/fabrilov/sloeber//arduinoPlugin/packages/arduino/hardware/sam/1.6.10/system/CMSIS/Device/ATMEL/"  -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/cores/arduino" -I"/home/fabrilov/sloeber/arduinoPlugin/packages/arduino/hardware/sam/1.6.10/variants/arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

evo.cpp.o: ../evo.cpp
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


