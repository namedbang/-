################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Code/%.obj: ../Code/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo '正在调用： Arm Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/TI_Code/msp432e4/432P/empty_MSP_EXP432P401R_freertos_ccs/Code" --include_path="C:/TI_Code/msp432e4/432P/empty_MSP_EXP432P401R_freertos_ccs" --include_path="C:/TI_Code/msp432e4/432P/empty_MSP_EXP432P401R_freertos_ccs/Debug" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/posix/ccs" --include_path="C:/TI_Code/FreeRTOSv202212.01 (1)/FreeRTOSv202212.01/FreeRTOS/Source/include" --include_path="C:/TI_Code/FreeRTOSv202212.01 (1)/FreeRTOSv202212.01/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/TI_Code/msp432e4/432P/freertos_builds_MSP_EXP432P401R_release_ccs" --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=none -g --c99 --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="Code/$(basename $(<F)).d_raw" --include_path="C:/TI_Code/msp432e4/432P/empty_MSP_EXP432P401R_freertos_ccs/Debug/syscfg" --obj_directory="Code" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


