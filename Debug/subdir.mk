################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../Random.cc \
../SmartPtr.cc \
../TestBasicAtomic.cc \
../TestPool.cc \
../TestProducerConsumer.cc \
../TestRandom.cc \
../Utility.cc 

OBJS += \
./Random.o \
./SmartPtr.o \
./TestBasicAtomic.o \
./TestPool.o \
./TestProducerConsumer.o \
./TestRandom.o \
./Utility.o 

CC_DEPS += \
./Random.d \
./SmartPtr.d \
./TestBasicAtomic.d \
./TestPool.d \
./TestProducerConsumer.d \
./TestRandom.d \
./Utility.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -O0 -g3 -p -pg -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


