echo "Cross compiling darknet ..."
if [ -d build_cross ]; then
  rm -rf build_cross
fi
mkdir build_cross
cd build_cross
cmake -DCMAKE_TOOLCHAIN_FILE=../aarch64_glibc.cmake .. -DCMAKE_BUILD_TYPE=Release
make -j8