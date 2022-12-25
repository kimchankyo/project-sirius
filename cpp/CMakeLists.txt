# Define CMake Program
cmake_minimum_required(VERSION 3.10)
project(project_sirius VERSION 1.0)

# Set Source Directory Locations
set(PROJECT_SOURCE_INCLUDE "${PROJECT_SOURCE_DIR}/include")
set(PROJECT_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src")
set(PROJECT_SOURCE_LIBRARIES "${PROJECT_SOURCE_DIR}/lib")

# Find all source files (Generates a list of source files)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${PROJECT_SOURCE_FILES}/*.cpp")

# Set Build Directory Locations
set(PROJECT_BUILD_INCLUDE "${PROJECT_BINARY_DIR}/include")
set(PROJECT_BUILD_BINARY "${PROJECT_BINARY_DIR}/bin")

# Add Libraries -> Add subdirectories + Link libraries + Link library headers
# NOTE: MAKING HEAVY ASSUMPTION THAT LIBRARIES HAVE CMakeLists.txt AND /include FOLDERS
# NOTE: UNCOMMENT BELOW IF USING LIBRARIES
# # Add Subdirectories for each library
# file(GLOB LIBS RELATIVE "${PROJECT_SOURCE_LIBRARIES}" "${PROJECT_SOURCE_LIBRARIES}/*")
# foreach(LIB "${LIBS}")
#   add_subdirectory("${PROJECT_SOURCE_LIBRARIES}/${LIB}")
#
#   # Add Standard Library Header Files
#   # list(APPEND LIB_DIRS "${PROJECT_SOURCE_LIBRARIES}/${LIB}")    # For .lib files
#   list(APPEND LIB_HEADERS "${PROJECT_SOURCE_LIBRARIES}/${LIB}/include")
# endforeach()

# Configure Version Header File
configure_file(config.h.in "${PROJECT_BUILD_INCLUDE}/config.h")

# Create Executable Using Source Files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BUILD_BINARY}")
add_executable(project_sirius "${SRC_FILES}")

# Target Link Libraries (.lib files)
# NOTE: UNCOMMENT BELOW IF USING EXTERNAL .lib FILES
# target_link_libraries(project_sirius PUBLIC "${LIB_DIRS}")

# Target Include Directories
# NOTE: UNCOMMENT BELOW IF USING LIBRARIES
# target_include_directories(project_sirius PUBLIC "${PROJECT_BUILD_INCLUDE}" "${LIB_HEADERS}")
target_include_directories(project_sirius PUBLIC "${PROJECT_BUILD_INCLUDE}" "${PROJECT_SOURCE_INCLUDE}")
