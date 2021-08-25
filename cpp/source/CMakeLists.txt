# Adds convenience methods, see cmake/cleanCppExtensions.cmake
include(cleanCppExtensions)

# Creates options to turn on sanitizers, see cmake/sanitizers.cmake
include(sanitizers)

# Enable helpfull warnings and C++20 for all files
if(MSVC)
    add_compile_options(/std:c++17 /W3 /WX )
else()
    add_compile_options(-std=c++17 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wunused -pedantic)
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

target_include_directories(
        ${PROJECT_NAME}
        ${BITWYRE_SYSTEM_INCLUDE} INTERFACE
        $<BUILD_INTERFACE:"${PROJECT_SOURCE_DIR}/source/"}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries (bitwyresdk PRIVATE Threads::Threads ${CONAN_LIBS})
add_library(bitwyresdk::bitwyresdk ALIAS bitwyresdk)

install(
        TARGETS bitwyresdk
        EXPORT bitwyresdk
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(
        DIRECTORY "${PROJECT_SOURCE_DIR}/source/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Using macro from cmake/cleanCpppExtensions.cpp included on the top
# Provides bitwyresdk-run a nd bitwyresdk-dbg
addRunAndDebugTargets(bitwyresdk)

# short convenience target from cmake/cleanCpppExtensions.cpp
add_custom_target(run DEPENDS bitwyresdk-run)

#------------------------------------------------------------------------------
# Unit tests
if(BUILD_TESTING)
    add_subdirectory(unittest)
endif()
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


