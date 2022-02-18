
add_library(std_image STATIC "")

target_sources(std_image
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/std_image_tutorial.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/std_image_tutorial.hpp 

  )

target_include_directories(std_image
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR} 
    ${PROJECT_INCLUDE_DIR}
  )
