set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})
# target_link_libraries(main division)
install(TARGETS main DESTINATION ${PROJECT_BIN_DIR})