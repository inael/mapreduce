################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/deviceQuery.cpp 

CU_SRCS += \
../src/cuPrintf.cu \
../src/simplePrintf.cu 

CU_DEPS += \
./src/cuPrintf.d \
./src/simplePrintf.d 

OBJS += \
./src/cuPrintf.o \
./src/deviceQuery.o \
./src/simplePrintf.o 

CPP_DEPS += \
./src/deviceQuery.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -G -g -O0 -gencode arch=compute_10,code=sm_10 -gencode arch=compute_11,code=sm_11 -gencode arch=compute_12,code=sm_12 -gencode arch=compute_13,code=sm_13 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_20,code=sm_21 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35 -odir "src" -M -o "$(@:%.o=%.d)" "$<"
	nvcc --compile -G -O0 -g -gencode arch=compute_10,code=compute_10 -gencode arch=compute_10,code=sm_10 -gencode arch=compute_11,code=compute_11 -gencode arch=compute_11,code=sm_11 -gencode arch=compute_12,code=compute_12 -gencode arch=compute_12,code=sm_12 -gencode arch=compute_13,code=compute_13 -gencode arch=compute_13,code=sm_13 -gencode arch=compute_20,code=compute_20 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_20,code=sm_21 -gencode arch=compute_30,code=compute_30 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=compute_35 -gencode arch=compute_35,code=sm_35  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -G -g -O0 -gencode arch=compute_10,code=sm_10 -gencode arch=compute_11,code=sm_11 -gencode arch=compute_12,code=sm_12 -gencode arch=compute_13,code=sm_13 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_20,code=sm_21 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35 -odir "src" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


