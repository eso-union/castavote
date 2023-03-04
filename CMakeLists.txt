cmake_minimum_required(VERSION 3.16.3)

project(Cast-a-vote
        VERSION 3
        DESCRIPTION "Internet search engine"
        HOMEPAGE_URL "https://EsoUnion.com")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O3")
include_directories(include)
file(GLOB SOURCES_WEB    "src/*.cpp")
add_executable(castavote.wt ${SOURCES_WEB})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(
    Boost 1.67 COMPONENTS
    filesystem
    regex
    program_options
    signals
    system
    thread)
find_package(fmt)

target_link_libraries(
    castavote.wt
    Boost::system
    Boost::regex
    Boost::program_options
    pqxx
    wt
    wtfcgi
    fmt::fmt
    Threads::Threads)

install(TARGETS castavote.wt DESTINATION /var/www/paranal/bin/)
#install(DIRECTORY etc/info DESTINATION /var/www/EsoUnion)
#install(DIRECTORY etc/style DESTINATION /var/www/EsoUnion)
install(DIRECTORY etc/approot DESTINATION /usr/local/etc/paranal)
#install(FILES etc/words.json DESTINATION /usr/local/etc/paranal)
