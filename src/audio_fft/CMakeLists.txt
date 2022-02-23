add_library(audio_fft STATIC "")
target_sources(audio_fft 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/HammingWindow.cpp
        ${CMAKE_CURRENT_LIST_DIR}/fft_demo.cpp
        ${CMAKE_CURRENT_LIST_DIR}/kiss_fft.cpp
        ${CMAKE_CURRENT_LIST_DIR}/kiss_fftr.cpp

    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/HammingWindow.h
        ${CMAKE_CURRENT_LIST_DIR}/RingBuffer.h
        ${CMAKE_CURRENT_LIST_DIR}/fft_demo.h
        ${CMAKE_CURRENT_LIST_DIR}/kiss_fft.h
        ${CMAKE_CURRENT_LIST_DIR}/kiss_fftr.h
        ${CMAKE_CURRENT_LIST_DIR}/_kiss_fft_guts.h
        ${CMAKE_CURRENT_LIST_DIR}/kiss_fft_log.h
)
# target_link_libraries(audio_fft kiss_fft kiss_fftr)
target_include_directories(audio_fft 
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_LIB_DIR}
)