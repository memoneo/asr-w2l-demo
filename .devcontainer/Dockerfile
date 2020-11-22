FROM wav2letter/wav2letter:inference-latest

RUN export KENLM_ROOT_DIR=/root/kenlm && \
    export MKLROOT=/opt/intel/mkl && \
    APT_INSTALL="apt-get install -y --no-install-recommends" && \
    apt-get update && \
    DEBIAN_FRONTEND=noninteractive $APT_INSTALL \
        libopenblas-dev \