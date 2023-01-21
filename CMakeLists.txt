cmake_minimum_required(VERSION 3.7.2)

project(filesystem-read-coroutine)

find_package(fmt REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(IOURING REQUIRED liburing)

add_executable(filesystem-coroutine filesystem-coroutine.cpp)
target_link_libraries(filesystem-coroutine pthread fmt::fmt ${IOURING_LIBRARIES})
target_compile_features(filesystem-coroutine PUBLIC cxx_std_20)
target_compile_options(filesystem-coroutine PUBLIC -fcoroutines)
