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
wget -q -O cmake-linux.sh https://github.com/Kitware/CMake/releases/download/v3.22.2/cmake-3.22.2-Linux-x86_64.sh
sh cmake-linux.sh -- --skip-license --prefix=$MY_INSTALL_DIR
rm cmake-linux.sh

# additional required tools
sudo apt install -y build-essential autoconf libtool pkg-config

# may need this if it is missing
sudo apt-get install libz-dev
```

## Make and CMAKE build

### Clone and Build gRPC and Protobuf

``` BASH
# Clone the grpc repo
git clone --recurse-submodules -b v1.44.0 https://github.com/grpc/grpc

# go to grpc folder
cd grpc

GRPC_CPP_DISTRIBTEST_BUILD_COMPILER_JOBS=${GRPC_CPP_DISTRIBTEST_BUILD_COMPILER_JOBS:-4}

mkdir -p cmake/build

pushd cmake/build

# run cmake commands
cmake ../.. -DgRPC_INSTALL=ON \
            -DCMAKE_INSTALL_PREFIX=$HOME/.local \
            -DABSL_PROPAGATE_CXX_STD=ON \
            -DgRPC_BUILD_TYPE=Release \
            -DgRPC_BUILD_TESTS=OFF \
            -DgRPC_SSL_PROVIDER=package \
            -DgRPC_ZLIB_PROVIDER=package # necessary if you installed the libz-dev package or zlib is already there.

# make the files and install
make "-j${GRPC_CPP_DISTRIBTEST_BUILD_COMPILER_JOBS}" install

popd
```

## build a quick request
[GRPC C Introduction](https://medium.com/@andrewvetovitz/grpc-c-introduction-45a66ca9461f)

### Build
``` BASH
mkdir -p cmake/build

pushd cmake/build

cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..