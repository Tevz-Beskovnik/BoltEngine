#!/bin/bash

BUILD_TYPE=$1

echo "Checking that cmake is installed"
cmake --version
if [[ $? -ne 0 ]]; then
  echo "Please install cmake"
fi

echo "Checking that conan is installed"
conan --version
if [[ $? -ne 0 ]]; then
  echo "Please install conan"
fi


if [[ "$BUILD_TYPE" == "Debug" ]]; then
  conan install . --build=missing --settings=build_type=Debug

  cd ./build

  cmake .. --preset=defaultDebug
elif [[ "$BUILD_TYPE" == "Release" ]]; then
  conan install . --build=missing

  cd ./build

  cmake .. --preset=defaultRelease
else
  echo "Build options are Debug and Release"
fi
