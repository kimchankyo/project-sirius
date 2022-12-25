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

# variables
reqDirs=("build")
reqFiles=("CMakeLists.txt")
filesExist=true

# check if required directories exist
for target in ${reqDirs[@]}; do
  if [ ! -d "./${target}" ]; then filesExist=false; fi
done

# check if required files exist
for target in ${reqFiles[@]}; do
  if [ ! -f "./${target}" ]; then filesExist=false; fi
done

# exit if required files do not exist
if [ "$filesExist" = false ]; then
  error "No build directory and/or CMake files were found."
  exit
fi

# perform compilation and linking using cmake
cd build
cmake ..
cmake --build .
success "Project binary executable available in ./bin directory."