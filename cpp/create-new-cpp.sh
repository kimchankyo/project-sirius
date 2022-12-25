#!/bin/bash

# functions
function warning() {
  echo -e "\033[1;33m[WARNING]: $1\033[0m"
}

function error() {
  echo -e "\033[1;31m[ ERROR ]: $1\033[0m"
}

function success() {
  echo -e "\033[1;32m[SUCCESS]: $1\033[0m"
}

function getFileContents() {
  case "$1" in
  CMakeLists.txt)

    retval=\
"# Define CMake Program
cmake_minimum_required(VERSION 3.10)
project(${projectName} VERSION 1.0)

# Set Source Directory Locations
set(PROJECT_SOURCE_INCLUDE \"\${PROJECT_SOURCE_DIR}/include\")
set(PROJECT_SOURCE_FILES \"\${PROJECT_SOURCE_DIR}/src\")
set(PROJECT_SOURCE_LIBRARIES \"\${PROJECT_SOURCE_DIR}/lib\")

# Find all source files (Generates a list of source files)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS \"\${PROJECT_SOURCE_FILES}/*.cpp\")

# Set Build Directory Locations
set(PROJECT_BUILD_INCLUDE \"\${PROJECT_BINARY_DIR}/include\")
set(PROJECT_BUILD_BINARY \"\${PROJECT_BINARY_DIR}/bin\")

# Add Libraries -> Add subdirectories + Link libraries + Link library headers
# NOTE: MAKING HEAVY ASSUMPTION THAT LIBRARIES HAVE CMakeLists.txt AND /include FOLDERS
# NOTE: UNCOMMENT BELOW IF USING LIBRARIES
# # Add Subdirectories for each library
# file(GLOB LIBS RELATIVE \"\${PROJECT_SOURCE_LIBRARIES}\" \"\${PROJECT_SOURCE_LIBRARIES}/*\")
# foreach(LIB \"\${LIBS}\")
#   add_subdirectory(\"\${PROJECT_SOURCE_LIBRARIES}/\${LIB}\")
#
#   # Add Standard Library Header Files
#   # list(APPEND LIB_DIRS \"\${PROJECT_SOURCE_LIBRARIES}/\${LIB}\")    # For .lib files
#   list(APPEND LIB_HEADERS \"\${PROJECT_SOURCE_LIBRARIES}/\${LIB}/include\")
# endforeach()

# Configure Version Header File
configure_file(config.h.in \"\${PROJECT_BUILD_INCLUDE}/config.h\")

# Create Executable Using Source Files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"\${PROJECT_BUILD_BINARY}\")
add_executable(${projectName} \"\${SRC_FILES}\")

# Target Link Libraries (.lib files)
# NOTE: UNCOMMENT BELOW IF USING EXTERNAL .lib FILES
# target_link_libraries(${projectName} PUBLIC \"\${LIB_DIRS}\")

# Target Include Directories
# NOTE: UNCOMMENT BELOW IF USING LIBRARIES
# target_include_directories(${projectName} PUBLIC \"\${PROJECT_BUILD_INCLUDE}\" \"\${LIB_HEADERS}\")
target_include_directories(${projectName} PUBLIC \"\${PROJECT_BUILD_INCLUDE}\" \"\${PROJECT_SOURCE_INCLUDE}\")"
    ;;
  config.h.in)
    retval=\
"#define version_major @${projectName}_VERSION_MAJOR@
#define version_minor @${projectName}_VERSION_MINOR@"
    ;;
  src/main.cpp)
    retval=\
"#include <iostream>

using namespace std;

int main() {
  cout << \"Hello World!\" << endl;
  return 0;
}"
    ;;
  esac
}

# variables
reqDirs=("build" "include" "lib" "src")
reqFiles=("CMakeLists.txt" "config.h.in" "src/main.cpp")
filesExist=false
overwrite=false
projectName=proj

# terminal arguments
while getopts "o:n:" option; do
  case "$option" in
    o)
      if [ "$OPTARG" = true ]; then overwrite=true; fi
      ;;
    n)
      if [ ${#OPTARG} -gt 0 ]; then 
        if [[ "$OPTARG" == *-* ]]; then
          error "No hyphens are allowed in project name."
          exit
        fi
        projectName="$OPTARG"
      fi
      ;;
  esac
done

# check if required directories exist
for target in ${reqDirs[@]}; do
  if [ -d "./${target}" ]; then filesExist=true; fi
done

# check if required files exist
for target in ${reqFiles[@]}; do
  if [ -f "./${target}" ]; then filesExist=true; fi
done

# either overwrite existing directories or quit
if [ "${filesExist}" = true ]; then
  warning "Existing C++ project files found."
  if [ "${overwrite}" = false ]; then 
    error "Cannot create new C++ project files. Consider setting the overwrite flag '-o' to true."
    exit
  fi
  warning "Overwriting existing C++ project files."
  for target in ${reqDirs[@]}; do rm -rf "./${target}"; done
  for target in ${reqFiles[@]}; do rm -f "./${target}"; done
  success "Removed existing C++ project files."
fi

# create project directories
for target in ${reqDirs[@]}; do mkdir "${target}"; done
success "Created new C++ project directories."

# create required files
for target in ${reqFiles[@]}; do
  getFileContents "${target}"
  echo -e "${retval}" > "${target}"
done