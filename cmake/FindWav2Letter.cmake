set(WAV2LETTER_ROOT_DIR /root/wav2letter/build)
set(KENLM_ROOT_DIR /root/kenlm/build)
set(WAV2LETTER_INC /root/wav2letter)

message(STATUS "Looking for WAV2LETTER in ${WAV2LETTER_ROOT_DIR}")

find_library(WAV2LETTER_LIB
  wav2letter-libraries
  PATHS
    ${WAV2LETTER_ROOT_DIR}/src/libraries
)

find_library(WAV2LETTER_INFERENCE_LIB
    wav2letter-inference
    PATHS
        ${WAV2LETTER_ROOT_DIR}/inference    
)

set(WAV2LETTER_LIBRARIES ${WAV2LETTER_LIB})
set(WAV2LETTER_INCLUDE_DIRS ${WAV2LETTER_INC}/src/libraries)
set(WAV2LETTER_INFERENCE ${WAV2LETTER_INFERENCE_LIB})
set(WAV2LETTER_INFERENCE_INCLUDE_DIRS /root/wav2letter/inference/inference)

if (NOT WAV2LETTER_LIB-NOTFOUND)
  message(STATUS "Found wav2letter (include: ${WAV2LETTER_INCLUDE_DIRS}, libraries: ${WAV2LETTER_LIBRARIES})")
  mark_as_advanced(WAV2LETTER_ROOT_DIR WAV2LETTER_INCLUDE_DIRS WAV2LETTER_LIBRARIES WAV2LETTER_INFERENCE)
endif()