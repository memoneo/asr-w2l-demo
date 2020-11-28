FROM wav2letter/wav2letter:inference-latest

RUN export KENLM_ROOT_DIR=/root/kenlm && \
    export MKLROOT=/opt/intel/mkl 

RUN APT_INSTALL="apt-get install -y --no-install-recommends" && \
    apt-get update && \
    DEBIAN_FRONTEND=noninteractive $APT_INSTALL \
        libopenblas-dev && \
        libjsoncpp-dev uuid-dev openssl libssl-dev zlib1g-dev

RUN apt-get -y --purge remove cmake && \
    pip install cmake

RUN cd $WORK_DIR && \
    git clone https://github.com/oatpp/oatpp.git && \
    cd oatpp && \
    mkdir build && cd build && \
    cmake .. && \
    make install

EXPOSE 8000