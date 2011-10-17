################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/client-tcp.cpp \
../test/comm-server.cpp \
../test/keyParser.cpp \
../test/server-tcp.cpp \
../test/test1.cpp \
../test/virtualdevice.cpp 

OBJS += \
./test/client-tcp.o \
./test/comm-server.o \
./test/keyParser.o \
./test/server-tcp.o \
./test/test1.o \
./test/virtualdevice.o 

CPP_DEPS += \
./test/client-tcp.d \
./test/comm-server.d \
./test/keyParser.d \
./test/server-tcp.d \
./test/test1.d \
./test/virtualdevice.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/java/include/ -I/opt/java/include/linux -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


