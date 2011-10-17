################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/wii/StateCircularBuffer.cpp \
../src/wii/WiiButtonReport.cpp \
../src/wii/WiiDriver.cpp \
../src/wii/WiiEvent.cpp \
../src/wii/WiiEventPoster.cpp \
../src/wii/WiiMote.cpp \
../src/wii/WiiState.cpp 

OBJS += \
./src/wii/StateCircularBuffer.o \
./src/wii/WiiButtonReport.o \
./src/wii/WiiDriver.o \
./src/wii/WiiEvent.o \
./src/wii/WiiEventPoster.o \
./src/wii/WiiMote.o \
./src/wii/WiiState.o 

CPP_DEPS += \
./src/wii/StateCircularBuffer.d \
./src/wii/WiiButtonReport.d \
./src/wii/WiiDriver.d \
./src/wii/WiiEvent.d \
./src/wii/WiiEventPoster.d \
./src/wii/WiiMote.d \
./src/wii/WiiState.d 


# Each subdirectory must supply rules for building sources it contributes
src/wii/%.o: ../src/wii/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/java/include/ -I/opt/java/include/linux -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


