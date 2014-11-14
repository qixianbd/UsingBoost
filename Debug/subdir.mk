################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../MtHashTable.cc \
../MtHashTable_Test.cc \
../Person.cc \
../Random.cc \
../TestBasicAtomic.cc \
../TestPool.cc \
../TestProducerConsumer.cc \
../TestProducerConsumer2.cc \
../TestProducerConsumer3.cc \
../TestRandom.cc \
../TestSmartPtr.cc \
../Utility.cc 

OBJS += \
./MtHashTable.o \
./MtHashTable_Test.o \
./Person.o \
./Random.o \
./TestBasicAtomic.o \
./TestPool.o \
./TestProducerConsumer.o \
./TestProducerConsumer2.o \
./TestProducerConsumer3.o \
./TestRandom.o \
./TestSmartPtr.o \
./Utility.o 

CC_DEPS += \
./MtHashTable.d \
./MtHashTable_Test.d \
./Person.d \
./Random.d \
./TestBasicAtomic.d \
./TestPool.d \
./TestProducerConsumer.d \
./TestProducerConsumer2.d \
./TestProducerConsumer3.d \
./TestRandom.d \
./TestSmartPtr.d \
./Utility.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


