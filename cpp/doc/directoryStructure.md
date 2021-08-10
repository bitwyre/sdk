# Directory structure

* mainProjectFolder
    - **build** - user created, build takes place here
        + **dist** - here builded application is copied (by deafult, see CMAKE_INSTALL_PREFIX in main CMakeLists.txt)
            * **bin**
            * **share**
                - **data** - here folder data is copied
            * **doc**
                - doxygen lives here documentation
    - **cmake** - contains cmake scripts that can be included with include()
        + cleanCppExtensions.cmake - reusable helpers for source/CMakeLists.txt
        + sanitizers.cmake - adds sanitizers options
        + useGoldLinker.cmake - enables simple use of gold linker for faster linkage
    - **data** - contain data
    - **doc** - contains documentation
        + CMakeLists.txt - doc building
        + **doxygen**
            * doxygen settings, and modern style config
    - **source** - contain source files
        + CMakeLists.txt - source building
        + **unittest* contains unittest build
            + CMakeLists.txt - unittest building
            + testmain.cpp - main unit tests function
    - **test** - integration tests, CTest, data sets for tests and unit tests
        + CMakeLists.txt - tests specification
    - README.md - main readme file
    - CMakeLists.md - Main CMake configuration
    - .clang-format - clang format config file
    - .clang-tidy - clang tidy config file


