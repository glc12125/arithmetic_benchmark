mkdir build
cd build
cmake ..
getCoreNumCmd="getconf _NPROCESSORS_ONLN"
coreNum=eval ${getCoreNumCmd}
echo "Number of cores: ${coreNum}"
make -j${coreNum}
cd ..
