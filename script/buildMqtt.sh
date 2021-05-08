#!/bin/bash

file=./build

if [-f "$file"];then
    mkdir build
else
    echo -e "\033[5;35m build exist\033[0m"
fi

cd build && rm -rf * && ninja clean

cmake -GNinja  -DCMAKE_C_COMPILER=${GCC_ARM_GCC} -DCMAKE_CXX_COMPILER=${GCC_ARM_GXX} -DOPENSSL_ROOT_DIR="/mnt/d/code/r14_ltev2x_app/system/packages/openssl-OpenSSL_1_1_1h/OUT" -DOPENSSL_LIB_SEARCH_PATH="/mnt/d/code/r14_ltev2x_app/system/packages/openssl-OpenSSL_1_1_1h/OUT/lib/" -DOPENSSL_INC_SEARCH_PATH="/mnt/d/code/r14_ltev2x_app/system/packages/openssl-OpenSSL_1_1_1h/OUT/include/openssl/" -DPAHO_WITH_SSL=TRUE -DOPENSSL_ROOT_DIR=/mnt/d/code/r14_ltev2x_app/system/packages/openssl-OpenSSL_1_1_1h/OUT ..

ninja package

echo -e "\033[5;35m build finished!\033[0m"
