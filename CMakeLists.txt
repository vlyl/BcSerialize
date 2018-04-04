cmake_minimum_required(VERSION 3.10)
project(bcSerialize)

set(CMAKE_CXX_STANDARD 11)
set(SRC_LIST serialize.h
        streams.h
        transaction.cpp
        amount.h
        uint256.cpp
        compat.h
        cleanse.cpp
        script/script.cpp
        zeroafterfree.h
        #compat/byteswap.h
        #compat/endian.h
        prevector.h
        tinyformat.h
        utilstrencodings.cpp
        hash.cpp
        crypto/common.h
        crypto/sha256.cpp
        crypto/sha512.cpp
        crypto/hmac_sha256.cpp
        crypto/hmac_sha512.cpp
        version.h)
include_directories(${PROJECT_SOURCE_DIR})
#aux_source_directory(script)
#link_directories(/usr/lib/x86_64-linux-gnu/)
add_executable(bcSerialize main.cpp ${SRC_LIST})
#target_link_libraries(bcSerialize crypto ssl)