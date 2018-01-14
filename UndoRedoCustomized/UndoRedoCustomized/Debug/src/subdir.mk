################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/UndoRedoStackImpl.cpp 

OBJS += \
./src/UndoRedoStackImpl.o 

CPP_DEPS += \
./src/UndoRedoStackImpl.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++1y -I"D:\DevProjects\Cpp\GitProjectsNeon\UndoRedoCustomized\include" -I"C:\Users\Gerd\git\CppNeon\Cpp-UndoRedoFramework\UndoRedoFramework\include" -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


