################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ink/Channel.cpp \
../src/ink/Ink.cpp \
../src/ink/InkMLParser.cpp \
../src/ink/Trace.cpp \
../src/ink/TraceFormat.cpp \
../src/ink/Utility.cpp 

OBJS += \
./src/ink/Channel.o \
./src/ink/Ink.o \
./src/ink/InkMLParser.o \
./src/ink/Trace.o \
./src/ink/TraceFormat.o \
./src/ink/Utility.o 

CPP_DEPS += \
./src/ink/Channel.d \
./src/ink/Ink.d \
./src/ink/InkMLParser.d \
./src/ink/Trace.d \
./src/ink/TraceFormat.d \
./src/ink/Utility.d 


# Each subdirectory must supply rules for building sources it contributes
src/ink/%.o: ../src/ink/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/java/include/ -I/opt/java/include/linux -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


