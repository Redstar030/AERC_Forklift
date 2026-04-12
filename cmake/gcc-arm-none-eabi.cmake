set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)

# Some default GCC settings
# arm-none-eabi- must be part of path environment
set(TOOLCHAIN_PREFIX                arm-none-eabi-)

# Optional override for local toolchain folder, e.g. C:/.../tools/bin
set(TOOLCHAIN_BIN_DIR "" CACHE PATH "Directory containing arm-none-eabi toolchain binaries")

set(_TOOLCHAIN_HINTS)
if(TOOLCHAIN_BIN_DIR)
	list(APPEND _TOOLCHAIN_HINTS ${TOOLCHAIN_BIN_DIR})
endif()
list(APPEND _TOOLCHAIN_HINTS
	"C:/ST/STM32CubeIDE_1.19.0/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.13.3.rel1.win32_1.0.0.202411081344/tools/bin"
)

find_program(ARM_GCC    NAMES ${TOOLCHAIN_PREFIX}gcc HINTS ${_TOOLCHAIN_HINTS})
find_program(ARM_GXX    NAMES ${TOOLCHAIN_PREFIX}g++ HINTS ${_TOOLCHAIN_HINTS})
find_program(ARM_OBJCOPY NAMES ${TOOLCHAIN_PREFIX}objcopy HINTS ${_TOOLCHAIN_HINTS})
find_program(ARM_SIZE   NAMES ${TOOLCHAIN_PREFIX}size HINTS ${_TOOLCHAIN_HINTS})

if(NOT ARM_GCC OR NOT ARM_GXX)
	message(FATAL_ERROR "ARM GCC toolchain not found. Add arm-none-eabi-* to PATH or set TOOLCHAIN_BIN_DIR cache variable.")
endif()

set(CMAKE_C_COMPILER                ${ARM_GCC})
set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER              ${ARM_GXX})
set(CMAKE_LINKER                    ${ARM_GXX})
set(CMAKE_OBJCOPY                   ${ARM_OBJCOPY})
set(CMAKE_SIZE                      ${ARM_SIZE})

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# MCU specific flags
set(TARGET_FLAGS "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard ")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${TARGET_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp -MMD -MP")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fdata-sections -ffunction-sections")

set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "-Os -g0")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -g0")

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")

set(CMAKE_EXE_LINKER_FLAGS "${TARGET_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T \"${CMAKE_SOURCE_DIR}/STM32F407XX_FLASH.ld\"")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nano.specs")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")
set(TOOLCHAIN_LINK_LIBRARIES "m")
