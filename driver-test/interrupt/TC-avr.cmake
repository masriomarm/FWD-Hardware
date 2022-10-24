set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

set(CMAKE_C_COMPILER      avr-gcc)
set(CMAKE_CXX_COMPILER    avr-g++)
set(CMAKE_ASM_COMPILER    avr-as)
set(CMAKE_OBJCOPY         avr-objcopy)
set(CMAKE_OBJDUMP         avr-objdump)
set(CMAKE_NM              avr-nm)


set(CMAKE_FIND_ROOT_PATH /usr/lib/avr/)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_FLAGS "-mmcu=atmega32 -D__ATmega32__ -DF_CPU=1000000UL -Ofast -Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS "-Xlinker -Map=\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MapFile.map\"")
