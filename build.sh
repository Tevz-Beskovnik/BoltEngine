if [ $1 == "build" ]
then
    cd ./build
    cmake ..
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