################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deer.cpp \
../src/LTimer.cpp \
../src/Tree.cpp \
../src/nature.cpp 

OBJS += \
./src/Deer.o \
./src/LTimer.o \
./src/Tree.o \
./src/nature.o 

CPP_DEPS += \
./src/Deer.d \
./src/LTimer.d \
./src/Tree.d \
./src/nature.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


