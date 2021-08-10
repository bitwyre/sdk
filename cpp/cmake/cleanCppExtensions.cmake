# Helper macro for creating convenient targets
find_program(GDB_PATH gdb)

# Adds -run and -dbg targets
macro(addRunAndDebugTargets TARGET)
    add_custom_target(${TARGET}-run
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
        DEPENDS ${TARGET}
        COMMAND ./${TARGET})

    # convenience run gdb target
    if(GDB_PATH)
        add_custom_target(${TARGET}-gdb
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            USES_TERMINAL
            DEPENDS ${TARGET}
            COMMAND ${GDB_PATH} ./${TARGET})
    endif()
endmacro()

#------------------------------------------------------------------------------
# Other MISC targets - formatting, static analysis
# format, cppcheck, tidy
macro(addMiscTargets)
    file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.cc *.c)
    file(GLOB_RECURSE ALL_HEADER_FILES *.h *.hpp)

    # Static analysis via clang-tidy target
    # We check for program, since when it is not here, target makes no sense
    find_program(TIDY_PATH clang-tidy PATHS /usr/local/Cellar/llvm/*/bin)
    if(TIDY_PATH)
        message(STATUS "clang-tidy - static analysis              YES ")
        add_custom_target(tidy
            COMMAND ${TIDY_PATH} -header-filter=.* ${ALL_SOURCE_FILES} -p=./ )
    else()
        message(STATUS "clang-tidy - static analysis              NO ")
    endif()

    # cpp check static analysis
    find_program(CPPCHECK_PATH cppcheck)
    if(CPPCHECK_PATH)
        message(STATUS "cppcheck - static analysis                YES ")
        add_custom_target(
                cppcheck
                COMMAND ${CPPCHECK_PATH}
                --enable=warning,performance,portability,information,missingInclude
                --std=c++11
                --template=gcc
                --verbose
                --quiet
                ${ALL_SOURCE_FILES}
        )
    else()
        message(STATUS "cppcheck - static analysis                NO ")
    endif()

    # run clang-format on all files
    find_program(FORMAT_PATH clang-format)
    if(FORMAT_PATH)
        message(STATUS "clang-format - code formating             YES ")
        add_custom_target(format
            COMMAND ${FORMAT_PATH} -i ${ALL_SOURCE_FILES} ${ALL_HEADER_FILES} )
    else()
        message(STATUS "clang-format - code formating             NO ")
    endif()
endmacro()

#------------------------------------------------------------------------------
# Force compilers, this was deprecated in CMake, but still comes handy sometimes
macro(FORCE_C_COMPILER compiler id)
    set(CMAKE_C_COMPILER "${compiler}")
    set(CMAKE_C_COMPILER_ID_RUN TRUE)
    set(CMAKE_C_COMPILER_ID ${id})
    set(CMAKE_C_COMPILER_FORCED TRUE)

    # Set old compiler id variables.
    if(CMAKE_C_COMPILER_ID MATCHES "GNU")
        set(CMAKE_COMPILER_IS_GNUCC 1)
    endif()
endmacro()

macro(FORCE_CXX_COMPILER compiler id)
    set(CMAKE_CXX_COMPILER "${compiler}")
    set(CMAKE_CXX_COMPILER_ID_RUN TRUE)
    set(CMAKE_CXX_COMPILER_ID ${id})
    set(CMAKE_CXX_COMPILER_FORCED TRUE)

    # Set old compiler id variables.
    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
        set(CMAKE_COMPILER_IS_GNUCXX 1)
    endif()
endmacro()
