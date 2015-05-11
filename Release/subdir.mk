################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../Camera.o \
../GLerror.o \
../Game.o \
../GameObject.o \
../ModelLoader.o \
../Texture.o \
../keyCallback.o \
../loadShader.o \
../main.o 

CPP_SRCS += \
../Camera.cpp \
../GLerror.cpp \
../Game.cpp \
../GameObject.cpp \
../ModelLoader.cpp \
../Texture.cpp \
../keyCallback.cpp \
../loadShader.cpp \
../main.cpp 

OBJ_SRCS += \
../Dummy2.obj 

OBJS += \
./Camera.o \
./GLerror.o \
./Game.o \
./GameObject.o \
./ModelLoader.o \
./Texture.o \
./keyCallback.o \
./loadShader.o \
./main.o 

CPP_DEPS += \
./Camera.d \
./GLerror.d \
./Game.d \
./GameObject.d \
./ModelLoader.d \
./Texture.d \
./keyCallback.d \
./loadShader.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O3 -Wall -std=c++11 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


