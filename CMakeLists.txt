cmake_minimum_required(VERSION 3.10)
project(my-app LANGUAGES CXX)

set(CMAKE_TOOLCHAIN_FILE "D:/GitHub/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "Vcpkg toolchain file")

include(FetchContent)

FetchContent_Declare(
  dotenv
  GIT_REPOSITORY https://github.com/laserpants/dotenv-cpp.git
)

FetchContent_MakeAvailable(dotenv)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(libpqxx CONFIG REQUIRED)
find_package(plog REQUIRED)

add_executable(my-app ${SOURCES} ${HEADERS})

target_link_libraries(my-app PRIVATE libpqxx::pqxx)
target_link_libraries(my-app PRIVATE plog::plog)
target_link_libraries(my-app PRIVATE dotenv)


target_compile_options(my-app PRIVATE
    "-fdiagnostics-color=always"
    "-pedantic-errors"
    "-Wall"
    "-Weffc++"
    "-Wextra"
    "-Wconversion"
    "-Wsign-conversion"
    "-Werror"
    $<$<CONFIG:Debug>:-ggdb>
    $<$<CONFIG:Release>:-O2>
    $<$<CONFIG:Release>:-DNDEBUG>
)
target_include_directories(my-app PRIVATE include)
