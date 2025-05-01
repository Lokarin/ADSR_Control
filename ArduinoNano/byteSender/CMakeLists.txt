cmake_minimum_required(VERSION 3.10)
project(byteSender)

set(CMAKE_CXX_STANDARD 11)

# Adiciona o único arquivo-fonte com os dois códigos unificados
add_executable(${PROJECT_NAME} src/main.cpp)

# Linka bibliotecas do sistema quando necessário
if(WIN32)
    target_link_libraries(${PROJECT_NAME} setupapi)
endif()

