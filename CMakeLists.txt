cmake_minimum_required(VERSION 3.5)
project(ChessMind LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

include(cmake/CPM.cmake)
include(CMakeDependentOption)
include(GNUInstallDirs)
include(CheckIPOSupported)

# Add local project module path so CMake includes custom CMake modules.
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")

add_library(helloworld_lib SHARED
    include/CppWallet/HelloWorld.hpp
	src/CppWallet/HelloWorld.cpp
)
add_library(helloworld::library ALIAS helloworld_lib)

target_include_directories(helloworld_lib
	PUBLIC
        ${PROJECT_SOURCE_DIR}/include
		src
)
target_compile_options(helloworld_lib
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			 -Wall -Wextra>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4>
)

#
# NOTE: Include 3rd party libraries, Perry and I maintain an open-source extras C++ library, which
# is used extensively in dmgcore, it comes bundled with spdlog, cpr, and nlohmann json. extras has
# project options that allow us to control how other libraries it includes are built. for example we
# can tell extras to build spdlog as a static library (for faster compile times) by settings
# MAKE_SPDLOG_SHARED OFF
#
CPMAddPackage(
  NAME extras
  GITHUB_REPOSITORY mattcoding4days/extras
  VERSION 3.9.2
  OPTIONS "MAKE_SPDLOG_SHARED OFF"
)
if(extras_ADDED)
  #
  # NOTE:  enable c++11 to avoid compilation errors, and force spdlog into release build
  #
  print(STATUS "Configuring extras build properties")
  set_target_properties(extras PROPERTIES CMAKE_BUILD_TYPE Release)
else()
  print(WARNING "extras was not configured properly")
endif()

#
# Create executable that uses the ChessMind lib to say Hello.
#
add_executable(helloworld
	src/main.cpp
)
target_link_libraries(helloworld
	PRIVATE
	    helloworld::library 
		extras
)
target_compile_options(helloworld
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Wall -Wextra>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4>
)

#
# Create a target for executing the Catch2 unit tests.
#
add_executable(run-unittests
	test/main.cpp
	test/mock_KeyPair.cpp
	test/mock_Transaction.cpp
	test/mock_Wallet.cpp
	test/test_FakeIt.cpp
	test/test_List.cpp
	test/test_HelloWorld.cpp
)
target_include_directories(run-unittests
	PUBLIC
		test/
)
target_link_libraries(run-unittests
   helloworld::library 
   extras
)
# -Werror
target_compile_options(run-unittests
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			  -Wall -Wextra>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4>
)

############################################################
# Install
############################################################

# Binaries
install (TARGETS helloworld
    DESTINATION bin)

# Library
# Note: may not work on windows
install (TARGETS helloworld_lib
    LIBRARY DESTINATION lib)

# Header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ 
    DESTINATION include)

# Config
install (FILES cmake-examples.conf
    DESTINATION etc)

