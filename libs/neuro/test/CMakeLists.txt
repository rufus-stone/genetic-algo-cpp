message(STATUS "Configuring ${PROJECT_NAME}_tests...")

add_library(${PROJECT_NAME}_catch_main STATIC catch_main.cpp)

add_executable(${PROJECT_NAME}_tests tests.cpp)

target_compile_features(${PROJECT_NAME}_tests PRIVATE cxx_std_17)

# Link to the library
target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME}_catch_main
                                                    neuro::neuro)
