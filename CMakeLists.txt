cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME SuperEMMETT)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

# Source files
file(GLOB SRC src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

include_directories(C:/SFML/include)
target_link_libraries(${PROJECT_NAME} -mwindows sfml-system sfml-window sfml-graphics sfml-audio sfml-network)