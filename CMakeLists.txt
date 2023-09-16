cmake_minimum_required(VERSION 3.0)  # Defina a versão mínima do CMake
project(controle)
set(CMAKE_GENERATOR_TOOLSET "v143" CACHE STRING "Toolset version used by Visual Studio" FORCE)

set(MAIN_PATH "internal/main.cpp")
set(INIT_PATH "internal/init.cpp")
set(INSTALL_PATH "install/install.cpp")
set(INIT_INSTALL_PATH "install/init_install.cpp")
set(UPDATE_PATH "update/update.cpp")
SET(CURL_PATH "libs/curl-8.2.1")

add_executable(main ${MAIN_PATH})
add_executable(init ${INIT_PATH})
# add_executable(install_dir ${INSTALL_PATH})
add_executable(init_install ${INIT_INSTALL_PATH})
# add_executable(update ${UPDATE_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories("libs/libgit2/include")
# include_directories("libs/curl-8.2.1/include")

# find_library(GIT2_LIBRARY git2)
# if(GIT2_LIBRARY)
#     target_link_libraries(install PRIVATE git2)
#     target_link_libraries(update PRIVATE git2)
# else()
#     message(FATAL_ERROR "biblioteca GIT2 não encontrada.")
# endif()

