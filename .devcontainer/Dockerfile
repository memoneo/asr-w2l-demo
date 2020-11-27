FROM wav2letter/wav2letter:inference-latest

RUN export KENLM_ROOT_DIR=/root/kenlm && \
    export MKLROOT=/opt/intel/mkl 

RUN APT_INSTALL="apt-get install -y --no-install-recommends" && \
    apt-get update && \
    DEBIAN_FRONTEND=noninteractive $APT_INSTALL \
        libopenblas-dev

# Install updated Boost
RUN apt-get -y --purge remove libboost-dev && \
    apt-get -y --purge remove libboost-all-dev && \
    apt-get -y --purge autoremove libboost-all-dev

RUN cd $WORK_PATH && \
    wget https://dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.tar.gz && \
    tar -xzvf boost_1_74_0.tar.gz && \
    rm boost_1_74_0.tar.gz && \
    cd boost_1_74_0 && \
    sh bootstrap.sh && \
    ./b2 && \
    ./b2 install

# Install Drogon
RUN APT_INSTALL="apt-get install -y --no-install-recommends" && \
    DEBIAN_FRONTEND=noninteractive $APT_INSTALL \
        libjsoncpp-dev uuid-dev zlib1g-dev && \
    cd $WORK_PATH && \
    git clone https://github.com/an-tao/drogon && \
    cd drogon && \
    git submodule update --init && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && make install
