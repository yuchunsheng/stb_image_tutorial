
# add_library(std_image "")
# include(${CMAKE_CURRENT_LIST_DIR}/std_image_tutorial/CMakeLists.txt)

set(SOURCE_FILES main.cpp)

add_executable(main "")
target_sources(main PRIVATE ${SOURCE_FILES})
target_include_directories(main PUBLIC ${PROJECT_INCLUDE_DIR})
add_subdirectory(std_image_tutorial)

target_link_libraries(main std_image)
install(TARGETS main DESTINATION ${PROJECT_BIN_DIR})