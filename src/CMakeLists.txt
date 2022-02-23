
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

set(SOURCE_FILES main.cpp)

add_executable(main "")
target_sources(main PRIVATE ${SOURCE_FILES})
target_include_directories(main 
  PUBLIC 
    ${PROJECT_INCLUDE_DIR}
    
  )


target_link_libraries(main std_image audio_test audio_fft)
install(TARGETS main DESTINATION ${PROJECT_BIN_DIR})