cmake_minimum_required(VERSION 3.16)

project(lab-crypto VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(lab-crypto
    src/main.cpp
    src/Client.cpp
    src/LoginWindow.cpp
    src/UserWindow.cpp
    src/HistoryWindow.cpp
    src/VigenereWindow.cpp
    src/MD5Window.cpp
    src/SecantWindow.cpp
    src/GraphWindow.cpp
    src/VigenereCipher.cpp
    src/MD5.cpp
    src/SecantMethod.cpp
    src/GraphCycle.cpp
    src/ServerStub.cpp
)

target_link_libraries(lab-crypto PRIVATE Qt6::Core Qt6::Widgets)