cmake_minimum_required(VERSION 3.25)
project(app_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

include_directories(class/include)

add_executable(app_test main.cpp class/editor/Editor.cpp class/include/Editor.h class/editor/Editor.ui)
target_link_libraries(app_test Qt::Core Qt::Gui Qt::Widgets)