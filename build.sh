if [ $1 == "build" ]
then
    cd ./build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    cmake --build .
    make
else
    if [ $1 == "clean" ]
    then
        cd ./build
        cmake ..
        make clean
    else
        echo "incorrect params"
    fi
fi