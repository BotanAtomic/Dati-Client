cmake_minimum_required(VERSION 3.12)
project(Dati C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-lpthread")

link_directories(${PROJECT_SOURCE_DIR}/json-c/.libs)

add_executable(Dati core/main.c network/client.c network/client.h command/parser.c command/parser.h utils/utils.c utils/utils.h network/protocol.c network/protocol.h utils/buffer.c utils/buffer.h)

target_link_libraries(Dati json-c)
