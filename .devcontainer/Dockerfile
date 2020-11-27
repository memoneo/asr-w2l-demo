FROM wav2letter/wav2letter:inference-latest

RUN export KENLM_ROOT_DIR=/root/kenlm && \
    export MKLROOT=/opt/intel/mkl 

RUN APT_INSTALL="apt-get install -y --no-install-recommends" && \
    apt-get update && \
    DEBIAN_FRONTEND=noninteractive $APT_INSTALL \
        libopenblas-dev && \
        openssl && \
        libssl-dev

RUN apt-get -y --purge remove cmake && \
    pip install cmake