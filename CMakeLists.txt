cmake_minimum_required(VERSION 3.12)
project(Dati C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-lpthread -lm")

link_directories(${PROJECT_SOURCE_DIR}/lib/json-c/.libs)

include_directories(include lib)

add_executable(Dati src/core/main.c src/network/client.c include/client.h src/network/protocol.c
        include/protocol.h src/network/buffer.c include/buffer.h src/shell/shell.c include/shell.h src/network/query.c
        include/query.h src/utils/decimal.c include/decimal.h)

target_link_libraries(Dati json-c)
