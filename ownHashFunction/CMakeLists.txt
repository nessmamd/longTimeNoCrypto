cmake_minimum_required(VERSION 3.26)
project(ownHashFunction)

set(CMAKE_CXX_STANDARD 17)

add_executable(ownHashFunction main.cpp
        hashfunction.cpp
        hashfunction.h
        sha256modif.h
        sha256modif.cpp
        BlockChain.h
        Block.h
        Block.cpp
        BlockChain.cpp
        mRoot.h
        mRoot.cpp
        node.h
        node.cpp)
