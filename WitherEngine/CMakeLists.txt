cmake_minimum_required(VERSION 3.10)

# Name of the project
project(WitherEngine)

#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

# Put executable inside of bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Use C++17 standard 
set(CMAKE_CXX_STANDARD_REQUIRED 17)

# Add dependencies if build succeeds
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/dependencies/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/dependencies)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)