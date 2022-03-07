# GRPC in C++

Using the following to get myself acqauinted with yet another language and gRPC :P https://grpc.io/docs/languages/cpp/quickstart/

## ENV Setup

``` BASH
# Export package directory location
export MY_INSTALL_DIR=$HOME/.local

# add the local bin to path variable
export PATH="$MY_INSTALL_DIR/bin:$PATH"

# Install cmake
sudo apt install -y cmake

# more recent version use:
wget -q -O cmake-linux.sh https://github.com/Kitware/CMake/releases/download/v3.19.6/cmake-3.19.6-Linux-x86_64.sh
sh cmake-linux.sh -- --skip-license --prefix=$MY_INSTALL_DIR
rm cmake-linux.sh

# additional required tools
sudo apt install -y build-essential autoconf libtool pkg-config
```

## Clone and Build gRPC and Protobuf

``` BASH
# Clone the grpc repo
git clone --recurse-submodules -b v1.43.0 https://github.com/grpc/grpc

# go to grpc folder
cd grpc

mkdir -p cmake/build

pushd cmake/build

# run cmake commands
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      ../..

# make the files and install
make -j
make install

popd
```