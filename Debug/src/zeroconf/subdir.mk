################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/zeroconf/CommunicationManager.cpp 

OBJS += \
./src/zeroconf/CommunicationManager.o 

CPP_DEPS += \
./src/zeroconf/CommunicationManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/zeroconf/%.o: ../src/zeroconf/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/java/include/ -I/opt/java/include/linux -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


