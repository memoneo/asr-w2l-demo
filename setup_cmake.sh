cd build && \
rm -rf * && \
export KENLM_ROOT_DIR=/root/kenlm && \
export MKLROOT=/opt/intel/mkl && \
cmake .. -DCMAKE_BUILD_TYPE=Release -DW2L_BUILD_LIBRARIES_ONLY=ON -DW2L_LIBRARIES_USE_CUDA=OFF -DW2L_BUILD_INFERENCE=ON \
-DW2L_INFERENCE_BUILD_EXAMPLES=OFF -DW2L_INFERENCE_BUILD_TESTS=OFF
