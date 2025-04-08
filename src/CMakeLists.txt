cmake_minimum_required(VERSION 3.28)
project(Chess LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(chess main.cpp interface.cpp gameLogic.cpp fen.cpp)
target_compile_features(chess PRIVATE cxx_std_17)
target_link_libraries(chess PRIVATE sfml-graphics)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/textures
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/)

if(WIN32)
    add_custom_command(
        TARGET chess
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:chess>
        VERBATIM)
endif()
