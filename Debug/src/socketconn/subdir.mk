################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/socketconn/ServerSocketTCP.cpp \
../src/socketconn/SocketTCP.cpp \
../src/socketconn/TCPCommServer.cpp \
../src/socketconn/TCPDevice.cpp 

OBJS += \
./src/socketconn/ServerSocketTCP.o \
./src/socketconn/SocketTCP.o \
./src/socketconn/TCPCommServer.o \
./src/socketconn/TCPDevice.o 

CPP_DEPS += \
./src/socketconn/ServerSocketTCP.d \
./src/socketconn/SocketTCP.d \
./src/socketconn/TCPCommServer.d \
./src/socketconn/TCPDevice.d 


# Each subdirectory must supply rules for building sources it contributes
src/socketconn/%.o: ../src/socketconn/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/java/include/ -I/opt/java/include/linux -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


