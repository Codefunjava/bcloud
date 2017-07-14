cmake_minimum_required(VERSION 3.1)
project(bcloud CXX C)

# Only generate Debug and Release configuration types.
set(CMAKE_CONFIGURATION_TYPES Debug Release)
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror -Wextra")
  # -fno-rtti, Disable real-time type information
  # -fno-exceptions Disable exceptions
  # -fsanitize=address Enable memory sanitize plugin
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -Wextra -fno-exceptions")
  # -fsanitize=address, Enable memory address sanitizer.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  # -fsanitize=leak, Enable memory leak sanitizer.
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
  # -fsanitize=memory, Enable detecting uninitited memory sanitizer.
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory "
  #    "-fsanitize-memory-track-origins -fPIC -pie -fno-omit-frame-pointer")
else()
  # -Wl, -O2 Enable linker optimizations
  #-Wl, --gc-sections Remove unused code resulting from -fdsta-sections and -ffunction-sections
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -Wl,-O1 -Wl,--gc-sections")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -Wl,-O1 -Wl,--gc-sections -Wno-unused-result")
endif()

find_package(PkgConfig REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5X11Extras REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5LinguistTools)

add_subdirectory(third_party/gtest)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(Qt_LIBS
    Qt5::Gui
    Qt5::Network
    Qt5::Widgets)

set(BASE_FILES
    base/file_util.cpp
    base/file_util.h
    base/json_util.cpp
    base/json_util.h)

set(SERVICES_FILES
    services/pcs.cpp
    services/pcs.h)

set(UNITTEST_FILES
    base/file_util_test.cpp
    base/json_util_test.cpp)

## Executables
add_executable(passport-test
               app/passport_test.cpp
               ${BASE_FILES}
               ${SERVICES_FILES})
target_link_libraries(passport-test ${Qt_LIBS})


add_executable(unittest-main
               app/unittest_main.cpp
               ${BASE_FILES}
               ${UNITTEST_FILES})
target_link_libraries(unittest-main
                      ${Qt_LIBS}
                      gtest)