cmake_minimum_required(VERSION 3.22)

# ================================================================
#   PROJECT CONFIGURATION
# ================================================================
set(CMAKE_PROJECT_NAME empp_pjt)
project(${CMAKE_PROJECT_NAME} LANGUAGES C CXX ASM)

# Default to Debug unless specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif ()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ================================================================
#   COMPILER CONFIG
# ================================================================
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# ================================================================
#   BUILD INFO MESSAGE
# ================================================================
message(STATUS "")
message(STATUS "============ STM32H750 Build Configuration ============")
message(STATUS "Project          : ${CMAKE_PROJECT_NAME}")
message(STATUS "Build Type       : ${CMAKE_BUILD_TYPE}")
message(STATUS "Toolchain File   : ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "Compiler (C)     : ${CMAKE_C_COMPILER}")
message(STATUS "Compiler (CXX)   : ${CMAKE_CXX_COMPILER}")
message(STATUS "CPU/FPU          : Cortex-M7 / fpv5-d16 hard-float")
message(STATUS "Output Dir       : ${CMAKE_BINARY_DIR}")
message(STATUS "=======================================================")
message(STATUS "")


# ================================================================
#   TARGET: EXECUTABLE
# ================================================================
add_executable(${CMAKE_PROJECT_NAME})


# ================================================================
#   DIRECTORIES
# ================================================================
add_subdirectory(cmake/stm32cubemx) # Add STM32CubeMX generated sources
message(STATUS "[OK] STM32CubeMX sources loaded")

add_subdirectory(empp)
message(STATUS "[OK] Platform sources loaded")

# ================================================================
#   TARGET SOURCES
# ================================================================
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        UserApp/Main.cpp
)

# ================================================================
#   TARGET INCLUDE DIRECTORIES
# ================================================================
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        UserApp
)

# ================================================================
#   TARGET DEFINITIONS
# ================================================================
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
)

# ================================================================
#   LINK LIBRARIES
# ================================================================
target_link_libraries(${CMAKE_PROJECT_NAME}
        stm32cubemx
        empp_platform
)

# Platform depends on stm32cubemx HAL/LL includes
target_link_libraries(empp_platform PUBLIC stm32cubemx)

# ================================================================
#   LINK LIBRARIES DIR
# ================================================================
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE

)

# ================================================================
#   REMOVE WRONG LIBS
# ================================================================
# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# ================================================================
#   SHOW FINAL CONFIG
# ================================================================
message(STATUS "")
message(STATUS "------------ Final Build Summary ----------------")
message(STATUS "Executable Target   : ${CMAKE_PROJECT_NAME}")

get_target_property(INC_DIRS ${CMAKE_PROJECT_NAME} INCLUDE_DIRECTORIES)
message(STATUS "Include Dirs:")
foreach (item ${INC_DIRS})
    message(STATUS "  - ${item}")
endforeach ()

get_target_property(LIBS ${CMAKE_PROJECT_NAME} LINK_LIBRARIES)
message(STATUS "Linked Libraries:")
foreach (item ${LIBS})
    message(STATUS "  - ${item}")
endforeach ()

get_target_property(SRCS ${CMAKE_PROJECT_NAME} SOURCES)
message(STATUS "Sources:")
foreach (item ${SRCS})
    message(STATUS "  - ${item}")
endforeach ()

message(STATUS "--------------------------------------------------")
message(STATUS "")

