
add_library(jpeg_decoder STATIC "")

target_sources(jpeg_decoder
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/tjpgd.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/jpeg_decode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/jpeg_decode_grayscale.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/tjpgd.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/jpeg_decode.h
    ${CMAKE_CURRENT_SOURCE_DIR}/jpeg_decode_grayscale.h

  )

# target_include_directories(jpeg_decoder
#   PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR} 
#     ${PROJECT_INCLUDE_DIR}
#     ${PROJECT_INCLUDE_DIR}/std_image

#   )
