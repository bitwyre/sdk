# Adds convenience methods, see cmake/cleanCppExtensions.cmake
include(cleanCppExtensions)

# Creates options to turn on sanitizers, see cmake/sanitizers.cmake
include(sanitizers)

# Enable helpfull warnings and C++20 for all files
if(MSVC)
    add_compile_options(/std:c++20 /W3 /WX )
else()
    add_compile_options(-std=c++20 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wunused -pedantic)
endif()

# configure version.cpp.in with selected version
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/version.cpp.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.cpp"
  )
# If you want to have date and time of the build, your targets has to depend on this.
# This will force recompilation of version.o and thus forcing gcc to update __DATE__ macro.
add_custom_target(versionFileTouchForRebuild
    COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")


#------------------------------------------------------------------------------
# Libraries dependencies
find_package (Threads REQUIRED) #threading

#------------------------------------------------------------------------------
# By using macro to add common dependencies you can avoid repetition when you have
# multiple binaries.
# Use with `addCommonDependencies(bitwyresdk)`
# macro(addCommonDependencies TARGET)
#     add_dependencies(${TARGET} versionFileTouchForRebuild) # We want precise time of build in version
#     target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#     target_link_libraries (${TARGET} PRIVATE Threads::Threads)
#     target_compile_definitions(${TARGET} PRIVATE -DSOME_DEFINE)
# endmacro()

add_library(bitwyresdk
        ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/Time.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/details/Config.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/details/ConstexprMap.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/Market.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/Product.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/details/Response.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/Asset.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/CryptoAsset.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/FiatAsset.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/Instrument.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/Ticker.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/Trades.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/details/Types.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/Depth.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/Contract.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/Announcements.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/OrderTypes.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/public/SupportedLanguages.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/private/AccountBalance.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/private/AccountStatement.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/private/TradesHistory.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/private/CancelOrder.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/private/ClosedOrders.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/private/OrderInfo.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/private/NewOrder.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/private/OpenOrders.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rest/private/TransactionHistory.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/details/Utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/details/Dispatcher.hpp)

add_dependencies(bitwyresdk versionFileTouchForRebuild) # We want precise time of build in version
target_include_directories(bitwyresdk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (bitwyresdk PRIVATE Threads::Threads ${CONAN_LIBS})

install(TARGETS bitwyresdk
    BUNDLE DESTINATION "."
    RUNTIME DESTINATION bin)

# Using macro from cmake/cleanCpppExtensions.cpp included on the top
# Provides bitwyresdk-run a nd bitwyresdk-dbg
addRunAndDebugTargets(bitwyresdk)

# short convenience target from cmake/cleanCpppExtensions.cpp
add_custom_target(run DEPENDS bitwyresdk-run)

# Manually specified convenience target for running the binary, we use macro
# add_custom_target(bitwyresdk-run
#     WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin
#     USES_TERMINAL
#     COMMAND ./bitwyresdk
#     DEPENDS Install_)

# And this would add -DBAR_ENABLE_FEATURE or equivalent to build command
# target_compile_definitions(bitwyresdk PRIVATE BAR_ENABLE_FEATURE)

# Add compile time definition based on option
# option(OPTION_NAME "description for end user" OFF)
# if(OPTION_NAME)
#     # you can do anything here, eg. setup new optional executable
#     target_compile_definitions(bitwyresdk PRIVATE DEFINE_NAME)
# endif()

# Add building new shared library
# add_library(exampleLibrary SHARED ${LIBRARY_SOURCES})
# target_link_libraries (exampleLibrary PRIVATE ${CMAKE_THREAD_LIBS_INIT})
# set_property(TARGET exampleLibrary PROPERTY CXX_STANDARD 14) # we want C++14

# How to include and link OpenGL and GLUT libraries
# find_package(OpenGL REQUIRED)
# find_package(GLUT REQUIRED)
# target_include_directories(bitwyresdk PRIVATE SYSTEM ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )
# target_link_libraries(bitwyresdk PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

# How to use some other standard packages
# find_package(ZLIB REQUIRED) 
# target_link_libraries (bitwyresdk PRIVATE ZLIB::ZLIB)
# 
# find_package(OpenSSL REQUIRED)
# target_link_libraries (bitwyresdk PRIVATE OpenSSL::SSL OpenSSL::Crypto)
#
# find_package(CURL REQUIRED)
# target_link_libraries (bitwyresdk PRIVATE CURL::libcurl)

#------------------------------------------------------------------------------
# Unit tests

add_subdirectory(unittest)

#-------------------------------------------------------------------------------
# Copy MINGW needed libraries for building on windows

if(MINGW)
    message(STATUS "MinGW detected")
    get_filename_component(GCC_PATH ${CMAKE_C_COMPILER} PATH)
    if(${GCC_PATH} MATCHES "mingw64/bin")
        set(libgcc "libgcc_s_seh-1.dll") #64bit
        message(STATUS "  64bit dlls is building")
    else()
        set(libgcc "libgcc_s_dw2-1.dll") #32bit
        message(STATUS "  32bit dlls is building")
    endif()

    install(FILES ${GCC_PATH}/${libgcc}
        ${GCC_PATH}/libwinpthread-1.dll
        ${GCC_PATH}/libstdc++-6.dll
        DESTINATION ./bin/
    )
endif(MINGW)


#------------------------------------------------------------------------------
# Other MISC targets

# Adds misc targets: format, cppcheck, tidy, see cmake/cleanCppExtensions.cmake
addMiscTargets()


