################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../bindings/java/AccelerationEvent.cpp \
../bindings/java/KeyEvent.cpp \
../bindings/java/ListenerAdapter.cpp \
../bindings/java/MMIManager.cpp 

OBJS += \
./bindings/java/AccelerationEvent.o \
./bindings/java/KeyEvent.o \
./bindings/java/ListenerAdapter.o \
./bindings/java/MMIManager.o 

CPP_DEPS += \
./bindings/java/AccelerationEvent.d \
./bindings/java/KeyEvent.d \
./bindings/java/ListenerAdapter.d \
./bindings/java/MMIManager.d 


# Each subdirectory must supply rules for building sources it contributes
bindings/java/%.o: ../bindings/java/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/java/include/ -I/opt/java/include/linux -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


