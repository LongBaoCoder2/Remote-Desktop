cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(RemoteDesktop LANGUAGES CXX)

# Set C++17 as the standard for the entire project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# hack for buggy CMake's FindwxWidgets script
if(DEFINED ENV_WX_CONFIG)
    set(ENV{WX_CONFIG} ${ENV_WX_CONFIG})
endif()

set(wxWidgets_USE_STATIC 1)

find_package(wxWidgets REQUIRED)

set(asio_PACKAGE_DIR ../thirdparty/asio)

set(SOURCE_DIR "")

# set(SRCS main.cpp)
# file(GLOB SOURCE_FILES 
#     main.cpp
#     "${SOURCE_DIR}/*.cpp"
#     "${SOURCE_DIR}/*.h"
# )
file(GLOB_RECURSE SOURCE_FILES 
    main.cpp 
    models/*.cpp
    networks/*.cpp
    utils/FileNameGenerator/*.cpp

    windows/Application.cpp 
    windows/BasicTextWindow/*.cpp
    windows/components/NavigationBar/*.cpp
    windows/LoginWindow/LoginFrame.cpp 
    windows/MainWindow/*.cpp
    windows/MainWindow/CaptureWindow/ClientWindow/*.cpp
    windows/MainWindow/CaptureWindow/ServerWindow/*.cpp
    windows/MainWindow/CaptureWindow/*.hpp
    windows/MainWindow/HomeWindow/*.cpp
    windows/MainWindow/ManageWindow/*.cpp
    windows/MainWindow/MenuWindow/*.cpp
    windows/MainWindow/SettingsWindow/*.cpp
)

add_definitions(-D_WIN32_WINNT=0x0601)

# set(OpenCV_DIR C:/ProgramData/opencv/build)

# find_package(OpenCV REQUIRED)
# include_directories(${OpenCV_INCLUDE_DIRS})

include(${wxWidgets_USE_FILE})
include_directories(../thirdparty/asio)

link_directories(${LINK_WEBP})


if(APPLE)
    # create bundle on apple compiles
    add_executable(main MACOSX_BUNDLE ${SOURCE_FILES})

    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(main PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
else()
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    add_executable(main WIN32 ${SOURCE_FILES} main.exe.manifest)
endif()

target_link_libraries(main PRIVATE ${wxWidgets_LIBRARIES})


