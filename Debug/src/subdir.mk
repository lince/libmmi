################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AccelerationEvent.cpp \
../src/AccelerationFactory.cpp \
../src/EventBuffer.cpp \
../src/EventParser.cpp \
../src/KeyEvent.cpp \
../src/KeyEventFactory.cpp \
../src/MMIEvent.cpp \
../src/MMIManager.cpp 

OBJS += \
./src/AccelerationEvent.o \
./src/AccelerationFactory.o \
./src/EventBuffer.o \
./src/EventParser.o \
./src/KeyEvent.o \
./src/KeyEventFactory.o \
./src/MMIEvent.o \
./src/MMIManager.o 

CPP_DEPS += \
./src/AccelerationEvent.d \
./src/AccelerationFactory.d \
./src/EventBuffer.d \
./src/EventParser.d \
./src/KeyEvent.d \
./src/KeyEventFactory.d \
./src/MMIEvent.d \
./src/MMIManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/java/include/ -I/opt/java/include/linux -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


