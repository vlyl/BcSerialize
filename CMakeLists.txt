cmake_minimum_required(VERSION 3.10)
project(bcSerialize)

set(CMAKE_CXX_STANDARD 11)
set(SRC_LIST serialize.h
        streams.h
        transaction.cpp
        amount.h
        uint256.cpp
        script/script.cpp
        zeroafterfree.h
        compat/endian.h
        prevector.h
        tinyformat.h
        utilstrencodings.cpp
        hash.cpp
        crypto/common.h
        version.h)

#aux_source_directory(script)
link_directories(/usr/local/opt/openssl/lib)
add_executable(bcSerialize main.cpp ${SRC_LIST})
target_link_libraries(bcSerialize ssl)