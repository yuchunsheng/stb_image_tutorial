
add_library(audio_test STATIC "")

target_sources(audio_test  
    PRIVATE 
        ${CMAKE_CURRENT_LIST_DIR}/audio_read.cpp 
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/audio_read.hpp
)

target_include_directories(audio_test 
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR} 
        ${PROJECT_LIB_DIR}/kissfft
    
)