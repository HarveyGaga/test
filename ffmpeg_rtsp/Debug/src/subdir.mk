################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main.cpp \
../src/utimer.cpp \
../src/video_api.cpp 

O_SRCS += \
../src/main.o \
../src/utimer.o \
../src/video_api.o 

OBJS += \
./src/main.o \
./src/utimer.o \
./src/video_api.o 

CPP_DEPS += \
./src/main.d \
./src/utimer.d \
./src/video_api.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__STDC_CONSTANT_MACROS -I/opt/opencv-pc/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


