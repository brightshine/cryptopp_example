cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

# Project data
PROJECT(aes)

# Define variable
add_definitions(-DCRYPTOPP_DISABLE_AESNI)

if (WIN32)
        set(LIB_PREFIX "")
        set(LIB_APPENDIX "lib")
        set(CRYTPOPP "cryptlib")
else()
        set(LIB_PREFIX "lib")
        set(LIB_APPENDIX "a")
        set(CRYTPOPP "cryptopp")
endif()
set(PANTHEIOS "pantheios")

# Set include files
set(INC_DIR "/home/daniel/src/SUM/scebioscfg_lib/src/util")
include_directories("${INC_DIR}")

set(PREBUILD_LIB_DIR "/home/daniel/src/SUM/scebioscfg_lib/prebuild_libs/Release/")

# cryptopp
add_library(cryptopp STATIC IMPORTED)
set_target_properties(cryptopp PROPERTIES IMPORTED_LOCATION "${PREBUILD_LIB_DIR}/${LIB_PREFIX}${CRYTPOPP}.${LIB_APPENDIX}")

# Build binary
add_executable ( aes aes.cc)

target_link_libraries(${PROJECT_NAME} cryptopp )
