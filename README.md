# GRPC in C++

Using the following to get myself acqauinted with yet another language and gRPC :P https://grpc.io/docs/languages/cpp/quickstart/

A note for anyone using this: you need to run through all of the steps for this to work. The steps matter. gRPC tools are stored in a local folder as recommended by the gRPC quickstart.

## Step 1: ENV Setup

``` BASH
# Export package directory location
export MY_INSTALL_DIR=$HOME/.local

# create the directory just in case it doesn't already exist
mkdir -p $MY_INSTALL_DIR

# add the local bin to path variable
export PATH="$MY_INSTALL_DIR/bin:$PATH"

# Install cmake, if not on Ubuntu 20.04, consider using the wget way of getting cmake
sudo apt install -y cmake

# for a more recent version of cmake use:
wget -q -O cmake-linux.sh https://github.com/Kitware/CMake/releases/download/v3.22.2/cmake-3.22.2-Linux-x86_64.sh
sh cmake-linux.sh -- --skip-license --prefix=$MY_INSTALL_DIR
rm cmake-linux.sh

# additional required tools
sudo apt install -y build-essential autoconf libtool pkg-config libssl-dev
```

## Step 2: Clone and Build gRPC and Protobuf

``` BASH
# Clone the grpc repo
git clone --recurse-submodules -b v1.44.0 https://github.com/grpc/grpc

# go to grpc folder
cd grpc

# this is the limmiter for the number of jobs run simultaneously. Defaults to 4
GRPC_CPP_DISTRIBTEST_BUILD_COMPILER_JOBS=${GRPC_CPP_DISTRIBTEST_BUILD_COMPILER_JOBS:-4}

# need a build folder
mkdir -p cmake/build

# go to build folder
pushd cmake/build

# run cmake commands
cmake ../.. -DgRPC_INSTALL=ON \
            -DCMAKE_INSTALL_PREFIX=$HOME/.local \
            -DABSL_PROPAGATE_CXX_STD=ON \
            -DgRPC_BUILD_TYPE=Release \
            -DgRPC_BUILD_TESTS=OFF \
            -DgRPC_SSL_PROVIDER=package

# make the files and install
make "-j${GRPC_CPP_DISTRIBTEST_BUILD_COMPILER_JOBS}" install

# return to previous location
popd
```

## Step 3: build a quick request
[GRPC C Introduction](https://medium.com/@andrewvetovitz/grpc-c-introduction-45a66ca9461f)

### Build
``` BASH
mkdir -p cmake/build

pushd cmake/build

cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..
make
```
