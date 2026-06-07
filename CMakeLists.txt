cmake_minimum_required(VERSION 3.15)
project(bolt)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(src)

find_package(CURL REQUIRED)

add_executable(Bolt
    src/main.cpp
    src/cli/cli.cpp
    src/search/search.cpp
    src/manifest/manifest.cpp
    src/downloader/downloader.cpp
    src/resolver/resolver.cpp
    src/injector/injector.cpp
)

target_link_libraries(Bolt CURL::libcurl)