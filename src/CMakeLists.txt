cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(wx_cmake_template_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# hack for buggy CMake's FindwxWidgets script
if(DEFINED ENV_WX_CONFIG)
    set(ENV{WX_CONFIG} ${ENV_WX_CONFIG})
endif()

set(wxWidgets_USE_STATIC 1)

find_package(wxWidgets REQUIRED)

set(SOURCE_DIR "")

# set(SRCS main.cpp)
# file(GLOB SOURCE_FILES 
#     main.cpp
#     "${SOURCE_DIR}/*.cpp"
#     "${SOURCE_DIR}/*.h"
# )
file(GLOB_RECURSE SOURCE_FILES 
    main.cpp 
    windows/Application.cpp 
    windows/LoginWindow/LoginFrame.cpp 
    networks/*.cpp
)
file(GLOB_RECURSE HEADER_FILES 
    windows/Application.h 
    windows/LoginWindow/LoginFrame.h 
    networks/*.h
)

add_definitions(-D_WIN32_WINNT=0x0601)


include(${wxWidgets_USE_FILE})
include_directories(../thirdparty/asio)

if(APPLE)
    # create bundle on apple compiles
    add_executable(main MACOSX_BUNDLE ${SOURCE_FILES} ${HEADER_FILES})

    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(main PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
else()
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    add_executable(main WIN32 ${SOURCE_FILES} main.exe.manifest)
endif()

target_link_libraries(main PRIVATE ${wxWidgets_LIBRARIES})