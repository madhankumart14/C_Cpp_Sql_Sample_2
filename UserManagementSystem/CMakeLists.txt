cmake_minimum_required(VERSION 3.10)
project(UserManagementSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Locate SQL Library Package
find_package(SQLite3 REQUIRED)

# Include directories
include_directories(include)

# Define source targets
file(GLOB SOURCES "src/*.cpp")

add_executable(UserManagementSystem ${SOURCES})

# Bind SQLite libraries to executable compilation
target_link_libraries(UserManagementSystem PRIVATE SQLite3::SQLite3)
