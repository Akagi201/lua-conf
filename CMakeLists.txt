cmake_minimum_required(VERSION 2.8.4)

project(lua_conf_sample)

set(SOURCE_FILES sample.c src/conf.c)

include_directories("/usr/local/include" ${PROJECT_SOURCE_DIR}/src)

link_directories("/usr/local/lib")

add_executable(lua_conf_sample ${SOURCE_FILES})

target_link_libraries(lua_conf_sample "liblua.a")
