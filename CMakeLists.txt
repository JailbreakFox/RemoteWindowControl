cmake_minimum_required(VERSION 3.7)
project(RemoteWindowControl)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_BUILD_TYPE "RelWithDebInfo")

# Close not commonly used WIN32 modules 
add_definitions(-DWIN32_LEAN_AND_MEAN)

find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)

file(GLOB_RECURSE src_files src/*.cpp src/*.h ./*.qrc)

add_executable(${PROJECT_NAME}_server main_server.cpp ${src_files})
target_include_directories(${PROJECT_NAME}_server PUBLIC src/base src/windows)
target_link_libraries(${PROJECT_NAME}_server Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)

add_executable(${PROJECT_NAME}_client main_client.cpp ${src_files})
target_include_directories(${PROJECT_NAME}_client PUBLIC src/base src/windows)
target_link_libraries(${PROJECT_NAME}_client Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)