
# add_library(std_image STATIC "")

# include(${CMAKE_CURRENT_LIST_DIR}/std_image_tutorial/CMakeLists.txt)

set(USE_LIBRARY ON)

if(USE_LIBRARY)
  message(STATUS "compile source in to a library ${USE_LIBRARY}")
else()
  message(STATUS "no library ${USE_LIBRARY}")
endif()

add_subdirectory(std_image_tutorial)
add_subdirectory(audio_tutorial)
add_subdirectory(audio_fft)
add_subdirectory(jpeg_decoder)

set(SOURCE_FILES main.cpp)

add_executable(main "")
target_sources(main PRIVATE ${SOURCE_FILES})
target_include_directories(main 
  PUBLIC 
    ${PROJECT_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/jpeg_decoder
    ${CMAKE_CURRENT_SOURCE_DIR}/audio_fft
    ${CMAKE_CURRENT_SOURCE_DIR}/audio_tutorial
    ${CMAKE_CURRENT_SOURCE_DIR}/std_image_tutorial
    
  )


target_link_libraries(main PUBLIC std_image audio_test audio_fft jpeg_decoder)
install(TARGETS main DESTINATION ${PROJECT_BIN_DIR})